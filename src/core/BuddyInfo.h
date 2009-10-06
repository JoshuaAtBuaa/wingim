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

#ifndef BUDDYINFO_H_
#define BUDDYINFO_H_

#include "Wingdefines.h"
#include "Signature.h"


class BuddyInfo
{
public:

	/*! 构造函数*/
	BuddyInfo();

	/*! 释构函数*/
	~BuddyInfo();

	/*! 压入好友的各项信息
	 * \param buf 一个字符串指针，指向输入缓冲区。
	 * \param dataLen 一个整型指针，用于返回压入数据的长度。
	 */
	void putData(uint8 *buf, int *dataLen);

public:
	uint32 qqNum;	/*!< QQ号  */
	uint16 head;	/*!< 头像  */
	uint8 age;		/*!< 年龄  */
	uint8 gender;	/*!< 性别  */
	uint8 *nick;	/*!< 昵称  */
	int8 nickLen;	/*!< 昵称长度  */
	uint32 userFlag;	/*!< 用户属性标志  */
	uint8 status;	/*!< 好友状态  */
	Signature signature;	/*!< 好友的签名信息  \sa Signature */

};

/*! \class BuddyInfo
 *  \brief 这是一个用来保存好友信息的类。
 *  \sa BuddyInfoManager
 */

#endif /* BUDDYINFO_H_ */
