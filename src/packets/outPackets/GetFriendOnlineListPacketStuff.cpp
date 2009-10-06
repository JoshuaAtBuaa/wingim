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
#include "GetFriendOnlineListPacketStuff.h"
#include "InPacket.h"
#include "OutPacket.h"
#include "QQKeys.h"
#include "Wingdefines.h"
#include "ToolKit.h"
//
GetFriendOnlineListPacketStuff::GetFriendOnlineListPacketStuff()
{
	offset = 0;
	bodyBuf = NULL;
}
//
GetFriendOnlineListPacketStuff::~GetFriendOnlineListPacketStuff()
{

}
//
void GetFriendOnlineListPacketStuff::fromInPacket(InPacket *inPacketPtr)
{
 if(NULL == inPacketPtr)
 {
	offset = 0;
 }
 else
 {
	 uint8 *bodyPtr = inPacketPtr->getBody();
	 offset = bodyPtr[0];
 }
}
//
void GetFriendOnlineListPacketStuff::process()
{
	bodyBuf = new uint8[5];
	int pos = 0;
	bodyBuf[pos++] = 0x02;
	bodyBuf[pos++] = offset;
	memset(bodyBuf+pos, 0, 3);
}
//
OutPacket *GetFriendOnlineListPacketStuff::toOutPacket()
{
	OutPacket *outPacketPtr = new OutPacket(QQ_GET_FRIEND_ONLINE, true);
	outPacketPtr->putBody(bodyBuf, 5);
	SAFE_DELETE_ARRAY(bodyBuf);
	return outPacketPtr;
}
