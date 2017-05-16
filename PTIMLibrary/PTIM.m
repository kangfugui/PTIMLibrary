//
//  PTIM.m
//  PTIMLibrary
//
//  Created by admin on 2017/5/15.
//  Copyright © 2017年 Putao. All rights reserved.
//

#import "PTIM.h"

@implementation PTIM

+ (PTIMConnectStatus)currentStatus {
    return [PTIMClient shared].currentStatus;
}

+ (void)registerWithConfigure:(PTIMConfigure * _Nonnull)configure
                     callback:(void (^_Nonnull)(BOOL successed))callback {
    [[PTIMClient shared] registerWithConfigure:configure callback:callback];
}

+ (void)sendCommand:(PTCommandMessage * _Nonnull)command
           callback:(PTIMSendCommandCallback _Nonnull)callback {
    [[PTIMClient shared] sendCommand:command callback:callback];
}

+ (BOOL)logout {
    return [[PTIMClient shared] logout];
}

+ (void)disConnect {
    [[PTIMClient shared] disConnect];
}

@end
