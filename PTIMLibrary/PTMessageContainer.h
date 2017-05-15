//
//  PTMessageContainer.h
//  PTIMLibrary
//
//  Created by admin on 2017/5/15.
//  Copyright © 2017年 Putao. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PTIMHandler.h"
#import "PTCommandMessage.h"

@interface PTMessageContainer : NSObject

- (instancetype)initWithMessage:(PTCommandMessage *)message
                       callback:(PTIMSendCommandCallback)callback;

@property (strong, nonatomic) PTCommandMessage *message;
@property (copy, nonatomic) PTIMSendCommandCallback callback;

@end
