//
//  UINibRegisterHelper.swift
//  Mobile Client
//
//  Created by Marcin Kielesinski on 12.06.2017.
//

import Foundation
import UIKit

extension UITableView {
    
    func reg(nibName: String) -> (UINib) {
        return UINib(nibName: nibName, bundle: nil)
    }
    
    func register(nibName: String) {
        self.register(reg(nibName: nibName), forCellReuseIdentifier: nibName)
    }
}
