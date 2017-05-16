//
//  PTCommandContent.swift
//  PTIMLibrary
//
//  Created by admin on 2017/5/16.
//  Copyright © 2017年 Putao. All rights reserved.
//

import Foundation

enum PTCommandType: String {
    case lock = "padlock"
    case rest = "timingrest"
    case sleep = "sleep"
    case limit = "timeLimit"
    case current = "currentApp"
}

struct PTCommandContent<T> {
    
    let appid: String
    let type: String
    let session: Int
    let content: T
    
    init(content: T, type: PTCommandType) {
        self.content = content
        self.appid = ""
        self.session = Int(arc4random()%9999) + 1
        self.type = type.rawValue
    }
}

struct PTLockCommand {
    
    let state: Bool
    let lockdelay: Int
    
    init(state: Bool, lockdelay: Int) {
        self.state = state
        self.lockdelay = lockdelay
    }
}

struct PTRestCommand {
    
    let state: Bool
    let availabletime: Int
    let resttime: Int
    
    init(state: Bool, availabletime: Int, resttime:Int) {
        self.state = state
        self.availabletime = availabletime
        self.resttime = resttime
    }
}

struct PTSleepCommand {
    
    let state: Bool
    let start: Int
    let end: Int
    let `repeat`: String
    
    init(state: Bool, start: Int, end: Int, `repeat`: String) {
        self.state = state
        self.start = start
        self.end = end
        self.`repeat` = `repeat`
    }
}

struct PTForbiddenCommand {
    
    let state: Bool
    let start: Int
    let end: Int
    let `repeat`: String
    let package: [String]
    
    init(state: Bool, start: Int, end: Int, `repeat`: String, package: [String]) {
        self.state = state
        self.start = start
        self.end = end
        self.`repeat` = `repeat`
        self.package = package
    }
}

struct PTLimitCommand {
    
    let package: String
    let time: Int
    
    init(package: String, time: Int) {
        self.package = package
        self.time = time
    }
}
