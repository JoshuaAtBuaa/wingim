/*
 ***************************************************************************
 *           Copyright © 2009 by konglinglong                              *
 *           konglinglong@gmail.com                                        *
 *           我的主页:https://sites.google.com/site/konglinglong/           *
 ***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************
 */

#include <cstring>
#include "ReceiveIMPacket.h"
#include "InPacket.h"
#include "ToolKit.h"
#include "WingDebug.h"
#include "Wingdefines.h"


IMHeader::IMHeader()
	:sender(0),reveiver(0),serverSequence(0),senderIP(0),senderPort(0),msgSource(0)
{

}

IMHeader::~IMHeader()
{

}

void IMHeader::fromInPacket(InPacket *inPacket)
{
	uint8 *bodyPtr = inPacket->getBody();
	int32 pos = 0;
	//
	ToolKit::readBufDW(bodyPtr, sender);
	pos += 4;
	//
	ToolKit::readBufDW(bodyPtr+pos, reveiver);
	pos += 4;
	//
	ToolKit::readBufDW(bodyPtr+pos, serverSequence);
	pos += 4;
	//
	ToolKit::readBufDW(bodyPtr+pos, senderIP);
	pos += 4;
	//
	ToolKit::readBufW(bodyPtr+pos, senderPort);
	pos += 2;
	//
	ToolKit::readBufW(bodyPtr+pos, msgSource);
}

NormalIMHeader::NormalIMHeader()
{

}

NormalIMHeader::~NormalIMHeader()
{

}

void NormalIMHeader::fromInPacket(InPacket *inPacket)
{
	uint8 *bodyPtr = inPacket->getBody();
	int32 pos = 20;
	//
	ToolKit::readBufW(bodyPtr+pos, senderVersion);
	pos += 2;
	//
	ToolKit::readBufDW(bodyPtr+pos, sender);
	pos += 4;
	//
	ToolKit::readBufDW(bodyPtr+pos, receiver);
	pos += 4;
	//
	memcpy(fileSessionKey, bodyPtr+pos, QQ_KEY_LENGTH);
	pos += QQ_KEY_LENGTH;
	//
	ToolKit::readBufW(bodyPtr+pos, msgType);
	pos += 2;
	//
	ToolKit::readBufW(bodyPtr+pos, imSequence);
	pos += 2;
	//
	ToolKit::readBufDW(bodyPtr+pos, sendTime);
	pos += 4;
	//
	ToolKit::readBufW(bodyPtr+pos, senderFace);
}

NormalIM::NormalIM()
{

}

NormalIM::~NormalIM()
{
	SAFE_DELETE_ARRAY(msgBuf);
}

void NormalIM::fromInPacket(InPacket *inPacket)
{
	uint8 *bodyPtr = inPacket->getBody();
	int32 pos = 56;

	//字体属性
	ToolKit::readBufDW(bodyPtr+pos, fontType);
	pos += 4;
	//消息的分片数
	msgSubNum = bodyPtr[pos++];
	//分片序号
	msgSubSeq = bodyPtr[pos++];
	//消息id
	ToolKit::readBufW(bodyPtr+pos, msgID);
	pos += 2;
	//消息类型，是否自动回复
	replyType = bodyPtr[pos++];
	//未知8字节
	pos += 8;
	//消息正文
	for(msgLen = 0; bodyPtr[pos+msgLen] != 0; msgLen++)
		;
	msgBuf = new uint8[msgLen+1];	//多一个 '\0'
	memcpy(msgBuf, bodyPtr+pos, msgLen);
	msgBuf[msgLen] = '\0';

	//后面还字体属性，现在暂不处理
}

SysMessage::SysMessage()
{

}

SysMessage::~SysMessage()
{
	SAFE_DELETE_ARRAY(msgBuf);
}

void SysMessage::fromInPacket(InPacket *inPacket)
{
	int32 pos = 20;
	uint8 *bodyPtr = inPacket->getBody();
	sysMsgType = bodyPtr[pos++];
	msgLen = bodyPtr[pos++];
	msgBuf = new uint8[msgLen+1];
	memcpy(msgBuf, bodyPtr+pos, msgLen);
	msgBuf[msgLen] = '\0';
	//pos += msgLen;
}

ReceiveIMPacket::ReceiveIMPacket()
	:imKind(CANNOT_PARSE),imHeader(NULL),normalHeader(NULL),
	normalIM(NULL),sysMessage(NULL)
{

}

ReceiveIMPacket::~ReceiveIMPacket()
{
	SAFE_DELETE(imHeader);
	SAFE_DELETE(normalHeader);
	SAFE_DELETE(normalIM);
	SAFE_DELETE(sysMessage);
}

void ReceiveIMPacket::fromInPacket(InPacket *inPacket)
{
	imHeader = new IMHeader();
	imHeader->fromInPacket(inPacket);

	switch(imHeader->msgSource)
	{
			//是从好友或者陌生人处发来的消息
		case QQ_RECV_IM_FROM_BUDDY:
		case QQ_RECV_IM_FROM_STRANGER:
			processNormalIM(inPacket);
			break;
		case QQ_RECV_IM_SYS_MESSAGE:
			processSystemMessage(inPacket);
			break;
		default:
			processUnknownIMPacket(inPacket);
	}
}

void ReceiveIMPacket::processNormalIM(InPacket *inPacket)
{
	normalHeader = new NormalIMHeader();
	normalHeader->fromInPacket(inPacket);

	switch(normalHeader->msgType)
	{
			//普通文本消息
		case QQ_IM_NORMAL_TEXT:
			normalIM = new NormalIM();
			normalIM->fromInPacket(inPacket);
			imKind = QQ_IM_FROM_USER;
			break;
		default:
			processUnknownIMPacket(inPacket);
	}
}

void ReceiveIMPacket::processSystemMessage(InPacket *inPacket)
{
	sysMessage = new SysMessage();
	sysMessage->fromInPacket(inPacket);
	imKind = QQ_IM_FROM_SYS;
}

void ReceiveIMPacket::processUnknownIMPacket(InPacket *inPacket)
{
	//打印调试信息
	DWHERE();
	DPRINT("- - - > there is one IMPacket not be processed!");
}
