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

#ifndef TOUCHREPLYPACKET_H_
#define TOUCHREPLYPACKET_H_

#include "Wingdefines.h"

class InPacket;
class TouchReplyPacket
{
public:
	//
	TouchReplyPacket();
	//
	~TouchReplyPacket();
	//
	void fromInPacket(InPacket *inPacketPtr);
	//
	uint16 getFlag();
	//
	uint32 getNewIP();
private:
	uint16 flag;
	uint32 newIP;
};

/*! \class TouchReplyPacket
 *  \brief 握手应答包。
 */

#endif /* TOUCHREPLYPACKET_H_ */
