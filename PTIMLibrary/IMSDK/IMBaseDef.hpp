#ifndef _IM_BASE_DEFINE_HPP_
#define _IM_BASE_DEFINE_HPP_

#include <string>
#include <vector>
#include <cstdint>




#ifdef USE_P2P_FILE

class CP2PFileHandler;

#endif
namespace PT {
	namespace IM {
		///////////////////////// Login //////////////////////////
#define IMReturnCode_Map(XX)								  \
	/*000*/	XX(OK, "OK"),										 \
	/*001*/ XX(Unkown, "Unkown error"),						  \
	/*002*/ XX(ObjInitError, "Object has not been initialize or initialize error"),	  \
	/*003*/ XX(NetConnError, "Network connect failed"),				  \
	/*004*/ XX(LoginAlready, "This client has login already"),			  \
	/*005*/ XX(Loginning, "This client is loginning"),				  \
	/*006*/ XX(LoginNotYet, "This client has not login yet"),			  \
	/*007*/ XX(LogoutFail, "Logout failed"),					  \
	/*008*/ XX(Timeouted, "Network or operate has occured timeout"),		  \
	/*009*/ XX(NetError, "Network has occured error"),				  \
	/*010*/ XX(NetNotYetConn, "This client has not been connected yet"),		  \
	/*011*/ XX(NetProtoError, "Network protocol error"),				  \
	/*012*/ XX(IOError, "Queue of file or message is full, or Message is too large"), \
	/*013*/ XX(ServerLogicError, "Logic error on server"),				  \
	/*014*/ XX(LocalLogicError, "Logic error on local"),				  \
	/*015*/ XX(DbError, "Database validate fail"),					  \
	/*016*/ XX(ParamError, "Parameter error"),					  \
	/*017*/ XX(TryAgain, "The operate on processing"),				  \
	/*018*/ XX(PkgParseError, "Parse package of flatbuffer error"),			  \
	/*019*/ XX(UserNotExist, "User isn't exist"),					  \
	/*020*/ XX(UserPwdError, "Password of user error"),				  \
	/*021*/ XX(OldVersion, "Version is too old"),					  \
	/*022*/ XX(NoData, "Data that return is empty"),				  \
	/*023*/ XX(NoPrivilege, "No Privilege to operate"),				  \
	/*024*/ XX(BusyYourself, "It's busy yourself"),					  \
	/*025*/ XX(Busy, "Something is busy"),						  \
	/*026*/ XX(Cancel, "This operation has been cancel by yourself or others"),	  \
	/*027*/ XX(Rejected, "This operation has been Rejected by yourself or others"),	  \
	/*028*/ XX(NetAlreadyConn, "This client has connected already"),		  \
	/*029*/	XX(NetConnecting , "This client is connecting"),						\
	/*030*/	XX(OATokenError, "oa's token error")		,		\
	/*031*/	XX(IDEXISTS, "id already is exist")
		enum IMReturnCode
		{
#define IMRC_ENUM_GEN(n, s) IMRC_##n
			IMReturnCode_Map(IMRC_ENUM_GEN)
#undef IMRC_ENUM_GEN
		};
		struct IMReturnDescription
		{
			const char      *name;
			const char      *desc;
		};
		static inline const char *getIMRCName(IMReturnCode code)
		{
			static struct IMReturnDescription _IMReturnDescription[] = {
#define IMRC_ENUM_GEN(n, s) \
	{ #n, s }
				IMReturnCode_Map(IMRC_ENUM_GEN)
#undef IMRC_ENUM_GEN
			};

			return _IMReturnDescription[code].name;
		}

		static inline const char *getIMRCDescription(IMReturnCode code)
		{
			static struct IMReturnDescription _IMReturnDescription[] = {
#define IMRC_ENUM_GEN(n, s) { #n, s }
				IMReturnCode_Map(IMRC_ENUM_GEN)
#undef IMRC_ENUM_GEN
			};

			return _IMReturnDescription[code].desc;
		}

		/* ---------------------				*/
		/**客户端类型*/
		enum UIMClientType
		{
			CLIENT_TYPE_PC = 0,
			CLIENT_TYPE_MOBILE_IOS = 1,
			CLIENT_TYPE_MOBILE_ANDROID = 2,
			CLIENT_TYPE_MOBILE_WP = 3,
			CLINET_TYPE_MOBILE_OTHER = 4,
			CLIENT_TYPE_WEB = 5,
			CLIENT_TYPE_PC_MAC = 6,
			CLIENT_TYPE_PC_LINUX = 7
		};

		/**用户在线状态 枚举*/
		enum UIMUserOnlineStatType
		{
			/**在线*/
			USER_STATUS_ONLINE = 0,
			/**离线*/
			USER_STATUS_OFFLINE = 1,
			/**离开*/
			USER_STATUS_LEAVE = 2,
			/*登出*/
			USER_STATUS_LOGOUT = 3
		};

		/**用户信息状态*/
		enum UIMUserStatType
		{
			USER_STAT_EXISTS = 0,		/*用户存在，可能有更新*/
			USER_STAT_NOTEXISTS = 1,	/*用户不存在，已经销号或从好友列表中删除*/
		};

		/**用户性别 枚举*/
		enum UIMUserGender
		{
			/* 男 */
			USER_GENDER_MALE = 0,
			/* 女 */
			USER_GENDER_FEMALE = 1,
		};
		/**好友改变通知*/
		enum UIMFriendChangeType
		{
			FRIEND_CHANGE_ADD = 0,
			FRIEND_CHANGE_DEL = 1,
		};
		/**通知触发类型 主动／被动*/
		enum UIMFriendActionType
		{
			FRIEND_ACTION_ACTIVE = 0,
			FRIEND_ACTION_PASSIVE = 1,
		};
		/*添加好友应答类型*/
		enum UIMFriendAnswerType
		{
			FRIEND_ANSWER_ACCEPT = 0,
			FRIEND_ANSWER_REJECT = 1,
		};
		/* -----------				*/
		enum UIMMsgType
		{
			/* ------------------------------------   */
			MSG_TYPE_TEXT = 0,	/*消息内容为文本*/
			MSG_TYPE_PICTURE = 1,	/*消息内容为文件url文本*/
			MSG_TYPE_AUDIO = 2,	/*消息内容为文件url文本*/
			MSG_TYPE_VEDIO = 3,	/*消息内容为文件url文本*/
			/* ------------------------------------   */
			MSG_TYPE_NOTIFY = 4,	/*通知类型*/
			MSG_TYPE_ADDFRIEND = 5,	/*添加好友请求*/
			MSG_TYPE_ANSFRIEND = 6,	/*添加好友应答*/
			MSG_TYPE_DELFRIEND = 7,	/*被好友删除通知*/
			MSG_TYPE_CANCEL = 8,	/*撤销消息通知*/

			MSG_TYPE_FILE = 9,		/*文件消息-*/
			MSG_TYPE_SHIELD = 10,
			MSG_TYPE_CANCEL_SHIELD = 11,
		};
		enum UIMMsgCancelResult
		{
			MSG_CANCEL_OK = 0,			/*撤销成功*/
			MSG_CANCEL_MSG_ID_WRONG = 1,		/*无效的消息id.*/
			MSG_CANCEL_MSG_TIME_OUT = 2,		/*不能撤销太久之前的消息*/
		};
		enum UIMSessionType
		{
			SESSION_TYPE_SINGLE = 0,
			SESSION_TYPE_GROUP = 1
		};
		enum UIMGroupChangeType
		{
			GROUP_CHANGE_CREATE = 0,	/**<创建群*/
			GROUP_CHANGE_ADD = 1,		/**<添加成员*/
			GROUP_CHANGE_DEL = 2,		/**<删除成员*/
			GROUP_CHANGE_DROP = 3,		/**<删除群*/
			GROUP_CHANGE_MODIFY = 4,	/**<修改成员*/
			GROUP_CHANGE_CREATOR = 5,	/*转移群主*/
		};
		enum UIMVideoAnswerType
		{
			VIDEO_CALL_ACCEPT = 0,
			VIDEO_CALL_REJECT = 1,
			VIDEO_CALL_TIMEOUT = 2,		// msg_server 超时的时候发送。
			VIDEO_CALL_BUSY = 3,
		};

		struct UIMUserAllStat
		{
			std::uint32_t           		userId = 0; /**< 状态所属用户id*/
			UIMUserOnlineStatType   		pc_stat = UIMUserOnlineStatType::USER_STATUS_OFFLINE;		/**< 用户最新状态*/
			UIMClientType           		pc_type = UIMClientType::CLIENT_TYPE_PC;	/**< 用户最新客户端类型*/
			UIMUserOnlineStatType   		mobile_stat = UIMUserOnlineStatType::USER_STATUS_OFFLINE;		/**< 用户最新状态*/
			UIMClientType           		mobile_type = UIMClientType::CLIENT_TYPE_MOBILE_IOS;	/**< 用户最新客户端类型*/
		};
		/* ------------------				*/
		/*登录返回的服务器信息*/
		struct UIMServerStat
		{
			std::uint32_t           		serverTime = 0;	/* 服务器时间*/
			UIMUserOnlineStatType   		userStatType = UIMUserOnlineStatType::USER_STATUS_OFFLINE;	/*用户在线状态*/
			UIMClientType           		clientType = UIMClientType::CLIENT_TYPE_PC;		/*客户端类型*/
			std::string						usrToken;			/*用户登录的token */
		};


		struct UIMUserInfo
		{
			std::uint32_t   				userId = 0;	/**< 用户id */
			UIMUserGender   				userGender = UIMUserGender::USER_GENDER_MALE;	/**< 性别 */
			UIMUserStatType 				stat = UIMUserStatType::USER_STAT_EXISTS;	/**< 状态 */
			std::uint32_t   				parentId = 0;
			std::string     				strUserNickName;	/**< 昵称 */
			std::string     				strAvatarUrl;		/**< 头像url地址 */
			std::string     				strEmail;			/**< email */
			std::string     				strUserRealName;	/**<  */
			std::string     				strUserTel;			/**< 电话号码 */
			std::string     				strUserDomain;		/**< 家庭地址 */
			std::string     				strSignInfo;		/**< 签名 */
			UIMServerStat   				serverStat;			/**< 服务器信息 */
			std::string						strRemarks;			/**< 备注 */
			std::string						strPosition;		// 职位		
			std::vector<std::string>		strOrganize;		// 公司/部门
			UIMUserAllStat					userStat;
		};
		struct UIMUserShortInfo
		{
			std::uint32_t   				userId = 0;	/**< 用户id */
			UIMUserGender   				gender;		/**< 性别 */
			std::string     				nickName;	/**< 昵称 */
			std::string     				realName;	/**< 用户真实姓名 */
		};

		/*修改状态*/
		struct UIMChangeUserStat
		{
			std::uint32_t           		userId = 0;
			UIMUserOnlineStatType   		stat;
		};

		/*修改操作类结果响应*/
		struct UIMResult
		{
			std::uint32_t                   userId = 0;
			std::uint32_t                   resultCode; /**< 操作结果, 0:success;1:fail*/
			std::vector <std::int8_t>       attachData;
		};

		/*用户详细信息*/
		struct UIMUserInfoList
		{
			std::uint32_t                   userId = 0; /**< 接受消息用户的id*/
			std::uint32_t                   updateTime;	/**< 更新时间*/
			std::vector <UIMUserInfo>       userList;	/**< 用户信息列表*/
			std::vector <std::int8_t>       attachData;	/**< 附加信息*/
		};
		struct UIMUserList
		{
			std::uint32_t                   userId = 0; /**< 请求用户的id*/
			std::uint32_t                   updateTime;	/**< 更新时间*/
			std::vector <std::uint32_t>     userIdList;	/**< 与请求用户相关的用户id数组*/
			std::vector <std::int8_t>       attachData;
		};
		struct UIMUserStat
		{
			std::uint32_t           		userId = 0; /**< 状态所属用户id*/
			UIMUserOnlineStatType   		stat = UIMUserOnlineStatType::USER_STATUS_OFFLINE;		/**< 用户最新状态*/
			UIMClientType           		clientType = UIMClientType::CLIENT_TYPE_PC;	/**< 用户最新客户端类型*/
		};




		struct UIMUserStatList
		{
			std::uint32_t						userId;
			std::vector <UIMUserAllStat>       userStatList;
			std::vector <std::int8_t>			 attachData;
		};

		/* --------------			*/
		/*确认已读消息(添加朋友请求，响应，删除；群操作通知等)*/
		struct UIMConfirmMsg
		{
			std::uint32_t   				userId = 0;	/**< 用户id*/
			std::uint32_t   				sessionId = 0;	/**< 会话id , 对应接收到消息中的fromUserId*/
			std::uint32_t   				msgId = 0;	/**< 消息id*/
			UIMSessionType  				sessionType = UIMSessionType::SESSION_TYPE_SINGLE;/**< 会话类型*/
			UIMMsgType      				msgType = UIMMsgType::MSG_TYPE_TEXT;	/**< 消息类型*/
		};

		/* --------------			*/
		/*发起／应答 添加好友 信息*/
		struct UIMMakeFriend
		{
			std::uint32_t					msgId;			/* 消息id*/
			std::uint32_t   				userId = 0;		/**< 自身id*/
			std::uint32_t   				strangerId = 0;	/**< 陌生人id*/
			std::string     				sayHello;	/**< 打招呼*/
			std::uint32_t					time;			/*时间*/
			UIMConfirmMsg   				confirmInfo;	/**< 确认信息 自动填写*/
		};
		/*发起删除好友／通知被好友删除 信息*/
		typedef UIMMakeFriend UIMNoLongerFriend;

		/*用户通知*/
		struct UIMUserNotify
		{
			std::uint32_t           		userId = 0;	/**<自身id*/
			UIMUserInfo             		friendInfo;	/**<好友信息*/
			UIMFriendChangeType     		chgType = UIMFriendChangeType::FRIEND_CHANGE_ADD;	/**<改变类型*/
			UIMFriendActionType     		actType = UIMFriendActionType::FRIEND_ACTION_ACTIVE;	/**<触发类型*/
		};

		/* --------------			*/

		/*
		 * 消息内容会根据消息类型不同，而有所区别
		 * 当消息类型为文件时，消息类容为该文件的url，而消息扩展内容为文件的属性，如下：
		 * {"file_name":"a.jpg" , "file_size":1024 , "duration": 10, "width": 64 , "height":64 }
		 * sessionId的解释，如果你在群组里聊天，会话id就是群组id，其他情况则是自身userId
		 */
		struct UIMUnReadMsg
		{
			std::uint32_t                   sessionId = 0;	/**<会话id*/
			UIMSessionType                  sessionType = UIMSessionType::SESSION_TYPE_SINGLE;	/**<会话类型 */
			std::uint32_t                   lastFromUserId = 0;	/**<最新发信人id*/
			std::uint32_t                   unReadCount = 0;	/**<未读消息个数*/
			std::uint32_t                   latestMsgId = 0;	/**<最新的消息id*/
			UIMMsgType                      latestMsgType = UIMMsgType::MSG_TYPE_TEXT;	/**<最新消息类型*/
			std::vector <std::int8_t>       msgData;	/**<最新消息内容*/
			std::string                     strMsgExt;	/**<最新消息附加信息*/
			std::uint32_t					lastestDate;	/* 最新消息时间 */
		};
		struct UIMUnReadMsgList
		{
			std::uint32_t                   userId = 0;	/**< 请求用户的id*/
			std::vector <std::int8_t>       attachData;	/**< 附加数据*/
			std::vector <UIMUnReadMsg>      unReadMsg;	/**< 返回的未读消息简易信息*/
		};
		struct UIMMsgData
		{
			std::uint32_t                   localId = 0;	/**< 本地消息id 输出参数*/
			std::uint32_t                   msgId = 0;		/**<服务器消息id */
			std::uint32_t                   fromUserId = 0;	/**<发送用户id */
			std::uint32_t                   sessionId = 0;	/**<会话id */
			std::uint32_t                   createTime = 0;	/**<消息创建时间 */
			UIMMsgType                      type = UIMMsgType::MSG_TYPE_TEXT;		/**<消息类型 */
			UIMSessionType                  sessionType = UIMSessionType::SESSION_TYPE_SINGLE;	/**<消息会话类型*/
			std::vector <std::int8_t>       msgData;	/**<消息内容*/
			std::string                     extInfo;	/**<消息扩展内容*/
			std::vector <std::int8_t>       attachData;	/**<消息附加数据*/
			std::string						localData; /**<调用层数据，仅在发送消息的回调函数中返回*/
		};
		struct UIMMsgDataList
		{
			std::uint32_t                   userId = 0;		/**<接收用户id*/
			std::uint32_t                   sessionId = 0;	/**<消息所属会话id*/
			UIMSessionType                  sessionType = UIMSessionType::SESSION_TYPE_SINGLE;	/**<会话类型*/
			std::uint32_t                   beginMsgId = 0;	/**<起始消息id*/
			std::uint32_t                   msgCount = 0;	/**<消息数*/
			std::vector <std::int8_t>       attachData;	/**<附加消息*/
			std::vector <UIMMsgData>        unReadMsg;	/**<未读消息*/
		};
		struct UIMMsgCancelNotify
		{
			std::uint32_t					self_msgId = 0;			/*消息id*/
			std::uint32_t   				msgId = 0;	/**<撤销的消息id */
			std::uint32_t   				sessionId = 0;		/**<消息所属会话id*/
			std::uint32_t   				fromUserId = 0;		/**<发送用户id */
			std::uint32_t					time = 0;			/*时间*/
			UIMSessionType  				sessionType = UIMSessionType::SESSION_TYPE_SINGLE;/**<会话类型*/
			UIMMsgType      				type = UIMMsgType::MSG_TYPE_TEXT;		/**<消息类型 */

			UIMConfirmMsg   				confirmInfo;/**< 确认信息 自动填写*/
		};

		struct UIMMsgShieldNotify
		{
			std::uint32_t					msgId = 0;				/*消息id*/
			std::uint32_t					groupId = 0;			/*消息所属会话*/
			std::uint32_t					fromUserId = 0;			/**<发送用户id */
			bool							shield = false;			/*屏蔽是否*/
			std::uint32_t					time = 0;				/*时间*/
			UIMConfirmMsg					confirmInfo;			/**< 确认信息 自动填写*/
		};

		/* -------------- department info -------------- */
		struct UIMDepartment
		{
			std::int32_t oid;
			bool updated;
			std::string jsonData;
		};

		struct UIMDepartmentList
		{
			std::uint32_t                   userId = 0;		/**<获取／接收用户id*/
			std::uint32_t                   updateTime = 0;	/**<最后更新时间*/
			std::vector<UIMDepartment>		list;
		};

		/* -------------- group info -------------- */
		struct UIMGroupMemberStat
		{
			std::uint32_t                   userId = 0;		/**< 用户id*/
			std::uint32_t                   groupId = 0;	/**< 组id*/
			std::vector <UIMUserAllStat>       statList;	/**< 成员的最新状态*/
		};

		/*群成员信息*/
		struct UIMUserGroupInfo
		{
			std::uint32_t           		userId = 0;		/**< 成员用户id*/
			UIMUserGender           		userGender = UIMUserGender::USER_GENDER_MALE;	/**< 成员性别*/
			UIMUserOnlineStatType   		stat = UIMUserOnlineStatType::USER_STATUS_OFFLINE;		/**< 成员在线状态*/
			std::string             		userNickName;	/**< 成员昵称*/
			std::string             		avatarUrl;	/**< 成员头像url*/
			UIMUserAllStat					allstat;

		};

		/*群详细信息*/
		struct UIMGroupInfo
		{
			std::uint32_t                   groupId = 0;/**<组id*/
			std::uint32_t                   version = 0;/**<组版本号，每次修改都会发生变化，且在删除时变为最大值*/
			std::uint32_t                   userId = 0;	/**<创建者id*/
			std::string                     groupName;	/**<群名称*/
			std::string                     groupAvatar;/**< 群图标*/
			std::vector <UIMUserGroupInfo>  memberList;	/**< 成员列表*/
			std::vector <std::int8_t>       attachData;	/**< 附加信息*/
		};

		/*主要用于创建，修改，删除，核实删除*/
		struct UIMGroupShortInfo
		{
			std::uint32_t                   userId = 0; /**< 操作群的用户id*/
			std::uint32_t                   groupId = 0;/**< 被操作群id*/
			std::string                     groupName;	/**< 群名称*/
			std::string                     groupAvatar;/**< 群图标*/
			std::vector <std::uint32_t>     memberList;	/**< 成员列表*/
			std::vector <std::int8_t>       attachData;	/**< 附加信息*/
			std::uint32_t					group_creator_id;	/* 群创建者id */
		};
		struct UIMGroupVersion
		{
			std::uint32_t   				groupId = 0; /**< 群版id*/
			std::uint32_t   				version = 0; /**< 群版本号*/
			bool							shield;		//是否屏蔽
		};
		struct UIMGroupList
		{
			std::uint32_t                   userId = 0; /**< 接收通知用户id*/
			std::vector <std::int8_t>       attachData;	/**< 附加信息*/
			std::vector <UIMGroupVersion>   version;	/**< 群版本号*/
		};
		struct UIMGroupInfoList
		{
			std::uint32_t                   userId = 0;		/**< 接收通知用户id*/
			std::vector <std::int8_t>       attachData;	/**< 附加信息*/
			std::vector <UIMGroupInfo>      groupInfo;	/**< 群信息*/
		};
		struct UIMGroupNotify
		{
			std::uint32_t					msgId = 0;		/**消息id**/
			std::uint32_t                   userId = 0;		/**< 操作者用户id*/
			std::uint32_t                   groupId = 0;	/**< 通知的群组id*/
			std::string                     groupName;	/**< 群名称*/
			std::string                     groupAvatar;	/**< 群头像url*/
			std::vector <UIMUserGroupInfo>  memberList;	/**< 通知内容*/
			std::vector <std::int8_t>       attachData;	/**< 附加信息*/
			UIMConfirmMsg                   confirmInfo;	/**< 确认信息 自动填写*/
			bool							isOnline = true; /* 是否在线 群通知 */
			std::uint32_t					creator_id = 0;	/* 转移后的群主id */
			std::uint32_t					operator_time = 0; /* 操作时间 */
		};

		/* --------------				*/
		struct UIMLoginServerInfo
		{
			uint16_t        				code = 302;				/**< 有效性 0为有效*/
			uint16_t        				port = 80;
			std::string     				priorIP;
			std::string     				backupIP;
			std::string     				discoveryURL;
			std::string     				msfsBackupURL;
			std::string     				msfsPriorURL;
			std::string     				rtcserverURL;
			std::string     				msg;
		};

		struct UIMLoginTokenInfo
		{
			std::uint32_t           		appId = 0;		/**<验证appid*/
			std::uint32_t           		usrId = 0;		/**<用户id*/
			std::string             		devToken;	/**<设备id*/
			std::string             		pushToken;	/**<推送id*/
			UIMUserOnlineStatType   		stat = UIMUserOnlineStatType::USER_STATUS_OFFLINE;		/**<登录状态*/
			UIMClientType           		clientType = UIMClientType::CLIENT_TYPE_PC;	/**<客户端类型*/
		};
		struct UIMLoginPwdInfo
		{
			std::string             		usrName;	/**<登录用户名*/
			std::string             		usrPassword;	/**<登录密码*/
			std::string             		pushToken;	/**<推送id*/
			UIMUserOnlineStatType   		stat = UIMUserOnlineStatType::USER_STATUS_OFFLINE;		/**<以何种状态登录：离线，在线，离开*/
			UIMClientType           		clientType = UIMClientType::CLIENT_TYPE_PC;	/**<客户端类型*/
		};


		struct UIMLoginOAToken
		{
			std::string						usrName;
			std::string						usrToken;
			std::string						pushToken;
			UIMUserOnlineStatType   		stat = UIMUserOnlineStatType::USER_STATUS_OFFLINE;		/**<以何种状态登录：离线，在线，离开*/
			UIMClientType           		clientType = UIMClientType::CLIENT_TYPE_PC;	/**<客户端类型*/
		};


		/* -------------- video call -------------- */
		struct UIMVideoCall
		{
			std::uint32_t   				fromUserId = 0;	/**<消息发起者id*/
			std::uint32_t   				toUserId = 0;	/**<消息应答者id*/
			UIMClientType   				clientType = UIMClientType::CLIENT_TYPE_PC;	/**<消息发起者客户端类型*/
			UIMClientType   				peerType = UIMClientType::CLIENT_TYPE_PC;	/**<消息应答者客户端类型*/
			std::string     				roomId;		/**<房间号*/
		};

		struct UIMUserRemarks
		{
			std::uint32_t					userId;			/** 自己的userid */
			std::string						turing_userid;	/** 图灵的userid*/
			std::uint32_t					changedId;		/**  好友的id */
			std::string						remarks;		/** 备注 */
		};

		struct UIMP2PMsg
		{
			std::uint32_t					userId;		/* 自己的userid */
			std::uint32_t					toUserId;	/* 对方的id */
			std::string						type;		/* json 类型 */		
			std::string						content;	/* 内容 */
			std::string						localid;	/* 本地id */
			int								timeout;	/* 超时时间*/
		};

//pc 通知		
#define  PC_NOTIFY_TYPE  "PC_NOTIFY_TYPE"

//mobile 命令
#define  MOBILE_COMMAND_TYPE "MOBILE_COMMAND_TYPE"



//通知
#define COMMON_NOTIFY_TYPE	"COMMON_NOTIFY_TYPE"
//命令
#define COMMON_COMMAND_TYPE "COMMON_COMMAND_TYPE"
//确定
#define COMMON_CONFIRM_TYPE	"COMMON_CONFIRM_TYPE"
//消息已读未读
#define MESSAGE_READ_ACK	"MESSAGE_READ_ACK"




#ifdef USE_P2P_FILE		
#define FILE_REQ_TYPE	"IMSSERVER_FILE_REQ"
		struct UIMFileReq
		{
			std::string file_id;
			std::string file_hash;
			std::uint64_t file_length;
			std::string file_name;
			std::string file_mime;
			std::string sdp;
		};

#define FILE_RSP_TYPE	"IMSERVER_FILE_RSP"
		struct UIMFileRsp
		{
			std::string file_id;
			std::string file_hash;
			uint64_t file_index;
			std::string sdp;
		};

#define FILE_BEGIN_TYPE	"IMSERVER_FILE_BEGIN"
		struct UIMFileBegin
		{
			std::string file_id;
			std::string file_hash;
			uint64_t	file_index;
		};

#define FILE_END_TYPE	"IMSERVER_FILE_END"
		struct UIMFileEnd
		{
			std::string file_id;
			uint32_t	file_result;
		};

		enum P2PFileState{
			FILE_PEER_ACCEPT,
			FILE_NET_ERROR,	
			FILE_PEER_CANCEL,
			FILE_PEER_REJECT,
			FILE_DATA_ERROR,
			FILE_FINISH
		};

		struct P2PFileInfo
		{
			std::string file_id;
			std::uint32_t from_userid;
			std::uint32_t to_userid;
			std::string file_hash;
			std::uint64_t file_length;
			std::string file_name;
			std::string file_mime;
			std::string sdp;
		};
		
#endif


	}
}
#endif	// !_IM_BASE_DEFINE_HPP_
