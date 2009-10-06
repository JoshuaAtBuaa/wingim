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
#include <time.h>
#include "SendIMPacketStuff.h"
#include "OutPacket.h"
#include "QQKeys.h"
#include "Wingdefines.h"
#include "ToolKit.h"

//
SendIMPacketStuff::SendIMPacketStuff()
{
	IMHeaderLen = 53;
	fontAttrLen = 13;
	receiver = 0;
	msgType = 0;
	msgID = 0;
	msgFragmentNum = 0;
	msgfragmentSeq = 0;
	replyType = 0;
	msgBuf = NULL;
	msgLen = 0;
	bodyBuf = NULL;
}
//
SendIMPacketStuff::~SendIMPacketStuff()
{

}
//
void SendIMPacketStuff::setSender(uint32 send)
{
	sender = send;
}
//
void SendIMPacketStuff::setReceiver(uint32 rece)
{
	receiver = rece;
}
//
void SendIMPacketStuff::putMsg(uint8 *msg, int32 len)
{
	msgLen = len + 2;	//末尾添加2个空格
	msgBuf = new uint8[msgLen];
	memcpy(msgBuf, msg, len);
	msgBuf[len] = 0x20;
	msgBuf[len+1] = 0x20;
}
//
void SendIMPacketStuff::process()
{
	bodyBuf = new uint8[IMHeaderLen+fontAttrLen+msgLen];
	int32 pos = 0;
	//发送者QQ号
	ToolKit::writeBufDW(bodyBuf+pos, sender);
	pos += 4;
	//接收者QQ号
	ToolKit::writeBufDW(bodyBuf+pos, receiver);
	pos += 4;
	//发送者QQ版本
	ToolKit::writeBufW(bodyBuf+pos, QQ_DEFAULT_VERSION);
	pos += 2;
	//发送者QQ号
	ToolKit::writeBufDW(bodyBuf+pos, sender);
	pos += 4;
	//收者的QQ号
	ToolKit::writeBufDW(bodyBuf+pos, receiver);
	pos += 4;
	//文件会话密钥
	memcpy(bodyBuf+pos, QQKeys::fileSessionKey, QQ_KEY_LENGTH);
	pos += QQ_KEY_LENGTH;
	//消息类型
	msgType = QQ_IM_NORMAL_TEXT;
	ToolKit::writeBufW(bodyBuf+pos, msgType);
	pos += 2;
	//会话ID
	ToolKit::writeBufW(bodyBuf+pos, OutPacket::getOutPacketSequence());
	pos += 2;
	//发送时间
	time_t sendTime = time(NULL);
	ToolKit::writeBufDW(bodyBuf+pos, sendTime);
	pos += 4;
	//QQ头像
	memset(bodyBuf+pos, 0 ,2);
	pos += 2;
	//字体信息
	memset(bodyBuf+pos, 0 , 4);
	pos += 4;
	//消息分片数
	bodyBuf[pos++] = 1;
	//分片序号
	bodyBuf[pos++] = 0;
	//消息ID
	memset(bodyBuf+pos, 0, 2);
	pos += 2;
	//是发送还是自动回复
	bodyBuf[pos++] = 1;
	//信息体
	memcpy(bodyBuf+pos, msgBuf, msgLen);
	pos += msgLen;
	SAFE_DELETE_ARRAY(msgBuf);
	//
	bodyBuf[pos++] = 0;
	//字体属性
	bodyBuf[pos++] = 0x09;
	//字体颜色
	memset(bodyBuf+pos, 0, 4);
	pos += 4;
	//
	uint8 font[7] = {0x86,0x02,0xcb,0xce,0xcc,0xe5,0x0d};
	memcpy(bodyBuf+pos, font, 7);
}
//
OutPacket *SendIMPacketStuff::toOutPacket()
{
	OutPacket *outPacketPtr = new OutPacket(QQ_SEND_IM, true);
	outPacketPtr->putBody(bodyBuf, IMHeaderLen+fontAttrLen+msgLen);
	SAFE_DELETE_ARRAY(bodyBuf);
	return outPacketPtr;
}
