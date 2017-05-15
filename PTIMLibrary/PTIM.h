//
//  PTIM.h
//  PTIMLibrary
//
//  Created by admin on 2017/5/15.
//  Copyright © 2017年 Putao. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PTIMClient.h"

@interface PTIM : NSObject

+ (void)registerWithConfigure:(PTIMConfigure * _Nonnull)configure
                     callback:(void (^_Nonnull)(BOOL successed))callback;

+ (void)sendCommand:(PTCommandMessage * _Nonnull)command
           callback:(PTIMSendCommandCallback _Nonnull)callback;

@end
