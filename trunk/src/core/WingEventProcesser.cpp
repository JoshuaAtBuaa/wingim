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


#include "WingEventProcesser.h"
#include "WingDebug.h"
#include "Wingdefines.h"
#include "WingMain.h"
#include "EventStruct.h"
#include "PacketBuilder.h"
#include "WingUser.h"
#include "LoginModule.h"
#include "NetworkManager.h"
#include "GuiHandling.h"
#include "PacketStorage.h"
#include "PacketProcesser.h"
#include "Packet.h"


//
WingEventProcesser::WingEventProcesser(QObject *parent)
	:QObject(parent)
{
	connect(this, SIGNAL(longEventHandlingSignal(WING_EVENT *)), this, SLOT(longEventHandlingSlot(WING_EVENT *)));
}

WingEventProcesser::~WingEventProcesser()
{
	//打印调试信息
	DWHERE();
}

void WingEventProcesser::longEventHandling(WING_EVENT *event)
{
	emit longEventHandlingSignal(event);
}





void WingEventProcesser::longEventHandlingSlot(WING_EVENT *event)
{
	//打印调试信息
	DWHERE();
	DPRINT("- - - > <WING_EVENT>");
	DPRINT("- - - > eventID:%ld",event->eventID);
	DPRINT("- - - > eventSource:%s",event->source);
	DPRINT("- - - > eventDescription:%s",event->description);
	DPRINT("- - - > eventType:%d",event->type);

	switch(event->type)
	{
		case WING_EVENT::netInitSucceed:
			processNetInitSucceedEvent(event);
			break;
		case WING_EVENT::loginRequest:
			processLoginRequestEvent(event);
			break;
		case WING_EVENT::needVerify:
			processNeedVerifyEvent(event);
			break;
		case WING_EVENT::needActivated:
			processNeedActivatedEvent(event);
			break;
		case WING_EVENT::passwdError:
			processPasswdErrorEvent(event);
			break;
		case WING_EVENT::logoutRequest:
			processLogoutRequestEvent(event);
			break;
		case WING_EVENT::loginSucceed:
			processLoginSucceedEvent(event);
			break;
		case WING_EVENT::loginFailed:
			processLoginFailedEvent(event);
			break;
		case WING_EVENT::fallLine:
			processFallLineEvent(event);
			break;
		case WING_EVENT::gotAllBuddyList:
			processGotAllBuddyListEvent(event);
			break;
		case WING_EVENT::gotBuddyOnlineList:
			processGotBuddyOnlineListEvent(event);
			break;
		case WING_EVENT::gotUserInfo:
			processGotUserInfoEvent(event);
			break;
		case WING_EVENT::gotUserSig:
			processGotUserSigEvent(event);
			break;
		case WING_EVENT::newLoginStatus:
			break;
		default:
			;
	}

}



void WingEventProcesser::processLoginRequestEvent(WING_EVENT *event)
{
	if(wingApp->guiHandling->getNetTypeSetting() == 0)
	{
		Packet::setUDP(true);
		wingApp->netManager->setNetType(NetworkManager::UDP);
	}
	else
	{
		Packet::setUDP(false);
		wingApp->netManager->setNetType(NetworkManager::TCP);
	}
	wingApp->netManager->startConnect();
	SAFE_DELETE(event);
}

void WingEventProcesser::processNeedActivatedEvent(WING_EVENT *event)
{
	wingApp->guiHandling->needActivated();
	SAFE_DELETE(event);
}

void WingEventProcesser::processNeedVerifyEvent(WING_EVENT *event)
{
	wingApp->guiHandling->needVerify();
	SAFE_DELETE(event);
}

void WingEventProcesser::processPasswdErrorEvent(WING_EVENT *event)
{
	wingApp->guiHandling->passwdError();
	SAFE_DELETE(event);
}

void WingEventProcesser::processNetInitSucceedEvent(WING_EVENT *event)
{
	wingApp->wingUser->init();
	wingApp->loginModule = new LoginModule();
	wingApp->loginModule->startLogin();
	SAFE_DELETE(event);
}

void WingEventProcesser::processLoginSucceedEvent(WING_EVENT *event)
{
	wingApp->packetStorage->startKeepAliveTimer();
	wingApp->guiHandling->loginSucceed();

	OutPacket *getFriendList = wingApp->packetBuilder->buildFriendListRequestPacket(NULL);
	wingApp->packetStorage->appendOutPacket(getFriendList);

	SAFE_DELETE(event);
	SAFE_DELETE(wingApp->loginModule);
}

void WingEventProcesser::processLoginFailedEvent(WING_EVENT *event)
{
	wingApp->packetStorage->stopKeepAliveTimer();
	wingApp->packetStorage->deleteAllPacket();

	//打印调试信息
	DWHERE();

	wingApp->guiHandling->loginFailed();

	SAFE_DELETE(event);
}

void WingEventProcesser::processFallLineEvent(WING_EVENT *event)
{
	wingApp->packetStorage->stopKeepAliveTimer();
	wingApp->packetStorage->deleteAllPacket();

	wingApp->guiHandling->fallLine();

	SAFE_DELETE(event);
}

void WingEventProcesser::processGotAllBuddyListEvent(WING_EVENT *event)
{
	OutPacket *getOnlineList = wingApp->packetBuilder->buildFriendOnlineListRequestPacket(NULL);
	wingApp->packetStorage->appendOutPacket(getOnlineList);

	SAFE_DELETE(event);
}

void WingEventProcesser::processGotBuddyOnlineListEvent(WING_EVENT *event)
{
	uint32 qqNum = Packet::getQQNum();
	OutPacket *getUserInfo = wingApp->packetBuilder->buildGetUserInfoPacket(qqNum);
	wingApp->packetStorage->appendOutPacket(getUserInfo);

	SAFE_DELETE(event);
}

void WingEventProcesser::processGotUserInfoEvent(WING_EVENT *event)
{
	wingApp->guiHandling->fetchUserInfo();

	OutPacket *getUserSig = wingApp->packetBuilder->buildUserSignatureRequestPacket(wingApp->wingUser->signature);
	wingApp->packetStorage->appendOutPacket(getUserSig);

	SAFE_DELETE(event);
}

void WingEventProcesser::processGotUserSigEvent(WING_EVENT *event)
{

	SAFE_DELETE(event);
}

void WingEventProcesser::processLogoutRequestEvent(WING_EVENT *event)
{
	wingApp->packetStorage->stopKeepAliveTimer();
	wingApp->packetStorage->deleteAllPacket();

	//直接发送三次
	OutPacket *logoutPacket = wingApp->packetBuilder->buildLogoutRequestPacket();
	wingApp->packetProcesser->processOutPacketSlot(logoutPacket);

	logoutPacket = wingApp->packetBuilder->buildLogoutRequestPacket();
	wingApp->packetProcesser->processOutPacketSlot(logoutPacket);

	logoutPacket = wingApp->packetBuilder->buildLogoutRequestPacket();
	wingApp->packetProcesser->processOutPacketSlot(logoutPacket);

	wingApp->wingUser->setCurrentStatus(WingUser::offline);

	SAFE_DELETE(event);
}
