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
#import "PTMessageContainer.h"
#import <iostream>

FOUNDATION_EXTERN NSString * const baseURL_Test = @"http://10.1.11.177:8090/msg_server";
FOUNDATION_EXTERN NSString * const baseURL_Production = @"http://webrtc-im-gateway.putao.com/msg_server";
FOUNDATION_EXTERN NSString * const kIMConnectTimeoutNotify = @"com.putao.im.connect.timeout";
FOUNDATION_EXTERN NSString * const kIMConnectSuccessNotify = @"com.putao.im.connect.success";
FOUNDATION_EXTERN NSString * const kIMLoginFinishNotify = @"com.putao.im.login.success";
FOUNDATION_EXTERN NSString * const kIMReceiveConfirmNotify = @"com.putao.im.receive.confirm";

using namespace PT::IM;
using namespace std;

typedef void(^PTConnectCallback)(BOOL successed);
typedef void(^PTLoginCallback)(BOOL successed);

@interface PTIMClient() {
    PTIMHandler *handler;
    IMClientInterface *pIMClient;
    NSInteger _connectCount;
}

@property (copy, nonatomic) PTConnectCallback connectCallback;
@property (copy, nonatomic) PTLoginCallback loginCallback;
@property (strong, nonatomic) NSMutableArray<PTMessageContainer *> *didSentMessage;

@end

@implementation PTIMClient

- (instancetype)init {
    if (self = [super init]) {
        if (!pIMClient)
            pIMClient = IMClnt_Create(false);
        if (!handler)
            handler = new PTIMHandler(pIMClient, true);
        
        _connectCount = 0;
        self.didSentMessage = [[NSMutableArray alloc] init];
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

- (void)registerWithConfigure:(PTIMConfigure *)configure
                     callback:(void (^)(BOOL successed))callback {
    
    __weak __typeof(self) weak_self = self;
    [self connectWithDomain:configure.domain callback:^(BOOL successed) {
        if (successed) {
            
            [weak_self
             loginWithUsrID:configure.usrID
             appID:configure.appID
             deviceID:configure.deviceID
             token:configure.pushToken
             callback:^(BOOL successed) {
                 callback(successed);
            }];
        } else {
            callback(NO);
        }
    }];
}

- (void)sendCommand:(PTCommandMessage *)command
           callback:(PTIMSendCommandCallback)callback {
    
    PTMessageContainer *container = [[PTMessageContainer alloc] initWithMessage:command
                                                                       callback:callback];
    [self.didSentMessage addObject:container];
    
    pIMClient->command_peer(command.localID.UTF8String,
                            command.toUsrID,
                            command.content.UTF8String);
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
                 token:(NSString *)token
              callback:(PTLoginCallback)callback {
    
    self.loginCallback = callback;
    UIMLoginTokenInfo info;
    info.usrId = UsrID.intValue;
    info.appId = appID;
    info.devToken = deviceID.UTF8String;
    info.pushToken = token.UTF8String;
    info.stat = USER_STATUS_ONLINE;
    info.clientType = CLIENT_TYPE_MOBILE_IOS;
    
    IMReturnCode rc = pIMClient->login(info);
    if (rc != IMRC_OK) {
        [[NSNotificationCenter defaultCenter] postNotificationName:kIMLoginFinishNotify
                                                            object:nil
                                                          userInfo:@{@"result":@(NO)}];
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

// MARK: Notification

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
    
    [center addObserver:self
               selector:@selector(receiveIMLoginSuccessNotify:)
                   name:kIMLoginFinishNotify
                 object:nil];
    
    [center addObserver:self
               selector:@selector(receiveConfirmNotify:)
                   name:kIMReceiveConfirmNotify
                 object:nil];
}

- (void)unregisterNotifications {
    NSNotificationCenter *center = [NSNotificationCenter defaultCenter];
    [center removeObserver:self name:kIMConnectSuccessNotify object:nil];
    [center removeObserver:self name:kIMConnectTimeoutNotify object:nil];
    [center removeObserver:self name:kIMLoginFinishNotify object:nil];
    [center removeObserver:self name:kIMReceiveConfirmNotify object:nil];
}

- (void)receiveIMConnectSuccessNotify:(NSNotification *)sender {
    self.currentStatus = PTIMConnectStatusConnectSuccess;
    if (self.connectCallback) {
        self.connectCallback(YES);
    }
}

- (void)receiveIMConnectTimeoutNotify:(NSNotification *)sender {
    self.currentStatus = PTIMConnectStatusConnectFail;
    if (self.connectCallback) {
        self.connectCallback(NO);
    }
}

- (void)receiveIMLoginSuccessNotify:(NSNotification *)sender {
    BOOL result = [sender.userInfo[@"result"] boolValue];
    self.currentStatus = result ? PTIMConnectStatusLoginSuccess : PTIMConnectStatusLoginFail;
    if (self.loginCallback) {
        self.loginCallback(result);
    }
}

- (void)receiveConfirmNotify:(NSNotification *)sender {
    
    PTCommandMessage *command = sender.userInfo[@"msg"];
    [self.didSentMessage enumerateObjectsUsingBlock:^(PTMessageContainer *obj, NSUInteger idx, BOOL *stop) {
        if ([obj.message.localID isEqualToString:command.localID]) {
            obj.callback(YES);
            *stop = YES;
            [self.didSentMessage removeObjectAtIndex:idx];
        }
    }];
}

@end
