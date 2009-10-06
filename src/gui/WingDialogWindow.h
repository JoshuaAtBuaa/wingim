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

#ifndef WINGDIALOGWINDOW_H
#define WINGDIALOGWINDOW_H

#include <QTextBrowser>
#include "ui_DialogWindow.h"

class WingTextBrowser : public QTextBrowser
{
    Q_OBJECT

public:
    WingTextBrowser(QWidget *parent = 0);
    ~WingTextBrowser();
public:
	unsigned int buddyQQNum;
};


class WingTreeWidgetItem;
class WingMainWindow;
class WingDialogWindow : public QWidget, public Ui::DialogWindow
{
    Q_OBJECT

public:
    /*! 构造函数 */
    WingDialogWindow(WingMainWindow *mainWind, QWidget *parent = 0);

    /*! 释构函数 */
    ~WingDialogWindow();

	/*! 通过qq号码找到消息窗口
	 * \param qqNum
	 * \return 找到则返回一个WingTextBrowser指针，否则返回NULL
	 */
	WingTextBrowser *findBrowserByQQNum(unsigned int qqNum);

public slots:
	/*! 槽，发送按钮被按下时会被调用
	 */
	void onSendButtonClicked();

	/*! 槽，清空按钮被按下时会被调用
	 */
	void onClearButtonClicked();

	/*! 槽，双击树表项时会被调用
	 * \param item
	 */
	void onTreeItemDoubleClicked(WingTreeWidgetItem *item);

	/*! 槽，按下tab的关闭按钮时会被调用
	 * \param index
	 */
	void onTabCloseRequested(int index);

	/*! 槽，当前的tab改变时会被调用
	 * \param index
	 */
	void onCurrentChanged(int index);

private:
	/*! 初始化
	 */
    void init();

public:
    WingTextBrowser *sysMsgBrowser;		/*!< 用于显示系统消息的窗口 \sa WingTextBrowser */

private:
    WingMainWindow *mainWindPtr;	/*!< 一个主窗口指针，主要是为了方便操作  */
};

/*! \class WingDialogWindow
 *  \brief 聊天窗口类
 *
 */

#endif // WINGDIALOGWINDOW_H
