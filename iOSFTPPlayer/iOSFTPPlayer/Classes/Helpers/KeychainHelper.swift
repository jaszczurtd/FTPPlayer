//
//  Created by Marcin Kielesiński on 10.08.2017.
//

import Foundation
import KeychainAccess

class KeychainHelper {
    static var keychain: Keychain = Keychain()

    static func setValue(key: String, value: String) {
        do {
            if(KeychainHelper.removeValue(key: key)) {
                try KeychainHelper.keychain.set(value, key: key)
            }
        } catch let error {
            dbge("Error saving keychain item: \(error.localizedDescription)")
        }

    }
    
    static func getValue(key: String) -> String {
        var result = ""
        if key.count > 0 {
            do {
                result = try KeychainHelper.keychain.getString(key) ?? ""
            } catch let error {
                dbge("keychain error: \(error.localizedDescription)")
            }
        }
        return result
    }
    
    @discardableResult
    static func removeValue(key: String) -> Bool {
        do {
            try KeychainHelper.keychain.remove(key)
            
            return true
        } catch let error {
            dbge("error: \(error)")
            
            return false
        }
    }
    
    static func clear() {
        do {
            try KeychainHelper.keychain.removeAll()
        } catch let error {
            dbge("error: \(error)")
        }
    }
    
}
