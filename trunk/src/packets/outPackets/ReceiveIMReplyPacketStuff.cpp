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
#include "ReceiveIMReplyPacketStuff.h"
#include "InPacket.h"
#include "OutPacket.h"
#include "QQKeys.h"
#include "Wingdefines.h"
#include "ToolKit.h"

//
ReceiveIMReplyPacketStuff::ReceiveIMReplyPacketStuff()
{
	sequence = 0;
	memset(replyKey, 0, 16);
	bodyBuf = NULL;
}
//
ReceiveIMReplyPacketStuff::~ReceiveIMReplyPacketStuff()
{

}
//
void ReceiveIMReplyPacketStuff::fromInPacket(InPacket *inPacketPtr)
{
	if(NULL != inPacketPtr)
	{
		sequence = inPacketPtr->getSequence();
		uint8 *bodyPtr = inPacketPtr->getBody();
		memcpy(replyKey, bodyPtr, 16);
	}
}
//
void ReceiveIMReplyPacketStuff::process()
{
	bodyBuf = new uint8[16];
	memcpy(bodyBuf, replyKey, 16);
}
//
OutPacket *ReceiveIMReplyPacketStuff::toOutPacket()
{
	OutPacket *outPacketPtr = new OutPacket(QQ_RECV_IM, false);
	outPacketPtr->setSequence(sequence);
	outPacketPtr->putBody(bodyBuf, 16);
	SAFE_DELETE_ARRAY(bodyBuf);
	return outPacketPtr;
}
