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
#include "GetVerifyPngPacketStuff.h"
#include "InPacket.h"
#include "OutPacket.h"
#include "QQKeys.h"
#include "Wingdefines.h"
#include "ToolKit.h"

GetVerifyPngPacketStuff::GetVerifyPngPacketStuff()
{
	bodyBuf = NULL;
	tail = NULL;
	tailLen = 0;
	uint8 tempByte1_4[4] = {0x03, 0x00, 0x05, 0x00};
	memcpy(unknown1_4b, tempByte1_4, 4);
	uint8 tempByte2_4[4] = {0x00, 0x00, 0x00, 0x01};
	memcpy(unknown2_4b, tempByte2_4, 4);
}
//
GetVerifyPngPacketStuff::~GetVerifyPngPacketStuff()
{

}
//
void GetVerifyPngPacketStuff::fromInPacket(InPacket *inPacketPtr)
{
	//什么也不用做
}

void GetVerifyPngPacketStuff::putTail(uint8 *str, int len)
{
	tailLen = len;
	tail = new uint8[tailLen];
	memcpy(tail, str, tailLen);
}
//
void GetVerifyPngPacketStuff::process()
{
	bodyBuf = new uint8[35+tailLen];
	int pos = 0;
	bodyBuf[pos++] = QQKeys::preTokenLen;
	memcpy(bodyBuf+pos, QQKeys::preToken, QQKeys::preTokenLen);
	pos += QQKeys::preTokenLen;
	memcpy(bodyBuf+pos, unknown1_4b, 4);
	pos += 4;
	memcpy(bodyBuf+pos, unknown2_4b, 4);
	pos += 4;
	bodyBuf[pos++] = 0;
	bodyBuf[pos++] = tailLen;
	memcpy(bodyBuf+pos, tail, tailLen);
}
//
OutPacket *GetVerifyPngPacketStuff::toOutPacket()
{
	OutPacket *outPacketPtr = new OutPacket(QQ_REQUEST_LOGIN_TOKEN, true);
	outPacketPtr->putBody(bodyBuf, 35+QQKeys::loginTokenLen);
	SAFE_DELETE_ARRAY(bodyBuf);
	SAFE_DELETE_ARRAY(tail);
	return outPacketPtr;
}
