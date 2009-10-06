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
#include "PreSessionKeyRequestPacketStuff.h"
#include "InPacket.h"
#include "OutPacket.h"
#include "QQKeys.h"
#include "Wingdefines.h"
#include "ToolKit.h"

//
PreSessionKeyRequestPacketStuff::PreSessionKeyRequestPacketStuff()
{
	neckBuf = NULL;
	bodyBuf = NULL;
	LoginToken = QQKeys::loginToken;
	LTLen = QQKeys::loginTokenLen;
	passwdRandKey = QQKeys::passwdRandomKey;
	passwdRandKeyLen = QQKeys::passwdRKLen;
	uint8 tempByte1_8b[8] = {0x00,0x5F,0x00,0x00,0x08,0x04,0x01,0xE0};
	memcpy(unknown1_8b, tempByte1_8b, 8);
	uint8 tempByte2_20b[20] = {0xFA,0x24,0x84,0x58,0x58,0x17,0xD0,0xA1,0x5F,0x92,0x75,0xF9,0x68,0xD5,0x3F,0x14,0x87,0x6A,0x46,0x9C};
	memcpy(unknown2_20b, tempByte2_20b, 20);
	memset(padding, 0, 0x64);
}
//
PreSessionKeyRequestPacketStuff::~PreSessionKeyRequestPacketStuff()
{

}
//
void PreSessionKeyRequestPacketStuff::fromInPacket(InPacket *inPacketPtr)
{

}
//
void PreSessionKeyRequestPacketStuff::process()
{
	neckBuf = QQKeys::randomKey;

	bodyBuf = new uint8[199];
	int pos = 0;
	memcpy(bodyBuf, unknown1_8b, 8);
	pos += 8;
	bodyBuf[pos++] = LTLen;
	memcpy(bodyBuf+pos, LoginToken, LTLen);
	pos += LTLen;
	bodyBuf[pos++] = 0;
	bodyBuf[pos++] = passwdRandKeyLen;
	memcpy(bodyBuf+pos, passwdRandKey, passwdRandKeyLen);
	pos += passwdRandKeyLen;
	bodyBuf[pos++] = 0;
	bodyBuf[pos++] = 20;
	memcpy(bodyBuf+pos, unknown2_20b, 20);
	pos += 20;
	bodyBuf[pos++] = 0;
	bodyBuf[pos++] = 0x64;
	memset(bodyBuf+pos, 0, 0x64);
}
//
OutPacket *PreSessionKeyRequestPacketStuff::toOutPacket()
{
	OutPacket *outPacketPtr = new OutPacket(QQ_REQUEST_PRE_SESSION_KEY, true);
	outPacketPtr->putNeck(neckBuf, QQ_KEY_LENGTH);
	outPacketPtr->putBody(bodyBuf, 199);
	SAFE_DELETE_ARRAY(bodyBuf);
	return outPacketPtr;
}
