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

#ifdef _WIN32
#include <winsock.h>
#else
#include <cstring>
#include <netdb.h>
#endif

#include <QUdpSocket>
#include "WingMain.h"
#include "WingDebug.h"
#include "NetworkManager.h"
#include "Wingdefines.h"
#include "EventStruct.h"
#include "WingEventProcesser.h"
#include "PacketStorage.h"

NetworkManager::NetworkManager(QObject * parent)
	:QObject(parent), networkReady(false), dnsOK(false)
{
	udpSocket = new QUdpSocket(this);
	uint16 port = 2050;
	while(!udpSocket->bind(port))
		port++;
	//打印调试信息
	DWHERE();
	DPRINT("- - - > UdpSocket bind to:%d!", port);
}
//
NetworkManager::~NetworkManager()
{
	//打印调试信息
	DWHERE();

	udpSocket->close();
	SAFE_DELETE(udpSocket);
}
//
bool NetworkManager::DNS()
{
	struct hostent *host;
	char **pp;
	if(dnsOK)
		return true;
	//解释域名 sz8.tencent.com
	host = gethostbyname("sz8.tencent.com");
	if(!host)
		return false;
	pp = host->h_addr_list;
	if(!pp)
		return false;

	unsigned long tempIP = *((unsigned int *)*pp);
	//把网络序转换成主机序
	tempIP = ntohl(tempIP);
	setServerAddress(QHostAddress(tempIP));
	dnsOK = true;
	return true;
}
//
void NetworkManager::startConnect()
{

	for(int i = 0; i < 10; i++)
		if(DNS())
			break;

	if(!dnsOK)
	{
		networkReady = false;
		//域名解释失败，由事件处事器进行处理
		WING_EVENT *domainError = new WING_EVENT(WING_EVENT::netInitFailed,"NetworkManager","Domain interpretation error!",0);
		wingApp->eventProcesser->longEventHandling(domainError);
		return;
	}
	connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
	networkReady = true;

	//网络连接成功
	WING_EVENT *netOK = new WING_EVENT(WING_EVENT::netInitSucceed,"NetworkManager","network connect succeed!",0);
	wingApp->eventProcesser->longEventHandling(netOK);
}
//
void NetworkManager::stopConnect()
{
	if(networkReady)
	{
		disconnect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
		networkReady = false;
	}
}
//
bool NetworkManager::isNetworkReady()
{
	return networkReady;
}
//
void NetworkManager::send(const uint8 *outStr, int len)
{
	int sentLen = 0;
	sentLen = udpSocket->writeDatagram((const char *)outStr, len, serverAddress, 8000);
	if(sentLen != len)
	{
		//打印调试信息
		DWHERE();
		DPRINT("- - - > msgdata sent failed");
	}
	else
	{
		//打印调试信息
		DWHERE();
		DPRINT("- - - > msgdata has be sent! msgLength:%d",len);
	}


	SAFE_DELETE_ARRAY(outStr);
}
//设置服务器IP地址
void NetworkManager::setServerAddress(QHostAddress addr)
{
	serverAddress = addr;
	//打印调试信息
	DWHERE();
	DPRINT("- - - > serverAddress has be set:%s",serverAddress.toString().toStdString().c_str());
}
//收到信息后执行这个槽
void NetworkManager::processPendingDatagrams()
{
	//QByteArray datagram;
	int dataSize = 0;
	if(udpSocket->hasPendingDatagrams())
	{
		dataSize = udpSocket->pendingDatagramSize();
		char *inStr = new char[dataSize];
		udpSocket->readDatagram(inStr, dataSize);

		//打印调试信息
		DWHERE();
		DPRINT("- - - > receive msgdata! dataLength:%d",dataSize);

		//判断是不是QQ数据包，以0x02开始，0x03结尾
		if(inStr[0] == 0x02 && inStr[dataSize-1] == 0x03)
			wingApp->packetStorage->appendInPacket(inStr, dataSize);
		else
			SAFE_DELETE_ARRAY(inStr);
	}
}
