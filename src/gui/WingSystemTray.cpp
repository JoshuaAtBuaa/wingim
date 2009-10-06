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

#include <QApplication>
#include <QAction>
#include <QIcon>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QPixmap>
#include "GuiHandling.h"
#include "WingSystemTray.h"
#include "WingMainWindow.h"
#include "WingDialogWindow.h"
#include "WingUser.h"
#include "WingMain.h"
#include "WingDebug.h"

WingSystemTray::WingSystemTray(WingMainWindow *mainWind, WingDialogWindow *dialogWind, QWidget *parent)
	:QWidget(parent),mainWindPtr(mainWind),dialogWindPtr(dialogWind)
{
	createActions();
	createTrayIcon();
	doConnect();
}

WingSystemTray::~WingSystemTray()
{
	//打印调试信息
	DWHERE();
}

void WingSystemTray::showTray()
{
	sysTray->show();
}

void WingSystemTray::hideTray()
{
	sysTray->hide();
}

void WingSystemTray::startFlashTray()
{
	if (!trayFlashTimer.isActive())
		trayFlashTimer.start(600);
}

void WingSystemTray::stopFlashTray()
{
	if (trayFlashTimer.isActive())
		trayFlashTimer.stop();

	sysTray->setIcon(trayIcon);
}

void WingSystemTray::flashTray()
{
	static bool flashFlag = true;
	if(flashFlag)
		sysTray->setIcon(QPixmap(":/resources/trayIcon/newmsg.png"));
	else
		sysTray->setIcon(QPixmap(""));
	flashFlag = !flashFlag;
}

void WingSystemTray::onIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
		case QSystemTrayIcon::DoubleClick:
		{
			if(trayFlashTimer.isActive())
			{
				stopFlashTray();
				dialogWindPtr->showNormal();
				dialogWindPtr->raise();
				dialogWindPtr->activateWindow();
			}
			else
			{
				if(mainWindPtr->isHidden())
				{
					mainWindPtr->showNormal();
					mainWindPtr->raise();
					mainWindPtr->activateWindow();
				}
				else
					mainWindPtr->hide();
			}

		}
			break;
		case QSystemTrayIcon::Trigger:
		{

		}
			break;
		default:
			;
    }
}

void WingSystemTray::setStatus()
{
	if(QObject::sender() == onlineAction)
	{
		wingApp->guiHandling->changeUserStatus(WingUser::online);
		trayIcon.addPixmap(onlineAction->icon().pixmap(32));
	}
	else if(QObject::sender() == callmeAction)
	{
		wingApp->guiHandling->changeUserStatus(WingUser::callme);
		trayIcon.addPixmap(callmeAction->icon().pixmap(32));
	}
	else if(QObject::sender() == invisibleAction)
	{
		wingApp->guiHandling->changeUserStatus(WingUser::invisible);
		trayIcon.addPixmap(invisibleAction->icon().pixmap(32));
	}
	else if(QObject::sender() == awayAction)
	{
		wingApp->guiHandling->changeUserStatus(WingUser::away);
		trayIcon.addPixmap(awayAction->icon().pixmap(32));
	}
	else if(QObject::sender() == busyAction)
	{
		wingApp->guiHandling->changeUserStatus(WingUser::busy);
		trayIcon.addPixmap(busyAction->icon().pixmap(32));
	}
	else
	{}

	sysTray->setIcon(trayIcon);
}

void WingSystemTray::logoutRequest()
{
	wingApp->guiHandling->logoutRequest();
}

void WingSystemTray::createActions()
{
    onlineAction = new QAction(QPixmap(":/resources/trayIcon/yellowstar32.png"), tr("online"), this);
    connect(onlineAction, SIGNAL(triggered()), this, SLOT(setStatus()));

    callmeAction = new QAction(QPixmap(":/resources/trayIcon/starcallme32.png"), tr("callme"), this);
    connect(callmeAction, SIGNAL(triggered()), this, SLOT(setStatus()));

    invisibleAction = new QAction(QPixmap(":/resources/trayIcon/starinvisible32.png"), tr("invisible"), this);
    connect(invisibleAction, SIGNAL(triggered()), this, SLOT(setStatus()));

    awayAction = new QAction(QPixmap(":/resources/trayIcon/staraway32.png"), tr("away"), this);
    connect(awayAction, SIGNAL(triggered()), this, SLOT(setStatus()));

    busyAction = new QAction(QPixmap(":/resources/trayIcon/starbusy32.png"), tr("busy"), this);
    connect(busyAction, SIGNAL(triggered()), this, SLOT(setStatus()));

    quitAction = new QAction(QPixmap(":/resources/image/quit.png"), tr("quit"), this);
    connect(quitAction, SIGNAL(triggered()), this, SLOT(logoutRequest()));

}

void WingSystemTray::createTrayIcon()
{
    sysTrayMenu = new QMenu(this);
    sysTrayMenu->addAction(onlineAction);
    sysTrayMenu->addAction(callmeAction);
    sysTrayMenu->addAction(invisibleAction);
    sysTrayMenu->addAction(awayAction);
    sysTrayMenu->addAction(busyAction);
    sysTrayMenu->addSeparator();
    sysTrayMenu->addAction(quitAction);

    trayIcon.addPixmap(QPixmap(":/resources/trayIcon/yellowstar32.png"));
    sysTray = new QSystemTrayIcon(this);
    sysTray->setContextMenu(sysTrayMenu);
    sysTray->setIcon(trayIcon);

}

void WingSystemTray::doConnect()
{
    connect(&trayFlashTimer, SIGNAL(timeout()), this, SLOT(flashTray()));
    connect(sysTray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(onIconActivated(QSystemTrayIcon::ActivationReason)));
}
