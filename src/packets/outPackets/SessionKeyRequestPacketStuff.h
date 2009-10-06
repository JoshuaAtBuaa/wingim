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

#ifndef SESSIONKEYREQUESTPACKETSTUFF_H_
#define SESSIONKEYREQUESTPACKETSTUFF_H_

#include "Wingdefines.h"

class InPacket;
class OutPacket;
class SessionKeyRequestPacketStuff
{
public:
	//
	SessionKeyRequestPacketStuff();
	//
	~SessionKeyRequestPacketStuff();
	//
	void fromInPacket(InPacket *inPacketPtr);
	//
	void putStatus(uint8 sta);
	//
	void process();
	//
	OutPacket *toOutPacket();
private:
	uint8 *tempTK;
	uint16 tempTKLen;
	static uint8 QQ_Hash[16];
	//uint8 unknown1_17b[17];
	uint8 status;
	static uint8 unknown2_16b[16];
	static uint8 unknown3_12b[12];
	static uint8 macRelative1_5b[5];
	static uint8 unknown4_16b[16];
	static uint8 macRelative2_5b[5];
	static uint8 macRelative3_16b[16];
	uint8 *neckBuf;
	uint8 *bodyBuf;
	//
	int8 numProcess;
};

/*! \class SessionKeyRequestPacketStuff
 *  \brief 会话密钥请求包。
 */

#endif /* SESSIONKEYREQUESTPACKETSTUFF_H_ */
