//
//  PTIMClient.h
//  PTIMLibrary
//
//  Created by admin on 2017/5/11.
//  Copyright © 2017年 Putao. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PTIMConfigure.h"

FOUNDATION_EXTERN NSString * _Nonnull const kIMConnectTimeoutNotify;
FOUNDATION_EXTERN NSString * _Nonnull const kIMConnectSuccessNotify;
FOUNDATION_EXTERN NSString * _Nonnull const kIMLoginSuccessNotify;
FOUNDATION_EXTERN NSString * _Nonnull const kIMLoginFailureNotify;

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

- (void)registerWithConfigure:(PTIMConfigure * _Nonnull)configure;

@end
