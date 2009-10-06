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

#include "SignatureOpPacket.h"
#include "Signature.h"
#include "OutPacket.h"
#include "ToolKit.h"


uint32 SignatureOpPacket::nextQQ = 0;
SignatureOpPacket::SignatureOpPacket(enum QQ_SUB_CMD cmd)
	: num(0),bodyLen(0),subCmd(cmd)
{

}

SignatureOpPacket::~SignatureOpPacket()
{

}

void SignatureOpPacket::putUserSignature(const Signature &sig)
{
	int pos = 0;
	num = 1;
	bodyLen = num*8+3;
	bodyBuf = new uint8[bodyLen];
	bodyBuf[pos++] = subCmd;
	bodyBuf[pos++] = 0;
	bodyBuf[pos++] = num;

	ToolKit::writeBufDW(bodyBuf+pos, sig.qqNum);
	pos += 4;
	ToolKit::writeBufDW(bodyBuf+pos, sig.modifiedTime);
	pos += 4;
}

void SignatureOpPacket::putSignatureList(std::list<Signature> sigList)
{
	switch(subCmd)
	{
		case MODIFY_SIGNATURE:
		{
			//修改签名功能暂时未实现
		}
			break;
		case GET_SIGNATURE:
		{
			int pos = 0;
			num = sigList.size();
			bodyLen = num*8+3;
			bodyBuf = new uint8[bodyLen];
			bodyBuf[pos++] = subCmd;
			bodyBuf[pos++] = 0;
			bodyBuf[pos++] = num;
			while(!sigList.empty())
			{
				Signature &sig = sigList.front();
				ToolKit::writeBufDW(bodyBuf+pos, sig.qqNum);
				pos += 4;
				ToolKit::writeBufDW(bodyBuf+pos, sig.modifiedTime);
				pos += 4;
			}

		}
			break;
		default:
			;
	}
}

void SignatureOpPacket::process()
{
	//什么也不用做
}

OutPacket *SignatureOpPacket::toOutPacket()
{
	OutPacket *outPacketPtr = new OutPacket(QQ_SIGNATURE_OP, true);
	outPacketPtr->putBody(bodyBuf, bodyLen);
	SAFE_DELETE_ARRAY(bodyBuf);
	return outPacketPtr;
}
