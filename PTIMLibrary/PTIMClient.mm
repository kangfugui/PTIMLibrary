//
//  PTIMClient.m
//  PTIMLibrary
//
//  Created by admin on 2017/5/11.
//  Copyright © 2017年 Putao. All rights reserved.
//

#import "PTIMClient.h"
#import "IMClientInterface.hpp"
#import "PTIMHandler.h"
#import <iostream>

FOUNDATION_EXTERN NSString * const baseURL_Test = @"http://gate-putao-im.ptdev.cn/msg_server";
FOUNDATION_EXTERN NSString * const baseURL_Production = @"http://gate-putao-im-online.putao.com/msg_server";
FOUNDATION_EXTERN NSString * const kIMConnectTimeoutNotify = @"com.putao.im.connect.timeout";
FOUNDATION_EXTERN NSString * const kIMConnectSuccessNotify = @"com.putao.im.connect.success";
FOUNDATION_EXTERN NSString * const kIMLoginSuccessNotify = @"com.putao.im.login.success";
FOUNDATION_EXTERN NSString * const kIMLoginFailureNotify = @"com.putao.im.login.failure";

using namespace PT::IM;
using namespace std;

typedef void(^PTConnectCallback)(BOOL successed);

@interface PTIMClient() {
    PTIMHandler *handler;
    IMClientInterface *pIMClient;
    NSInteger _connectCount;
}
@property (copy, nonatomic) PTConnectCallback connectCallback;
@end

@implementation PTIMClient

- (instancetype)init {
    if (self = [super init]) {
        if (!pIMClient)
            pIMClient = IMClnt_Create(true);
        if (!handler)
            handler = new PTIMHandler(pIMClient, true);
        
        _connectCount = 0;
        [self registerNotifications];
    }
    return self;
}

- (void)dealloc {
    [self unregisterNotifications];
}

+ (instancetype)shared {
    
    static PTIMClient *_shared = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _shared = [[self alloc] init];
    });
    
    return _shared;
}

- (void)receiveIMConnectSuccessNotify:(NSNotification *)sender {
    if (self.connectCallback) {
        self.connectCallback(YES);
    }
}

- (void)receiveIMConnectTimeoutNotify:(NSNotification *)sender {
    if (self.connectCallback) {
        self.connectCallback(NO);
    }
}

- (void)registerWithConfigure:(PTIMConfigure *)configure {
    
    __weak __typeof(self) weak_self = self;
    [self connectWithDomain:configure.domain callback:^(BOOL successed) {
        if (successed) {
            [weak_self loginWithUsrID:configure.usrID
                                appID:configure.appID
                             deviceID:configure.deviceID
                                token:configure.pushToken];
        }
    }];
}

//MARK: - 登录处理
/** 连接服务器 */

- (void)connectWithDomain:(PTIMServiceDomain)domain callback:(PTConnectCallback)callback {
    
    self.connectCallback = callback;
    NSString *baseURL = domain == 0 ? baseURL_Test : baseURL_Production;
    [self connectWithServerURL:baseURL];
}

- (void)connectWithServerURL:(NSString *)URL {
    pIMClient->SetHandler(handler);
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        IMReturnCode rc = pIMClient->loginConnect2([URL UTF8String]);
        
        dispatch_async(dispatch_get_main_queue(), ^{
            
            if (rc == IMRC_NetAlreadyConn) {
                // 已经连接
            } else if (rc == IMRC_OK) {
                // 连接成功
            } else if (rc == IMRC_LoginAlready) {
                // 已经登录了
            } else if (rc == IMRC_NetError) {
                // 无网络
                
                if (_connectCount >= 5) {
                    [[NSNotificationCenter defaultCenter] postNotificationName:kIMConnectTimeoutNotify object:nil];
                    _connectCount = 0;
                    return;
                }
                _connectCount++;
                dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                    [self connectWithServerURL:URL];
                });
                
            } else {
                [[NSNotificationCenter defaultCenter] postNotificationName:kIMConnectTimeoutNotify object:nil];
            }
        });
    });
}

- (void)disConnect {
    pIMClient->disConnect();
    pIMClient->SetHandler(nil);
}

- (void)loginWithUsrID:(NSString *)UsrID
                 appID:(int)appID
              deviceID:(NSString *)deviceID
                 token:(NSString *)token {
    
    UIMLoginTokenInfo info;
    info.usrId = UsrID.intValue;
    info.appId = appID;
    info.devToken = deviceID.UTF8String;
    info.pushToken = token.UTF8String;
    info.stat = USER_STATUS_ONLINE;
    info.clientType = CLIENT_TYPE_MOBILE_IOS;
    
    IMReturnCode rc = pIMClient->login(info);
    if (rc != IMRC_OK) {
        
        [[NSNotificationCenter defaultCenter] postNotificationName:kIMLoginFailureNotify
                                                            object:nil
                                                          userInfo:nil];
    }
    
    self.currentStatus = PTIMConnectStatusLogining;
}

/** 退出登录 */
- (BOOL)logout {
    IMReturnCode rc = pIMClient->logout();
    if (rc == IMRC_OK) {
        return true;
    }
    return false;
}


- (void)registerNotifications {
    NSNotificationCenter *center = [NSNotificationCenter defaultCenter];
    [center addObserver:self
               selector:@selector(receiveIMConnectSuccessNotify:)
                   name:kIMConnectSuccessNotify
                 object:nil];
    
    [center addObserver:self
               selector:@selector(receiveIMConnectTimeoutNotify:)
                   name:kIMConnectTimeoutNotify
                 object:nil];
}

- (void)unregisterNotifications {
    NSNotificationCenter *center = [NSNotificationCenter defaultCenter];
    [center removeObserver:self name:kIMConnectSuccessNotify object:nil];
    [center removeObserver:self name:kIMConnectTimeoutNotify object:nil];
}

@end
