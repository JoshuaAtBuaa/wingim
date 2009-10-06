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
#include "LoginTokenRequestPacketStuff.h"
#include "InPacket.h"
#include "OutPacket.h"
#include "QQKeys.h"
#include "Wingdefines.h"
#include "ToolKit.h"

LoginTokenRequestPacketStuff::LoginTokenRequestPacketStuff()
{
	neckBuf = NULL;
	bodyBuf = NULL;
	uint8 tempByte5[5] = {0x03, 0x0, 0x05, 0x00, 0x00};
	memcpy(unknown1_5b, tempByte5, 5);
	memset(unknown2_5b, 0, 5);
}
//
LoginTokenRequestPacketStuff::~LoginTokenRequestPacketStuff()
{

}
//
void LoginTokenRequestPacketStuff::fromInPacket(InPacket *inPacketPtr)
{
	uint8 *bodyPtr = inPacketPtr->getBody();
	int pos = 0;
	pos++;
	QQKeys::preTokenLen = (char)bodyPtr[pos++];
	QQKeys::preToken = new uint8[QQKeys::preTokenLen];
	memcpy(QQKeys::preToken, bodyPtr+pos, QQKeys::preTokenLen);
}
//
void LoginTokenRequestPacketStuff::process()
{
	neckBuf = QQKeys::randomKey;
	bodyBuf = new uint8[35];
	int pos = 0;
	bodyBuf[pos++] = QQKeys::preTokenLen;
	memcpy(bodyBuf+pos, QQKeys::preToken, QQKeys::preTokenLen);
	pos += QQKeys::preTokenLen;
	memcpy(bodyBuf+pos, unknown1_5b, 5);
	pos += 5;
	memcpy(bodyBuf+pos, unknown2_5b, 5);
}
//
OutPacket *LoginTokenRequestPacketStuff::toOutPacket()
{
	OutPacket *outPacketPtr = new OutPacket(QQ_REQUEST_LOGIN_TOKEN, true);
	outPacketPtr->putNeck(neckBuf, QQ_KEY_LENGTH);
	outPacketPtr->putBody(bodyBuf, 35);
	SAFE_DELETE_ARRAY(bodyBuf);
	return outPacketPtr;
}
