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

#ifndef WINGSYSTEMTRAY_H_
#define WINGSYSTEMTRAY_H_

#include <QWidget>
#include <QTimer>
#include <QSystemTrayIcon>

QT_BEGIN_NAMESPACE
class QIcon;
class QAction;
class QMenu;
QT_END_NAMESPACE

class WingMainWindow;
class WingDialogWindow;
class WingSystemTray : public QWidget
{
	Q_OBJECT

public:
	WingSystemTray(WingMainWindow *mainWind, WingDialogWindow *dialogWind, QWidget *parent = 0);
	~WingSystemTray();
	void showTray();
	void hideTray();

public slots:
	void startFlashTray();
	void stopFlashTray();
	void flashTray();

private slots:
	void onIconActivated(QSystemTrayIcon::ActivationReason reason);
	void setStatus();
	void logoutRequest();

private:
	void doConnect();
    void createActions();
    void createTrayIcon();

    QAction *onlineAction;
    QAction *callmeAction;
    QAction *invisibleAction;
    QAction *awayAction;
    QAction *busyAction;
    QAction *quitAction;
    QMenu *sysTrayMenu;

    QSystemTrayIcon *sysTray;
    QIcon trayIcon;

    QTimer trayFlashTimer;

    WingMainWindow *mainWindPtr;
    WingDialogWindow *dialogWindPtr;
};

/*! \class WingSystemTray
 *  \brief 系统托盘类。
 */

#endif /* WINGSYSTEMTRAY_H_ */
