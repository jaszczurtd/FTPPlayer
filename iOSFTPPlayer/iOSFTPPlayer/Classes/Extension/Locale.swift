//
//  Locale.swift
//  sipclient
//
//  Created by ministerq on 11.08.2017.
//

import Foundation

protocol Localizable {
    var localized: String { get }
}

extension String: Localizable {
    var localized: String {
        return NSLocalizedString(self, tableName: nil, bundle: Bundle.main, value: "", comment: "")
    }
}

protocol XIBLocalizable {
    var xibLocKey: String? { get set }
}

extension UILabel: XIBLocalizable {
    @IBInspectable var xibLocKey: String? {
        get { return nil }
        set(key) {
            text = key?.localized
        }
    }
}
extension UIButton: XIBLocalizable {
    @IBInspectable var xibLocKey: String? {
        get { return nil }
        set(key) {
            setTitle(key?.localized, for: .normal)
        }
    }
}

extension UITextField: XIBLocalizable {
    @IBInspectable var xibLocKey: String? {
        get { return nil }
        set(key) {
            if attributedPlaceholder != nil {
                let attributes = attributedPlaceholder!.attributes(at: 0, effectiveRange: nil)
                attributedPlaceholder = NSAttributedString(string: key!.localized, attributes:attributes)
            } else {
                placeholder = key?.localized
            }
        }
    }
}

