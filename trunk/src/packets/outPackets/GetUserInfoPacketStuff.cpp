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
#include "GetUserInfoPacketStuff.h"
#include "OutPacket.h"
#include "Wingdefines.h"
//
GetUserInfoPacketStuff::GetUserInfoPacketStuff()
{
	qqNum = 0;
	bodyLen = 0;
	bodyBuf = NULL;
}
//
GetUserInfoPacketStuff::~GetUserInfoPacketStuff()
{

}
//
void GetUserInfoPacketStuff::putUserQQ(uint32 qq)
{
	qqNum = qq;
}
void GetUserInfoPacketStuff::process()
{
	uint8 tempBuf[15];
	memset(tempBuf, 0, 15);
	sprintf((char *)tempBuf, "%d", (int)qqNum);
	bodyLen = strlen((char *)tempBuf);
	bodyBuf = new uint8[bodyLen];
	memcpy(bodyBuf, tempBuf, bodyLen);
}
//
OutPacket *GetUserInfoPacketStuff::toOutPacket()
{
	OutPacket *outPacketPtr = new OutPacket(QQ_GET_USER_INFO, true);
	outPacketPtr->putBody(bodyBuf, bodyLen);
	SAFE_DELETE_ARRAY(bodyBuf);
	return outPacketPtr;
}
