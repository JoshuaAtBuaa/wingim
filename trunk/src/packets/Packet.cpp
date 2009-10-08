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
#include "ToolKit.h"
#include "Packet.h"


uint32 Packet::qqNum = 19401127;
bool Packet::mIsUDP = true;
Packet::Packet()
	:version(0),command(0),sequence(0)
{

}

Packet::Packet(uint8 *buf, int *len)
{
	int pos;

	if(mIsUDP)
		pos = 1;
	else
		pos = 3;

	ToolKit::readBufW(buf+pos, version);
	pos += 2;

	ToolKit::readBufW(buf+pos, command);
	pos += 2;

	ToolKit::readBufW(buf+pos, sequence);
	pos += 2;

	(*len) = (*len)-pos;
	memcpy(buf, buf+pos, *len);
}

Packet::Packet(const uint16 ver, const uint16 com, const uint16 seq)
	:version(ver),command(com),sequence(seq)
{

}

Packet::~Packet()
{
}

//设置QQ号码 静态函数
void Packet::setQQNum(const uint32 num)
{
	qqNum = num;
}
//
void Packet::setUDP(bool t)
{
	mIsUDP = t;
}
//
bool Packet::isUDP()
{
	return mIsUDP;
}
//设置QQ版本
void Packet::setQQVersion(const uint16 ver)
{
	version = ver;
}

//设置命令字
void Packet::setCommand(const uint16 com)
{
	command = com;
}

//设置包序列
void Packet::setSequence(const uint16 seq)
{
	sequence = seq;
}

//获取QQ版本
uint16 Packet::getQQVersion()
{
	return version;
}

//获取QQ命令字
uint16 Packet::getCommand()
{
	return command;
}

//获取包序列
uint16 Packet::getSequence()
{
	return sequence;
}

//获取QQ号码 静态函数
uint32 Packet::getQQNum()
{
	return qqNum;
}
