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

#ifndef FRIENDCHANGESTATUSPACKET_H_
#define FRIENDCHANGESTATUSPACKET_H_

#include "Wingdefines.h"

class InPacket;
class OutPacket;
class FriendChangeStatusPacket
{
public:
	//
	FriendChangeStatusPacket();
	//
	~FriendChangeStatusPacket();
	//
	void fromInPacket(InPacket *inPacketPtr);
	//
	uint32 getSender();
	//
	uint8 getNewStatus();
private:
	uint32 sender;
	uint8 status;
};

/*! \class FriendChangeStatusPacket
 *  \brief 好友改变状态包。
 */

#endif /* FRIENDCHANGESTATUSPACKET_H_ */
