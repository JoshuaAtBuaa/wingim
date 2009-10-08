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

#ifndef GUIHANDLING_H_
#define GUIHANDLING_H_

#include <QObject>
#include <QMap>
#include <string>
#include "Wingdefines.h"
#include "WingUser.h"

class BuddyInfo;
class ReceiveIMPacket;
class WingLoginWindow;
class WingMainWindow;
class WingDialogWindow;
class WingSystemTray;
class GuiHandling : public QObject
{
	Q_OBJECT
public:
	/*! 构造函数 */
	GuiHandling(QObject *parent = 0);

	/*! 释构函数 */
	~GuiHandling();

	/*! 初始化
	 */
	void init();

	/*! 取得登陆QQ
	 */
	uint32 getLoginQQ();

	/*! 取得登陆状态设置
	 */
	WingUser::UserStatus getStatusSetting();

	/*! 取得网络类型设置
	 */
	int getNetTypeSetting();

	/*! 登陆成功
	 */
	void loginSucceed();

	/*! 登陆失败
	 */
	void loginFailed();

	/*! 要求输入验证码
	 */
	void needVerify();

	/*! 要示重新激活
	 */
	void needActivated();

	/*! 密码错误
	 */
	void passwdError();

	/*! 掉线处理
	 */
	void fallLine();

	/*! 退出请求
	 */
	void logoutRequest();

	/*! 获取好友列表
	 *  \param buddyList
	 */
	void fetchBuddyList(QMap<unsigned int, BuddyInfo *> buddyList);

	/*! 获取用户信息
	 */
	void fetchUserInfo();

	/*! 好友改变状态
	 *  \param qq
	 *  \param sta
	 */
	void friendChangeStatus(uint32 qq, uint8 sta);

	/*! 更新签名
	 *  \param sig
	 */
	void putNewSignature(std::string sig);

	/*! 收到用户消息
	 *  \param event
	 */
	void imFromUser(ReceiveIMPacket *imPacket);

	/*! 收到系统消息
	 *  \param imPacket
	 */
	void imFromSys(ReceiveIMPacket *imPacket);

	/*! 收到群消息
	 *  \param imPacket
	 */
	void imFromCluster(ReceiveIMPacket *imPacket);

	/*! 收到sms消息
	 *  \param imPacket
	 */
	void imFromSms(ReceiveIMPacket *imPacket);

	/*! 构造请求改变状态包
	 *  \param status
	 */
	void changeUserStatus(uint8 status);

	/*! 播放声音
	 */
	void palySound();

	/*! 设置皮肤
	 */
	void setSkin();

protected:
	/*! 事件过滤器
	 *  \param obj
	 *  \param event
	 */
    bool eventFilter(QObject *obj, QEvent *event);

public:
	WingLoginWindow *loginWindow;	/*!< 登陆窗口  \sa WingLoginWindow */
	WingMainWindow *mainWindow;		/*!< 主窗口  \sa WingMainWindow */
	WingDialogWindow *dialogWindow;	/*!< 聊天窗口  \sa WingDialogWindow */
	WingSystemTray *systemTray;		/*!< 系统托盘  \sa WingSystemTray */

};

/*! \class GuiHandling
 *  \brief 这是一个用来处理界面的类
 *
 *  几乎所有对界面的操作都由它进行。
 */

#endif /* GUIHANDLING_H_ */
