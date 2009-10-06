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

#ifndef USERINFO_H
#define USERINFO_H

#include <string>
#include <vector>
#include "Signature.h"


class WingUser
{
public:

	/*! 一个枚举类型
	 * 用来表示登陆模式或当前登陆状态。
	 */
	enum UserStatus {online = 0x0A,		/*!< 在线  */
					callme = 0x3C,		/*!< Q我  */
					offline = 0x14,		/*!< 离线  */
					away = 0x1E,		/*!< 离开  */
					invisible = 0x28,	/*!< 隐身  */
					busy = 0x32,		/*!< 忙碌  */
					quiet = 0x46		/*!< 静音  */
					};

	/*! 一个枚举类型
	 * 用于索引用户信息。
	 */
	enum InfoIndex{Info_qqID,       Info_nick,     Info_country,  Info_province,  Info_zipcode,
					Info_address,    Info_telephone, Info_age,      Info_gender,    Info_name,
					Info_email,      Info_pagerSn,   Info_pagerNum, Info_pagerSp,   Info_pagerBaseNum,
					Info_pagerType,  Info_occupation,Info_homepage, Info_authType,  Info_unknown1,
					Info_unknown2,   Info_face,      Info_mobile,   Info_mobileType,Info_intro,
					Info_city,       Info_unknown3,  Info_unknown4, Info_unknown5,  Info_openHp,
					Info_openContact,Info_college,   Info_horoscope,Info_zodiac,    Info_blood,
					Info_qqShow,     Info_unknown6  };

	/*! 构造函数 */
	WingUser();

	/*! 释构函数 */
	~WingUser();

	/*! 初始化 */
	void init();

	/*! 获取登陆模式
	 * \param sta
	 * \sa UserStatus
	 */
	void setLoginMode(const UserStatus sta);

	/*! 获取登陆模式
	 * \return 返回用户的登陆模式。
	 * \sa UserStatus
	 */
	UserStatus getLoginMode();

	/*! 设置当前状态
	 * \param sta
	 * \sa UserStatus
	 */
	void setCurrentStatus(const UserStatus sta);

	/*! 获取当前状态
	 * \return 返回用户的当前状态。
	 * \sa UserStatus
	 */
	UserStatus getCurrentStatus();

	/*! 压入好友的各项信息
	 * \param buf 一个字符串指针，指向输入缓冲区。
	 * \param dataLen 一个整型指针，用于返回压入数据的长度。
	 */
	void putData(const unsigned char *buf, const int len);

	/*! 由索引index取得用户的各项信息
	 * \param index 一个enum类型值。
	 * \return 返回该项信息的字符串值。
	 * \sa InfoIndex
	 */
	const std::string &at(const InfoIndex index) const;

public:
	/*! 用户的签名信息
	 * \sa Signature
	 */
	Signature signature;

private:
	UserStatus loginMode;	/*!< 登陆模式  */
	UserStatus currentStatus;	/*!< 当前状态，如登陆成功后online，掉线后offline  */
	std::vector<std::string> infoList;	/*!< 用户信息队列  \see at()*/
	static const unsigned char DIVIDER = 0x1E;	/*!< 每项信息分割标志  */
	static const unsigned int QQ_CONTACT_FIELDS = 37;	/*!< 共37个部分信息  */

};

/*! \class WingUser
 *  \brief 这是一个用来保存用户信息的类。
 */

#endif // USERINFO_H
