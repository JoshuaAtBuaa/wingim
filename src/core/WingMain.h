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

#ifndef WINGMAIN_H_
#define WINGMAIN_H_

class WingMain;
extern WingMain *wingApp;		//一个全局WingMain指针

class GuiHandling;
class WingEventProcesser;
class NetworkManager;
class PacketBuilder;
class LoginModule;
class PacketProcesser;
class PacketStorage;
class BuddyInfoManager;
class WingUser;
class WingMain
{
public:
	WingMain();
	~WingMain();

public:
	//界面管理类
	GuiHandling *guiHandling;
	//事件处理器
	WingEventProcesser *eventProcesser;
	//网络连接管理器
	NetworkManager *netManager;
	//种类请求操作
	PacketBuilder *packetBuilder;
	//登陆模块
	LoginModule *loginModule;
	//包处理模块
	PacketProcesser *packetProcesser;
	//包管理模块
	PacketStorage *packetStorage;
	//好友信息管理
	BuddyInfoManager *buddyManager;
	//用户信息
	WingUser *longUser;

};

/*! \class WingMain
 *  \brief 这是一个用来把各个模块集在一起的类。
 */

#endif /* WINGMAIN_H_ */
