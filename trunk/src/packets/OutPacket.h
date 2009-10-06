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

#ifndef OUTPACKET_H
#define OUTPACKET_H

#include "Packet.h"
#include "Wingdefines.h"
#include <string>

class OutPacket : public Packet
{
public:

	OutPacket();
	//
	OutPacket(const short command, const bool ack);

	virtual ~OutPacket();
	//是否需要应答
	bool ifNeedAck() const;
	//
	void setNeedAck(bool ack);
	//是否需要重发
	bool ifNeedResend();
	//每个包在发送前，调用这个函数来把包转换成字符序列
	void toByteArrary(uint8 * outStr, int * outStrLen);
	//返回脖子长度
	int32 getNeckLength();
	//返回脖子的指针
	uint8 *getNeck();
	//返回身体的指针
	uint8 *getBody();
	//返回身体长度
	int32 getBodyLen();
	//添加脖子部分
	void putNeck(uint8 * inStr, int len);
	//添加身体部分
	void putBody(uint8 * inStr, int len);
	//
	void clone(OutPacket *outPacketPtr);
	//
	static int16 getOutPacketSequence();
protected:
	//发送包序列号
	static int16 OutPacketSequence;
	//是否需要应答
	bool needAck;
	//重发次数计数器
	int32 resendCount;
	//脖子部分
	uint8 * neck;

	/*
	 * 说明：
	 * 之所以分为脖子部分和身体部分,
	 * 因为脖子部分不需要加密，
	 * 而身体部分需要加密（大多时候脖子部分是空的）
	 */

	//包头长度
	int32 headLen;
	//脖子长度
	int32 neckLen;
	//主体部分
	uint8 * body;
	//主体长度
	int32 bodyLen;

private:

	//复制头部到将要发送的字节序列上
	void copyHead (uint8 * outStr );

	//复制脖子部到将要发送的字节序列上
	void copyNeck (uint8 * outStr );

	//加密主体部份，并复制到将要发送的字节序列上
	void encryptAndCopyBody (uint8 * outBody, int32 * outLen );

};

/*! \class OutPacket
 *  \brief 所有发送包的基类。
 */

#endif // OutPacket_H
