//Update and Report functions for the shop inventory management system
//The update function handles selling to customers (reduces the stock)
//The report function handles managing inventory (shows stock, value and low stock)
#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
using namespace std;

// One product in the shop (uses the same details as the add function)
struct Product {
    int productID;
    string itemName;
    string supplier;
    int quantity;
    double price1;       // entry price (what the shop paid)
    double price2;       // selling price (what the customer pays)
    string expiryDate;
};

// The shared list of products. The add function should push_back into this
// list, and deleteproduct should remove from it.
vector<Product> products;

//selling to the customers/updating the stock
void updateproduct() {
    int productID;
    int quantity;

    cout << "Enter product ID: ";
    cin >> productID;
    cout << "Enter quantity of goods sold: ";
    cin >> quantity;

    for (Product &p : products) {
        if (p.productID == productID) {

            if (quantity > p.quantity) {
                cout << "Not enough stock. Only " << p.quantity
                     << " of " << p.itemName << " left." << endl;
                return;
            }

            p.quantity = p.quantity - quantity;   // reduce the stock
            cout << "Sold " << quantity << " x " << p.itemName << endl;
            cout << "Total sales amount: " << quantity * p.price2 << endl;
            cout << "Remaining stock: " << p.quantity << endl;
            return;
        }
    }
    cout << "Product not found." << endl;
}

//managing the inventory
void report() {
    const int lowStockLimit = 5;
    double totalValue = 0;

    if (products.empty()) {
        cout << "No products in the inventory." << endl;
        return;
    }

    cout << "\n=== INVENTORY REPORT ===" << endl;
    cout << left << setw(8) << "ID" << setw(16) << "Name" << setw(14) << "Supplier"
         << setw(8) << "Qty" << setw(10) << "Price" << setw(12) << "Expiry" << endl;

    for (const Product &p : products) {
        cout << left << setw(8) << p.productID << setw(16) << p.itemName
             << setw(14) << p.supplier << setw(8) << p.quantity
             << setw(10) << p.price2 << setw(12) << p.expiryDate << endl;
        totalValue = totalValue + p.quantity * p.price2;
    }

    cout << "\nTotal stock value (at selling price): " << totalValue << endl;

    cout << "Running low on: ";
    bool anyLow = false;
    for (const Product &p : products) {
        if (p.quantity <= lowStockLimit) {
            cout << p.itemName << "  ";
            anyLow = true;
        }
    }
    if (!anyLow) cout << "none";
    cout << endl;
}

// Quick test: delete this main() when joining the group's code
int main() {
    products.push_back({1, "Sugar", "Mumias", 20, 120, 300, "2027-05-01"});
    products.push_back({2, "Milk", "Brookside", 4, 50, 125, "2026-12-10"});

    updateproduct();   // try: ID 1, sell 3
    report();
    return 0;
}
