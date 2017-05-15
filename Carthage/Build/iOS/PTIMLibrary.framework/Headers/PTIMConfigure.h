//
//  PTIMConfigure.h
//  PTIMLibrary
//
//  Created by admin on 2017/5/12.
//  Copyright © 2017年 Putao. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM (NSUInteger, PTIMServiceDomain) {
    PTIMServiceDomainTest = 0,
    PTIMServiceDomainProduction = 1
};

@interface PTIMConfigure : NSObject

@property (strong, nonatomic) NSString *usrID;
@property (assign, nonatomic) int appID;
@property (strong, nonatomic) NSString *deviceID;
@property (strong, nonatomic) NSString *pushToken;
@property (assign, nonatomic) PTIMServiceDomain domain;

@end
