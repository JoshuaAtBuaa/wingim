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

#ifndef QQKEYS_H
#define QQKEYS_H

#include <string>
#include "Wingdefines.h"


	/**
	 * 构造密码随机串的方法：
	 * 明文 = 密码的一次MD5(16B)+随机字节(4B)
	 * 密钥 = 密码的两次MD5
	 * 密码随机串 = TEA加密(明文,密钥)
	 *
	 * 构造密码验证串的方法：
	 * 明文 = 空字符串
	 * 密钥 = 密码的两次MD5
	 * 密码验证串 = TEA加密(明文,密钥)
	 */

class QQKeys
{
public:
	QQKeys();

	~ QQKeys();
	static void initPasswdKey(char *passwd, int32 passwdLen);
	//
	static void deleteAllKey();
public:
	//随机密钥
	static uint8 randomKey[16];
	//临时密钥
	static uint8 *tempKey;
	//密码随机串=M2P(md5(passwd)+4随机)
	static uint8 *passwdRandomKey;
	//密码随机串长度
	static int32 passwdRKLen;
	//密码验证串=M2P(空字符串)
	static uint8 *passwdVerifyKey;
	//密码验证串长度
	static int32 passwdVKLen;
	//会话密钥
	static uint8 *sessionKey;
	//MD5(passwd)
	static uint8 *md5PasswdKey;
	//密码密钥M2P(passwd)
	static uint8 *md5Md5PasswdKey;
	//预登陆令箭
	static uint8 *preToken;
	//预登陆令箭长度
	static int32 preTokenLen;
	//登陆令箭
	static uint8 *loginToken;
	//登陆令箭长度
	static int32 loginTokenLen;
	//文件会话密钥
	static uint8 *fileSessionKey;
};

#endif // QQKEYS_H
