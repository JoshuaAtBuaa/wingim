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

#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QHostAddress>
#include <QString>
#include "Wingdefines.h"


class QUdpSocket;
class NetworkManager:public QObject
{
  Q_OBJECT
public:
	/*! 构造函数 */
	NetworkManager(QObject * parent = NULL);

	/*! 释构函数 */
	~NetworkManager();

	/*! 发送数据
	 * \param outStr 一个字符串指针，指向输出缓冲区。
	 * \param len 要输出的数据长度。
	 */
	void send(const uint8 *outStr, int len);

	/*! 开始连接
	 */
	void startConnect();
	//
	/*! 停止连接
	 */
	void stopConnect();

	/*! 解释域名 sz8.tencent.com
	 */
	bool DNS();

public slots:
	/*! 设置服务器IP地址
	 * \param addr
	 */
	void setServerAddress(QHostAddress addr);

	/*! 返回网络连接状态
	 */
	bool isNetworkReady();

	/*! 收到数据后执行这个槽
	 */
	void processPendingDatagrams();

private:
	/*! udp套接字
	 * 在整个程序的运行过程中，都用这个套接字来发送接收包 。
	 */
	QUdpSocket * udpSocket;
	QHostAddress serverAddress;	/*!< 服务器IP地址  */
	bool networkReady;		/*!< 网络是否准备好  */
	bool dnsOK;			/*!< 是否已成功解释域名  */
};

/*! \class NetworkManager
 *  \brief 这是一个用来管理网络连接的类。
 */

#endif //NETWORKMANAGER_H
