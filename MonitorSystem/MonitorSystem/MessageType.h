#pragma once

#define MAX_DATA_SIZE 2048
///////////////////////////////////////////////////////////////////////
//定义消息协议结构体与类型
///////////////////////////////////////////////////////////////////////

//主消息类型，用来约定MESSAGE结构体中type的值
enum MSGTYPE
{
	MT_LOGIN = 1,	//客户端登陆
	MT_CLIENT_DISCONNECT = 2,	//客户端断开连接
	MT_SERVER_DISCONNECT = 3,	//断开服务器连接
};

//异常定义
enum MSGSTATUS
{
	MS_NORMAL = 1,	//正常状态
	MS_FAILED = 2,	//验证失败
	MS_SUCCEED = 3,	//验证成功
};

/** 主消息:核心消息结构体
** 思路:作为核心接收消息，考虑到大部分的消息，只有参数就可以确定，
** 为了减少空字符串的大量船速。将核心消息结构定义到最小装态，
** 且能解决大部分的通讯请求。
**/
struct MESSAGE
{
	char			session[32];			//存放IP地址和端口号
	MSGTYPE		type;				//消息类型
	MSGSTATUS	status;				//应答状态
	int			msg_id;				//消息序列号，每一次通讯产生一个序列号
	size_t		data_total_size;		//数据总长度
	char			security[64];		//验证码。（存放用户名和密码）
};

//打包数据包
struct MSGDATA
{
	char			session[32];			//存放IP地址和端口号
	int			msg_id;				//消息序列号，每一次通讯产生一个序列号
	int			msg_no;				//消息编号（从1开始编号）
	int			data_size;			//数据长度
	//char			data[MAX_DATA_SIZE];//数据区

};
