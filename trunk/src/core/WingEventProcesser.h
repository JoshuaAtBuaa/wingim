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

#ifndef WINGEVENTFILTER_H_
#define WINGEVENTFILTER_H_

#include <QObject>

class WING_EVENT;
class WingEventProcesser : public QObject
{
	Q_OBJECT
public:
	WingEventProcesser(QObject *parent = NULL);
	~WingEventProcesser();

public:
	void longEventHandling(WING_EVENT *event);

signals:
	void longEventHandlingSignal(WING_EVENT *event);

private slots:
	void longEventHandlingSlot(WING_EVENT *event);

private:
	void processLoginRequestEvent(WING_EVENT *event);
	void processNeedVerifyEvent(WING_EVENT *event);
	void processNeedActivatedEvent(WING_EVENT *event);
	void processPasswdErrorEvent(WING_EVENT *event);
	void processNetInitSucceedEvent(WING_EVENT *event);
	void processLoginSucceedEvent(WING_EVENT *event);
	void processLoginFailedEvent(WING_EVENT *event);
	void processFallLineEvent(WING_EVENT *event);
	void processGotAllBuddyListEvent(WING_EVENT *event);
	void processGotBuddyOnlineListEvent(WING_EVENT *event);
	void processGotUserInfoEvent(WING_EVENT *event);
	void processGotUserSigEvent(WING_EVENT *event);
	void processLogoutRequestEvent(WING_EVENT *event);

};

/*! \class WingEventProcesser
 *  \brief 这是一个用来处理各类事件的类。
 *
 *  wing产生的事件都由这个类进行处理。
 */

#endif /* WINGEVENTFILTER_H_ */
