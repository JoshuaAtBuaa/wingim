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

#ifndef BUDDYINFOMANAGER_H_
#define BUDDYINFOMANAGER_H_

#include <QMap>
#include "Wingdefines.h"
#include "BuddyInfo.h"

class BuddyInfoManager
{
public:
	/*! 构造函数 */
	BuddyInfoManager();

	/*! 释构函数 */
	~BuddyInfoManager();

	/*! 压入好友列表
	 * \param buf 一个字符串指针，指向输入缓冲区。
	 * \param len 缓冲区数据的长度。
	 */
	void putBuddyList(uint8 *buf, int len);

	/*! 压入在线好友列表
	 * \param buf 一个字符串指针，指向输入缓冲区。
	 * \param len 缓冲区数据的长度。
	 */
	void putOnlineBuddyList(uint8 *buf, int len);

private:
	/*! 好友信息列表
	 *  \sa BuddyInfo
	 */
	QMap<unsigned int, BuddyInfo *> buddyList;
};

/*! \class BuddyInfoManager
 *  \brief 这是一个用来管理好友信息的类。
 *
 * \see BuddyInfo
 */

#endif /* BUDDYINFOMANAGER_H_ */
