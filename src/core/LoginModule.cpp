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

#include <QObject>
#include <QHostAddress>
#include <QTemporaryFile>
#include "WingDebug.h"
#include "LoginModule.h"
#include "EventStruct.h"
#include "WingEventProcesser.h"
#include "NetworkManager.h"
#include "PacketStorage.h"
#include "PacketBuilder.h"
#include "WingMain.h"
#include "InPacket.h"
#include "OutPacket.h"
#include "ToolKit.h"
#include "QQKeys.h"
#include "WingLoginWindow.h"
#include "GuiHandling.h"
#include "TouchReplyPacket.h"
#include "GetVerifyPngPacketStuff.h"


LoginModule::LoginModule()
	:loginStatus(noStart)
{

}

LoginModule::~LoginModule()
{
	//打印调试信息
	DWHERE();
}

void LoginModule::startLogin()
{
	//初始化一些密码相关的密码串
	QString passwd = wingApp->guiHandling->loginWindow->pwdInput->text();
	int passwdLen = passwd.size();
	QQKeys::initPasswdKey(passwd.toUtf8().data(), passwdLen);

	//构造第一个握手请求包
	OutPacket *outPacketPtr = wingApp->packetBuilder->buildTouchRequestPacket(NULL);
	wingApp->packetStorage->appendOutPacket(outPacketPtr);
}

void LoginModule::processReply(InPacket *inPacket)
{
	short command = inPacket->getCommand();
	switch(command)
	{
			//处理握手请求应答 0x0091
		case QQ_TOUCH_REQUEST:
			processTouchReply(inPacket);
			break;
			//处理预登陆令箭请求应答 0x0062
		case QQ_REQUEST_PRE_LOGIN_TOKEN:
			processPreLoginTokenReply(inPacket);
			break;
			//处理登陆令箭请求应答 0x00ba
		case QQ_REQUEST_LOGIN_TOKEN:
			processLoginTokenReply(inPacket);
			break;
			//处理预会话密钥应答 0X00DD
		case QQ_REQUEST_PRE_SESSION_KEY:
			processPreSessionReply(inPacket);
			break;
			//处理会话密钥应答 0x0022
		case QQ_REQUEST_SESSION_KEY:
			processSessionReply(inPacket);
			break;
		default:
			//虽然不应该出现这个情况，但还是预防万一
			processUnknownReply(inPacket);
	}
}

void LoginModule::processTouchReply(InPacket *inPacket)
{
	static short filter = 0;	//用于过滤重复收到的包
	short sequence = inPacket->getSequence();
	if(filter == sequence)
	{
		SAFE_DELETE(inPacket);
		return;
	}
	filter = sequence;

	//删除重发队列中的包
	wingApp->packetStorage->removeNeedAckPacketBySeq(sequence);

	//
	uint8 *bodyPtr = inPacket->getBody();
	uint16 flag;
	ToolKit::readBufW(bodyPtr, flag);
	if(0 == flag)
	{
		//打印调试信息
		DWHERE();
		DPRINT("- - - > touch succeed!");

		//预登陆令箭请求
		OutPacket *outPacketPtr = wingApp->packetBuilder->buildPreLoginTokenRequestPacket(inPacket);
		wingApp->packetStorage->appendOutPacket(outPacketPtr);

	}
	else if(1 == flag)
	{
		//打印调试信息
		DWHERE();
		DPRINT("- - - > touch failed! redirect IP...");

		TouchReplyPacket *touchReplyPacket = new TouchReplyPacket();
		touchReplyPacket->fromInPacket(inPacket);
		//设置新IP
		wingApp->netManager->setServerAddress(QHostAddress(touchReplyPacket->getNewIP()));
		SAFE_DELETE(touchReplyPacket);

		//第二次握手请求
		OutPacket *outPacketPtr = wingApp->packetBuilder->buildTouchRequestPacket(inPacket);
		wingApp->packetStorage->appendOutPacket(outPacketPtr);
	}
	else
	{
		loginFailed();

		//打印调试信息
		DWHERE();
		DPRINT("- - - > touch unknown error!");
	}

	SAFE_DELETE(inPacket);
}

void LoginModule::processPreLoginTokenReply(InPacket *inPacket)
{
	static short filter = 0;	//用于过滤重复收到的包
	short sequence = inPacket->getSequence();
	if(filter == sequence)
	{
		SAFE_DELETE(inPacket);
		return;
	}
	filter = sequence;

	//删除重发队列中的包
	wingApp->packetStorage->removeNeedAckPacketBySeq(sequence);

	//
	uint8 *bodyPtr = inPacket->getBody();
	uint8 flag;
	flag = bodyPtr[1];
	if(0x18 == flag)
	{
		//打印调试信息
		DWHERE();
		DPRINT("- - - > preLoginToken request succeed!");

		//发送登陆令箭请求
		OutPacket *outPacketPtr = wingApp->packetBuilder->buildLoginTokenRequestPacket(inPacket);
		wingApp->packetStorage->appendOutPacket(outPacketPtr);

	}
	else
	{
		loginFailed();

		//打印调试信息
		DWHERE();
		DPRINT("- - - > occur unknown error when requesting preLoginToken!");
	}

	SAFE_DELETE(inPacket);
}

void LoginModule::processLoginTokenReply(InPacket *inPacket)
{
	static short filter = 0;	//用于过滤重复收到的包
	short sequence = inPacket->getSequence();
	if(filter == sequence)
	{
		SAFE_DELETE(inPacket);
		return;
	}
	filter = sequence;

	//删除重发队列中的包
	wingApp->packetStorage->removeNeedAckPacketBySeq(sequence);

	//
	uint8 *bodyPtr = inPacket->getBody();
	uint8 flag;
	flag = bodyPtr[3];	//00成功 0x01需要输入验证码验证
	if(0 == flag)
	{
		//打印调试信息
		DWHERE();
		DPRINT("- - - > request LoginToken succeed!");

		//下面取得登陆令箭长度和登陆令箭
		int pos = 5;
		QQKeys::loginTokenLen = (char)bodyPtr[pos++];
		QQKeys::loginToken = new uint8[QQKeys::loginTokenLen];
		memcpy(QQKeys::loginToken, bodyPtr+pos, QQKeys::loginTokenLen);


		//紧接着构造预会话密钥请求包
		OutPacket *outPacketPtr = wingApp->packetBuilder->buildPreSessionKeyRequestPacket(inPacket);
		wingApp->packetStorage->appendOutPacket(outPacketPtr);
	}
	else if(0x01 == flag)
	{
		WING_EVENT *needVerify = new WING_EVENT(WING_EVENT::needVerify,"LoginModule","need verify!",0);
		wingApp->eventProcesser->longEventHandling(needVerify);

/*
		//下面取得登陆令箭长度和登陆令箭
		int pos = 5;
		QQKeys::loginTokenLen = (char)bodyPtr[pos++];
		QQKeys::loginToken = new uint8[QQKeys::loginTokenLen];
		memcpy(QQKeys::loginToken, bodyPtr+pos, QQKeys::loginTokenLen);
		pos += QQKeys::loginTokenLen;
		//验证图片长度
		uint16 pngDataLen = 0;
		ToolKit::readBufW(bodyPtr+pos, pngDataLen);
		pos += 2;
		//读取到缓冲区
		pngBuf.append((char *)(bodyPtr+pos), pngDataLen);
		pos += pngDataLen;
		//
		pos++;
		//
		char endFlag = (char)bodyPtr[pos++];
		if(0 == endFlag)
		{
			//打印调试信息
			DWHERE();
			DPRINT("- - - > have got all png data!");

		     QTemporaryFile file;
		     if (file.open()) {
		    	 file.write(pngBuf);
		    	 QTemporaryFile::createLocalFile (file);
		    	 file.close();
		     }
		}
		else
		{
			pos++;
			int tailLen = (char)bodyPtr[pos++];
			GetVerifyPngPacketStuff *verifyPngPacket = new GetVerifyPngPacketStuff();
			verifyPngPacket->putTail(bodyPtr+pos, tailLen);
			verifyPngPacket->process();
			OutPacket *outPacketPtr = verifyPngPacket->toOutPacket();
			wingApp->packetStorage->appendOutPacket(outPacketPtr);
			SAFE_DELETE(verifyPngPacket);
		}
*/
		//打印调试信息
		DWHERE();
		DPRINT("- - - > demand verify when requesting LoginToken!");


	}
	else
	{
		loginFailed();

		//打印调试信息
		DWHERE();
		DPRINT("- - - > occur unknown error when requesting LoginToken!");
	}

	SAFE_DELETE(inPacket);
}

void LoginModule::processPreSessionReply(InPacket *inPacket)
{
	static short filter = 0;	//用于过滤重复收到的包
	short sequence = inPacket->getSequence();
	if(filter == sequence)
	{
		SAFE_DELETE(inPacket);
		return;
	}
	filter = sequence;

	//删除重发队列中的包
	wingApp->packetStorage->removeNeedAckPacketBySeq(sequence);

	//
	uint8 *bodyPtr = inPacket->getBody();
	//
	uint8 flag;
	flag = bodyPtr[2];

	//打印调试信息
	DWHERE();
	DPRINT("- - - > preSessionKey flag:%#x",flag);

	if(0 == flag)
	{
		//打印调试信息
		DWHERE();
		DPRINT("- - - > request preSessionKey succeed!");

		//在这里设置tempKey,因为等会加密SessionKeyRequestPacket的body的时候要用到这条密钥
		QQKeys::tempKey = new uint8[16];
		int pos = 133;
		memcpy(QQKeys::tempKey, bodyPtr+pos, QQ_KEY_LENGTH);

		//紧接着构造会话密钥请求包
		OutPacket *outPacketPtr = wingApp->packetBuilder->buildSessionKeyRequestPacket(inPacket);
		wingApp->packetStorage->appendOutPacket(outPacketPtr);

	}
	else if(0x33 == flag)
	{
		WING_EVENT *needActivated = new WING_EVENT(WING_EVENT::needActivated,"LoginModule","need activated!",0);
		wingApp->eventProcesser->longEventHandling(needActivated);

		//打印调试信息
		DWHERE();
		DPRINT("- - - > need to be activated when requesting preSessionKey!");

	}
	else if(0x34 == flag)
	{
		WING_EVENT *passwdError = new WING_EVENT(WING_EVENT::passwdError,"LoginModule","password error!",0);
		wingApp->eventProcesser->longEventHandling(passwdError);

		//打印调试信息
		DWHERE();
		DPRINT("- - - > password error when requesting preSessionKey!");

	}
	else
	{
		loginFailed();

		//打印调试信息
		DWHERE();
		DPRINT("- - - > occur unknown error when requesting preSessionKey!");
	}

	SAFE_DELETE(inPacket);
}

void LoginModule::processSessionReply(InPacket *inPacket)
{
	static short filter = 0;	//用于过滤重复收到的包
	short sequence = inPacket->getSequence();
	if(filter == sequence)
	{
		SAFE_DELETE(inPacket);
		return;
	}
	filter = sequence;

	//删除重发队列中的包
	wingApp->packetStorage->removeNeedAckPacketBySeq(sequence);

	//
	uint8 *bodyPtr = inPacket->getBody();
	//0x00成功 0x01重定向服务器 0x05密码错误
	uint8 flag = bodyPtr[0];
	if(0 == flag)
	{
		//打印调试信息
		DWHERE();
		DPRINT("- - - > request SessionKey succeed! cheers~~~");

		//提取会话密钥
		QQKeys::sessionKey = new uint8[QQ_KEY_LENGTH];
		memcpy(QQKeys::sessionKey, bodyPtr+1, QQ_KEY_LENGTH);

		//设置文件会话密钥fileSessionKey
		QQKeys::fileSessionKey = new uint8[QQ_KEY_LENGTH];
		//现在设置fileSessionKey
		char *fsbuf = new char[QQ_KEY_LENGTH + 4];
		//QQ号码，网络字节序
		memcpy(fsbuf, bodyPtr + QQ_KEY_LENGTH + 1 , 4);
		//sessionKey
		memcpy(fsbuf+4, QQKeys::sessionKey, QQ_KEY_LENGTH);
		//设置fileSessionKey
		memcpy(QQKeys::fileSessionKey, ToolKit::doMd5(fsbuf, 4 + QQ_KEY_LENGTH), 16);
		SAFE_DELETE_ARRAY(fsbuf);

		//
		WING_EVENT *loginSucceed = new WING_EVENT(WING_EVENT::loginSucceed,"LoginModule","login succeed!",0);
		wingApp->eventProcesser->longEventHandling(loginSucceed);
	}
	else if(1 == flag)
	{
		//打印调试信息
		DWHERE();
		DPRINT("- - - > demand to redirect IP when requesting SessionKey!");

	}
	else if(5 == flag)
	{
		WING_EVENT *passwdError = new WING_EVENT(WING_EVENT::passwdError,"LoginModule","password error!",0);
		wingApp->eventProcesser->longEventHandling(passwdError);

		//打印调试信息
		DWHERE();
		DPRINT("- - - > wrong passwd when requesting SessionKey!");

	}
	else
	{
		loginFailed();

		//打印调试信息
		DWHERE();
		DPRINT("- - - > occur unknown error when requesting SessionKey!");

	}
	SAFE_DELETE(inPacket);
}

void LoginModule::processUnknownReply(InPacket *inPacket)
{
	//打印调试信息
	DWHERE();
	DPRINT("- - - > Oh,NO!");

	SAFE_DELETE(inPacket);
}

void LoginModule::loginFailed()
{
	WING_EVENT *loginFailed = new WING_EVENT(WING_EVENT::loginFailed,"LoginModule","login failed!",0);
	wingApp->eventProcesser->longEventHandling(loginFailed);
}
