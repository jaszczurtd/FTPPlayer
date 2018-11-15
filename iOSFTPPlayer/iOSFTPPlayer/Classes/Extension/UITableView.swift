//
//  UITableView.swift
//  sipclient
//
//

import UIKit

extension UITableViewCell {
    static var reuseIdentifier: String { return String(describing: self) }
}

extension UITableView {
    func register<T: UITableViewCell>(_ cellType: T.Type) {
        let nib = UINib(nibName: String(describing: T.self), bundle: nil)
        return register(nib, forCellReuseIdentifier: T.reuseIdentifier)
    }
    func dequeueReusableCell<T: UITableViewCell>(for indexPath: IndexPath, cellType: T.Type = T.self) -> T {
        guard let cell = dequeueReusableCell(withIdentifier: cellType.reuseIdentifier, for: indexPath) as? T else {
            fatalError("Failed to dequeue a cell with identifier \(cellType.reuseIdentifier) matching type \(cellType.self)")
        }
        return cell
    }
}

extension UITableView {
    func reloadData(completion: @escaping () -> Void) {
        UIView.animate(withDuration: 0, animations: { self.reloadData() })
        { _ in completion() }
    }
}

extension UICollectionView {
    func reloadData(completion: @escaping () -> Void) {
        UIView.animate(withDuration: 0, animations: { self.reloadData() })
        { _ in completion() }
    }
}
