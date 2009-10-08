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

#include <QScrollBar>
#include <QDateTime>
#include <QCloseEvent>
#include "WingDialogWindow.h"
#include "WingMainWindow.h"
#include "SendIMPacketStuff.h"
#include "WingMain.h"
#include "Packet.h"
#include "PacketStorage.h"
#include "PacketBuilder.h"
#include "Wingdefines.h"
#include "WingUser.h"
#include "WingDebug.h"



WingTextBrowser::WingTextBrowser(QWidget *parent)
	: QTextBrowser(parent),buddyQQNum(0)
{

}

WingTextBrowser::~WingTextBrowser()
{
	//打印调试信息
	DWHERE();
	DPRINT("- - - > WingTextBrowser was destructed! qqNum:%u",buddyQQNum);
}

WingDialogWindow::WingDialogWindow(WingMainWindow *mainWind, QWidget *parent)
    : QWidget(parent),sysMsgBrowser(NULL),mainWindPtr(mainWind)
{
        setupUi(this);
        init();
}

WingDialogWindow::~WingDialogWindow()
{
	SAFE_DELETE(sysMsgBrowser);

	//打印调试信息
	DWHERE();
}

WingTextBrowser *WingDialogWindow::findBrowserByQQNum(unsigned int qqNum)
{
	WingTextBrowser *browser = NULL;
	for(int i=0; i<tabWidget->count(); i++)
	{
		browser = (WingTextBrowser *)tabWidget->widget(i);
		if(browser && qqNum==browser->buddyQQNum)
		{
			return browser;
		}
	}
	return NULL;
}

void WingDialogWindow::onClearButtonClicked()
{
	textInput->clear();
}

void WingDialogWindow::onSendButtonClicked()
{
	QString outMsg = textInput->toPlainText();
	WingTextBrowser *browser = (WingTextBrowser *)tabWidget->currentWidget();
	if(!browser || outMsg.isEmpty())
		return;
	if(outMsg.count() > 1024)
	{
		browser->setTextColor(QColor(255, 175, 137));
		browser->append(QObject::tr("too many characters!\n"));
		return;
	}

	QDateTime dt = QDateTime::currentDateTime();
	browser->setTextColor(Qt::blue);
	browser->append("< Me > "+dt.time().toString()+" "+dt.date().toString(Qt::ISODate));
	browser->setTextColor(Qt::black);
	browser->append(outMsg);
	QScrollBar *bar = textInput->verticalScrollBar();
	bar->setValue (bar->maximum ());
	textInput->clear();

	OutPacket *outPacket = wingApp->packetBuilder->buildSendMsgRequestPacket(browser->buddyQQNum, outMsg);
	wingApp->packetStorage->appendOutPacket(outPacket);

}

void WingDialogWindow::onTreeItemDoubleClicked(WingTreeWidgetItem *item)
{
	//打印调试信息
	DWHERE();
	DPRINT("- - - > onItemDoubleClicked:%u",item->buddyQQNum);

	if(item->msgBrowser)
	{
		if(tabWidget->indexOf(item->msgBrowser) == -1)
			tabWidget->addTab(item->msgBrowser, item->icon(0), item->text(0));
	}
	else
	{
		item->msgBrowser = new WingTextBrowser();
		item->msgBrowser->buddyQQNum = item->buddyQQNum;
		tabWidget->addTab(item->msgBrowser, item->icon(0), item->text(0));
	}
	tabWidget->setCurrentWidget(item->msgBrowser);

	if(this->isHidden())
		this->show();
}

void WingDialogWindow::onTabCloseRequested(int index)
{
	tabWidget->removeTab(index);
	if(tabWidget->count() == 0)
		this->hide();
}

void WingDialogWindow::onCurrentChanged(int index)
{
	if(index == -1)
		return;
	setWindowTitle(QObject::tr("chatting with <")+tabWidget->tabText(index)+QObject::tr(">..."));
	tabWidget->setTabTextColor(index, Qt::black);
}

void WingDialogWindow::init()
{
	this->setWindowIcon(QPixmap(":/resources/image/dialog.png"));
	this->move(450, 250);

    tabWidget->clear();
	tabWidget->setTabsClosable(true);
	tabWidget->setMovable(true);
	tabWidget->setElideMode(Qt::ElideRight);

	connect(sendButton,SIGNAL(clicked()),this,SLOT(onSendButtonClicked()));
	connect(clearButton,SIGNAL(clicked()),this,SLOT(onClearButtonClicked()));
	connect(tabWidget,SIGNAL(tabCloseRequested(int)),SLOT(onTabCloseRequested(int)));
	connect(tabWidget,SIGNAL(currentChanged(int)),this,SLOT(onCurrentChanged(int)));
}
