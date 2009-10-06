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
#include "SessionKeyRequestPacketStuff.h"
#include "InPacket.h"
#include "OutPacket.h"
#include "QQKeys.h"
#include "Wingdefines.h"
#include "ToolKit.h"

uint8 SessionKeyRequestPacketStuff::QQ_Hash[16] =
		{0x56,0x4e,0xc8,0xfb,0x0a,0x4f,0xef,0xb3,
		 0x7a,0x5d,0xd8,0x86,0x0f,0xac,0xe5,0x1a};

uint8 SessionKeyRequestPacketStuff::unknown2_16b[16] =
		{0x4d,0xd9,0x59,0xf0,0xbc,0xea,0xc2,0x00,
		 0x5a,0xbb,0xc4,0xfd,0x6f,0x2d,0x01,0x6f};

uint8 SessionKeyRequestPacketStuff::unknown3_12b[12] =
		{0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x01,0x11};

uint8 SessionKeyRequestPacketStuff::macRelative1_5b[5] =
		{0x01,0xbf,0x46,0x87,0xdc};

uint8 SessionKeyRequestPacketStuff::unknown4_16b[16] =
		{0x50,0xd5,0xfe,0x43,0x96,0xdb,0xf4,0x87,
		 0x50,0xad,0x96,0x16,0x89,0xad,0x55,0xa9};

uint8 SessionKeyRequestPacketStuff::macRelative2_5b[5] =
		{0x02,0x43,0x41,0x2d,0xb9};

uint8 SessionKeyRequestPacketStuff::macRelative3_16b[16] =
		{0xf8,0xa8,0x70,0x80,0x34,0x8f,0x7b,0xba,
		 0x53,0x41,0x33,0xac,0x3a,0x9b,0x4f,0xba};

//
SessionKeyRequestPacketStuff::SessionKeyRequestPacketStuff()
{
	neckBuf = NULL;
	bodyBuf = NULL;
	numProcess = 0;
}
//
SessionKeyRequestPacketStuff::~SessionKeyRequestPacketStuff()
{

}
//
void SessionKeyRequestPacketStuff::putStatus(uint8 sta)
{
	status = sta;
}
//
void SessionKeyRequestPacketStuff::fromInPacket(InPacket *inPacketPtr)
{
	uint8 *bodyPtr = inPacketPtr->getBody();
	int pos = 75;
	ToolKit::readBufW(bodyPtr+pos, tempTKLen);
	pos += 2;
	tempTK = new uint8[tempTKLen];
	memcpy(tempTK, bodyPtr+pos, tempTKLen);
}
//
void SessionKeyRequestPacketStuff::process()
{
	neckBuf = new uint8[tempTKLen+2];
	int pos = 0;
	ToolKit::writeBufW(neckBuf, tempTKLen);
	pos += 2;
	memcpy(neckBuf+pos, tempTK, tempTKLen);
	SAFE_DELETE_ARRAY(tempTK);

	bodyBuf = new uint8[448];
	pos = 0;
	bodyBuf[pos++] = 0;
	bodyBuf[pos++] = 0;
	bodyBuf[pos++] = 0;
	bodyBuf[pos++] = QQKeys::passwdRKLen;
	memcpy(bodyBuf+pos, QQKeys::passwdRandomKey, 32);
	pos += 32;
	memcpy(bodyBuf+pos, QQKeys::passwdVerifyKey, QQKeys::passwdVKLen);
	pos += QQKeys::passwdVKLen;
	memset(bodyBuf+pos, 0, 19);
	pos += 19;

	memcpy(bodyBuf+pos, QQ_Hash, 16);
	pos += 16;

	//此代码来自EVA QQ
	unsigned char *tmp = new unsigned char[32];
	memcpy(tmp, QQKeys::passwdRandomKey, 16);
	memcpy(tmp+16, QQ_Hash, 16);
	char no_process = numProcess;
	for(int i=0; i<32;)
		no_process ^= tmp[i++];
	SAFE_DELETE_ARRAY(tmp);

	bodyBuf[pos++] = no_process;

	memcpy(bodyBuf+pos, &status, 1);
	pos++;
	memset(bodyBuf+pos, 0, 25);
	pos += 25;
	memcpy(bodyBuf+pos, unknown2_16b, 16);
	pos += 16;
	//LT长度
	bodyBuf[pos++] = QQKeys::loginTokenLen;
	memcpy(bodyBuf+pos, QQKeys::loginToken, QQKeys::loginTokenLen);
	pos += QQKeys::loginTokenLen;
	memcpy(bodyBuf+pos, unknown3_12b, 12);
	pos += 12;
	memcpy(bodyBuf+pos, macRelative1_5b, 5);
	pos += 5;
	bodyBuf[pos++] = 0;
	bodyBuf[pos++] = 16;
	memcpy(bodyBuf+pos, unknown4_16b, 16);
	pos += 16;
	memset(bodyBuf+pos, 0 ,25);
	pos += 25;
	memcpy(bodyBuf+pos, macRelative2_5b, 5);
	pos += 5;
	bodyBuf[pos++] = 0;
	bodyBuf[pos++] = 16;
	memcpy(bodyBuf+pos, macRelative3_16b, 16);
	pos += 16;
	bodyBuf[pos++] = 0;
	bodyBuf[pos++] = 0xc8;
	memset(bodyBuf+pos, 0, 0xc8);
}
//
OutPacket *SessionKeyRequestPacketStuff::toOutPacket()
{
	OutPacket *outPacketPtr = new OutPacket(QQ_REQUEST_SESSION_KEY, true);
	outPacketPtr->putNeck(neckBuf, tempTKLen+2);
	outPacketPtr->putBody(bodyBuf, 448);
	SAFE_DELETE_ARRAY(neckBuf);
	SAFE_DELETE_ARRAY(bodyBuf);
	return outPacketPtr;
}
