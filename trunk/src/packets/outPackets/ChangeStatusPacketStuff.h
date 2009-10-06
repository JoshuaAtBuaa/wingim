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

#ifndef CHANGESTATUSPACKETSTUFF_H_
#define CHANGESTATUSPACKETSTUFF_H_

#include "Wingdefines.h"

class InPacket;
class OutPacket;
class ChangeStatusPacketStuff
{
public:
	//
	ChangeStatusPacketStuff();
	//
	~ChangeStatusPacketStuff();
	//
	void setStatus(uint8 status);
	//
	void process();
	//
	OutPacket *toOutPacket();
private:
	uint8 newStatus;
	uint8 *bodyBuf;
};

/*! \class ChangeStatusPacketStuff
 *  \brief 改变状态包。
 */

#endif /* CHANGESTATUSPACKETSTUFF_H_ */
