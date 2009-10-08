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

#include <QCloseEvent>
#include <QMessageBox>
#include <QTreeWidgetItem>
#include "WingDebug.h"
#include "WingMain.h"
#include "EventStruct.h"
#include "WingEventProcesser.h"
#include "WingLoginWindow.h"
#include "PacketBuilder.h"

WingLoginWindow::WingLoginWindow(QWidget *parent, Qt::WindowFlags f) : QWidget(parent, f)
{
	setupUi(this);
	init();
}

WingLoginWindow::~WingLoginWindow()
{
	//打印调试信息
	DWHERE();
}

void WingLoginWindow::onLoginRequest()
{
	loginBtn->setEnabled(false);
	if(accInput->text().isEmpty() || pwdInput->text().isEmpty())
	{ QMessageBox::warning(this, tr("warning"),
	                       tr("Account or password can not be empty!"),
	                       QMessageBox::Ok);

		loginBtn->setEnabled(true);
		return;
	}
	WING_EVENT *loginEvent = new WING_EVENT(WING_EVENT::loginRequest, "LoginWindow", "request login", 0);
	wingApp->eventProcesser->longEventHandling(loginEvent);
}

void WingLoginWindow::init()
{
	//只能输入0～9，最多10个数字
	QRegExp rx_port("[0-9]{0,10}");
	QValidator *validator_port = new QRegExpValidator(rx_port, this);
	accInput->setValidator(validator_port);

	statusBox->addItem(tr("online"), 10);
	statusBox->addItem(tr("invisible"), 40);
	statusBox->addItem(tr("away"), 30);

	netSetBox->addItem(QString("UDP"), 0);
	netSetBox->addItem(QString("TCP"), 1);

	connect(loginBtn, SIGNAL(clicked()), this, SLOT(onLoginRequest()));

	this->setWindowIcon(QPixmap(":/resources/trayIcon/yellowstar.png"));
	this->move(450, 250);
}
