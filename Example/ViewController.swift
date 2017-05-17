//
//  ViewController.swift
//  Example
//
//  Created by admin on 2017/5/11.
//  Copyright © 2017年 Putao. All rights reserved.
//

import UIKit
import PTIMLibrary

class ViewController: UIViewController {
    
    let childrenID: Int32 = 60011165
    let appID: String = "1105"

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }
    
    @IBAction func lockButtonAction(_ sender: Any) {
        
        var content = [String: Any]()
        content["state"] = true
        content["lockdelay"] = 1
        
        var value = [String: Any]()
        value["appid"] = appID
        value["type"] = "padlock"
        value["session"] = Int(arc4random()%9999) + 1
        value["content"] = content
        
        let data = try! JSONSerialization.data(withJSONObject: value, options: .prettyPrinted)
        let json = String(data: data, encoding: String.Encoding.utf8) ?? ""
        
        let message = PTCommandMessage()
        message.content = json
        message.toUsrID = childrenID
        message.localID = String(format: "%.3f",NSDate().timeIntervalSince1970)

        
        PTIM.sendCommand(message) { success, result in
            
        }
    }
    
    @IBAction func restButtonAction(_ sender: Any) {
        
        var content = [String: Any]()
        content["state"] = true
        content["availabletime"] = 2
        content["resttime"] = 1
        
        var value = [String: Any]()
        value["appid"] = appID
        value["type"] = "timingrest"
        value["session"] = Int(arc4random()%9999) + 1
        value["content"] = content
        
        let data = try! JSONSerialization.data(withJSONObject: value, options: .prettyPrinted)
        let json = String(data: data, encoding: String.Encoding.utf8) ?? ""
        
        let message = PTCommandMessage()
        message.content = json
        message.toUsrID = childrenID
        message.localID = String(format: "%.3f",NSDate().timeIntervalSince1970)
        
        
        PTIM.sendCommand(message) { success, result in
            
        }
    }
    
    @IBAction func sleepButtonAction(_ sender: Any) {
        
        var content = [String: Any]()
        content["state"] = true
        content["start"] = 1495003500000
        content["end"] = 1495003560000
        content["repeat"] = "1,2,3,4,5" //不重复传空字符串
        
        var value = [String: Any]()
        value["appid"] = appID
        value["type"] = "sleep"
        value["session"] = Int(arc4random()%9999) + 1
        value["content"] = content
        
        let data = try! JSONSerialization.data(withJSONObject: value, options: .prettyPrinted)
        let json = String(data: data, encoding: String.Encoding.utf8) ?? ""
        
        let message = PTCommandMessage()
        message.content = json
        message.toUsrID = childrenID
        message.localID = String(format: "%.3f",NSDate().timeIntervalSince1970)
        
        
        PTIM.sendCommand(message) { success, result in
            
        }
    }
    
    @IBAction func forbiddenButtonAction(_ sender: Any) {
        
        var content = [String: Any]()
        content["state"] = true
        content["start"] = 1494979200
        content["end"] = 1494993600
        content["repeat"] = "1,2,3,4,5"
        content["package"] = ["all"]
        
        var value = [String: Any]()
        value["appid"] = appID
        value["type"] = "appTimeLimit"
        value["session"] = Int(arc4random()%9999) + 1
        value["content"] = content
        
        let data = try! JSONSerialization.data(withJSONObject: value, options: .prettyPrinted)
        let json = String(data: data, encoding: String.Encoding.utf8) ?? ""
        
        let message = PTCommandMessage()
        message.content = json
        message.toUsrID = childrenID
        message.localID = String(format: "%.3f",NSDate().timeIntervalSince1970)
        
        
        PTIM.sendCommand(message) { success, result in
            
        }
    }
    
    @IBAction func limitButtonAction(_ sender: Any) {
        
        var content = [String: Any]()
        content["time"] = 120
        content["package"] = ""
        
        var value = [String: Any]()
        value["appid"] = appID
        value["type"] = "padTimeLimit"
        value["session"] = Int(arc4random()%9999) + 1
        value["content"] = content
        
        let data = try! JSONSerialization.data(withJSONObject: value, options: .prettyPrinted)
        let json = String(data: data, encoding: String.Encoding.utf8) ?? ""
        
        let message = PTCommandMessage()
        message.content = json
        message.toUsrID = childrenID
        message.localID = String(format: "%.3f",NSDate().timeIntervalSince1970)
        
        
        PTIM.sendCommand(message) { success, result in
            
        }
    }
}

