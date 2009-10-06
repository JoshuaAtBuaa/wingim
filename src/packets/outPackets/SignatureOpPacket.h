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

#ifndef SIGNATUREOPPACKET_H_
#define SIGNATUREOPPACKET_H_

#include <list>
#include "Wingdefines.h"
#include "Signature.h"


class OutPacket;
class SignatureOpPacket
{
public:
	enum QQ_SUB_CMD{
		MODIFY_SIGNATURE = 0x01,	//修改个性签名
		DELETE_SIGNATURE = 0x02,	//删除个性签名
		GET_SIGNATURE = 0x03		//获取个性签名
	};
	SignatureOpPacket(enum QQ_SUB_CMD cmd);
	~SignatureOpPacket();
	//
	void putUserSignature(const Signature &sig);
	//
	void putSignatureList(std::list<Signature> sigList);
	//
	void process();
	//
	OutPacket *toOutPacket();

public:
	//nextQQ下个起始QQ号+1
	static uint32 nextQQ;

private:
	//在获取签名操作时才有效，表示要获取的个数
	int num;
	uint8 *bodyBuf;
	int bodyLen;
	enum QQ_SUB_CMD subCmd;
};

/*! \class SignatureOpPacket
 *  \brief 签名操作包。
 */

#endif /* SIGNATUREOPPACKET_H_ */
