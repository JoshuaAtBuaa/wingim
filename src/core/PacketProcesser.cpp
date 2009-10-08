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


#include "PacketProcesser.h"
#include "PacketStorage.h"
#include "WingMain.h"
#include "WingDebug.h"
#include "InPacket.h"
#include "OutPacket.h"
#include "NetworkManager.h"
#include "LoginModule.h"
#include "PacketBuilder.h"
#include "BuddyInfoManager.h"
#include "ToolKit.h"
#include "GuiHandling.h"
#include "ReceiveIMPacket.h"
#include "EventStruct.h"
#include "WingUser.h"
#include "WingEventProcesser.h"
#include "SignatureOpReplyPacket.h"


PacketProcesser::PacketProcesser(QObject *parent)
	: QObject(parent)
{
	connect(this, SIGNAL(processInPacketSignal(InPacket *)), this, SLOT(processInPacketSlot(InPacket *)), Qt::QueuedConnection);
	connect(this, SIGNAL(processOutPacketSignal(OutPacket *)), this, SLOT(processOutPacketSlot(OutPacket *)), Qt::QueuedConnection);
	connect(this, SIGNAL(processNoAckPacketSignal(OutPacket *)), this, SLOT(processNoAckPacketSlot(OutPacket *)), Qt::QueuedConnection);
}

PacketProcesser::~PacketProcesser()
{
	//打印调试信息
	DWHERE();
}

void PacketProcesser::processInPacket(InPacket *inPacket)
{
	emit processInPacketSignal(inPacket);
}

void PacketProcesser::processOutPacket(OutPacket *outPacket)
{
	emit processOutPacketSignal(outPacket);
}

void PacketProcesser::processNoAckPacket(OutPacket *outPacket)
{
	emit processNoAckPacketSignal(outPacket);
}

void PacketProcesser::processInPacketSlot(InPacket *inPacket)
{
	//取得接收包的命令字
	short command = inPacket->getCommand();

	//打印调试信息
	DWHERE();
	DPRINT("- - - > new inpacket! command:%#x bodyLen:%d",command, inPacket->getBodyLen());

/*
#ifdef QT_DEBUG
	uint8 *bodyPtr = inPacket->getBody();
	int bodyLen = inPacket->getBodyLen();

	for(int i=0; i<bodyLen; i++)
	{
		if(!(i%8))
			fprintf(stderr, "\n%d: ", i);
		fprintf(stderr, "%2x ", bodyPtr[i]);
	}
	fprintf(stderr, "\n");
	fflush(stderr);
#endif
*/
	switch(command)
	{
			//处理握手请求应答 0x0091
		case QQ_TOUCH_REQUEST:
			//处理预登陆令箭请求应答 0x0062
		case QQ_REQUEST_PRE_LOGIN_TOKEN:
			//处理登陆令箭请求应答 0x00ba
		case QQ_REQUEST_LOGIN_TOKEN:
			//处理预会话密钥应答 0X00DD
		case QQ_REQUEST_PRE_SESSION_KEY:
			//处理会话密钥应答 0x0022
		case QQ_REQUEST_SESSION_KEY:
		{
			if(NULL != wingApp->loginModule)
				wingApp->loginModule->processReply(inPacket);
			else
				processUnknownMsg(inPacket);
		}
			break;
			//处理获取好友列表应答 0x0026
		case QQ_GET_FRIEND_LIST:
			processGetFriendListReply(inPacket);
			break;
			//处理获取在线好友应答 0x0027
		case QQ_GET_FRIEND_ONLINE:
			processGetOnlineFriendListReply(inPacket);
			break;
			//收到用户信息 0x0006
		case QQ_GET_USER_INFO:
			processGetUserInfoReply(inPacket);
			break;
			//保持在线（心跳信息）0x0002
		case QQ_KEEP_ALIVE:
			processKeepAliveReply(inPacket);
			break;
			//收到消息 0x0017
		case QQ_RECV_IM:
			processReceiveIM(inPacket);
			break;
			//收到发送消息的应答 0x0016
		case QQ_SEND_IM:
			processSendIMReply(inPacket);
			break;
			//收到好友状态改变信息 0x0081
		case QQ_FRIEND_CHANGE_STATUS:
			processFriendChangeStatus(inPacket);
			break;
			//收到用户状态改变应答信息 0x000D
		case QQ_CHANGE_STATUS:
			processUserChangeStatus(inPacket);
			break;
			//签名操作 0x0067
		case QQ_SIGNATURE_OP:
			processSignatureOpReply(inPacket);
			break;
		default:
			processUnknownMsg(inPacket);
	}
}

void PacketProcesser::processOutPacketSlot(OutPacket *outPacket)
{
	//打印调试信息
	DWHERE();
	DPRINT("- - - > new outpacket! command:%#x bodyLen:%d",outPacket->getCommand(), (int)outPacket->getBodyLen());
/*
#ifdef QT_DEBUG
	uint8 *bodyPtr = outPacket->getBody();
	int bodyLen = outPacket->getBodyLen();

	for(int i=0; i<bodyLen; i++)
	{
		if(!(i%8))
			fprintf(stderr, "\n%d: ", i);
		fprintf(stderr, "%2x ", bodyPtr[i]);
	}
	fprintf(stderr, "\n");
	fflush(stderr);
#endif
*/
	uint8 *outStr = new uint8[QQ_PACKET_MAX_SIZE]; //65535
	int len = 0;
	outPacket->toByteArrary(outStr, &len);
	wingApp->netManager->send(outStr, len);

	//如果不是需要应答的包，删除
	if(!outPacket->ifNeedAck())
		SAFE_DELETE(outPacket);
}

void PacketProcesser::processNoAckPacketSlot(OutPacket *outPacket)
{
	//取得接收包的命令字
	short command = outPacket->getCommand();

	switch(command)
	{
		case QQ_TOUCH_REQUEST:
		case QQ_REQUEST_PRE_LOGIN_TOKEN:
		case QQ_REQUEST_LOGIN_TOKEN:
		case QQ_REQUEST_PRE_SESSION_KEY:
		case QQ_REQUEST_SESSION_KEY:
		{
			WING_EVENT *loginFailed = new WING_EVENT(WING_EVENT::loginFailed,"PacketProcesser","login failed!",0);
			wingApp->eventProcesser->longEventHandling(loginFailed);
		}
			break;
		case QQ_KEEP_ALIVE:
		{
			WING_EVENT *fallLine = new WING_EVENT(WING_EVENT::fallLine,"PacketProcesser","wing has fall line !",0);
			wingApp->eventProcesser->longEventHandling(fallLine);
		}
			break;

	}
	//打印调试信息
	DWHERE();
	DPRINT("- - - > failed to send msg!");
	SAFE_DELETE(outPacket);
}

void PacketProcesser::processGetFriendListReply(InPacket *inPacket)
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

	uint8 *bodyPtr = inPacket->getBody();
	int bodyLen = inPacket->getBodyLen();

	uint8 *bodyCopy = new uint8[bodyLen];
	memcpy(bodyCopy, bodyPtr, bodyLen);

	uint16 endFlag;
	memcpy(&endFlag, bodyPtr, 2);
	if(0xFFFF != endFlag)
	{
		OutPacket *getFriendList = wingApp->packetBuilder->buildFriendListRequestPacket(inPacket);
		wingApp->packetStorage->appendOutPacket(getFriendList);
	}
	wingApp->buddyManager->putBuddyList(bodyCopy, bodyLen);

	//打印调试信息
	DWHERE();
	DPRINT("- - - > receive GetFriendListReply!");
	SAFE_DELETE(inPacket);
}

void PacketProcesser::processGetOnlineFriendListReply(InPacket *inPacket)
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

	uint8 *bodyPtr = inPacket->getBody();
	int bodyLen = inPacket->getBodyLen();

	uint8 *bodyCopy = new uint8[bodyLen];
	memcpy(bodyCopy, bodyPtr, bodyLen);

	uint8 endFlag;
	endFlag = bodyPtr[0];
	if(0xFF != endFlag)
	{
		OutPacket *getFriendList = wingApp->packetBuilder->buildFriendListRequestPacket(inPacket);
		wingApp->packetStorage->appendOutPacket(getFriendList);
	}
	wingApp->buddyManager->putOnlineBuddyList(bodyCopy, bodyLen);
	//打印调试信息
	DWHERE();
	DPRINT("- - - > receive GetOnlineFriendListReply!");
	SAFE_DELETE(inPacket);
}

void PacketProcesser::processGetUserInfoReply(InPacket *inPacket)
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

	uint8 *bodyPtr = inPacket->getBody();
	int bodyLen = inPacket->getBodyLen();

	wingApp->wingUser->putData(bodyPtr, bodyLen);

	WING_EVENT *gotUserInfo = new WING_EVENT(WING_EVENT::gotUserInfo,"PacketProcesser","receive userinfo!",0);
	wingApp->eventProcesser->longEventHandling(gotUserInfo);

	SAFE_DELETE(inPacket);
}

void PacketProcesser::processReceiveIM(InPacket *inPacket)
{
	if(inPacket->getBodyLen() > 15)
	{
		//发送收到应答信息，通知服务消息已收到，内容是收到的信息的前16字节
		OutPacket *imReplyPacket = wingApp->packetBuilder->buildReceiveIMReplyPacket(inPacket);
		wingApp->packetStorage->appendOutPacket(imReplyPacket);
	}
	else
	{
		SAFE_DELETE(inPacket);
		return;
	}

	static short filter = 0;	//用于过滤重复收到的包
	short sequence = inPacket->getSequence();
	if(filter == sequence)
	{
		SAFE_DELETE(inPacket);
		return;
	}
	filter = sequence;

	ReceiveIMPacket *receiveIMPacket = new ReceiveIMPacket();
	receiveIMPacket->fromInPacket(inPacket);
	switch(receiveIMPacket->imKind)
	{
		case ReceiveIMPacket::QQ_IM_FROM_USER:
			wingApp->guiHandling->imFromUser(receiveIMPacket);
			break;
		case ReceiveIMPacket::QQ_IM_FROM_SYS:
			wingApp->guiHandling->imFromSys(receiveIMPacket);
			break;
		case ReceiveIMPacket::QQ_IM_FROM_CLUSTER:
			wingApp->guiHandling->imFromCluster(receiveIMPacket);
			break;
		case ReceiveIMPacket::QQ_IM_FROM_SMS:
			wingApp->guiHandling->imFromSms(receiveIMPacket);
			break;
		case ReceiveIMPacket::CANNOT_PARSE:
		{
			SAFE_DELETE(receiveIMPacket);

			//打印调试信息
			DWHERE();
			DPRINT("- - - > one im packet cannot be parsed!");
		}
			break;
		default:
			;
	}

	//打印调试信息
	DWHERE();
	DPRINT("- - - > receive ReceiveIMPacket!");
	SAFE_DELETE(inPacket);
}

void PacketProcesser::processSendIMReply(InPacket *inPacket)
{
	//删除重发队列中的包
	wingApp->packetStorage->removeNeedAckPacketBySeq(inPacket->getSequence());

	//打印调试信息
	DWHERE();
	DPRINT("- - - > receive SendIMReply!");
	SAFE_DELETE(inPacket);
}

void PacketProcesser::processFriendChangeStatus(InPacket *inPacket)
{
	static short filter = 0;	//用于过滤重复收到的包
	short sequence = inPacket->getSequence();
	if(filter == sequence)
	{
		delete inPacket;
		return;
	}
	filter = sequence;

	uint32 pos = 0, sender;
	uint8 sta;
	uint8 *bodyPtr = inPacket->getBody();
	ToolKit::readBufDW(bodyPtr, sender);
	pos += 4;
	pos += 8;
	sta = bodyPtr[pos++];

	wingApp->guiHandling->friendChangeStatus(sender, sta);

	//打印调试信息
	DWHERE();
	DPRINT("- - - > receive FriendChangeStatus!");
	SAFE_DELETE(inPacket);
}

void PacketProcesser::processUserChangeStatus(InPacket *inPacket)
{
	static short filter = 0;	//用于过滤重复收到的包
	short sequence = inPacket->getSequence();
	if(filter == sequence)
	{
		delete inPacket;
		return;
	}
	filter = sequence;
	//删除重发队列中的包
	wingApp->packetStorage->removeNeedAckPacketBySeq(sequence);


	uint8 *bodyPtr = inPacket->getBody();
	uint8 flag = bodyPtr[0];
	if(flag == 0x30) //成功
	{
		//打印调试信息
		DWHERE();
		DPRINT("- - - > User change status succeed!");
	}
	else
	{
		//打印调试信息
		DWHERE();
		DPRINT("- - - > User change status failed!");
	}

	SAFE_DELETE(inPacket);
}

void PacketProcesser::processKeepAliveReply(InPacket *inPacket)
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

	//打印调试信息
	DWHERE();
	DPRINT("- - - > receive keepAliveReplyPacket!");

	SAFE_DELETE(inPacket);
}

void PacketProcesser::processSignatureOpReply(InPacket *inPacket)
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

	SignatureOpReplyPacket *signatureReply = new SignatureOpReplyPacket();
	signatureReply->fromInPacket(inPacket);
	switch(signatureReply->result)
	{
		case SignatureOpReplyPacket::SIG_GET_SUCCEED:
		{
			std::list<Signature> sigList = signatureReply->getSignatureList();
			if(signatureReply->isUser)
			{
				Signature sig = sigList.front();
				wingApp->guiHandling->putNewSignature(sig.signature);
				wingApp->wingUser->signature = sig;
			}

		}
			break;
		case SignatureOpReplyPacket::SIG_GET_FAILED:
		{

		}
			break;
		case SignatureOpReplyPacket::SIG_MODIFY_SUCCEED:
			break;
		case SignatureOpReplyPacket::SIG_MODIFY_FAILED:
			break;
		default:
			;
	}

}

void PacketProcesser::processUnknownMsg(InPacket *inPacket)
{
	//打印调试信息
	DWHERE();
	DPRINT("- - - > RECEIVE UNKNOWN InPacket! COMMAND:%#x", inPacket->getCommand());
	SAFE_DELETE(inPacket);
}
