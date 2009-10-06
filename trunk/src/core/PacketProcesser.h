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

#ifndef PACKETPROCESSER_H_
#define PACKETPROCESSER_H_

#include <QObject>
#include "Wingdefines.h"

class InPacket;
class OutPacket;
class PacketProcesser : public QObject
{
	Q_OBJECT

public:
	/*! 构造函数 */
	PacketProcesser(QObject *parent = 0);

	/*! 释构函数 */
	~PacketProcesser();

	/*! 处理InPacket
	 * \param inPacket
	 */
	void processInPacket(InPacket *inPacket);

	/*! 处理OutPacket
	 * \param outPacket
	 */
	void processOutPacket(OutPacket *outPacket);

	/*! 处理没有应答的包
	 * \param outPacket
	 */
	void processNoAckPacket(OutPacket *outPacket);

private:
	/*! 处理获取好友列表应答
	 * \param inPacket
	 */
	void processGetFriendListReply(InPacket *inPacket);

	/*! 处理获取在线好友列表应答
	 * \param inPacket
	 */
	void processGetOnlineFriendListReply(InPacket *inPacket);

	/*! 处理获取用户信息应答
	 * \param inPacket
	 */
	void processGetUserInfoReply(InPacket *inPacket);

	/*! 处理收到消息
	 * \param inPacket
	 */
	void processReceiveIM(InPacket *inPacket);

	/*! 处理发送消息应答
	 * \param inPacket
	 */
	void processSendIMReply(InPacket *inPacket);

	/*! 处理好友改变状态
	 * \param inPacket
	 */
	void processFriendChangeStatus(InPacket *inPacket);

	/*! 处理用户改变状态应答
	 * \param inPacket
	 */
	void processUserChangeStatus(InPacket *inPacket);

	/*! 处理保持在线应答
	 * \param inPacket
	 */
	void processKeepAliveReply(InPacket *inPacket);

	/*! 处理签名操作应答
	 * \param inPacket
	 */
	void processSignatureOpReply(InPacket *inPacket);

	/*! 处理未知应答
	 * \param inPacket
	 */
	void processUnknownMsg(InPacket *inPacket);

signals:

	/*! 处理InPacket的信号
	 * \param inPacket
	 */
	void processInPacketSignal(InPacket *inPacket);

	/*! 处理OutPacket的信号
	 * \param outPacket
	 */
	void processOutPacketSignal(OutPacket *outPacket);

	/*! 处理没有应答的OutPacket的信号
	 * \param outPacket
	 */
	void processNoAckPacketSignal(OutPacket *outPacket);

public slots:
	/*! 处理InPacket的槽
	 * \param inPacket
	 */
	void processInPacketSlot(InPacket *inPacket);

	/*! 处理OutPacket的槽
	 * \param outPacket
	 */
	void processOutPacketSlot(OutPacket *outPacket);

	/*! 处理没有应答的OutPacket的槽
	 * \param outPacket
	 */
	void processNoAckPacketSlot(OutPacket *outPacket);
};

/*! \class PacketProcesser
 *  \brief 这是一个用来处理各种包的类。
 */

#endif /* PACKETPROCESSER_H_ */
