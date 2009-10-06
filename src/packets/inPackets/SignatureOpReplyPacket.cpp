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

#include "SignatureOpReplyPacket.h"
#include "SignatureOpPacket.h"
#include "ToolKit.h"
#include "Packet.h"
#include "InPacket.h"


SignatureOpReplyPacket::SignatureOpReplyPacket()
	: result(SIG_MODIFY_SUCCEED),isUser(false)
{

}
SignatureOpReplyPacket::~SignatureOpReplyPacket()
{

}
//
void SignatureOpReplyPacket::fromInPacket(InPacket *inPacket)
{
	int32 pos = 0;
	uint8 *bodyPtr = inPacket->getBody();
	int32 bodyLen = inPacket->getBodyLen();
	uint8 subCmd = bodyPtr[pos++];
	switch(subCmd)
	{
		case SignatureOpPacket::MODIFY_SIGNATURE:
		{

		}
			break;
		case SignatureOpPacket::GET_SIGNATURE:
		{
			uint8 flag = bodyPtr[pos++];
			if(flag == 0)	//成功
			{
				Signature sig;
				ToolKit::readBufDW(bodyPtr+pos, SignatureOpPacket::nextQQ);
				pos += 4;
				while(bodyLen > pos)
				{
					ToolKit::readBufDW(bodyPtr+pos, sig.qqNum);
					pos += 4;
					ToolKit::readBufDW(bodyPtr+pos, sig.modifiedTime);
					pos += 4;
					uint8 sigLen = bodyPtr[pos++];
					sig.signature.assign((char *)(bodyPtr+pos), sigLen);
					pos += sigLen;
					sigList.push_back(sig);
				}
				if(sigList.size() == 1 && sig.qqNum == Packet::getQQNum())
					isUser = true;
				result = SIG_GET_SUCCEED;
			}
			else
			{
				result = SIG_GET_FAILED;
			}
		}
			break;
	}
}
//
std::list<Signature> SignatureOpReplyPacket::getSignatureList()
{
	return sigList;
}
