//
//  UInt8.swift
//  sipclient
//
//  Created by Marcin Kielesiński on 20.09.2017.
//

import Foundation

extension UInt8 {
    func toBool() -> Bool {
        switch self {
        case 0x01:
            return true
        case 0x00:
            return false
        default:
            return false
        }
    }
}
