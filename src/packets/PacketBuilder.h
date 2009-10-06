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

#ifndef PACKETBUILDER_H_
#define PACKETBUILDER_H_

class InPacket;
class OutPacket;
class Signature;
class PacketBuilder
{
public:
	PacketBuilder();
	~PacketBuilder();
	//构造握手请求包
	OutPacket *buildTouchRequestPacket(InPacket *inPacket);
	//构造预登陆请求包
	OutPacket *buildPreLoginTokenRequestPacket(InPacket *inPacket);
	//构造登陆请求包
	OutPacket *buildLoginTokenRequestPacket(InPacket *inPacket);
	//构造预会话密钥包
	OutPacket *buildPreSessionKeyRequestPacket(InPacket *inPacket);
	//构造会话密钥请求包
	OutPacket *buildSessionKeyRequestPacket(InPacket *inPacket);
	//构造在线好友列表请求包
	OutPacket *buildFriendOnlineListRequestPacket(InPacket *inPacket);
	//构造好友列表请求包
	OutPacket *buildFriendListRequestPacket(InPacket *inPacket);
	//构造请求改变状态包
	OutPacket *buildChangeStatusRequestPacket(uint8 status);
	//构造心跳包
	OutPacket *buildKeepAliveRequestPacket();
	//构造发送消息包
	OutPacket *buildSendMsgRequestPacket(uint32 receiver, QString msg);
	//构造收到消息后的回应包
	OutPacket *buildReceiveIMReplyPacket(InPacket *inPacket);
	//构造获取用户信息包
	OutPacket *buildGetUserInfoPacket(uint32 qq);
	//构造退出请求包
	OutPacket *buildLogoutRequestPacket();
	//构造好友签名请求包
	OutPacket *buildBuddySignatureRequestPacket();
	//构造用户签名请求包
	OutPacket *buildUserSignatureRequestPacket(const Signature &sig);
	//修改签名
	OutPacket *buildSignatureModifyPacket(const Signature &sig);
};

/*! \class PacketBuilder
 *  \brief 这是一个用来构造各种包的类。
 */

#endif /* PACKETBUILDER_H_ */
