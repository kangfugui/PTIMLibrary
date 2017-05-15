//
//  PTMessageContainer.m
//  PTIMLibrary
//
//  Created by admin on 2017/5/15.
//  Copyright © 2017年 Putao. All rights reserved.
//

#import "PTMessageContainer.h"

@implementation PTMessageContainer

- (instancetype)initWithMessage:(PTCommandMessage *)message
                       callback:(PTIMSendCommandCallback)callback {
    self = [super init];
    if (!self) { return nil; }
    
    self.message = message;
    self.callback = callback;
    
    return self;
}

@end
