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

#include "PacketStorage.h"
#include "WingMain.h"
#include "WingDebug.h"
#include "PacketProcesser.h"
#include "InPacket.h"
#include "OutPacket.h"
#include "PacketBuilder.h"


PacketStorage::PacketStorage(QObject *parent)
	: QThread(parent),endThreadFlag(false)
{
	//做一些初始化工作，主要是连接信号和槽
	doConnect();

	//开始线程
	start();
}

PacketStorage::~PacketStorage()
{
	if(checker->isActive())
		checker->stop();
	SAFE_DELETE(checker);

	if(keepAliveTimer->isActive())
		keepAliveTimer->stop();
	SAFE_DELETE(keepAliveTimer);

	deleteAllPacket();

	mutex.lock();

	//设置结束线程标志
	endThreadFlag = true;
	packetListEmpty.wakeOne();

	mutex.unlock();
	//等待线程退出
	wait();

	//打印调试信息
	DWHERE();
}


void PacketStorage::run()
{

	while(1)
	{
		mutex.lock();

		//如果outPacketList和inPacketList同时为空且endThreadFlag为假时，则等待
		while(outPacketList.isEmpty() && inPacketList.isEmpty() && !endThreadFlag)
			packetListEmpty.wait(&mutex);

		//如果释构标志被设置，则跳出循环，结束线程
		if(endThreadFlag)
		{
			//打印调试信息
			DWHERE();
			break;
		}
		//发送包队列非空
		if(!outPacketList.isEmpty())
		{
			//打印调试信息
			DWHERE();
			DPRINT("- - - > outPacketList.size():%d",outPacketList.size());

			QHashIterator<short, OutPacket *> iter(outPacketList);
			if(iter.hasNext())
			{
				iter.next();
				OutPacket *outPacketPtr = iter.value();

				//
				wingApp->packetProcesser->processOutPacket(outPacketPtr);

				if(outPacketPtr->ifNeedAck())
				{
					//如果需要应答，把它插入需应答队列
					needAckPacketList.insert(iter.key(), iter.value());

					//打印调试信息
					DWHERE();
					DPRINT("- - - > needAckPacketList.size():%d",needAckPacketList.size());

					//包出队
					outPacketList.remove(iter.key());
				}
				else
				{
					//包出队
					outPacketList.remove(iter.key());
				}

				//打印调试信息
				DWHERE();
				DPRINT("- - - > outPacketList.size():%d",outPacketList.size());
			}
		}
		//接收包队列非空
		if(!inPacketList.isEmpty())
		{
			//打印调试信息
			DWHERE();
			DPRINT("- - - > inPacketList.size():%d",inPacketList.size());

			QHashIterator<short, InPacket *> iter(inPacketList);
			if(iter.hasNext())
			{
				iter.next();
				InPacket *inPacketPtr = iter.value();
				//送出一个接收包给WingController处理
				wingApp->packetProcesser->processInPacket(inPacketPtr);

				//打印调试信息
				DWHERE();
				DPRINT("- - - > longMainPtr->packetProcesser->processInPacket(inPacketPtr)");

				//包出队
				inPacketList.remove(iter.key());
			}

			//打印调试信息
			DWHERE();
			DPRINT("- - - > inPacketList.size():%d",inPacketList.size());

		}

		mutex.unlock();
	}

}

void PacketStorage::appendInPacket(InPacket *inPacket)
{
	mutex.lock();
	//插入到收到队列里
	inPacketList.insert(inPacket->getSequence(), inPacket);
	//唤醒线程
	packetListEmpty.wakeOne();
	mutex.unlock();
}

void PacketStorage::appendInPacket(char *inStr, int32 len)
{
	mutex.lock();
	InPacket *inPacket = new InPacket((uint8 *)inStr, len);
	//插入到收到队列里
	inPacketList.insert(inPacket->getSequence(), inPacket);
	//唤醒线程
	packetListEmpty.wakeOne();
	mutex.unlock();

	SAFE_DELETE_ARRAY(inStr);
}

void PacketStorage::appendOutPacket(OutPacket *outPacket)
{
	mutex.lock();
	//插入到收到队列里
	outPacketList.insert(outPacket->getSequence(), outPacket);
	//唤醒线程
	packetListEmpty.wakeOne();
	mutex.unlock();
}

void PacketStorage::removeOutPacketByCom(unsigned short com)
{
	mutex.lock();
	if(!outPacketList.isEmpty())
	{
		//打印调试信息
		DWHERE();
		DPRINT("- - - > outPacketList.size():%d",outPacketList.size());

		OutPacket * outPacketPtr = NULL;
		QHashIterator<short, OutPacket *> iter(outPacketList);
		while(iter.hasNext())
		{
			iter.next();
			outPacketPtr = iter.value();

			if(outPacketPtr->getCommand() == com)
			{
				outPacketList.remove(iter.key());
				SAFE_DELETE(outPacketPtr);

				//打印调试信息
				DWHERE();
				DPRINT("- - - > outPacketList.size():%d",outPacketList.size());
			}
		}
	}
	mutex.unlock();
}

void PacketStorage::removeOutPacketBySeq(unsigned short seq)
{
	mutex.lock();
	if(!outPacketList.isEmpty())
	{
		//打印调试信息
		DWHERE();
		DPRINT("- - - > outPacketList.size():%d",outPacketList.size());

		OutPacket * outPacketPtr = NULL;
		QHashIterator<short, OutPacket *> iter(outPacketList);
		while(iter.hasNext())
		{
			iter.next();

			if(iter.key() == seq)
			{
				//打印调试信息
				DWHERE();
				DPRINT("- - - > outPacketList.size():%d",outPacketList.size());

				outPacketPtr = iter.value();
				outPacketList.remove(iter.key());
				SAFE_DELETE(outPacketPtr);
			}
		}
	}
	mutex.unlock();
}

void PacketStorage::removeNeedAckPacketByCom(unsigned short com)
{
	mutex.lock();
	if(!needAckPacketList.isEmpty())
	{
		//打印调试信息
		DWHERE();
		DPRINT("- - - > needAckPacketList.size():%d",needAckPacketList.size());

		OutPacket * outPacketPtr = NULL;
		QHashIterator<short, OutPacket *> iter(needAckPacketList);
		while(iter.hasNext())
		{
			iter.next();
			outPacketPtr = iter.value();

			if(outPacketPtr->getCommand() == com)
			{

				needAckPacketList.remove(iter.key());
				SAFE_DELETE(outPacketPtr);

				//打印调试信息
				DWHERE();
				DPRINT("- - - > needAckPacketList.size():%d",needAckPacketList.size());
			}
		}
	}
	mutex.unlock();
}

void PacketStorage::removeNeedAckPacketBySeq(unsigned short seq)
{
	mutex.lock();
	if(!needAckPacketList.isEmpty())
	{
		//打印调试信息
		DWHERE();
		DPRINT("- - - > needAckPacketList.size():%d",needAckPacketList.size());

		OutPacket * outPacketPtr = NULL;
		QHashIterator<short, OutPacket *> iter(needAckPacketList);
		while(iter.hasNext())
		{
			iter.next();

			if(iter.key() == seq)
			{
				outPacketPtr = iter.value();
				needAckPacketList.remove(iter.key());
				SAFE_DELETE(outPacketPtr);

				//打印调试信息
				DWHERE();
				DPRINT("- - - > needAckPacketList.size():%d",needAckPacketList.size());
			}
		}
	}
	mutex.unlock();
}

void PacketStorage::checkNeedAckList()
{
	static int needResendCount = 0;
	mutex.lock();
	if(checker->isActive())
		checker->stop();
	OutPacket *outPacketPtr;
	QHashIterator<short, OutPacket *> iter(needAckPacketList);
	while(iter.hasNext()&&needResendCount-->0)
	{
		iter.next();
		outPacketPtr = iter.value();
		if(outPacketPtr->ifNeedResend())
		{
			//
			wingApp->packetProcesser->processOutPacket(outPacketPtr);
		}
		else
		{
			needAckPacketList.remove(iter.key());
			//重发5次后再无应答，表明发送失败
			wingApp->packetProcesser->processNoAckPacket(outPacketPtr);
		}
	}
	needResendCount = needAckPacketList.count();
	if(!checker->isActive())
		checker->start(3000);
	//唤醒线程
	packetListEmpty.wakeOne();
	mutex.unlock();

}

void  PacketStorage::doKeepAlive()
{
	OutPacket *keepAlivePacket = wingApp->packetBuilder->buildKeepAliveRequestPacket();
	appendOutPacket(keepAlivePacket);
}

void PacketStorage::startKeepAliveTimer()
{
	if(!keepAliveTimer->isActive())
		keepAliveTimer->start(60000);
}

void PacketStorage::stopKeepAliveTimer()
{
	if(keepAliveTimer->isActive())
		keepAliveTimer->stop();
}

void PacketStorage::deleteAllInPacket()
{
	mutex.lock();
	if(!inPacketList.isEmpty())
	{
		InPacket *inPacketPtr;
		QHashIterator<short, InPacket *> iter(inPacketList);
		while(iter.hasNext())
		{
			iter.next();
			inPacketPtr = iter.value();
			SAFE_DELETE(inPacketPtr);
		}
	}
	mutex.unlock();
}

void PacketStorage::deleteAllOutPacket()
{
	mutex.lock();

	if(!outPacketList.isEmpty())
	{
		OutPacket * outPacketPtr;
		QHashIterator<short, OutPacket *> iter(outPacketList);
		while(iter.hasNext())
		{
			iter.next();
			outPacketPtr = iter.value();
			SAFE_DELETE(outPacketPtr);
		}
	}
	mutex.unlock();
}

void PacketStorage::deleteAllNeedAckPacket()
{
	mutex.lock();
	if(!needAckPacketList.isEmpty())
	{
		OutPacket *needAckPacketPtr;
		QHashIterator<short, OutPacket *> iter(needAckPacketList);
		while(iter.hasNext())
		{
			iter.next();
			needAckPacketPtr = iter.value();
			SAFE_DELETE(needAckPacketPtr);
		}
	}
	mutex.unlock();
}

void PacketStorage::deleteAllPacket()
{
	deleteAllOutPacket();
	deleteAllInPacket();
	deleteAllNeedAckPacket();
}

void PacketStorage::doConnect()
{
	checker= new QTimer(this);
	connect(checker, SIGNAL(timeout()), this, SLOT(checkNeedAckList()));
	checker->start(3000);

	keepAliveTimer = new QTimer(this);
	connect(keepAliveTimer, SIGNAL(timeout()), this, SLOT(doKeepAlive()));
}

