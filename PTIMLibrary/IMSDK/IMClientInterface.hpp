#ifndef _IM_CLIENT_INTERFACE_HPP_
#define _IM_CLIENT_INTERFACE_HPP_

#include "IMBaseDef.hpp"

namespace PT {
	namespace IM {
#ifdef _WIN32
#define IMCLIENT_EXPORT __declspec(dllexport)
#else
#define IMCLIENT_EXPORT 
#endif
		class IMClientInterface;
		/* ------------------  */
		/**
		 * 初始化环境，如果有多个线程使用一个或多个接口句柄，需要调用
		 */
        IMCLIENT_EXPORT void IMClnt_Initial();
		/**
		 * 结束多线程环境
		 */
        IMCLIENT_EXPORT void IMClnt_Final();
		/**
		 * 创建用于操作功能函数的指针句柄 , 沟通不使用ssl , vitis 使用ssl 
		 */
        IMCLIENT_EXPORT IMClientInterface *IMClnt_Create(bool use_ssl = false);
		/**
		 * 关闭指针句柄内部的循环
		 */
        IMCLIENT_EXPORT void IMClnt_Shutdown(IMClientInterface *);
		/**
		 * 销毁用于操作功能函数的指针句柄
		 */
        IMCLIENT_EXPORT void IMClnt_Destory(IMClientInterface *);
		
		/* ------------------  */

		class IMClientHandler
		{
		public:
			IMClientHandler() {}
			
			virtual ~IMClientHandler() {}
			
		public:
			/* -------------------------			*\
			 * 每一个异步回调函数都可能对应一个IMClientInterface句柄中的功能回调函数
			 * (也可能是IMClientInterface句柄自动调用的回调函数)，
			 *
			 * 返回数据以指针的方式传递，如果需要保存，调用者必须保存其副本，其有意义性根据返回码指示
			 * 返回数据中有些字段有意义，有些字段无意义，请查看函数的具体说明
			 *
			 * 以下函数的IMReturnCode参数返回
			 * 1.IMRC_OK 功能函数调用状态成功，其他传入数据有意义
			 * 2.IMRC_XXXX(除IMRC_OK以外的错误码) 功能函数调用状态失败，其他参数传入数据大多数情况下都是无意义的
			 *
			 \* -------------------------			*/
			

			/** deprecated
			 * 连接请求发起后，自动回调，返回连接信息
			 * @param rc 返回码 IMRC_ParamError 表示从服务器获取的参数出错
			 *				   IMRC_NetAlreadyConn
			 *				   IMRC_NetConnectin
			 *				   IMRC_OK
			 * @param info 连接信息，即使返回码错误也是有意义的
			 */
			virtual void onLoginConnnectInfo(IMReturnCode rc, const UIMLoginServerInfo *info) {}
			
			/**
			 * 连接响应回调，指示是否成功连接
			 * @param rc 返回码 IMRC_ParamError 表示从服务器获取的参数出错
			 *				   IMRC_NetAlreadyConn
			 *				   IMRC_NetConnectin
			 *				   IMRC_OK
			 */
			virtual void onLoginConnect(IMReturnCode rc) {};
			
			/**
			 * 登录响应回调，指示是否成功登录，并返回登录者的部分信息
			 * @param rc 返回码 IMRC_OK
			 *				   IMRC_LoginAlready
			 *				   IMRC_NetProtoError	协议错误，一般为服务器错误
			 *					IMRC_DbError		服务器密码验证错误
			 *					IMRC_PkgParseError  解析错误、一般为服务器出错
			 *					IMRC_OATokenError	服务器Token验证错误
			 *					IMRC_Timeouted		
			 *				
			 */	
			virtual void onLogin(IMReturnCode rc, const UIMUserInfo *) {};
			/**
			 * 如果登录帐号通过其他客户端登录，则自动回调，其本客户端被踢下线，需要重新登录才能发起后序操作
			 * @param rc 忽略
			 */
			virtual void onKicked(IMReturnCode) {};
			/**
			 * 连接关闭，自动回调，需要重新连接并登录
			 * @param rc 忽略
			 */
			virtual void onLoginDisconnect(IMReturnCode) {};
			/**
			 * 登出响应回调
			 * @param rc 忽略
			 */
			virtual void onLogout(IMReturnCode) {};
			/* ------------------  */
			/**
			 * 好友在线状态改变通知，自动回调
			 * @param rc IMRC_NoData	返回数据为空 一般服务器错误
						 IMRC_OK
			 * @param usrStat 最新用户状态，字段都是有意义信息
			 */
			virtual void onFriendOnlineStatUpdate(IMReturnCode rc, const UIMUserStat *usrStat) {};
			/**
			 * 好友信息更新通知，自动回调
			 * 比如添加好友或删除好友后，会收到该通知。
			 * @param rc	忽略
			 * @param type 改变类型：添加／删除
			 * @param usrInfo 被改变好友的信息列表
			 */
			virtual void onFriendsChangeNotify(IMReturnCode rc, const UIMUserNotify *notify) {};
			/**
			 * 获取好友列表响应回调
			 * @param rc IMRC_NoData	返回数据为空 一般服务器错误
							 IMRC_OK
			 * @param usrInfo 好友的详细信息，所有字段都是有意义信息
			 */
			virtual void onGetFriendsList(IMReturnCode rc, const UIMUserInfoList *usrInfo) {};
			/**
			 * 获取指定用户信息响应回调
			 * @param rc 返回码
			 * @param rc IMRC_NoData	返回数据为空 一般服务器错误
						 IMRC_OK
			 * @param usrInfo 好友的详细信息，除updateTime字段都是有意义信息
			 */
			virtual void onGetUsersInfoList(IMReturnCode rc, const UIMUserInfoList *usrInfo) {};
			
			/** 
			 发送消息给对方
			 rc		IMRC_Unkown	服务器错误
					IMRC_OK
			**/
			virtual void onPeerMsg(IMReturnCode rc, const UIMP2PMsg *msg){};

			/**
			 * 精确查找用户信息响应回调
			 * @param rc IMRC_NoData	返回数据为空 一般服务器错误
						 IMRC_OK
			 */
			virtual void onGetUserInfo(IMReturnCode rc, const UIMUserInfo *usrinfo) {};
			/**
			 * 改变用户信息响应回调
			 * @param rc	忽略

			 */
			virtual void onChangeUserInfo(IMReturnCode rc, const UIMResult *rs) {};
			/**
			 * 改变用户状态响应回调
			 * @param rc	忽略
			 */
			virtual void onChangeUserStat(IMReturnCode rc, const UIMResult *rs) {};
			/**
			 * 获取用户在线状态信息
			 * rc		IMRC_Unkown	服务器错误
						IMRC_OK
			 * @param usrStat 好友的详细信息，所有字段都是有意义信息
			 */
			virtual void onGetUsersStat(IMReturnCode rc, const UIMUserStatList *usrStat) {};
			/**
			 * 添加陌生人为好友响应回调
			 * @param rc 忽略
			 * @param type 接受／拒绝
			 * @param sayHello 应答的详细信息，
			 * 除sayHello.confirmInfo.userId外所有字段有意义，
			 * 其中sayHello.confirmInfo字段用于确认该条消息
			 */
			virtual void onMakeFriendLaunch(IMReturnCode rc, UIMFriendAnswerType type, const UIMMakeFriend *sayHello) {};
			/**
			 * 请求添加好友，被请求者回调
			 * @param rc 忽略
			 */
			virtual void onMakeFriendLand(IMReturnCode rc, const UIMMakeFriend *sayHello) {};
			/**
			 * 被好友删除通知，自动回调
			 *  @param rc 忽略
			 */
			virtual void onNoLongerFriend(IMReturnCode rc, const UIMNoLongerFriend *noFriend) {};


			//rc =  TIMEOUT or OK. 好友操作成功 回调。
			virtual void onAddFriendSend(IMReturnCode rc, uint32_t user_id, uint32_t friend_id){};
			virtual void onDelFriendSend(IMReturnCode rc, uint32_t user_id, uint32_t friend_id){};
			virtual void onAnswerFriendSend(IMReturnCode rc, uint32_t user_id, uint32_t friend_id){};



			//rc 忽略
			virtual void onNotifyRecvMessage(IMReturnCode rc, UIMSessionType type , uint32_t session_id){};

			/**
			 * 发送消息回调
			 * @param rc 返回码
			 * @param msg 已发送的消息。
			 * 说明
			 * 当rc == IMRC_Timeouted 时指示在规定的时间内没有收到响应，发送失败，但msg指示的数据是有意义的
			 * (其余错误信息，msg数据无意义)
			 * 其中的字段 localId,msgId,sessionId,fromUserId,type,sessionType,createTime,msgData有意义，
			 * 且为原消息数据，msgId为本地发送序列，可以用于重发。
			 * rc == IMRC_OK 时指示发送成功, 除字段 msgId 为服务器端id外，其余为原消息数据
			 * 字段 sessionId,fromUserId,type,sessionType,createTime,msgData 有意义
			 * 其余错误msg都是无意义的数据
			 */
			virtual void onSendMessage(IMReturnCode rc, const UIMMsgData *msg) {};
			/**
			 * 撤销消息回调
			 * @param rc IMRC_ServerLogicError 服务器逻辑错误
						 IMRC_OK				


			 * @param rs 撤销的结果
			 * @param msg 请求撤销的消息，仅msgId,fromUserId,sessionId,type,sessionType有效
			 */
			virtual void onCancelMessage(IMReturnCode rc, UIMMsgCancelResult rs, const UIMMsgData *msg) {};
			/**
			 * 消息被撤销通知，自动回调
			 @param rc 忽略
			 */
			virtual void onMessageCancelNotify(IMReturnCode rc, const UIMMsgCancelNotify *notify) {};
			/**
			* 群屏蔽消息回调
			@param rc 忽略
			*/
			virtual void onGroupShieldNotify(IMReturnCode rc, const UIMMsgShieldNotify *notify){};
			/**
			 * 接收到消息，自动回调
			 * @param rc 返回码
			 * @param msg 接收到的消息。
			 * 说明:
			 * rc == IMRC_OK 的msg返回有意义的接收到的数据，所有字段有意义，msgId为远程数据库中的id，非本地id
			   rc == IMRC_NetProtoError 协议错误，未能识别消息类型
			 */
			virtual void onRecvMessage(IMReturnCode rc, const UIMMsgData *msg) {};
			/**
			 * 获取未读消息列表回调
			 * @param rc 返回码 IMRC_NoData
								IMRC_NetProtoError	
								IMRC_OK
			 * @param unReadMsg 未读的消息列表。成功时的所有字段有意义
			 */
			virtual void onGetUnreadMsgList(IMReturnCode rc, const UIMUnReadMsgList *unReadMsg) {};
			/**
			 * 获取未读消息的详细列表回调
			 * @param rc 返回码	IMRC_NetProtoError	
								IMRC_NoData
								IMRC_OK
			 * @param msgList 未读的消息列表。成功时的所有字段有意义
			 */
			virtual void onGetMessageList(IMReturnCode rc, const UIMMsgDataList *msgList) {};
			/* ------------------  */
			/**
			 * 获取群组成员状态回调
			 * @param rc 返回码	IMRC_NoData
								IMRC_OK
			 * @param grpMemStat grpMemStat.statList 成员状态列表
			 */
			virtual void onGetGroupMemberStat(IMReturnCode rc, const UIMGroupMemberStat *grpMemStat) {};
			/**
			 * 群通知，当群中添加，删除成员等时，自动回调
			 * @param rc 忽略
			 * @param type 通知类型
			 * @param notify 通知类容 notify.attachData与notify.memeberList为可选信息
			 * 其中notify.confirm字段用于确认该条消息。
			 */
			virtual void onGroupNotify(IMReturnCode rc, UIMGroupChangeType type, const UIMGroupNotify *notify) {};
			/**
			 * 获取群组列表响应回调
			 * @param rc 返回码 IMRC_NoData
								IMRC_OK
			 * @param grpList 返回的组信息列表，如果成功且有组信息，所有字段有效
			 */
			virtual void onGetGroupList(IMReturnCode rc, const UIMGroupList *grpList) {};
			/**
			 * 获取群组列表详细信息响应回调
			 * @param rc 返回码 IMRC_NoData
								 IMRC_OK
			 * @param grpInfoList 返回的组详细信息列表，如果成功且有组信息，所有字段有效
			 */
			virtual void onGetGroupInfoList(IMReturnCode rc, const UIMGroupInfoList *grpInfoList) {};
			/**
			 * 创建群组响应回调
			 * @param rc 返回码 IMRC_OK
								IMRC_NoData
								IMRC_NoPrivilege
								IMRC_ServerLogicError
			 * @param grpInfo 返回的所创建组详细信息，如果成功，所有字段有效
			 */
			virtual void onCreateGroup(IMReturnCode rc, const UIMGroupInfo *grpInfo) {};
			/**
			 * 修改群组响应回调
			 * @param rc 返回码 IMRC_OK
					IMRC_NoPrivilege
					IMRC_ServerLogicError
			 * @param grpShortInfo 返回的所修改组简短信息，如果成功，所有字段有效
			 */
			virtual void onModifyGroup(IMReturnCode rc, const UIMGroupShortInfo *grpShortInfo) {};
			/**
			 * 删除群组响应回调
			 * @param rc 返回码 IMRC_OK
							IMRC_NoPrivilege
							IMRC_ServerLogicError
			 * @param grpShortInfo 返回的所删除组简短信息，如果成功，所有字段有效
			 */
			virtual void onDropGroup(IMReturnCode rc, const UIMGroupShortInfo *grpShortInfo) {};
			/**
			 * 确认删除群组响应回调
			 * @param rc 忽略
			 * @param grpShortInfo 返回的所删除组简短信息，如果成功，所有字段有效
			 */
			virtual void onConfirmDropGroup(IMReturnCode rc, const UIMGroupShortInfo *grpShortInfo) {};
			/**
			 * 改变群组成员响应回调
			 * @param rc 返回码 IMRC_OK
							IMRC_NoData
							IMRC_NoPrivilege
							IMRC_ServerLogicError
			 * @param type 操作类型
			 * @param grpInfo 返回的变化的的群组信息，如果成功，所有字段有效
			 */
			virtual void onChangeGroupMember(IMReturnCode rc, UIMGroupChangeType type, const UIMGroupInfo *grpInfo) {};
			//rc 	rc = IMRC_ParamError; rc = IMRC_ServerLogicError; rc = IMRC_OK

			virtual void onSetGroupShield(IMReturnCode rc, uint32_t group_id , bool shield){};


			/**
			* 改变群组群主
			* @param rc 返回码 IMRC_OK
						IMRC_NoPrivilege
						IMRC_ServerLogicError
			* @param type 操作类型
			* @param grpInfo 返回的修改后的组信息，
			*/
			virtual void onChangeGroupOwner(IMReturnCode rc, const UIMGroupShortInfo *grpShortInfo){};




			/* ------------------  */
			/**
			 * 视频开始呼叫方发起视频请求完成回调
			 * @param rc 返回码，说明:
			 * IMRC_Rejected 被拒绝; IMRC_Cancel 被取消; 
			 * IMRC_Busy 对方正忙（可能已在已在视频通话）;
			 * IMRC_BusyYourself 自己正忙（可能已在已在视频通话）;
			 * IMRC_Timeouted 在一段内没有得到应答，超时。
			 * IMRC_ServerLogicError 服务器错误
			 * @param videocall 响应信息，除clientType字段都是有意义的信息，说明见其字段说明
			 */
			virtual void onVideoCallLaunch(IMReturnCode rc , const UIMVideoCall *videocall) {};
			/**
			 * 接收到视频呼叫请求，自动回调
			 * @param rc 返回码，无特殊说明
			 * @param videocall 请求信息 除peerType字段都是有意义的信息，说明见其字段说明
			 */
			virtual void onVideoCallLand(IMReturnCode rc, const UIMVideoCall *) {};
			/**
			 * 视频被呼叫方接响应呼叫请求完成回调
			 * @param rc 返回码 IMRC_Cancel
								IMRC_OK
								IMRC_ServerLogicError
			 * @see onVideoCallLaunch()
			 */
			virtual void onVideoCallAnswer(IMReturnCode rc, const UIMVideoCall *) {};
			/**
			 * 视频退出发起方发起退出请求完成回调
			 * @param rc 返回码，无特殊说明
			 * @param videocall 响应信息，字段roomId无意义，其他有意义
			 */
			virtual void onVideoQuitLaunch(IMReturnCode rc, const UIMVideoCall *) {};
			/**
			 * 视频退出响应方接收到退出响应，自动回调
			 * @param rc 忽略
			 */
			virtual void onVideoQuitLand(IMReturnCode rc, const UIMVideoCall *) {};
			/**
			 * 获取部门信息回调
			 * @param rc 忽略
			 * @param dList 部门信息列表，所有字段有意义
			 */
			virtual void onGetDepartmentList(IMReturnCode rc, const UIMDepartmentList *dList) {};


			/**
			 * 备注是否修改成功
			 *  @param rc 忽略
			 *  @param result_code 0 成功 1 失败
			 */
			virtual void onChangeUserRemarks(IMReturnCode rc, int result_code){};


			/*
				rc 忽略 
			*/

			virtual void on_command_peer(IMReturnCode rc, uint32_t from_uid, const std::string &local_id, const std::string &msg){};
			
			/*
			rc OK , TIMEOUT , IDEXIST
			*/

			virtual void on_confirm_peer(IMReturnCode rc, uint32_t from_uid, const std::string &local_id, const std::string &msg){};
			
			/*
			rc 忽略
			*/
			virtual void on_notify_peer(IMReturnCode rc, uint32_t from_uid, const std::string &msg){};

		


#ifdef USE_P2P_FILE
			// rc 忽略
			virtual void onRecvFile(IMReturnCode rc , 
				uint32_t from_userid,
				const std::string &file_id ,
				const std::string &file_name ,
				int64_t file_length){};


			virtual void OnFileState(IMReturnCode rc, const std::string &file_id,
				P2PFileState state){};

			virtual void OnFileUpload(const std::string &file_id, int64_t cur_len, int64_t file_length, int used_time, int left_time, int speed){};

			virtual void OnFileDownload(const std::string &file_id, int64_t cur_len, int64_t file_length, int used_time, int left_time, int speed){};
#endif

			//
			//Mobile 需处理，可能因为PC给你发请求了。
			virtual void on_pc_notify_mobile(const std::string &content){}
			
			//
			// PC端 需处理 , 可能因为移动端给你发命令了。
			virtual void on_mobile_command_pc(const std::string &content){}
	
		};
		
		class IMClientInterface
		{
		public:
			IMClientInterface() {}

			virtual ~IMClientInterface() {}

			virtual void SetHandler(IMClientHandler *handler) = 0;

		public:
			/* -------------------------			*\
			 * 每一个功能函数都对应一个IMClientHandler句柄中的异步回调函数，
			 * 用于功能函数成功或失败是通知调用者，可以在回调函数中调用功能函数，
			 * 或在其他线程中调用，这都是线程安全的。
			 * 功能函数与其回调函数命名规则如下：
			 * sendMessage() ==> onSendMessage()
			 *
			 * 如果只有回调函数，没有相应的功能，则为自动回调函数
			 *
			 * 以下函数可能会返回
			 * 0.IMRC_OK 成功发送了数据，当成功与否还在处理当中，并通过回调来通知你
			 * 1.IMRC_IOError 发送队列已满，重调对应需要操作
			 * 2.IMRC_ObjInitError 客户端对象初始化失败或被恶意改变了内部状态，需要销毁
			 * 3.IMRC_NetNotYetConn 客户端对象还没有连接到服务器
			 * 4.IMRC_LoginNotYet 客户端对象还没有登录
			 *
			\* -------------------------			*/
			

			//手机调用 如果使用OA的测试服务器则需要调用该接口
			virtual void oa_set_server_test() = 0;

			//手机调用 此接口为扫码登录的第一步，即Mobile扫完码之后，通知PC扫码成功
			virtual bool oa_notify_scan(const std::string &user_name,
				const std::string &token, const std::string &sid) = 0;

			//手机调用 此接口为扫码登录的第二步，即扫完码之后，是否允许PC登录
			//		  或者 
			//		  非首次登录 在on_pc_notify_mobile中，接收PC需要登录的请求时调用
			virtual bool oa_mobile_confirm_pc_login(const std::string &user_name,
				const std::string &token, const std::string &sid,
				bool allowLogin
				) = 0;

			//PC端调用 此接口为非首次登录时，将从websokcet获取的chat-id放置content中，请求Mobile允许登录，content最好可扩展。
			// rc IMRC_ObjInitError
			//	  IMRC_NetNotYetConn
			//	   IMRC_OK
			virtual IMReturnCode pc_notify_mobile(const std::string &content, uint32_t user_id) = 0;

			//手机调用 此接口为手机 踢出PC客户端。
			// rc IMRC_ObjInitError
			//	  IMRC_NetNotYetConn
			//	   IMRC_OK
			virtual IMReturnCode mobile_command_pc(const std::string &content) = 0;


			/*
				设置心跳时间及消息超时时间。默认为40s和5s.
				单位秒。必须在连接前调用才生效,
			*/
			// rc IMRC_OK
			virtual IMReturnCode setHeartTime(int keepAliveSec ,  int msgExpiredSec) = 0;


			/**
			 * 连接服务器
			 * @param url 如：http://10.1.11.34:8090/msg_server
			 * @return IMRC_ParamError url格式不正确
				IMRC_ObjInitError
				IMRC_NetAlreadyConn
				IMRC_LoginAlready
				IMRC_NetError			 网络错误
				IMRC_ParamError			 服务器错误
				IMRC_OK
			 */
			virtual IMReturnCode loginConnect(const std::string &url) = 0;
			/**
			 * 以用户和密码登录服务器
			 * @param info 所有字段须填入
			 * @return IMRC_ParamError url格式不正确
						 IMRC_ObjInitError
						 IMRC_NetAlreadyConn
						 IMRC_LoginAlready
						 IMRC_NetError			 网络错误
						 IMRC_ParamError			 服务器错误
						 IMRC_OK
			 * @return IMRC_LoginAlready 已经登录;
			 */
			virtual IMReturnCode loginConnect2(const std::string &url) = 0;


			/**
			 *
			 * @return  
						 IMRC_ObjInitError
						 IMRC_NetNotYetConn
						 IMRC_OK
			 *
			 */
			virtual IMReturnCode disConnect() = 0;

			/*			
				@return 

					IMRC_ObjInitError
					IMRC_NetNotYetConn
					IMRC_LoginAlready			
			*/
			virtual IMReturnCode login(const UIMLoginPwdInfo &info) = 0;
			/**
			 * 以用户id和设备token登录服务器
			 * @see login(const UIMLoginPwdInfo &)
			 */

			/*
			@return

			IMRC_ObjInitError
			IMRC_NetNotYetConn
			IMRC_LoginAlready
			*/

			virtual IMReturnCode login(const UIMLoginTokenInfo &info) = 0;
			/*
			@return

			IMRC_ObjInitError
			IMRC_NetNotYetConn
			IMRC_LoginAlready
			*/
			virtual IMReturnCode login_token(const UIMLoginOAToken &info) = 0;



			/*
			@return

			IMRC_ObjInitError
			IMRC_NetNotYetConn
			IMRC_LoginAlready
			*/
			virtual IMReturnCode logout() = 0;




			/* ------------------  */
			/**
			 * 获取用户的好友列表，需要发送getUsersStat()才能获取线上状态
			 * @param userid 请求用户id
			 @return	IMRC_ObjInitError
						IMRC_LoginNotYet		 
			 */
			virtual IMReturnCode getFriendsList(std::uint32_t userId) = 0;
			/**
			 * 获取用户的好友列表
			 * @param userlist 必填字段为userList.userId, 选填字段userList.updateTime
			 *（该值一般由上一次的返回结果列表UIMUserInfoList.updateTime确定）
			 * 如果填0则与getFriendsList(uint32)接口功能一致。
			 * 其它字段会被忽略。
			 * 获取特定时间之后新增的好友列表

			 @return	IMRC_ObjInitError
						IMRC_LoginNotYet
			 */
			virtual IMReturnCode getFriendsList(const UIMUserList &userlist) = 0;
			/**
			 * 获取用户的线上状态
			 * @param usrList 必填字段usrList.usrId; usrList.userIdList 要获取好友状态的id数组
			 * @return IMRC_ObjInitError 
					   IMRC_LoginNotYet


			 */
			virtual IMReturnCode getUsersStat(const UIMUserList &usrList) = 0;
			/**
			 * 获取用户的信息 update为增量更新时间
			 * @return IMRC_ObjInitError
						IMRC_LoginNotYet
						IMRC_ParamError
			 */
			virtual IMReturnCode getUsersInfoList(const UIMUserList &usList) = 0;
			/**
			 * 精确查找用户
			 * @param info 查找的条件集合，其中UIMUserShortInfo::userId为发起请求的用户ID，
			 * 其他的字段为被查找用户的信息，暂时只支持UIMUserShortInfo::realName一个字段的查找，
			 * 其他字段被忽略
			 * @return IMRC_ObjInitError
						 IMRC_LoginNotYet
			 */
			virtual IMReturnCode getUserInfo(const UIMUserShortInfo &info) = 0;
			/**
			 * 修改自己的状态
			 * @return IMRC_ObjInitError
						IMRC_LoginNotYet
			 */
			virtual IMReturnCode changeUserStat(const UIMChangeUserStat &stat) = 0;
			/**
			 * 修改用户信息
			 * @param usrInfo 可以修改的字段为 userGender，strUserNickName，
			 * strAvatarUrl，strEmail，strUserTel，strUserDomain，strSignInfo；
			 * 其他字段会被忽略
			 * @return IMRC_ObjInitError
						IMRC_LoginNotYet
			 */
			virtual IMReturnCode changeUserInfo(const UIMUserInfo &usrInfo) = 0;
			/**
			 * 添加陌生人为好友请求
			 * @param sayHello 请求信息和问候语
			 * @return IMRC_ObjInitError
						IMRC_LoginNotYet
						IMRC_ParamError
			 */
			virtual IMReturnCode makeFriendLaunch(const UIMMakeFriend &sayHello) = 0;
			/**
			 * 应答添加好友请求
			 * @param type 答应还是拒绝
			 * @param sayHello 请求信息和问候语
			 * @return IMRC_ObjInitError
						IMRC_LoginNotYet
						 IMRC_ParamError
			 */
			virtual IMReturnCode makeFriendAnswer(UIMFriendAnswerType type, const UIMMakeFriend &sayHello) = 0;
			/**
			 * 删除好友
			 * @return IMRC_ObjInitError
						IMRC_LoginNotYet
						 IMRC_ParamError
			 */
			virtual IMReturnCode deleteFriend(std::uint32_t userId, std::uint32_t friendId) = 0;
			/* ------------------  */
			/**
			 * 接收消息确认
			 * 客户端须在读取消息后，发送此消息，否则服务器端视为该条消息未读，从而继续出现在未读消息列表中
			 * @param msg ack确认消息 须填写到字段为 msg.userId;
			 * msg.sessionId ;msg.msgId; msg.msgType; msg.sessionType
			 * @return IMRC_ObjInitError
						IMRC_LoginNotYet
			 */
			virtual IMReturnCode confirmRecvMessage(const UIMConfirmMsg &msg) = 0;

			/*
				将已读状态返回给对端(手机通知给桌面、桌面通知给手机)
				@param session_id 会话id			
				* @return IMRC_ObjInitError
						  IMRC_LoginNotYet
			*/
			virtual IMReturnCode notifyRecvMessage(UIMSessionType type, uint32_t session_id) = 0;

			/**
			 * 发送消息
			 * @param msg 消息内容 须填写字段为 msg.fromUserId;
			 * msg.sessionId ; msg.msgType; msg.sessionType 其他字段为选填
			 * 其中msg.msgType 仅接受 MSG_TYPE_TEXT／MSG_TYPE_PICTURE／MSG_TYPE_AUDIO／MSG_TYPE_VEDIO
			 * @return IMRC_ObjInitError
						IMRC_LoginNotYet
						IMRC_ParamError
			 */
			virtual IMReturnCode sendMessage(UIMMsgData &msg) = 0;
			
			/**
			 * 撤销已发送的消息
			 * @param msg 消息内容，onSendMessage()返回的消息
			 * @return IMRC_ObjInitError
						IMRC_LoginNotYet
			 */
			virtual IMReturnCode cancelMessage(const UIMMsgData &msg) = 0;
			/**
			 * 获取未读消息列表
			 * @param unRead 未读消息hint 须填字段 unRead.userId 忽略字段 unRead.unReadMsg
			 * 其他字段忽略
			 * @return IMRC_ObjInitError
						IMRC_LoginNotYet
			 */
			virtual IMReturnCode getUnreadMsgList(const UIMUnReadMsgList &unRead) = 0;
			/**
			 * 获取消息列表
			 * 通过未读消息列表中返回信息，获取单个会话的部分或全部（未读）消息
			 * @param msgList 消息hint 必填字段 msgList.userId; msgList.sessionType;
			 * msgList.sessionId, msgList.beginMsgId, msgList.msgCount;其他选填

			 * @return IMRC_ObjInitError
						IMRC_LoginNotYet
			 */
			virtual IMReturnCode getMessageList(const UIMMsgDataList &msgList) = 0;

			/* ------------------  */
			/**
			 * 获取群组简易信息列表
			 * @param grpList 群组列表hint 须填写字段grpList.userId ;忽略字段 grpList.version ;其他选填
			 * @return IMRC_ObjInitError
						IMRC_LoginNotYet
			 */
			virtual IMReturnCode getGroupList(const UIMGroupList &grpList) = 0;
			/**
			 * 获取群组详细信息列表
			 * @param grpList 群组列表hint 须填写字段grpList.userId;
			 * grpList.version(可以通过getGroupList()获取) 其他选填
			 * @return IMRC_ParamError 字段grpList.version长度为0
			 *			IMRC_ObjInitError
						IMRC_LoginNotYet
			 */
			virtual IMReturnCode getGroupInfoList(const UIMGroupList &grpList) = 0;
			/**
			 * 创建群组
			 * @param grpSInfo 群组创建hint 须填写字段 grpSInfo.userId, grpSInfo.groupName, grpSInfo.groupAvatar
			 * grpSInfo.memberList; 忽略字段 grpSInfo.groupId ;其他字段选填
			 * @return IMRC_ParamError 字段grpSInfo.memberList长度为0 或者 包含了创建者自身id
			 *			IMRC_ObjInitError
						IMRC_LoginNotYet
			 */
			virtual IMReturnCode createGroup(const UIMGroupShortInfo &grpSInfo) = 0;
			/**
			 * 创建群组
			 * @param grpSInfo 群组修改hint 须填写字段 grpSInfo.userId, grpSInfo.groupId,
			 * grpSInfo.groupName, grpSInfo.groupAvatar; 忽略字段 grpSInfo.memberList ;其他字段选填
			 * @return IMRC_ObjInitError
						 IMRC_LoginNotYet
			 */
			virtual IMReturnCode modifyGroup(const UIMGroupShortInfo &grpSInfo) = 0;
			/**
			 * 删除群组
			 * @param grpSInfo 群组删除hint 须填写字段 grpSInfo.userId, grpSInfo.groupId 
			 * 选填字段 grpSInfo.attachData; 其他字段忽略
			 * @return IMRC_ObjInitError
						IMRC_LoginNotYet
			 */
			virtual IMReturnCode dropGroup(const UIMGroupShortInfo &grpSInfo) = 0;
			/**
			* 屏蔽群组
			* @param grpSInfo shield true 是设置屏蔽, false 取消屏蔽
			* 选填字段 grpSInfo.attachData; 其他字段忽略
			* @return IMRC_ObjInitError
			IMRC_LoginNotYet
			*/


			virtual IMReturnCode setGroupShield(uint32_t group_id, bool shield) = 0;
			/**
			 * 删除群组确认
			 * @see dropGroup()
			 * @return IMRC_ObjInitError
						IMRC_LoginNotYet
			 */
			virtual IMReturnCode confirmDropGroup(const UIMGroupShortInfo &grpSInfo) = 0;
			/**
			 * 修改群成员
			 * @param type 操作类型：群成员的添加／删除／
			 * @param grpSInfo 群修改hint 须填写字段 grpSInfo.userId, grpSInfo.groupId, grpSInfo.memberList
			 * @return IMRC_ParamError 字段grpSInfo.memberList长度为0
			 *			IMRC_ObjInitError
						IMRC_LoginNotYet
			 */
			virtual IMReturnCode changeGroupMember(UIMGroupChangeType type, const UIMGroupShortInfo &grpSInfo) = 0;
			
			/**
			* 转移创建者身份
			* @param group_id 群id
			* @param user_id  现在的群主
			* @param to_creator_id  将要成为群主的成员id
			* @return 	IMRC_ObjInitError
						IMRC_LoginNotYet
			*/
			virtual IMReturnCode changeGroupOwner(uint32_t group_id , uint32_t user_id , uint32_t to_creator_id) = 0;
					
			
			/**
			 * 获取群组成员状态
			 * @param grpMemStat 必须填写grpMemStat.userId, grpMemStat.groupId
			 * @return 	IMRC_ObjInitError
						IMRC_LoginNotYet
			 */
			virtual IMReturnCode getGroupMemberStat(const UIMGroupMemberStat &grpMemStat) = 0;
			/* ------------------  */
			/**
			 * 发起视频呼叫请求
			 * @param videocall 呼叫hint 须填写字段 videocall.fromUserId, videocall.toUserId, videocall.roomId, videocall.clientType
			 * @return 	IMRC_ObjInitError
						IMRC_LoginNotYet
			*/
			virtual IMReturnCode videoCallLaunch(const UIMVideoCall &videocall) = 0;
			/**
			 * 响应视频呼叫请求
			 * @param type 响应方式：接受、拒绝、忙碌
			 * @param videocall 响应hint 须填写字段 videocall.fromUserId, videocall.toUserId, videocall.clientType, videocall.roomId
			 * @return 	IMRC_ObjInitError
						IMRC_LoginNotYet
			 */
			virtual IMReturnCode videoCallAnswer(UIMVideoAnswerType type, const UIMVideoCall &videocall) = 0;
			
			/**
			 * 发起视频退出请求
			 * @param videocall 响应hint 须填写字段 videocall.fromUserId, videocall.toUserId, videocall.peerType, videocall.clientType
			 * @return 	IMRC_ObjInitError
						IMRC_LoginNotYet
			 
			 */
			virtual IMReturnCode videoQuitLaunch(const UIMVideoCall &videocall) = 0;

			/* ------------------  */
			/**
			 * 获取部门列表
			 * @param dList 部门信息hint 须填写字段 dList.userId 选填字段 dList.attachData，其他字段忽略
			 * @return 	IMRC_ObjInitError
						IMRC_LoginNotYet
			 */
			virtual IMReturnCode getDepartmentList(const UIMDepartmentList &dList) = 0;
			/* ------------------  */


			//			 * @return 	IMRC_ObjInitError
			//						IMRC_LoginNotYet

			virtual IMReturnCode sendToPeer(const UIMP2PMsg &msg) = 0;



			/* -------------------- */
			virtual bool isOnline() = 0;

			/* 修改好友备注 */
			//			 * @return 	IMRC_ObjInitError
			//						IMRC_LoginNotYet
			virtual IMReturnCode UpdateUserRemarks(const UIMUserRemarks &uRemarks) = 0;

		
			virtual IMReturnCode command_peer(const std::string &local_id , uint32_t to_uid ,  const std::string &msg , int timeout = 5) = 0;
			virtual IMReturnCode confirm_peer(const std::string &local_id, uint32_t to_uid ,  const std::string &msg) = 0;
			virtual IMReturnCode notify_peer(const std::string &msg , uint32_t to_uid) = 0;

			/*
				file
			*/
#ifdef USE_P2P_FILE
			//	IMRC_ParamError fileId已存在 或 路径不正确
			//	IMRC_OK
			virtual IMReturnCode sendFile(const std::string& fileId,
				uint32_t to_userid,
				const std::string &path,
				const std::string &filename) = 0;	

			//  IMRC_ParamError  fileId不存在
			//	IMRC_OK
			virtual IMReturnCode cancelSendFile(const std::string &fileId) = 0;
			
			//  IMRC_ParamError  fileId不存在 或者 dir错误
			//	IMRC_OK
			virtual IMReturnCode answerRecvFile(const std::string &fileId , 
				const std::string &filename , 
				const std::string &dir ,
				bool baccepted) = 0;

			//  IMRC_ParamError  fileId不存在
			//	IMRC_OK
			virtual IMReturnCode cancelRecvFile(const std::string &fileId) = 0;


			//以下归 p2p_file调用。
			virtual IMReturnCode notifyFileState(const std::string &fileId , int file_result) = 0;
			virtual IMReturnCode notifyupload(const std::string &fileId, int64_t cur_len, int64_t file_length, int used_time, int left_time, int speed) = 0;
			virtual IMReturnCode notifydownload(const std::string &fileId, int64_t cur_len, int64_t file_length, int used_time, int left_time, int speed) = 0;

			virtual IMReturnCode sendFileReq(uint32_t touserid, const UIMFileReq &req) = 0;
			virtual IMReturnCode sendFileRsp(uint32_t touserid, const UIMFileRsp &rsp) = 0;
			virtual IMReturnCode sendFileBegin(uint32_t touserid, const UIMFileBegin &begin) = 0;
			virtual IMReturnCode sendFileEnd(uint32_t touserid, const UIMFileEnd &end) = 0;


#endif

		};
	}
}
#endif	// ifndef _IM_CLIENT_INTERFACE_HPP_
