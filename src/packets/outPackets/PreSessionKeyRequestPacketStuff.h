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

#ifndef PRESESSIONKEYREQUESTPACKETSTUFF_H_
#define PRESESSIONKEYREQUESTPACKETSTUFF_H_

#include "Wingdefines.h"

class InPacket;
class OutPacket;
class PreSessionKeyRequestPacketStuff
{
public:
	//
	PreSessionKeyRequestPacketStuff();
	//
	~PreSessionKeyRequestPacketStuff();
	//
	void fromInPacket(InPacket *inPacketPtr);
	//
	void process();
	//
	OutPacket *toOutPacket();
private:
	uint8 *LoginToken;
	uint8 LTLen;
	uint8 *passwdRandKey;
	uint8 passwdRandKeyLen;
	uint8 unknown1_8b[8];	//0x00,0x5F,0x00,0x00,0x08,0x04,0x01,0xE0
	uint8 unknown2_20b[20];	//
	uint8 padding[0x64];
	uint8 *neckBuf;
	uint8 *bodyBuf;
};

/*! \class PreSessionKeyRequestPacketStuff
 *  \brief 预会话密钥请求包。
 */

#endif /* PRESESSIONKEYREQUESTPACKETSTUFF_H_ */
