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

#ifdef _WIN32
#include <winsock.h>
#else
#include <netinet/in.h>
#endif

#include "WingDebug.h"
#include <QtCore>
#include "OutPacket.h"
#include "Wingdefines.h"
#include "QQKeys.h"
#include "ToolKit.h"


//发送包的序列号
short OutPacket::OutPacketSequence = 1005;

OutPacket::OutPacket()
		:needAck(false),resendCount(0),neck(NULL),neckLen(0),body(NULL),bodyLen(0)
{

}


OutPacket::OutPacket(const short command, const bool ack)
		:Packet(QQ_DEFAULT_VERSION, command, ((OutPacketSequence++)%0xffff)),
		needAck(ack),resendCount(5),neck(NULL),neckLen(0),body(NULL),bodyLen(0)
{

}

OutPacket::~OutPacket ( )
{
	SAFE_DELETE_ARRAY(neck);

	SAFE_DELETE_ARRAY(body);
}

//是否需要应答
bool OutPacket::ifNeedAck() const
{
	return needAck;
}

void OutPacket::setNeedAck(bool ack)
{
	needAck = ack;
}

//是否需要重发
bool OutPacket::ifNeedResend()
{
	//
	if(resendCount-- > 0)
		return true;
	else
		return false;
}

//每个包在发送前，调用这个函数来把包转换成字符序列
void OutPacket::toByteArrary(uint8 *outStr, int *outStrLen)
{

	if(isUDP())
		*outStrLen = 0;
	else
		*outStrLen = 2;

	//头部
	copyHead(outStr + *outStrLen);
	*outStrLen += headLen;

	//脖子部分
	if(neckLen != 0)
	{
		copyNeck(outStr + *outStrLen);
		*outStrLen += neckLen;
	}

	//身体部分
	int32 bodyLenEncrypted;
	encryptAndCopyBody(outStr + *outStrLen, &bodyLenEncrypted);
	*outStrLen += bodyLenEncrypted;

	//QQ包尾标志
	outStr[*outStrLen] = (uint8) QQ_TAIL_TAG;
	*outStrLen += 1;

	if(!isUDP())
	{
		short tmp = htons(*outStrLen);
		memcpy(outStr, &tmp, 2);
	}
}

//返回脖子长度
int32 OutPacket::getNeckLength()
{
	return neckLen;
}

//返回身体长度
int32 OutPacket::getBodyLen()
{
	return bodyLen;
}

//返回脖子的指针
uint8 *OutPacket::getNeck()
{
	return neck;
}

//返回身体的指针
uint8 *OutPacket::getBody()
{
	return body;
}

//
int16 OutPacket::getOutPacketSequence()
{
	return ++OutPacketSequence;
}

//添加脖子部分
void OutPacket::putNeck(uint8 * inStr, int len)
{
	if(0==len)
	{
		neck = NULL;
		neckLen = 0;
	}
	else
	{
		neck = new uint8[len];
		memcpy(neck, inStr, len);
		neckLen = len;
	}
}

//添加身体部分
void OutPacket::putBody(uint8 * inStr, int len)
{
	if(0==len)
	{
		body = NULL;
		bodyLen = 0;
	}
	else
	{
		body = new uint8[len];
		memcpy(body, inStr, len);
		bodyLen  = len;
	}
}

//复制头部到将要发送的字节序列上
void OutPacket::copyHead(uint8 * outStr)
{
	headLen = 0;

	//QQ包头标志
	outStr[headLen++] = (uint8) QQ_HEAD_TAG;

	short tmp = htons(version);
	memcpy(outStr + headLen, &tmp, 2);
	headLen += 2;

	tmp = htons(command);
	memcpy(outStr + headLen, &tmp, 2);
	headLen += 2;

	tmp = htons(sequence);
	memcpy(outStr + headLen, &tmp, 2);
	headLen += 2;

	unsigned int qq = htonl(Packet::getQQNum());
	memcpy(outStr + headLen, &qq, 4);
	headLen += 4;

}

//复制脖子部到将要发送的字节序列上
void OutPacket::copyNeck(uint8 * outStr)
{
	memcpy(outStr, neck, neckLen);
}

//加密主体部份，并复制到将要发送的字节序列上
void OutPacket::encryptAndCopyBody(uint8 *outBody, int32 *outLen)
{
	uint8 *key = NULL;
	switch(command)
	{
		case QQ_TOUCH_REQUEST:
		case QQ_REQUEST_PRE_LOGIN_TOKEN:
		case QQ_REQUEST_LOGIN_TOKEN:
		case QQ_REQUEST_PRE_SESSION_KEY:
			key = QQKeys::randomKey;
			//加密身体部分
			ToolKit::WingEncrypt(body, bodyLen, key, outBody, outLen);
			break;
		case QQ_REQUEST_SESSION_KEY:
			if((key = QQKeys::tempKey) == NULL)
			{
				//打印调试信息
				DWHERE();
				DPRINT("- - - > QQKeys::tempKey has not be init, but someone want to use to encrypt!");
			}
			else
				//加密身体部分
				ToolKit::WingEncrypt(body, bodyLen, key, outBody, outLen);
			break;
		//取得会话密钥以后，都使用这条密钥加解密
		default:
			if((key = QQKeys::sessionKey) == NULL)
			{
				//打印调试信息
				DWHERE();
				DPRINT("- - - > QQKeys::sessionKey has not be init, but someone want to use to encrypt!");
			}
			else
				//加密身体部分
				ToolKit::WingEncrypt(body, bodyLen, key, outBody, outLen);
			break;
	}


}

void OutPacket::clone(OutPacket *outPacketPtr)
{
	outPacketPtr->version = this->version;
	outPacketPtr->command = this->command;
	outPacketPtr->sequence = this->sequence;
	outPacketPtr->needAck = needAck;
	outPacketPtr->resendCount = this->resendCount;

	if((outPacketPtr->neckLen = neckLen))
	{
		outPacketPtr->neck = new uint8[neckLen];
		memcpy(outPacketPtr->getNeck(), neck, neckLen);
	}
	else
	{
		outPacketPtr->neck = NULL;
		outPacketPtr->neckLen = 0;
	}
	if((outPacketPtr->bodyLen = bodyLen))
	{
		outPacketPtr->body = new uint8[bodyLen];
		memcpy(outPacketPtr->getBody(), body, bodyLen);
	}
	else
	{
		outPacketPtr->body = NULL;
		outPacketPtr->bodyLen = 0;
	}
}
