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

#ifndef LOGINTOKENREQUESTPACKETSTUFF_H_
#define LOGINTOKENREQUESTPACKETSTUFF_H_

#include "Wingdefines.h"

class InPacket;
class OutPacket;
class LoginTokenRequestPacketStuff
{
public:
	//
	LoginTokenRequestPacketStuff();
	//
	~LoginTokenRequestPacketStuff();
	//
	void fromInPacket(InPacket *inPacketPtr);
	//
	void process();
	//
	OutPacket *toOutPacket();
private:
	uint8 unknown1_5b[5];	//03 00 05 00 00
	uint8 unknown2_5b[5];	//00 00 00 00 00
	uint8 *neckBuf;
	uint8 *bodyBuf;
};

/*! \class LoginTokenRequestPacketStuff
 *  \brief 登陆令箭请求包。
 */

#endif /* LOGINTOKENREQUESTPACKETSTUFF_H_ */
