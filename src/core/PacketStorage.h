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

#ifndef PACKETSTORAGE_H_
#define PACKETSTORAGE_H_

#include <QtCore>
#include "Wingdefines.h"

class InPacket;
class OutPacket;
class PacketStorage : public QThread
{
	Q_OBJECT
public:
	/*! 构造函数 */
	PacketStorage(QObject *parent = 0);

	/*! 释构函数 */
	~PacketStorage();

	/*! 这是一个独立的进程
	 */
	void run();

private slots:
	/*! 收到timeout信号后检查needAckPacketList，重发要重发的包
	 */
	void checkNeedAckList();

	/*! 发送心跳包(保持在线)
	 */
	void doKeepAlive();

public:
	/*! 把接收包添加到队列中
	 * \param inPacket
	 */
	void appendInPacket(InPacket *inPacket);

	/*! 把接收包添加到队列中
	 * \param inStr
	 * \param len
	 */
	void appendInPacket(char *inStr, int32 len);

	/*! 把输出包添加到队列中
	 * \param outPacket
	 */
	void appendOutPacket(OutPacket *outPacket);

	/*! 通过顺序号从队列中删除包
	 * \param seq
	 */
	void removeOutPacketBySeq(unsigned short seq);

	/*! 通过命令字从队列中删除包
	 * \param com
	 */
	void removeOutPacketByCom(unsigned short com);

	/*! 通过顺序号从队列中删除包
	 * \param seq
	 */
	void removeNeedAckPacketBySeq(unsigned short seq);

	/*! 通过命令字从队列中删除包
	 * \param com
	 */
	void removeNeedAckPacketByCom(unsigned short com);

	/*! 开始保持在线定时器
	 */
	void startKeepAliveTimer();

	/*! 停止保持在线定时器
	 */
	void stopKeepAliveTimer();

	/*! 删除所有收到包
	 */
	void deleteAllInPacket();

	/*! 删除所有发送包
	 */
	void deleteAllOutPacket();

	/*! 删除所有需应答包
	 */
	void deleteAllNeedAckPacket();

	/*! 删除所有包
	 */
	void deleteAllPacket();

	/*! 连接信号和槽
	 */
	void doConnect();

private:
	QTimer *checker;			/*!< 用于定时检查needAckPacketList中包的情况  */
	QTimer *keepAliveTimer;		/*!< 定时器，每隔60秒种发送一个保持在线包  */
	QMutex mutex;				/*!< 用于保护各个包队列  */
	QWaitCondition packetListEmpty;		/*!< 线程同步  */
	QHash<short, InPacket *> inPacketList;	/*!< 收到的包队列  */
	QHash<short, OutPacket *> outPacketList;	/*!< 发送的包队列  */
	QHash<short, OutPacket *> needAckPacketList;	/*!< 需应答的包队列  */
	bool endThreadFlag;			/*!< 结束线程标志，当endThread==true时线程跳出无限循环 */

};

/*! \class PacketStorage
 *  \brief 这是一个用来管理包的仓库。
 */

#endif /* PACKETSTORAGE_H_ */
