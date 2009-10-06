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

#ifndef RECEIVEIMPACKET_H_
#define RECEIVEIMPACKET_H_

#include "Wingdefines.h"

class InPacket;
class IMHeader
{
public:
	//
	IMHeader();
	//
	~IMHeader();
	//
	void fromInPacket(InPacket *inPacket);

public:
	/*
	 * 共20字节
	 */

	uint32 sender;			//发送者QQ号
	uint32 reveiver;		//接收者QQ号
	uint32 serverSequence;	//服务器端产生的包序号
	uint32 senderIP;		//发送者ip
	uint16 senderPort;		//发送者端口
	uint16 msgSource;		//消息来源, 是好友发的，还是陌生人发的，还是系统消息等等
};

class NormalIMHeader
{
public:
	NormalIMHeader();
	~NormalIMHeader();
	void fromInPacket(InPacket *inPacket);

public:

	/*
	 * 共36字节
	 */

	uint16 senderVersion;	//发送者的QQ版本
	uint32 sender;			//发送者QQ号
	uint32 receiver;		//接收者QQ号
	uint8  fileSessionKey[QQ_KEY_LENGTH];	// md5处理的发送方的uid和session key，用来在传送文件时加密一些消息
	uint16 msgType;			//普通消息类型，是文本消息还是其他什么消息
	uint16 imSequence;		//消息序号
	uint32 sendTime;		//发送时间
	uint16 senderFace;		//发送者头像
};

class NormalIM
{
public:
	//
	NormalIM();
	//
	~NormalIM();
	//
	void fromInPacket(InPacket *inPacket);

public:

	uint32 fontType;		// 是否有字体属性，4字节，有一般是0x00000001
	uint16 msgID;			// 消息id，2字节，同一条消息的不同分片id相同
	uint8 msgSubNum;		// 消息的分片数，1字节
	uint8 msgSubSeq;		// 分片序号，1字节，从0开始
	uint8 replyType;		// 消息类型，这里的类型表示是正常回复还是自动回复之类的信息， 1字节
	uint8 *msgBuf;			// 消息正文
	int32 msgLen;			//消息长度

};

class SysMessage
{
public:
	SysMessage();
	~SysMessage();
	//
	void fromInPacket(InPacket *inPacket);

public:
	uint8 sysMsgType;		//消息类型
	uint8 msgLen;			//消息长度
	uint8 *msgBuf;			//消息正文

};

class ReceiveIMPacket
{
public:
	ReceiveIMPacket();
	~ReceiveIMPacket();
	//
	void fromInPacket(InPacket *inPacket);

public:
	enum IM_KIND{
		CANNOT_PARSE,				//不能解释的消息
		QQ_IM_FROM_USER,			//来自好友
		QQ_IM_FROM_SYS,				//来自系统
		QQ_IM_FROM_TEMP_SESSION,	//来自临时会话
		QQ_IM_FROM_CLUSTER,			//来自群
		QQ_IM_FROM_SMS				//来自短消息
	};
	enum IM_KIND imKind;

	//整个包的头
	IMHeader *imHeader;
	//仅用于普通消息时
	NormalIMHeader *normalHeader;
	NormalIM *normalIM;
	//仅用于系统消息
	SysMessage *sysMessage;

private:
	void processNormalIM(InPacket *inPacket);
	void processSystemMessage(InPacket *inPacket);
	void processUnknownIMPacket(InPacket *inPacket);
};

/*! \class ReceiveIMPacket
 *  \brief 收到消息包。
 */

#endif /* RECEIVEIMPACKET_H_ */
