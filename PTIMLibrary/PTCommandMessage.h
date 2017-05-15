//
//  PTCommandMessage.h
//  PTIMLibrary
//
//  Created by admin on 2017/5/15.
//  Copyright © 2017年 Putao. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM (NSUInteger, PTIMMessageType) {
    PTIMMessageTypeSend = 0,
    PTIMMessageTypeReceive = 1
};

@interface PTCommandMessage : NSObject

@property (copy, nonatomic) NSString *localID;

@property (copy, nonatomic) NSString *content;

@property (assign, nonatomic) int toUsrID;

@property (assign, nonatomic) int timeout;

@end
