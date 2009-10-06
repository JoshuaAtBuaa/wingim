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

#ifndef LOGINMODULE_H_
#define LOGINMODULE_H_

#include <QByteArray>

class InPacket;
class LoginModule
{
public:
	/*! 枚举类型
	 *  用来表示登陆过程中的各个状态。
	 */
	enum LoginingStatus{
		noStart,		/*!< 未开如  */
		touch,			/*!< 握手  */
		requestPreLT,	/*!< 请求预登陆令箭  */
		requestLT,		/*!< 请求登陆令箭  */
		requestPreSK,	/*!< 请求预会话密钥  */
		requestSK		/*!< 请求会话密钥  */
		};

	enum LoginingStatus loginStatus;	/*!< 登陆过程中的各个状态 \sa LoginingStatus */
public:
	LoginModule();
	~LoginModule();

	/*! 开始登陆 */
	void startLogin();

	/*! 应答处理函数
	 *  它只是一个接口，具体过程交由其他函数处理。
	 * \param inPacket 一个InPacket指针。
	 * \see processTouchReply()
	 * \see processPreLoginTokenReply()
	 * \see processLoginTokenReply()
	 * \see processPreSessionReply()
	 * \see processSessionReply()
	 * \sa InPacket
	 */
	void processReply(InPacket *inPacket);

	/*! 处理握手应答
	 * \param inPacket 一个InPacket指针。
	 */
	void processTouchReply(InPacket *inPacket);

	/*! 处理预登陆令箭应答
	 * \param inPacket 一个InPacket指针。
	 */
	void processPreLoginTokenReply(InPacket *inPacket);

	/*! 处理登陆令箭应答
	 * \param inPacket 一个InPacket指针。
	 */
	void processLoginTokenReply(InPacket *inPacket);

	/*! 处理预会话密钥应答
	 * \param inPacket 一个InPacket指针。
	 */
	void processPreSessionReply(InPacket *inPacket);

	/*! 处理会话应答
	 * \param inPacket 一个InPacket指针。
	 */
	void processSessionReply(InPacket *inPacket);

	/*! 处理未知应答
	 * \param inPacket 一个InPacket指针。
	 */
	void processUnknownReply(InPacket *inPacket);

private:
	/*! 登陆失败的处理函数。
	 */
	void loginFailed();

public:
	/*! 图片数据缓冲区。
	 *  在登陆过程如果需要图片验证，那么图片数据便保存在这里。
	 */
	QByteArray pngBuf;
};

/*! \class LoginModule
 *  \brief 这是一个用来专门处理登陆过程的类。
 */

#endif /* LOGINMODULE_H_ */
