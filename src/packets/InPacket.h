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

#ifndef INPACKET_H
#define INPACKET_H
#include <string>
#include "Packet.h"
#include "Wingdefines.h"


class InPacket:public Packet
{
public:

	InPacket();

	InPacket(uint8 *buf, int len);

	virtual ~ InPacket();

	//取得主体长度
	int getBodyLen();

	//取得主体数据
	uint8 *getBody();
protected:
	//主体长度
	int32 bodyLen;
	//解压缓冲区
	uint8 *decryptedBuf;

private:
	//解压主体部分
	void decryptBody(uint8 *inStr, int inLen);

};

/*! \class InPacket
 *  \brief 所有接收包的基类。
 */

#endif // INPACKET_H
