//
//  StringFromClass.swift
//  Mobile CLient
//
//  Created by Marcin Kielesinski on 11.06.2017.
//

import Foundation

extension NSObject {
	var className: String {
		return String(describing: type(of: self))
	}
	
	class var className: String {
		return String(describing: self)
	}
}
