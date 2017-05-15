//
//  PTIMHandler.h
//  PTIM
//
//  Created by xiaopeng on 2016/11/28.
//  Copyright © 2016年 com.putao. All rights reserved.
//

#ifndef PTIMHandler_h
#define PTIMHandler_h

#include <stdio.h>
#import "IMClientInterface.hpp"
#import "PTIMClient.h"
#import <Foundation/Foundation.h>
#include <mutex>

using namespace PT::IM;
using namespace std;


class PTIMHandler : public IMClientHandler {
public:
    //    PTIMHandler(){}
    PTIMHandler(IMClientInterface *pClient, bool isSingle = true);
    virtual  ~PTIMHandler();
public:
    
    void onLoginConnnectInfo(IMReturnCode rc, const UIMLoginServerInfo *info);
    /**
     * 连接响应回调，指示是否成功连接
     */
    void onLoginConnect(IMReturnCode);
    
    void on_pc_notify_mobile(const string &content);
    
    /**
     * 登录响应回调，指示是否成功登录，并返回登录者的部分信息
     */
    void onLogin(IMReturnCode rc, const UIMUserInfo *);
    /**
     * 如果登录帐号通过其他客户端登录，则自动回调，其本客户端被踢下线，需要重新登录才能发起后序操作
     * @param rc 忽略
     */
    void onKicked(IMReturnCode rc);
    /**
     * 连接关闭，自动回调，需要重新连接并登录
     * @param rc 忽略
     */
    void onLoginDisconnect(IMReturnCode rc);
    /**
     * 登出响应回调
     */
    void onLogout(IMReturnCode);
    
    void on_command_peer(IMReturnCode rc, uint32_t from_uid, const std::string &local_id, const std::string &msg);
    void on_confirm_peer(IMReturnCode rc, uint32_t from_uid, const std::string &local_id, const std::string &msg);
    
protected:
    IMClientInterface	*m_pClient;
    uint32_t			m_userId;
public:
    uint32_t getUserId() { return m_userId; }
};

#endif /* PTIMHandler_hpp */
