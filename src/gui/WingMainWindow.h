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

#ifndef WINGMAINWINDOW_H_
#define WINGMAINWINDOW_H_

#include <QWidget>
#include "ui_MainWindow.h"

class WingTextBrowser;
class WingTreeWidgetItem : public QTreeWidgetItem
{
public:
	WingTreeWidgetItem(QTreeWidget * parent = 0);
	~WingTreeWidgetItem();

public:
	unsigned int buddyQQNum;
	WingTextBrowser *msgBrowser;
};


class QAction;
class QMenu;
class QTreeWidgetItem;
class WingTreeWidgetItem;
class WingMainWindow : public QWidget, public Ui::MainWindow
{
	Q_OBJECT

public:
	WingMainWindow(QWidget *parent = 0, Qt::WindowFlags f = Qt::WindowMinimizeButtonHint |Qt::WindowCloseButtonHint);
	~WingMainWindow();
	WingTreeWidgetItem *findTreeItemByQQNum(unsigned int qqNum);
	void removeAndDeleteAllChildItem();

public slots:
	void onItemDoubleClicked(QTreeWidgetItem * item, int column);
	void onAboutAction();
	void onAboutQtAction();
	void onBugReportAction();
	void onSettingAction();
	void onQuitAction();

signals:
	void itemDoubleClicked(WingTreeWidgetItem *item);

private:
	void init();
	void createActions();

private:
    QAction *aboutAction;
    QAction *aboutQtAction;
    QAction *bugReportAction;
    QAction *settingAction;
    QAction *quitAction;
    QMenu *mainMenu;

};

/*! \class WingMainWindow
 *  \brief 主窗口类。
 */

#endif /* WINGMAINWINDOW_H_ */
