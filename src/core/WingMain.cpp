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


#include "WingMain.h"
#include "Wingdefines.h"
#include "WingDebug.h"
#include "GuiHandling.h"
#include "WingEventProcesser.h"
#include "NetworkManager.h"
#include "PacketStorage.h"
#include "PacketProcesser.h"
#include "PacketBuilder.h"
#include "BuddyInfoManager.h"
#include "WingUser.h"
#include "QQKeys.h"


WingMain *wingApp = 0;
WingMain::WingMain()
{
	wingApp = this;
	loginModule = NULL;
	packetBuilder = new PacketBuilder();
	eventProcesser = new WingEventProcesser();
	netManager = new NetworkManager();
	longUser = new WingUser();
	packetStorage = new PacketStorage();
	packetProcesser = new PacketProcesser();
	buddyManager = new BuddyInfoManager();
	guiHandling = new GuiHandling();
}

WingMain::~WingMain()
{

	QQKeys::deleteAllKey();
	SAFE_DELETE(netManager);
	SAFE_DELETE(packetBuilder);
	SAFE_DELETE(eventProcesser);
	SAFE_DELETE(longUser);
	SAFE_DELETE(buddyManager);
	SAFE_DELETE(packetStorage);
	SAFE_DELETE(guiHandling);

	//打印调试信息
	DWHERE();
}
