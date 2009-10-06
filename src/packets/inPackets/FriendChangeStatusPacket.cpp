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
#include "FriendChangeStatusPacket.h"
#include "InPacket.h"
#include "QQKeys.h"
#include "Wingdefines.h"
#include "ToolKit.h"
//
FriendChangeStatusPacket::FriendChangeStatusPacket()
{
	sender = 0;
	status = 0;
}
//
FriendChangeStatusPacket::~FriendChangeStatusPacket()
{

}
//
void FriendChangeStatusPacket::fromInPacket(InPacket *inPacketPtr)
{
	uint8 *bodyPtr = inPacketPtr->getBody();
	uint32 pos = 0;
	ToolKit::readBufDW(bodyPtr, sender);
	pos += 4;
	pos += 8;
	status = bodyPtr[pos++];
}
//
uint32 FriendChangeStatusPacket::getSender()
{
	return sender;
}
//
uint8 FriendChangeStatusPacket::getNewStatus()
{
	return status;
}
