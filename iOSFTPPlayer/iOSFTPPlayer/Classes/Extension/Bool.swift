//
//  Bool.swift
//  sipclient
//
//  Created by Marcin Kielesiński on 20.09.2017.
//

import Foundation

extension Bool {
    
    func toRaw() -> uint_fast8_t {
        switch self {
        case true:
            return 0x01
        case false:
            return 0x00
        }
    }
    
}


