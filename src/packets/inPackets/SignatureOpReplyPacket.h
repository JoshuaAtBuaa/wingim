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

#ifndef SIGNATUREOPREPLYPACKET_H_
#define SIGNATUREOPREPLYPACKET_H_

#include <list>
#include "Signature.h"
#include "Wingdefines.h"

class InPacket;
class SignatureOpReplyPacket
{
public:
	enum SIG_RESULT{
		SIG_MODIFY_SUCCEED,	//修改签名成功
		SIG_MODIFY_FAILED,	//修改签名失败
		SIG_GET_SUCCEED,	//获取签名成功
		SIG_GET_FAILED		//获取签名失败
	};
	SignatureOpReplyPacket();
	~SignatureOpReplyPacket();
	//
	void fromInPacket(InPacket *inPacket);
	//
	std::list<Signature> getSignatureList();

public:
	enum SIG_RESULT result;
	bool isUser;

private:
	std::list<Signature> sigList;

};

/*! \class SignatureOpReplyPacket
 *  \brief 签名应答包。
 */

#endif /* SIGNATUREOPREPLYPACKET_H_ */
