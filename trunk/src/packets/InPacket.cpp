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

#include <QtCore>
#include "InPacket.h"
#include "Wingdefines.h"
#include "WingDebug.h"
#include "ToolKit.h"
#include "QQKeys.h"


InPacket::InPacket()
{
	bodyLen = 0;
	decryptedBuf = NULL;
}

//要记得在构造完InPacket后，delete buf
InPacket::InPacket(uint8 *buf, int len)
		:Packet(buf, &len)
{
	decryptedBuf = new uint8[QQ_PACKET_MAX_SIZE];

	bodyLen = QQ_PACKET_MAX_SIZE;

	//减去QQ尾部一字节
	len--;
	//解密主体
	decryptBody(buf, len);

}

InPacket::~InPacket()
{
	SAFE_DELETE_ARRAY(decryptedBuf);
}

//取得主体数据
uint8 *InPacket::getBody()
{
	return decryptedBuf;
}

//取得主体长度
int InPacket::getBodyLen()
{
	return bodyLen;
}

//解压主体部分
void InPacket::decryptBody(uint8 *inStr, int inLen)
{
	switch(command)
	{
		//预登陆令箭请求应答
		case QQ_REQUEST_PRE_LOGIN_TOKEN:
			memcpy(decryptedBuf, inStr, inLen);
			bodyLen = inLen;
			break;
		//握手请求应答
		case QQ_TOUCH_REQUEST:
		//登陆令箭请求应答
		case QQ_REQUEST_LOGIN_TOKEN:
			ToolKit::WingDecrypt(inStr, inLen, QQKeys::randomKey, decryptedBuf, &bodyLen);

			//打印调试信息
			DWHERE();
			DPRINT("- - - > bodyLen:%ld",bodyLen);

			break;
		//预会话密钥请求应答
		case QQ_REQUEST_PRE_SESSION_KEY:
		//会话密钥请求应答
		case QQ_REQUEST_SESSION_KEY:
			/*
			 * 登录回复包使用密码密钥加密，或者使用初始密钥加密，在处理时，应该先尝试使用密码密钥解密，
			 * 如果失败，则再用初始密钥解密。为什么要这样呢，因为你可能密码输入错误，
			 * 这样的话服务器用密码密钥加密的包你就解密不了了，所以会用初始密钥加密。
			 */
			if(ToolKit::WingDecrypt(inStr, inLen, QQKeys::md5Md5PasswdKey, decryptedBuf, &bodyLen) != 1)
			{
				//打印调试信息
				DWHERE();
				DPRINT("- - - > there must be something wrong!");

				memset(decryptedBuf, 0, QQ_PACKET_MAX_SIZE);
				bodyLen = QQ_PACKET_MAX_SIZE;
				ToolKit::WingDecrypt(inStr, inLen, QQKeys::randomKey, decryptedBuf, &bodyLen);
			}

			//打印调试信息
			DWHERE();
			DPRINT("- - - > bodyLen:%ld",bodyLen);

			break;
		//其他应答以及未定义的
		default:
			if(QQKeys::sessionKey == NULL)
			{
				//打印调试信息
				DWHERE();
				DPRINT("- - - > QQKeys::sessionKey has not be init, but someone want to use it to decrypt!");
			}
			else
			{
				//解密身体部分
				ToolKit::WingDecrypt(inStr, inLen, QQKeys::sessionKey, decryptedBuf, &bodyLen);

				//打印调试信息
				DWHERE();
				DPRINT("- - - > bodyLen:%ld",bodyLen);
			}
			break;
	}

}
