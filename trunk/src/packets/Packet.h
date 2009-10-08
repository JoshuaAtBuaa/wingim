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

#ifndef PACKET_H
#define PACKET_H

#include "Wingdefines.h"

class Packet
{
public:

	Packet();

	Packet(uint8 *buf, int *len);

	Packet(const uint16 ver, const uint16 com, const uint16 seq);

	virtual ~ Packet();
	//设置QQ号码
	static void setQQNum(const uint32 num);
	//获取QQ号码
	static uint32 getQQNum();
	//
	static void setUDP(bool t);
	//
	static bool isUDP();
	//设置QQ版本
	void setQQVersion(const uint16 ver);
	//设置命令字
	void setCommand(const uint16 com);
	//设置包序列
	void setSequence(const uint16 seq);
	//获取QQ版本
	uint16 getQQVersion();
	//获取QQ命令字
	uint16 getCommand();
	//获取包序列
	uint16 getSequence();


protected:
	//版本
	uint16 version;
	//命令字
	uint16 command;
	//包序列
	uint16 sequence;
	//QQ号码
	static uint32 qqNum;
	//
	static bool mIsUDP;

};

/*! \class Packet
 *  \brief 所有包的基类。
 */

#endif // PACKET_H
