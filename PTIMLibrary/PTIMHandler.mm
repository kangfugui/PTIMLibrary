//
//  PTIMHandler.cpp
//  PTIM
//
//  Created by xiaopeng on 2016/11/28.
//  Copyright © 2016年 com.putao. All rights reserved.
//

#include "PTIMHandler.h"

PTIMHandler::PTIMHandler(IMClientInterface *pClient, bool isSingle)
{
    m_pClient = pClient;
    m_pClient->SetHandler(this);
    m_pClient->setHeartTime(5, 5);
}

PTIMHandler::~PTIMHandler() {
    if (m_pClient) {
        IMClnt_Destory(m_pClient);
    }
}

//MARK: - 登录处理
/**
 * 连接响应回调，指示是否成功连接
 */
void PTIMHandler::onLoginConnect(IMReturnCode rc) {
    if (rc == IMRC_OK) {
        printf("----- 连接服务器成功 -----\n");
        [[NSNotificationCenter defaultCenter] postNotificationName:kIMConnectSuccessNotify
                                                            object:nil
                                                          userInfo:nil];
    }
}

void PTIMHandler::onLoginConnnectInfo(IMReturnCode rc, const UIMLoginServerInfo *info) {
}

/**
 * 登录响应回调，指示是否成功登录，并返回登录者的部分信息
 */
void PTIMHandler::onLogin(IMReturnCode rc, const UIMUserInfo *info) {
    
    BOOL successed = rc == IMRC_OK;
    
    [[NSNotificationCenter defaultCenter] postNotificationName:kIMLoginFinishNotify
                                                        object:nil
                                                      userInfo:@{@"result":@(successed)}];
    if (rc == IMRC_OK) {
        printf("----- 登录成功 -----\n");
    }
}

void PTIMHandler::on_pc_notify_mobile(const std::string &content) {
}

/**
 * 连接关闭，自动回调，需要重新连接并登录
 * @param rc 忽略
 */
void PTIMHandler::onLoginDisconnect(IMReturnCode rc) {
}

/**
 * 登出响应回调
 */
void PTIMHandler::onLogout(PT::IM::IMReturnCode rc) {
}

/**
 * 如果登录帐号通过其他客户端登录，则自动回调，其本客户端被踢下线，需要重新登录才能发起后序操作
 * @param rc 忽略
 */
void PTIMHandler::onKicked(PT::IM::IMReturnCode rc) {
}

void PTIMHandler::on_command_peer(PT::IM::IMReturnCode rc, uint32_t from_uid, const std::string &local_id, const std::string &msg) {
    
    NSString *msgString = [NSString stringWithCString:msg.c_str() encoding:NSUTF8StringEncoding];
    NSString *local_idString = [NSString stringWithCString:local_id.c_str() encoding:NSUTF8StringEncoding];
    NSString *string = [NSString stringWithFormat:@"from_uid:%@\nlocal_id:%@\nmsg:%@",@(from_uid), local_idString, msgString];
    NSDictionary *dict = @{@"from_uid":@(from_uid), @"local_id":local_idString, @"msg":msgString};
    
    [[NSNotificationCenter defaultCenter] postNotificationName:@"kRecevieCommandNotification" object:dict];
    
    printf("----- on_command_peer: %s -----\n", [string UTF8String]);
}

void PTIMHandler::on_confirm_peer(IMReturnCode rc, uint32_t from_uid, const std::string &local_id, const std::string &msg){
    printf("\non_confirm_peer: %s\n", [[NSString stringWithCString:msg.c_str() encoding:NSUTF8StringEncoding] UTF8String]);
}
