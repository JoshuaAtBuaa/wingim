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
#include "KeepAlivePacketStuff.h"
#include "OutPacket.h"
//
KeepAlivePacketStuff::KeepAlivePacketStuff()
{
	bodyBuf = new uint8[4];
	memset(bodyBuf, 0, 4);
}
//
KeepAlivePacketStuff::~KeepAlivePacketStuff()
{

}
//
OutPacket *KeepAlivePacketStuff::toOutPacket()
{
	OutPacket *outPacketPtr = new OutPacket(QQ_KEEP_ALIVE, true);
	outPacketPtr->putBody(bodyBuf, 4);
	SAFE_DELETE_ARRAY(bodyBuf);
	return outPacketPtr;
}
