//
//  PTIMClient.h
//  PTIMLibrary
//
//  Created by admin on 2017/5/11.
//  Copyright © 2017年 Putao. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PTIMConfigure.h"
#import "PTCommandMessage.h"

FOUNDATION_EXTERN NSString * _Nonnull const kIMConnectTimeoutNotify;
FOUNDATION_EXTERN NSString * _Nonnull const kIMConnectSuccessNotify;
FOUNDATION_EXTERN NSString * _Nonnull const kIMLoginFinishNotify;
FOUNDATION_EXTERN NSString * _Nonnull const kIMReceiveConfirmNotify;

typedef void(^PTIMSendCommandCallback)(BOOL successed, PTCommandMessage * _Nullable result);

typedef NS_ENUM (NSUInteger, PTIMConnectStatus) {
    PTIMConnectStatusNone = 0,
    PTIMConnectStatusConnecting = 1,
    PTIMConnectStatusConnectSuccess = 2,
    PTIMConnectStatusConnectFail = 3,
    PTIMConnectStatusLogining = 4,
    PTIMConnectStatusLoginSuccess = 5,
    PTIMConnectStatusLoginFail = 6,
    PTIMConnectStatusTokenFail = 7,
    PTIMConnectStatusLoginTimeout = 8
};

@interface PTIMClient : NSObject

@property (assign, nonatomic) PTIMConnectStatus currentStatus;

+ (instancetype _Nonnull)shared;

- (void)registerWithConfigure:(PTIMConfigure * _Nonnull)configure
                     callback:(void (^_Nonnull)(BOOL successed))callback;

- (void)sendCommand:(PTCommandMessage * _Nonnull)command
           callback:(PTIMSendCommandCallback _Nonnull)callback;

- (BOOL)logout;

- (void)disConnect;

@end
