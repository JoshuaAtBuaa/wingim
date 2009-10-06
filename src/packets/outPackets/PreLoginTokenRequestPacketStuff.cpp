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

#include "PreLoginTokenRequestPacketStuff.h"
#include "OutPacket.h"

//
PreLoginTokenRequestPacketStuff::PreLoginTokenRequestPacketStuff()
{
	neckBuf = NULL;
	bodyBuf[0] = 0;
}
//
PreLoginTokenRequestPacketStuff::~PreLoginTokenRequestPacketStuff()
{

}
//
void PreLoginTokenRequestPacketStuff::fromInPacket(InPacket *inPacket)
{
	//暂时什么也不用干
}
//
void PreLoginTokenRequestPacketStuff::process()
{
	//暂时什么也不用干
}
//
OutPacket *PreLoginTokenRequestPacketStuff::toOutPacket()
{
	OutPacket *outPacketPtr = new OutPacket(QQ_REQUEST_PRE_LOGIN_TOKEN, true);
	outPacketPtr->putBody(bodyBuf, 1);
	return outPacketPtr;
}

