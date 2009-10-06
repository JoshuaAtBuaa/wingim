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

#include "BuddyInfoManager.h"
#include "BuddyInfo.h"
#include "ToolKit.h"
#include "Wingdefines.h"
#include "WingDebug.h"
#include "GuiHandling.h"
#include "WingMain.h"
#include "WingEventProcesser.h"
#include "EventStruct.h"


BuddyInfoManager::BuddyInfoManager()
{

}

BuddyInfoManager::~BuddyInfoManager()
{
	if(!buddyList.isEmpty())
	{
		BuddyInfo * buddyInfo;
		QMapIterator<unsigned int, BuddyInfo *> iter(buddyList);
		while(iter.hasNext())
		{
			iter.next();
			buddyInfo = iter.value();
			SAFE_DELETE(buddyInfo);
		}
	}

	//打印调试信息
	DWHERE();
}

void BuddyInfoManager::putBuddyList(uint8 *buf, int len)
{
	//打印调试信息
	DWHERE();

	int pos = 0;
	uint16 endFlag;
	memcpy(&endFlag, buf, 2);
	pos += 2;
	while(len > pos)
	{
		int infoLen = 0;
		BuddyInfo *buddyInfo = new BuddyInfo();
		buddyInfo->putData(buf+pos, &infoLen);
		buddyList.insert(buddyInfo->qqNum, buddyInfo);
		pos += infoLen;
	}
	SAFE_DELETE_ARRAY(buf);

	//0xFFFF表示列表已全部获取
	if(0xFFFF == endFlag)
	{
		wingApp->guiHandling->fetchBuddyList(buddyList);

		WING_EVENT *gotAllBuddyList = new WING_EVENT(WING_EVENT::gotAllBuddyList,"BuddyInfoManager","have got all buddy list");
		wingApp->eventProcesser->longEventHandling(gotAllBuddyList);

		//打印调试信息
		DWHERE();
		DPRINT("- - - > have got all buddy list!");
	}
}

void BuddyInfoManager::putOnlineBuddyList(uint8 *buf, int len)
{
	int pos = 0;
	uint8 endFlag;
	endFlag = buf[pos++];
	while(len > pos)
	{
		uint32 tempQQNum;
		ToolKit::readBufDW(buf+pos, tempQQNum);
		pos += 4;
		pos += 8;	//
		uint8 sta;
		sta = buf[pos++];
		BuddyInfo *buddyInfo = buddyList.value(tempQQNum);
		if(NULL != buddyInfo)
		{
			buddyInfo->status = sta;
			wingApp->guiHandling->friendChangeStatus(buddyInfo->qqNum, sta);

			//打印调试信息
			DWHERE();
			DPRINT("- - - > need to update interface!");

		}
		pos += 29;	//未知29字节
	}

	//0xFF表示列表已全部获取
	if(0xFF == endFlag)
	{
		WING_EVENT *gotOnlineList = new WING_EVENT(WING_EVENT::gotBuddyOnlineList,"BuddyInfoManager","gotOnlineList!",0);
		wingApp->eventProcesser->longEventHandling(gotOnlineList);

		//打印调试信息
		DWHERE();
		DPRINT("- - - > have got all online buddy list!");
	}
}
