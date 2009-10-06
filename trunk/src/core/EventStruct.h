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

#ifndef EVENTSTRUCT_H_
#define EVENTSTRUCT_H_

#include "Wingdefines.h"


class WING_EVENT
{
public:
	enum TYPE{
		invalid = 0,		/*!< 0 无效事件，用作默认类型  *///
		loginRequest,		/*!< 1 登陆请求事件，在点击登陆按钮时产生  */
		needVerify,			/*!< 2 要求图片验证  */
		needActivated,		/*!< 3 要求激活事件  */
		passwdError,		/*!< 4 密码错误事件  */
		newLoginStatus,		/*!< 5 新登陆状态事件，表示登陆过程中不同的阶段  */
		logoutRequest,		/*!< 6 退出请求事件，在关闭程序时产生  */
		netInitSucceed,		/*!< 7 网络初始化成功事件  */
		netInitFailed,		/*!< 8 网络初始化失败事件  */
		loginSucceed,		/*!< 9 登陆成功事件  */
		loginFailed,		/*!< 10 登陆失败事件  */
		fallLine,			/*!< 11 掉线事件  */
		gotAllBuddyList,	/*!< 12 获得好友列表事件  */
		gotBuddyOnlineList,	/*!< 13 获得在线好友列表事件 */
		gotUserInfo,		/*!< 14 获得用户信息事件  */
		gotUserSig			/*!< 15 获得用户签名事件  */
		};
public:
	/*! 构造函数
	 * \param t 事件类型
	 * \param so 事件来源
	 * \param de 事件描述
	 * \param da 事件数据
	 */
	WING_EVENT(enum TYPE t=invalid, const char *so=0, const char *de=0, uint32 da=0);

	/*! 释构函数 */
	~WING_EVENT();

	static uint32 eventID;	/*!< 事件序号  */
	enum TYPE type;			/*!< 事件类型  */
	const char *source;		/*!< 事件来源  */
	const char *description;	/*!< 事件描述  */
	uint32 data;		/*!< 事件数据，是否有效要看对应的事件类型  */
};

/*! \class WING_EVENT
 *  \brief 这是一个用来定义事件类型的类。
 *
 *  在wing中很多工作都由事件驱动，例如：当用户点击登陆按钮时，将产生一个loginRequest事件，
 *  再把这个事件交由WingEventProcesser处理。
 */

#endif /* EVENTSTRUCT_H_ */
