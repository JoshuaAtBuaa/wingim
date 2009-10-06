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

#include <QTreeWidgetItem>
#include <QMessageBox>
#include <QAction>
#include <QMenu>
#include "WingMainWindow.h"
#include "Wingdefines.h"
#include "WingDebug.h"
#include "WingUser.h"
#include "WingMain.h"
#include "EventStruct.h"
#include "WingDialogWindow.h"
#include "WingEventProcesser.h"
#include "GuiHandling.h"


WingTreeWidgetItem::WingTreeWidgetItem(QTreeWidget * parent)
		:QTreeWidgetItem(parent),buddyQQNum(0),msgBrowser(0)
{

}

WingTreeWidgetItem::~WingTreeWidgetItem()
{
	SAFE_DELETE(msgBrowser);
}

WingMainWindow::WingMainWindow(QWidget *parent, Qt::WindowFlags f) : QWidget(parent, f)
{
	setupUi(this);

	init();
	createActions();
}

WingMainWindow::~WingMainWindow()
{
	removeAndDeleteAllChildItem();

	//打印调试信息
	DWHERE();
}

void WingMainWindow::removeAndDeleteAllChildItem()
{
	for(int i=0; i < contactTreeView->topLevelItemCount(); i++)
	{
		WingTreeWidgetItem *topItem = (WingTreeWidgetItem *)contactTreeView->topLevelItem(i);
		QList<QTreeWidgetItem *> childList = topItem->takeChildren();
		while (!childList.isEmpty())
		{
			WingTreeWidgetItem *item = (WingTreeWidgetItem *)(childList.takeFirst());
			SAFE_DELETE(item);
		}
	}
}

WingTreeWidgetItem *WingMainWindow::findTreeItemByQQNum(unsigned int qqNum)
{

	for(int i=0; i < contactTreeView->topLevelItemCount(); i++)
	{
		WingTreeWidgetItem *topItem = (WingTreeWidgetItem *)contactTreeView->topLevelItem(i);
		for(int j=0; j < topItem->childCount(); j++)
		{
			WingTreeWidgetItem *childItem = (WingTreeWidgetItem *)topItem->child(j);
			if(childItem->buddyQQNum == qqNum)
				return childItem;
		}
	}
	return NULL;
}

void WingMainWindow::onItemDoubleClicked(QTreeWidgetItem * item, int column)
{
	//判断是不是 TopLevelItem，是则返回
	if(contactTreeView->indexOfTopLevelItem(item) != -1)
		return;

	WingTreeWidgetItem *myItem = (WingTreeWidgetItem *)item;
	emit itemDoubleClicked(myItem);

	//打印调试信息
	DWHERE();
	DPRINT("- - - > onItemDoubleClicked:%u",myItem->buddyQQNum);
}

void WingMainWindow::onAboutAction()
{
	 QMessageBox::about(0, tr("About"),QString("<center><font size=5><b><u>wing</u></b></font><br/></center>")+
	                    QString("<b>Version: 0.1.0 Beta<br/>") +
	                    QObject::tr("Copyright 2009 konglinglong<br/>") +
	                    QString("E-mail:<br/>konglinglong@gmail.com<br/>")+
	                    QString("Website:<br/><a href=\"http://sites.google.com/site/konglinglong/\">"
	                            "http://sites.google.com/site/konglinglong/</a><br/>")+
	                            QObject::tr("<br/><br/>This software is licenced under <br/> GPL version 2 published by<br/>"
	                               " the Free Software Foundation.<br></b>"));
}

void WingMainWindow::onAboutQtAction()
{
	QMessageBox::aboutQt (0, tr("About Qt"));
}

void WingMainWindow::onBugReportAction()
{
	 QMessageBox::about(0, tr("bug report"),
						 QObject::tr("<b>thank you for your eagerness!<br/>") +
						 QObject::tr("you can report a bug on the follow site:") +
						 QString("<br/><a href=\"http://groups.google.com/group/wingim?hl=zh-CN\">"
								 "http://groups.google.com/group/wingim?hl=zh-CN</a><br/>"));
}

void WingMainWindow::onSettingAction()
{

}

void WingMainWindow::onQuitAction()
{
	wingApp->guiHandling->logoutRequest();
}

void WingMainWindow::init()
{
	this->setWindowIcon(QPixmap(":/resources/trayIcon/yellowstar32.png"));
	this->move(950, 100);

	portrait->setIcon(QPixmap(":/resources/image/ubuntu128.png"));

	contactTreeView->header()->hide();

	WingTreeWidgetItem *topItem = new WingTreeWidgetItem();
	topItem->setText(0, QObject::tr("Friend List"));
	contactTreeView->insertTopLevelItem(0, topItem);

	topItem = new WingTreeWidgetItem();
	topItem->setText(0, QObject::tr("Stranger List"));
	contactTreeView->insertTopLevelItem(1, topItem);

	topItem = new WingTreeWidgetItem();
	topItem->setText(0, QObject::tr("Black List"));
	contactTreeView->insertTopLevelItem(2, topItem);

	connect(contactTreeView,SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)),this,SLOT(onItemDoubleClicked(QTreeWidgetItem*,int)));

}

void WingMainWindow::createActions()
{
	aboutAction = new QAction(QPixmap(":/resources/image/about.png"), tr("about"), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(onAboutAction()));

    aboutQtAction = new QAction(QPixmap(":/resources/image/aboutQt.png"), tr("aboutQT"), this);
    connect(aboutQtAction, SIGNAL(triggered()), this, SLOT(onAboutQtAction()));

    bugReportAction = new QAction(QPixmap(":/resources/image/bug.png"), tr("bug report"), this);
    connect(bugReportAction, SIGNAL(triggered()), this, SLOT(onBugReportAction()));

    settingAction = new QAction(QPixmap(":/resources/image/setting.png"), tr("setting"), this);
    connect(settingAction, SIGNAL(triggered()), this, SLOT(onSettingAction()));

    quitAction = new QAction(QPixmap(":/resources/image/quit.png"), tr("quit"), this);
    connect(quitAction, SIGNAL(triggered()), this, SLOT(onQuitAction()));

    mainMenu = new QMenu();
    mainMenu->addAction(aboutAction);
    mainMenu->addAction(aboutQtAction);
    mainMenu->addAction(bugReportAction);
    mainMenu->addAction(settingAction);
    mainMenu->addSeparator();
    mainMenu->addAction(quitAction);

    menuBtn->setMenu(mainMenu);
    connect(menuBtn, SIGNAL(clicked()), menuBtn, SLOT(showMenu()));
}
