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
#include "QQKeys.h"
#include "ToolKit.h"
#include "Wingdefines.h"
#include "WingDebug.h"

//初始化随机密钥，我们设为固定值^_^
uint8 QQKeys::randomKey[16] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01};

uint8 *QQKeys::tempKey = NULL;
uint8 *QQKeys::passwdRandomKey = NULL;
int32 QQKeys::passwdRKLen = 0;
uint8 *QQKeys::passwdVerifyKey = NULL;
int32 QQKeys::passwdVKLen = 0;
uint8 *QQKeys::sessionKey = NULL;
uint8 *QQKeys::md5PasswdKey = NULL;
uint8 *QQKeys::md5Md5PasswdKey = NULL;
uint8 *QQKeys::fileSessionKey = NULL;
uint8 *QQKeys::preToken = NULL;
int32 QQKeys::preTokenLen = 0;
uint8 *QQKeys::loginToken = NULL;
int32 QQKeys::loginTokenLen = 0;

QQKeys::QQKeys()
{

}

QQKeys::~QQKeys()
{

}

void QQKeys::initPasswdKey(char *passwd, int32 passwdLen)
{
	QQKeys::md5PasswdKey = new uint8[QQ_KEY_LENGTH];
	QQKeys::md5Md5PasswdKey = new uint8[QQ_KEY_LENGTH];
	memcpy(QQKeys::md5PasswdKey, ToolKit::doMd5(passwd, passwdLen), 16);
	memcpy(QQKeys::md5Md5PasswdKey, ToolKit::doMd5Md5(passwd, passwdLen), 16);

	//在这里设置密码随机串，将在预会话密钥请求和会话密钥请求中用到。
	uint8 byte20[20];
	memset(byte20, 0, 20);
	memcpy(byte20, QQKeys::md5PasswdKey, 16);
	memset(byte20+16, 1, 4);
	QQKeys::passwdRandomKey = new uint8[32];
	ToolKit::WingEncrypt(byte20, 20, QQKeys::md5Md5PasswdKey, QQKeys::passwdRandomKey, &QQKeys::passwdRKLen);

	//在这里设置密码验证串，将在会话密钥请求中用到。
	QQKeys::passwdVerifyKey = new uint8[16];
	ToolKit::WingEncrypt(NULL, 0, QQKeys::md5Md5PasswdKey, QQKeys::passwdVerifyKey, &QQKeys::passwdVKLen);

#ifdef QT_DEBUG
	uint8 *cstr = QQKeys::md5PasswdKey;
	int strLen = QQ_KEY_LENGTH;

	fprintf(stdout, "md5PasswdKey:");
	for(int i=0; i<strLen; i++)
	{
		if(!(i%8))
			fprintf(stdout, "\n%d: ", i);
		fprintf(stdout, "%2x ", cstr[i]);
	}

	cstr = QQKeys::md5Md5PasswdKey;
	strLen = QQ_KEY_LENGTH;

	fprintf(stdout, "\nmd5Md5PasswdKey:");
	for(int i=0; i<strLen; i++)
	{
		if(!(i%8))
			fprintf(stdout, "\n%d: ", i);
		fprintf(stdout, "%2x ", cstr[i]);
	}

	cstr = QQKeys::passwdRandomKey;
	strLen = QQKeys::passwdRKLen;

	fprintf(stdout, "\npasswdRandomKey:");
	for(int i=0; i<strLen; i++)
	{
		if(!(i%8))
			fprintf(stdout, "\n%d: ", i);
		fprintf(stdout, "%2x ", cstr[i]);
	}

	cstr = QQKeys::passwdVerifyKey;
	strLen = QQKeys::passwdVKLen;

	fprintf(stdout, "\npasswdVerifyKey:");
	for(int i=0; i<strLen; i++)
	{
		if(!(i%8))
			fprintf(stdout, "\n%d: ", i);
		fprintf(stdout, "%2x ", cstr[i]);
	}

	fprintf(stdout, "\n");
	fflush(stdout);
#endif
}

void QQKeys::deleteAllKey()
{
	//打印调试信息
	DWHERE();

	SAFE_DELETE_ARRAY(tempKey);

	SAFE_DELETE_ARRAY(passwdRandomKey);

	SAFE_DELETE_ARRAY(sessionKey);

	SAFE_DELETE_ARRAY(md5PasswdKey);

	SAFE_DELETE_ARRAY(md5Md5PasswdKey);

	SAFE_DELETE_ARRAY(preToken);

	SAFE_DELETE_ARRAY(loginToken);

	SAFE_DELETE_ARRAY(fileSessionKey);

}
