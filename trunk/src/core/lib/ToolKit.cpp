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

#ifdef _WIN32
#include <winsock.h>
#else
#include <netinet/in.h>
#endif

#include <cstring>
#include <QString>
#include <QTextCodec>
#include "ToolKit.h"
#include "crypt.h"
extern "C"
{
#include "md5.h"
}

char ToolKit::md5Buf[QQ_KEY_LENGTH];

ToolKit::ToolKit()
{

}
//
ToolKit::~ToolKit()
{

}

char *ToolKit::doMd5(char *instr, int32 len)
{
	md5_state_t ctx;
	md5_init(&ctx);
	md5_append(&ctx, (md5_byte_t *) instr, len);
	md5_finish(&ctx, (md5_byte_t *) md5Buf);
	return md5Buf;
}

char *ToolKit::doMd5Md5(char *instr, int32 len)
{
	doMd5(instr, len);
	doMd5(md5Buf, QQ_KEY_LENGTH);
	return md5Buf;
}

void ToolKit::WingEncrypt(uint8 *instr, int32 instrlen,
						  uint8 *key, uint8 *outstr,
						  int32 *outstrlen)
{
	Crypt::encrypt(instr, instrlen, key, outstr, outstrlen);
}

int32 ToolKit::WingDecrypt(uint8 *instr, int32 instrlen,
						  uint8 *key, uint8 *outstr,
						  int32 *outstrlen)
{
	return Crypt::decrypt(instr, instrlen, key, outstr, outstrlen);
}

void ToolKit::readBufW(uint8 *buf, uint16 &value)
{
	uint16 temp = *(uint16 *)buf;
	value = ntohs(temp);
}

void ToolKit::readBufDW(uint8 *buf, uint32 &value)
{
	uint32 temp = *(uint32 *)buf;
	value = ntohl(temp);
}

void ToolKit::writeBufW(uint8 *buf, const uint16 value)
{
	uint16 temp = htons(value);
	memcpy(buf, &temp, 2);
}

void ToolKit::writeBufDW(uint8 *buf, const uint32 value)
{
	uint32 temp = htonl(value);
	memcpy(buf, &temp, 4);
}

QString ToolKit::GBctrToUTF8(char *text)
{
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB18030"));
	return QString::fromLocal8Bit(text);
}

char *ToolKit::UTF8ToGBctr(QString text, int &outLen)
{
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB18030"));
	const char *str = text.toLocal8Bit().constData();
	outLen = strlen(str);
	char *outStr = new char[outLen];
	memcpy(outStr, str, outLen);
	return outStr;
	//QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
}
