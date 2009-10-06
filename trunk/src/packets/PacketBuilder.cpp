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

#include <QString>
#include <list>
#include <QTextCodec>
#include "Wingdefines.h"
#include "QQKeys.h"
#include "ToolKit.h"
#include "WingMain.h"
#include "WingDebug.h"
#include "PacketBuilder.h"
#include "LoginModule.h"
#include "WingUser.h"
#include "Signature.h"
#include "AllPacketsHead.h"


PacketBuilder::PacketBuilder()
{

}

PacketBuilder::~PacketBuilder()
{
	//打印调试信息
	DWHERE();
}

//构造握手请求包
OutPacket *PacketBuilder::buildTouchRequestPacket(InPacket *inPacket)
{
	TouchRequestPacketStuff *touchPacket = new TouchRequestPacketStuff();
	touchPacket->fromInPacket(inPacket);
	touchPacket->process();
	OutPacket *outPacket = touchPacket->toOutPacket();
	SAFE_DELETE(touchPacket);
	return outPacket;
}
//构造预登陆请求包
OutPacket *PacketBuilder::buildPreLoginTokenRequestPacket(InPacket *inPacket)
{
	PreLoginTokenRequestPacketStuff *preLTPacket = new PreLoginTokenRequestPacketStuff();
	preLTPacket->fromInPacket(inPacket);
	preLTPacket->process();
	OutPacket *outPacket = preLTPacket->toOutPacket();
	SAFE_DELETE(preLTPacket);
	return outPacket;
}
//构造登陆请求包
OutPacket *PacketBuilder::buildLoginTokenRequestPacket(InPacket *inPacket)
{
	LoginTokenRequestPacketStuff *loginTokenPacket = new LoginTokenRequestPacketStuff();
	loginTokenPacket->fromInPacket(inPacket);
	loginTokenPacket->process();
	OutPacket *outPacket = loginTokenPacket->toOutPacket();
	SAFE_DELETE(loginTokenPacket);
	return outPacket;
}
//构造预会话密钥包
OutPacket *PacketBuilder::buildPreSessionKeyRequestPacket(InPacket *inPacket)
{
	PreSessionKeyRequestPacketStuff *preSKPacket = new PreSessionKeyRequestPacketStuff();
	preSKPacket->fromInPacket(inPacket);
	preSKPacket->process();
	OutPacket *outPacket = preSKPacket->toOutPacket();
	SAFE_DELETE(preSKPacket);
	return outPacket;
}
//构造会话密钥请求包
OutPacket *PacketBuilder::buildSessionKeyRequestPacket(InPacket *inPacket)
{
	SessionKeyRequestPacketStuff *sessionKeyPacket = new SessionKeyRequestPacketStuff();
	sessionKeyPacket->fromInPacket(inPacket);
	sessionKeyPacket->putStatus((uint8)wingApp->wingUser->getLoginMode());
	sessionKeyPacket->process();
	OutPacket *outPacket = sessionKeyPacket->toOutPacket();
	SAFE_DELETE(sessionKeyPacket);
	return outPacket;
}
//构造在线好友列表请求包
OutPacket *PacketBuilder::buildFriendOnlineListRequestPacket(InPacket *inPacket)
{
	GetFriendOnlineListPacketStuff *getFOLPacket = new GetFriendOnlineListPacketStuff();
	getFOLPacket->fromInPacket(inPacket);
	getFOLPacket->process();
	OutPacket *outPacket = getFOLPacket->toOutPacket();
	SAFE_DELETE(getFOLPacket);
	return outPacket;
}
//构造好友列表请求包
OutPacket *PacketBuilder::buildFriendListRequestPacket(InPacket *inPacket)
{
	GetFriendListPacketStuff *getFLPacket = new GetFriendListPacketStuff();
	getFLPacket->fromInPacket(inPacket);
	getFLPacket->process();
	OutPacket *outPacket = getFLPacket->toOutPacket();
	SAFE_DELETE(getFLPacket);
	return outPacket;
}
//构造请求改变状态包
OutPacket *PacketBuilder::buildChangeStatusRequestPacket(uint8 status)
{
	ChangeStatusPacketStuff *changeStatusPacket = new ChangeStatusPacketStuff();
	changeStatusPacket->setStatus(status);
	changeStatusPacket->process();
	OutPacket *outPacket = changeStatusPacket->toOutPacket();
	SAFE_DELETE(changeStatusPacket);
	return outPacket;
}
//构造心跳包
OutPacket *PacketBuilder::buildKeepAliveRequestPacket()
{
	KeepAlivePacketStuff *keepAlivePacket = new KeepAlivePacketStuff();
	OutPacket *outPacket = keepAlivePacket->toOutPacket();
	SAFE_DELETE(keepAlivePacket);
	return outPacket;
}
//构造发送消息包
OutPacket *PacketBuilder::buildSendMsgRequestPacket(uint32 receiver, QString msg)
{
	int outLen = 0;
	char *outMsg = ToolKit::UTF8ToGBctr(msg, outLen);
	SendIMPacketStuff *msgPacket = new SendIMPacketStuff();
	msgPacket->setSender(Packet::getQQNum());
	msgPacket->setReceiver(receiver);
	msgPacket->putMsg((uint8 *)outMsg, outLen);
	msgPacket->process();
	OutPacket *outPacket = msgPacket->toOutPacket();
	SAFE_DELETE_ARRAY(outMsg);
	SAFE_DELETE(msgPacket);
	return outPacket;
}
//构造收到消息后的回应包
OutPacket *PacketBuilder::buildReceiveIMReplyPacket(InPacket *inPacket)
{
	ReceiveIMReplyPacketStuff *imReplyPacket = new ReceiveIMReplyPacketStuff();
	imReplyPacket->fromInPacket(inPacket);
	imReplyPacket->process();
	OutPacket *outPacket = imReplyPacket->toOutPacket();
	SAFE_DELETE(imReplyPacket);
	return outPacket;
}
//构造获取用户信息包
OutPacket *PacketBuilder::buildGetUserInfoPacket(uint32 qq)
{
	GetUserInfoPacketStuff *getUserInfo = new GetUserInfoPacketStuff();
	getUserInfo->putUserQQ(qq);
	getUserInfo->process();
	OutPacket *outPacket = getUserInfo->toOutPacket();
	SAFE_DELETE(getUserInfo);
	return outPacket;
}
//构造退出请求包
OutPacket *PacketBuilder::buildLogoutRequestPacket()
{
	LogoutPacketStuff *logoutPacket = new LogoutPacketStuff();
	logoutPacket->process();
	OutPacket *outPacket = logoutPacket->toOutPacket();
	SAFE_DELETE(logoutPacket);
	return outPacket;
}
//获取好友签名
OutPacket *PacketBuilder::buildUserSignatureRequestPacket(const Signature &sig)
{
	SignatureOpPacket *sigOpPacket = new SignatureOpPacket(SignatureOpPacket::GET_SIGNATURE);
	sigOpPacket->putUserSignature(sig);
	OutPacket *outPacket = sigOpPacket->toOutPacket();
	SAFE_DELETE(sigOpPacket);
	return outPacket;
}
//获取好友签名
OutPacket *PacketBuilder::buildBuddySignatureRequestPacket()
{
	/*
	if(isUser)
	{
		std::list<Signature> sigList;
		sigList.push_back(wingApp->wingUser->signature);
		SignatureOpPacket *sigOpPacket = new SignatureOpPacket(SignatureOpPacket::GET_SIGNATURE);
		sigOpPacket->putSignatureList(sigList);
		OutPacket *outPacket = sigOpPacket->toOutPacket();
		SAFE_DELETE(sigOpPacket);
		return outPacket;
	}
	if(next)
	{
		SignatureOpPacket *sigOpPacket = new SignatureOpPacket(SignatureOpPacket::GET_SIGNATURE);
		sigOpPacket->process();
		OutPacket *outPacket = sigOpPacket->toOutPacket();
	}
	else
	{

	}
	*/
	return NULL;

}
//修改签名
OutPacket *PacketBuilder::buildSignatureModifyPacket(const Signature &sig)
{
	return NULL;
}
