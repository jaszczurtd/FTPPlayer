//
//	String.swift
//
//  Mobile Client
//
//  Created by Marcin Kielesinski on 17.06.2017.
//

extension String: LocalizedError {
    public var errorDescription: String? { return self }
}

extension String {
    
    func toBool() -> Bool? {
        switch self {
            case "True", "true", "yes", "1":
                return true
            case "False", "false", "no", "0":
                return false
            default:
                return nil
        }
    }
    
    var nilIfEmpty: String? {
        return self.isEmpty ? nil : self
    }
    
    var isEmptyOrSpacesOnlyField: Bool {
        
        var isEmpty = false;
        
        if(self.trimmingCharacters(in: .whitespaces).isEmpty){
            isEmpty = true
        }
        
        if(self.replacingOccurrences(of: " ", with: "").count < 1) {
            isEmpty = true
        }
        
        return isEmpty;
    }


    func fileName() -> String {
        
        if let fileNameWithoutExtension = NSURL(fileURLWithPath: self).deletingPathExtension?.lastPathComponent {
            return fileNameWithoutExtension
        } else {
            return ""
        }
    }
    
    func fileExtension() -> String {
        
        if let fileExtension = NSURL(fileURLWithPath: self).pathExtension {
            return fileExtension
        } else {
            return ""
        }
    }
    
    func stringByAppendingPathComponent(path: String) -> String {
        let nsSt = self as NSString
        return nsSt.appendingPathComponent(path)
    }
    
    var pathComponents: [String] {
        return (self as NSString).pathComponents
    }
    
    func slice(from: String, to: String) -> String? {
        
        return (range(of: from)?.upperBound).flatMap { substringFrom in
            (range(of: to, range: substringFrom..<endIndex)?.lowerBound).map { substringTo in
                String(self[substringFrom..<substringTo])
            }
        }
    }
    
    func camelCaseToWords() -> String {
        return unicodeScalars.reduce("") {
            if CharacterSet.uppercaseLetters.contains($1) {
                if $0.count > 0 {
                    return ($0 + " " + String($1).lowercased())
                }
            }
            return $0 + String($1)
        }
    }
    
    func deletingPrefix(_ prefix: String) -> String {
        guard self.hasPrefix(prefix) else { return self }
        return String(self.dropFirst(prefix.count))
    }
    
}
