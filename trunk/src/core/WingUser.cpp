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


#include "Packet.h"
#include "WingUser.h"
#include "ToolKit.h"
#include "QQKeys.h"
#include "WingDebug.h"
#include "WingMain.h"
#include "GuiHandling.h"


WingUser::WingUser()
	: signature(),loginMode(offline),
	currentStatus(offline)
{
	infoList.reserve(QQ_CONTACT_FIELDS);
	infoList.push_back("-");		//qq number
	infoList.push_back("wing");	//nick
}

WingUser::~WingUser()
{
	//打印调试信息
	DWHERE();
}

//设置登陆状态
void WingUser::setLoginMode(const UserStatus sta)
{
	loginMode = sta;
}

//获取登陆状态
WingUser::UserStatus WingUser::getLoginMode()
{
	return loginMode;
}

//设置当前状态
void WingUser::setCurrentStatus(const UserStatus sta)
{
	currentStatus = sta;
}

//获取当前状态
WingUser::UserStatus WingUser::getCurrentStatus()
{
	return currentStatus;
}

void WingUser::init()
{
	//取得帐号
	unsigned int qqNum = wingApp->guiHandling->getLoginQQ();
	Packet::setQQNum(qqNum);
	signature.qqNum = qqNum;

	//取得状态
	loginMode = (WingUser::UserStatus)wingApp->guiHandling->getStatusSetting();
}

void WingUser::putData(const unsigned char *buf, const int len)
{
	int start = 0;
	infoList.clear();
	for(int i = 0; i< len; i++)
	{
		if(buf[i]!= DIVIDER) continue;
		char *tmp = (char *)malloc( (i-start+1) *sizeof(char));
		memcpy(tmp, buf+start, i-start);
		tmp[i-start] = 0x00;
		infoList.push_back(std::string(tmp));
		start = i+1;
		free(tmp);
	}
	//如果小于37个部分
	if(infoList.size() < QQ_CONTACT_FIELDS)
	{
		char *tmp = (char *)malloc( (len-start+1) *sizeof(char));
		memcpy(tmp, buf+start, len-start);
		tmp[len-start]=0x00;
		infoList.push_back(std::string(tmp));
		free(tmp);
	}
}

const std::string &WingUser::at(const InfoIndex index) const
{
	return infoList[index];
}
