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

#include <string>
#include <QObject>
#include <QMessageBox>
#include <QTextCodec>
#include <QScrollBar>
#include <QList>
#include <QDateTime>
#include <QProcess>
#include <QSound>
#include "GuiHandling.h"
#include "WingMain.h"
#include "WingDebug.h"
#include "Wingdefines.h"
#include "BuddyInfo.h"
#include "WingUser.h"
#include "WingLoginWindow.h"
#include "WingMainWindow.h"
#include "ReceiveIMPacket.h"
#include "WingDialogWindow.h"
#include "WingSystemTray.h"
#include "WingTabWidget.h"
#include "ToolKit.h"
#include "EventStruct.h"
#include "WingEventProcesser.h"
#include "PacketBuilder.h"
#include "PacketStorage.h"


class WingTreeWidgetItem;
GuiHandling::GuiHandling(QObject *parent)
	: QObject(parent)
{
	loginWindow = new WingLoginWindow();
	mainWindow = new WingMainWindow();
	dialogWindow = new WingDialogWindow(mainWindow);
	systemTray = new WingSystemTray(mainWindow, dialogWindow, mainWindow);

	dialogWindow->installEventFilter(this);
	mainWindow->installEventFilter(this);

	init();

	setSkin();

	//systemTray->showTray();
	//dialogWindow->show();
	//mainWindow->show();

	loginWindow->show();
}

GuiHandling::~GuiHandling()
{
	SAFE_DELETE(loginWindow);
	SAFE_DELETE(mainWindow);
	SAFE_DELETE(dialogWindow);
	//SAFE_DELETE(systemTray);

	//打印调试信息
	DWHERE();
}

void GuiHandling::init()
{
	connect(mainWindow,SIGNAL(itemDoubleClicked(WingTreeWidgetItem *)),dialogWindow,SLOT(onTreeItemDoubleClicked(WingTreeWidgetItem *)));
}

void GuiHandling::loginSucceed()
{
	wingApp->wingUser->setCurrentStatus(WingUser::online);

	loginWindow->hide();
	systemTray->showTray();
	mainWindow->show();
	SAFE_DELETE(loginWindow);
}

uint32 GuiHandling::getLoginQQ()
{
	return loginWindow->accInput->text().toULong();
}

WingUser::UserStatus GuiHandling::getStatusSetting()
{
	int currentIndex = loginWindow->statusBox->currentIndex();
	return (WingUser::UserStatus)loginWindow->statusBox->itemData(currentIndex).toUInt();
}

int GuiHandling::getNetTypeSetting()
{
	int currentIndex = loginWindow->netSetBox->currentIndex();
	return loginWindow->netSetBox->itemData(currentIndex).toInt();
}

void GuiHandling::loginFailed()
{
	QMessageBox::warning(loginWindow, QObject::tr("ERROR"),
	                     QObject::tr("Login Failed !"),
		                       QMessageBox::Ok);

	wingApp->wingUser->setCurrentStatus(WingUser::offline);
	if(loginWindow)
		loginWindow->loginBtn->setEnabled(true);
}

void GuiHandling::needVerify()
{
	QMessageBox::warning(loginWindow, QObject::tr("ERROR"),
	                     QObject::tr("Need to be verified ! But the function has not be finished.:-("),
		                       QMessageBox::Ok);

	wingApp->wingUser->setCurrentStatus(WingUser::offline);
	qApp->quit();
}

void GuiHandling::needActivated()
{
	 QMessageBox::warning(loginWindow, QObject::tr("ERROR"),
						 QObject::tr("<b>your QQ account need to be activated !<br/>") +
						 QObject::tr("activated website:") +
						 QString("<br/><a href=\"http://aq.qq.com/cn/services/abnormal/abnormal_index\">"
								 "http://aq.qq.com/cn/services/abnormal/abnormal_index</a><br/>"),
						QMessageBox::Ok);

	wingApp->wingUser->setCurrentStatus(WingUser::offline);
	if(loginWindow)
		loginWindow->loginBtn->setEnabled(true);
}

void GuiHandling::passwdError()
{
	QMessageBox::warning(loginWindow, QObject::tr("ERROR"),
	                     QObject::tr("password error !"),
		                       QMessageBox::Ok);

	wingApp->wingUser->setCurrentStatus(WingUser::offline);
	if(loginWindow)
		loginWindow->loginBtn->setEnabled(true);
}

void GuiHandling::fallLine()
{
	QMessageBox::warning(0, QObject::tr("WARNING"),
	                     QObject::tr("wing has fall line !"),
		                       QMessageBox::Ok);

	wingApp->wingUser->setCurrentStatus(WingUser::offline);
	dialogWindow->hide();
	mainWindow->removeAndDeleteAllChildItem();
	systemTray->hideTray();
	mainWindow->hide();
	if(NULL == loginWindow)
		loginWindow = new WingLoginWindow(0);
	loginWindow->show();
}

void GuiHandling::logoutRequest()
{
	dialogWindow->hide();
	systemTray->hideTray();

	WingUser::UserStatus currentStatus = wingApp->wingUser->getCurrentStatus();
	int i = 2;
	while(currentStatus != WingUser::offline && i--)
	{
		//打印调试信息
		DWHERE();

		WING_EVENT *logoutEvent = new WING_EVENT(WING_EVENT::logoutRequest,"WingMainWindow","request logout!",0);
		wingApp->eventProcesser->longEventHandling(logoutEvent);
	}
	qApp->quit();
}

void GuiHandling::fetchBuddyList(QMap<unsigned int, BuddyInfo *> buddyList)
{
	WingTreeWidgetItem *topItem = (WingTreeWidgetItem *)mainWindow->contactTreeView->topLevelItem(0);

	QMapIterator<unsigned int, BuddyInfo *> iter(buddyList);
	while(iter.hasNext())
	{
		iter.next();

		BuddyInfo *buddyInfo = iter.value();
		WingTreeWidgetItem *item = new WingTreeWidgetItem();
		QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB18030"));
		item->setIcon(0 ,QPixmap(":/resources/head/ubuntu1_64off.png"));
		item->setText(0, QString::fromLocal8Bit((char *)(buddyInfo->nick)));
		item->buddyQQNum = buddyInfo->qqNum;
		topItem->addChild(item);
	}

	//打印调试信息
	DWHERE();
	DPRINT("- - - > have got all buddy list! count:%d",buddyList.count());
}

void GuiHandling::fetchUserInfo()
{
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB18030"));
	std::string nick = wingApp->wingUser->at(WingUser::Info_nick);
	QString nickName = QString::fromLocal8Bit(nick.c_str());
	mainWindow->nickName->setText(nickName);

}

void GuiHandling::friendChangeStatus(uint32 qq, uint8 sta)
{
	WingTreeWidgetItem *item = (WingTreeWidgetItem *)mainWindow->findTreeItemByQQNum(qq);
	if(item)
	{
		WingTreeWidgetItem *topItem = (WingTreeWidgetItem *)item->parent();
		if(10 == sta || 30 == sta || 40 == sta)
		{
			topItem->removeChild(item);
			topItem->insertChild(0, item);
			item->setIcon(0 ,QPixmap(":/resources/head/ubuntu1_64.png"));
		}
		else
		{
			topItem->removeChild(item);
			topItem->addChild(item);
			item->setIcon(0 ,QPixmap(":/resources/head/ubuntu1_64off.png"));
		}

		WingTabWidget *tabWidget = dialogWindow->tabWidget;
		int index = -1;
		if((index = tabWidget->indexOf(item->msgBrowser)) == -1)
			return;
		tabWidget->setTabIcon(index, item->icon(0));
	}
}

void GuiHandling::putNewSignature(std::string sig)
{
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB18030"));
	QString signature = QString::fromLocal8Bit(sig.c_str());
	mainWindow->signature->setText(signature);
}

void GuiHandling::imFromUser(ReceiveIMPacket *imPacket)
{

	unsigned int sender = imPacket->normalHeader->sender;

	WingTreeWidgetItem *item = mainWindow->findTreeItemByQQNum(sender);
	if(item)
	{
		if(NULL == item->msgBrowser)
		{
			item->msgBrowser = new WingTextBrowser();
			item->msgBrowser->buddyQQNum = sender;
		}

		WingTabWidget *tabWidget = dialogWindow->tabWidget;
		int index = -1;
		if(tabWidget->indexOf(item->msgBrowser) == -1)
		{
			index = tabWidget->addTab(item->msgBrowser, item->icon(0), item->text(0));
		}
		else
			index = tabWidget->indexOf(item->msgBrowser);
		if(tabWidget->currentWidget() != item->msgBrowser)
			tabWidget->setTabTextColor(index, Qt::magenta);

		if(dialogWindow->isHidden())
			systemTray->startFlashTray();
		else
			qApp->alert(dialogWindow);


		QDateTime dt;
		dt.setTime_t(imPacket->normalHeader->sendTime);

		QString inMsg = ToolKit::GBctrToUTF8((char *)imPacket->normalIM->msgBuf);

		item->msgBrowser->setTextColor(Qt::darkGreen);
		item->msgBrowser->append(QString("<")+item->text(0)+"> "+dt.time().toString()+" "+dt.date().toString(Qt::ISODate));
		item->msgBrowser->setTextColor(Qt::black);
		item->msgBrowser->append(inMsg);
		QScrollBar *bar = item->msgBrowser->verticalScrollBar ();
		bar->setValue(bar->maximum ());

		palySound();
	}

	SAFE_DELETE(imPacket);

	//打印调试信息
	DWHERE();
	DPRINT("- - - > imFromUser");
}

void GuiHandling::imFromSys(ReceiveIMPacket *imPacket)
{
	SysMessage *sysMsg = imPacket->sysMessage;

	WingTextBrowser *sysMsgBrowser = dialogWindow->sysMsgBrowser;
	if(NULL == sysMsgBrowser)
	{
		sysMsgBrowser = new WingTextBrowser();
		sysMsgBrowser->buddyQQNum = 10000;
	}

	WingTabWidget *tabWidget = dialogWindow->tabWidget;
	int index = -1;
	if(tabWidget->indexOf(sysMsgBrowser) == -1)
	{
		index = tabWidget->addTab(sysMsgBrowser, QObject::tr("system message"));
	}
	else
		index = tabWidget->indexOf(sysMsgBrowser);
	if(tabWidget->currentWidget() != sysMsgBrowser)
		tabWidget->setTabTextColor(index, Qt::magenta);

	if(dialogWindow->isHidden())
		systemTray->startFlashTray();
	else
		qApp->alert(dialogWindow);

	QDateTime dt = QDateTime::currentDateTime();

	QString inMsg = ToolKit::GBctrToUTF8((char *)sysMsg->msgBuf);

	sysMsgBrowser->setTextColor(Qt::darkGreen);
	sysMsgBrowser->append(QString("<")+QObject::tr("10000")+"> "+dt.time().toString()+" "+dt.date().toString(Qt::ISODate));
	sysMsgBrowser->setTextColor(Qt::black);
	sysMsgBrowser->append(inMsg);
	QScrollBar *bar = sysMsgBrowser->verticalScrollBar ();
	bar->setValue(bar->maximum ());

	palySound();

	//打印调试信息
	DWHERE();
	DPRINT("- - - > imFromSys");

	SAFE_DELETE(imPacket);


}

void GuiHandling::imFromCluster(ReceiveIMPacket *imPacket)
{
	SAFE_DELETE(imPacket);

	//打印调试信息
	DWHERE();
	DPRINT("- - - > imFromCluster");
}

void GuiHandling::imFromSms(ReceiveIMPacket *imPacket)
{
	SAFE_DELETE(imPacket);

	//打印调试信息
	DWHERE();
	DPRINT("- - - > imFromSms");
}

void GuiHandling::changeUserStatus(uint8 status)
{
	if(status == wingApp->wingUser->getCurrentStatus())
		return;
	OutPacket *outPacket = wingApp->packetBuilder->buildChangeStatusRequestPacket(status);
	wingApp->packetStorage->appendOutPacket(outPacket);
	wingApp->wingUser->setCurrentStatus((WingUser::UserStatus)status);
}

void GuiHandling::palySound()
{
#ifdef Q_OS_LINUX
	QProcess *playerProcess = new QProcess(this);
	QStringList arguments;
	arguments << "../resources/sound/incomingMsg.wav";
	playerProcess->start(QString("aplay"), arguments);
	if(!playerProcess->waitForStarted(100))
	{
		//打印调试信息
		DWHERE();
		DPRINT("- - - > can not play the sound!");
	}
#endif

#ifdef Q_OS_WIN32
	QSound ring("../resources/sound/incomingMsg.wav");
	ring.play();
#endif
}

void GuiHandling::setSkin()
{
	QFile file(":/resources/skin/default.qss");
	file.open(QFile::ReadOnly);
	QString styleSheet = QString::fromUtf8(file.readAll());
	qApp->setStyleSheet(styleSheet);
}

bool GuiHandling::eventFilter(QObject *target, QEvent *event)
{
	if(target == mainWindow)
	{
        if (event->type() == QEvent::Close)
        {
        	mainWindow->hide();
        	event->ignore();
            return true;
        }
	}
	if(target == dialogWindow)
	{
        if (event->type() == QEvent::Close)
        {
        	dialogWindow->hide();
        	event->ignore();
            return true;
        }
	}

	return QObject::eventFilter(target, event);
}
