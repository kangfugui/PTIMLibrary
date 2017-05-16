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

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }
    
    @IBAction func lockButtonAction(_ sender: Any) {
        
        let lock = PTLockCommand(state: true, lockdelay: 5)
        let command = PTCommandContent(content: lock, type: .lock)
        print(command)
    }
}

