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
#include "BuddyInfo.h"
#include "ToolKit.h"
#include "Wingdefines.h"
#include "WingDebug.h"


BuddyInfo::BuddyInfo()
	:qqNum(0),head(0),age(0),gender(0),
	nick(NULL),status(20),signature()
{

}

BuddyInfo::~BuddyInfo()
{
	SAFE_DELETE_ARRAY(nick);
}

void BuddyInfo::putData(uint8 *buf, int *dataLen)
{
	//打印调试信息
	DWHERE();

	int pos = 0;
	//好友QQ号
	ToolKit::readBufDW(buf, qqNum);
	pos += 4;
	//头像
	ToolKit::readBufW(buf+pos, head);
	pos += 2;
	//年龄
	age = buf[pos++];
	//性别
	gender = buf[pos++];
	//昵称长度
	nickLen = buf[pos++];
	//昵称
	nick = new uint8[nickLen+1];
	memcpy(nick, buf+pos, nickLen);
	nick[nickLen] = '\0';
	pos += nickLen;
	//用户属性
	ToolKit::readBufDW(buf+pos, userFlag);
	pos += 4;
	//跳过未知4字节
	pos += 4;

	*dataLen = pos;
}
