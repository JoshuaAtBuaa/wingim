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

#ifndef SIGNATURE_H_
#define SIGNATURE_H_

#include <string>
#include "Wingdefines.h"

class Signature
{
public:
	/*! 构造函数*/
	Signature();

	/*! 构造函数
	 * \param qq QQ号。
	 * \param mt 签名更新时间。
	 * \param sig 签名信息。
	 */
	Signature(uint32 qq, uint32 mt, std::string sig);

	/*! 释构函数*/
	~Signature();

	/*! 压入签名的各项信息
	 * \param buf 一个字符串指针，指向输入缓冲区。
	 * \param dataLen 一个整型指针，用于返回压入数据的长度。
	 */
	void putData(uint8 *buf, int32 *dataLen);

public:
	uint32 qqNum;			/*!< QQ帐号 。*/
	uint32 modifiedTime;	/*!< 签名更新的时间 。*/
	std::string signature;	/*!< 签名 。*/
};

/*! \class Signature
 *  \brief 这是一个用来保存签名信息的类。
 *
 * 在BuddyInfo和WingUser中被用作数据成员。
 */

#endif /* SIGNATURE_H_ */
