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

#ifndef TOOLKIT_H_
#define TOOLKIT_H_

#include "Wingdefines.h"


class QString;
class ToolKit
{
public:
	//
	ToolKit();
	//
	~ToolKit();
	//
	static char *doMd5(char *instr, int32 len);
	//
	static char *doMd5Md5(char *instr, int32 len);
	//
	static void WingEncrypt(uint8 *instr, int32 instrlen,
							uint8 *key, uint8 *outstr,
							int32 *outstrlen);
	//
	static int32 WingDecrypt(uint8 *instr, int32 instrlen,
							uint8 *key, uint8 *outstr,
							int32 *outstrlen);
	//
	static void readBufW(uint8 *buf, uint16 &value);
	//
	static void readBufDW(uint8 *buf, uint32 &value);
	//
	static void writeBufW(uint8 *buf, const uint16 value);
	//
	static void writeBufDW(uint8 *buf, const uint32 value);
	//
	static QString GBctrToUTF8(char *text);
	//
	static char *UTF8ToGBctr(QString text, int &outLen);

private:
	static char md5Buf[QQ_KEY_LENGTH];
};

#endif /* TOOLKIT_H_ */
