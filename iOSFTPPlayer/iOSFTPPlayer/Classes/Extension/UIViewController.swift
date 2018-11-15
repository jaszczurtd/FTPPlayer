//
//  UIViewController.swift
//  sipclient
//
//  Created by Mateusz Łudzeń on 11/09/2017.
//

import UIKit

extension UIViewController {
    
    func hideKeyboardWhenTappedAround() {
        let tap: UITapGestureRecognizer = UITapGestureRecognizer(target: self, action: #selector(UIViewController.endEditing))
        tap.cancelsTouchesInView = false
        view.addGestureRecognizer(tap)
    }
    
    func dismissKeyboard() {
        view.endEditing(true)
    }
    
    @objc func endEditing() {
        dismissKeyboard()
    }
    
    func hideBackButtonTitle() {
        navigationItem.hidesBackButton = true
        let item = UIBarButtonItem(image: #imageLiteral(resourceName: "arrow_back1"), style: .plain, target: self, action: #selector(goBack))
        navigationItem.leftBarButtonItem = item
    }
    
    @objc func goBack() {
        navigationController?.popViewController(animated: true)
    }
    
    func presentAlert(title: String? = nil, message: String? = nil) {
        let alert = UIAlertController(title: title, message: message, preferredStyle: .alert)
        alert.addAction(UIAlertAction(title: "ok".localized, style: .default, handler: nil))
        
        present(alert, animated: true)
    }
    
    func presentAlertWithCompletion(title: String, message: String, completion: @escaping () -> Void) {
        
        let alert : UIAlertController = UIAlertController(title: title, message: message, preferredStyle: UIAlertController.Style.alert)
        
        let action : UIAlertAction = UIAlertAction(title: "ok".localized, style: .cancel) { action -> Void in
            alert.dismiss(animated: true, completion: nil)
            completion()
        }
        
        alert.addAction(action)
        
        present(alert, animated: true)
    }
    
    func presentAlertWithCompletion(title: String, message: String, completionOK: @escaping () -> Void, completionCancel: @escaping () -> Void) {
        
        let alert : UIAlertController = UIAlertController(title: title, message: message, preferredStyle: UIAlertController.Style.alert)
        
        let action : UIAlertAction = UIAlertAction(title: "ok".localized, style: .default) { action -> Void in
            alert.dismiss(animated: true, completion: nil)
            completionOK()
        }
        
        let actionCancel: UIAlertAction = UIAlertAction(title: "label.not.now".localized, style: .cancel) { action -> Void in
            alert.dismiss(animated: true, completion: nil)
            completionCancel()
        }
        
        alert.addAction(action)
        alert.addAction(actionCancel)
        
        present(alert, animated: true)
    }

    func setTabBarHidden(_ hidden: Bool, animated: Bool = true, duration: TimeInterval = 0.3) {
        if animated {
            if let frame = self.tabBarController?.tabBar.frame {
                let factor: CGFloat = hidden ? 1 : -1
                let y = self.view.frame.size.height + frame.size.height * factor
                UIView.animate(withDuration: duration, animations: {
                    self.tabBarController?.tabBar.frame = CGRect(x: frame.origin.x, y: y, width: frame.width, height: frame.height)
                })
                return
            }
        }
        self.tabBarController?.tabBar.isHidden = hidden
    }
}
