//
//  ViewController.swift
//  iOSFTPPlayer
//
//  Created by ministerq on 14/11/2018.
//  Copyright © 2018 Profi-Soft. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        if let client = FTPClient.init(host: "host", port: 21, username: "user", password: "password") {
            if let contents = client.listContents(atPath: "/", showHiddenFiles: true) {
        
                dbg("dir contents: \(contents)")
                
            }
        }
        
    }


}

