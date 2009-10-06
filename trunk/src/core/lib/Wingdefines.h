#ifndef WINGDEFINES_H
#define WINGDEFINES_H

typedef	unsigned long int	uint32;
typedef	unsigned short		uint16;
typedef	unsigned char		uint8;

typedef	signed long int		int32;
typedef	signed short		int16;
typedef	signed char			int8;

//定义宏，删除对象并置NULL
#define SAFE_DELETE(p) {if(p) {delete (p);(p)=NULL;}}
//定义宏，删除对象数组并置NULL
#define SAFE_DELETE_ARRAY(p) {if(p) {delete[] (p);(p)=NULL;}}

/**********************************************************************/
/*设置默认的QQ版本为 qq for linux preview 1.0*/
#define QQ_DEFAULT_VERSION                    0X1131

/*定义种类QQ密钥的长度，都为16字节*/
#define QQ_KEY_LENGTH                         16

/*QQ Packet 的最大长度*/
#define QQ_PACKET_MAX_SIZE                    65535

/*QQ报文开始标志*/
#define QQ_HEAD_TAG                           0x02

/*QQ报文结束标志*/
#define QQ_TAIL_TAG                           0x03

/**********************************************************************/

/* QQ命令字, unsigned short( 2 bytes) */

/*退出*/
#define QQ_LOGOUT                             0x0001
/*保持在线*/
#define QQ_KEEP_ALIVE                         0x0002
/*修改信息*/
#define QQ_MODIFY_INFO                        0x0004
/*用户查找*/
#define QQ_SEARCH_USER                        0x0005
/*获取用户信息*/
#define QQ_GET_USER_INFO                      0x0006
/*增加联系人*/
#define QQ_ADD_FRIEND                         0x0009
/*删除联系人*/
#define QQ_DELETE_FRIEND                      0x000A
/*添加好友验证*/
#define QQ_ADD_FRIEND_AUTH                    0x000B
/*改变状态*/
#define QQ_CHANGE_STATUS                      0x000D
/**/
#define QQ_ACK_SYS_MSG                        0x0012
/*发送信息*/
#define QQ_SEND_IM                            0x0016
/*接收信息*/
#define QQ_RECV_IM                            0x0017
/*删除我*/
#define QQ_DELETE_ME                          0x001C
/*获取密钥*/
#define QQ_REQUEST_KEY                        0x001D
#define QQ_CELL_PHONE_1                       0x0021
/*请求会话密钥*/
#define QQ_REQUEST_SESSION_KEY                0x0022
/*获取好友列表*/
#define QQ_GET_FRIEND_LIST                    0x0026
/*获取在线好友*/
#define QQ_GET_FRIEND_ONLINE                  0x0027
#define QQ_CELL_PHONE_2                       0x0029
/*QQ群命令*/
#define QQ_QUN_CMD                            0x0030
#define QQ_TEST                               0x0031
#define QQ_GROUP_NAME_OP                      0x003C
#define QQ_UPLOAD_GROUP_FRIEND                0x003D
/*备注操作*/
#define QQ_MEMO_OP                            0x003E
/*获取好友分组*/
#define QQ_DOWNLOAD_GROUP_FRIEND              0x0058
#define QQ_GET_LEVEL                          0x005C
#define QQ_ADVANCED_SEARCH                    0x0061
/*请求预登陆令牌*/
#define QQ_REQUEST_PRE_LOGIN_TOKEN            0x0062
#define QQ_REQUEST_EXTRA_INFORMATION          0x0065
#define QQ_TEMP_SESSION_OP                    0x0066
/*QQ签名操作*/
#define QQ_SIGNATURE_OP                       0x0067
#define QQ_RECV_MSG_SYS                       0x0080
/*好友改变状态*/
#define QQ_FRIEND_CHANGE_STATUS               0x0081
/*握手请求*/
#define QQ_TOUCH_REQUEST                      0x0091
/*获取天气预报*/
#define QQ_WEATHER                            0x00A6
#define QQ_ADD_FRIEND_EX                      0x00A7
#define QQ_ADD_FRIEND_AUTH_EX                 0x00A8
#define QQ_ADD_FRIEND_AUTH_INFO               0x00AE
#define QQ_VERIFY_ADDING_MSG                  0x00B5
#define QQ_ADD_FRIEND_AUTH_QUESTION           0x00B7
/*请求登陆令牌*/
#define QQ_REQUEST_LOGIN_TOKEN                0x00BA
/*QQ上次登陆报告*/
#define QQ_LOGIN_LOCATION_CHECK               0x00DA
/*请求预会话密钥*/
#define QQ_REQUEST_PRE_SESSION_KEY            0X00DD


/** 消息回复类型 - 正常回复 */
#define QQ_IM_NORMAL_REPLY 	 0x01
/** 消息回复类型 - 自动回复 */
#define QQ_IM_AUTO_REPLY 	 0x02


/** 消息的来源*/
#define QQ_RECV_IM_NEWS                 0x0018
#define QQ_RECV_IM_FROM_BUDDY      		0x0084
#define QQ_RECV_IM_FROM_STRANGER    	0x0085
#define QQ_RECV_IM_SYS_MESSAGE    		0x0030


/**消息子类型，从属于QQ_RECV_IM_TO_BUDDY*/
#define QQ_IM_TCP_REQUEST               0x0001
#define QQ_IM_ACCEPT_TCP_REQUEST        0x0003
#define QQ_IM_REJECT_TCP_REQUEST        0x0005
/*普通文本消息 */
#define QQ_IM_NORMAL_TEXT               0x000B
#define QQ_IM_UDP_REQUEST               0x0035
#define QQ_IM_ACCEPT_UDP_REQUEST        0x0037
#define QQ_IM_REJECT_UDP_REQUEST        0x0039
#define QQ_IM_NOTIFY_IP                 0x003B
#define QQ_IM_ARE_YOU_BEHIND_FIREWALL   0x003F
#define QQ_IM_ARE_YOU_BEHIND_PROXY      0x0041
#define QQ_IM_YES_I_AM_BEHIND_PROXY     0x0042
#define QQ_IM_NOTIFY_FILE_AGENT_INFO    0x004B
#define QQ_IM_REQUEST_CANCELED          0x0049


#endif //WINGDEFINES_H
