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

#include <string>
#include "Signature.h"
#include "ToolKit.h"
#include "WingDebug.h"



Signature::Signature()
: qqNum(0),modifiedTime(0),signature()
{

}

Signature::Signature(uint32 qq, uint32 mt, std::string sig)
	: qqNum(qq),modifiedTime(mt),signature(sig)
{

}

void Signature::putData(uint8 *buf, int32 *dataLen)
{
	//打印调试信息
	DWHERE();

	int pos = 0;
	//QQ号
	ToolKit::readBufDW(buf, qqNum);
	pos += 4;
	//上次签名修改时间
	ToolKit::readBufDW(buf+pos, modifiedTime);
	pos += 4;
	//签名长度
	char sigLen = buf[pos++];
	//签名
	signature.assign((char *)(buf+pos), sigLen);
	pos += sigLen;

	*dataLen = pos;
}

Signature::~Signature()
{

}
