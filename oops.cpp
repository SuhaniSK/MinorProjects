/* ERP is a type of software that integrates core business processes such as
 finance, human resources, inventory, manufacturing, and sales into a single
 system. It allows organizations to streamline operations, improve
collaboration, and make data-driven decisions.*/
#include <iostream>
#include <string>

using namespace std;


const int MAX_PRODUCTS = 100; // Maximum number of products
const int MAX_EXPENSES = 100; // Maximum number of expenses

class Product {
public:
    int id;
    string name;
    double price;
    int quantity;

    // Default constructor
    Product() {}

    // Product parameterised constructor
    Product(int id, string name, double price, int quantity) {
        this->id = id;
        this->name = name;
        this->price = price;
        this->quantity = quantity;
    }

    // Function to display product information
    void display() {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Price: Rs" << price << endl;
        cout << "Quantity: " << quantity << endl;
    }
};

class Expense {
public:
    string description;
    double amount;

    // Default constructor
    Expense() {}

    // Expense constructor
    Expense(string description, double amount) {
        this->description = description;
        this->amount = amount;
    }

    // Function to display expense information
    void display() {
        cout << "Description: " << description << endl;
        cout << "Amount: Rs" << amount << endl;
    }
};

Product products[MAX_PRODUCTS]; // Array to store products
Expense expenses[MAX_EXPENSES]; // Array to store expenses
int productCount = 0; // Tracks the number of products in the array
int expenseCount = 0; // Tracks the number of expenses in the array

// Function to add a new product
void addProduct() {
    if (productCount < MAX_PRODUCTS) {
        int id, quantity;
        string name;
        double price;

        cout << "Enter product details:" << endl;
        cout << "ID: ";
        cin >> id;
        cout << "Name: ";
        cin >> name;
        cout << "Price: ";
        cin >> price;
        cout << "Quantity: ";
        cin >> quantity;

        products[productCount++] = Product(id, name, price, quantity);
        cout << "Product added successfully!" << endl;
    } else {
        cout << "Cannot add more products. Array is full." << endl;
    }
}

// Function to display all products
void displayProducts() {
    if (productCount == 0) {
        cout << "No products found." << endl;
    } else {
        cout << "Products:" << endl;
        for (int i = 0; i < productCount; i++) {
            products[i].display();
            cout << endl;
        }
    }
}

// Function to search for a product by ID
void searchProductByID() {
    if (productCount == 0) {
        cout << "No products found." << endl;
        return;
    }

    int id;
    cout << "Enter the ID of the product to search: ";
    cin >> id;

    int found = 0;
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            products[i].display();
            found = 1;
            break;
        }
    }

    if (!found) {
        cout << "Product with ID " << id << " not found." << endl;
    }
}

// Function to update the price of a product by ID
void updateProductPrice() {
    if (productCount == 0) {
        cout << "No products found." << endl;
        return;
    }

    int id;
    double newPrice;
    cout << "Enter the ID of the product to update: ";
    cin >> id;

    int found = 0;
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            cout << "Enter the new price: ";
            cin >> newPrice;
            products[i].price = newPrice;
            cout << "Price updated successfully!" << endl;
            found = 1;
            break;
        }
    }

    if (!found) {
        cout << "Product with ID " << id << " not found." << endl;
    }
}
//Function to manage expense
void manageExpenses() {
    if (expenseCount < MAX_EXPENSES) {
        string description;
        double amount;

        cout << "Enter expense details:" << endl;
        cout << "Description: ";
        cin>>description;
        
        cout << "Amount: ";
        cin >> amount;

        expenses[expenseCount++] = Expense(description, amount);
        cout << "Expense added successfully!" << endl;
    } else {
        cout << "Cannot add more expenses. Array is full." << endl;
    }
}
// Function to display all expenses
void displayExpenses() {
    if (expenseCount == 0) {
        cout << "No expenses found." << endl;
    } else {
        cout << "Expenses:" << endl;
        for (int i = 0; i < expenseCount; i++) {
            expenses[i].display();
            cout << endl;
        }
    }
}

// Function to manage finance
void manageFinance() {
    double totalRevenue = 0.0;
    double totalExpenses = 0.0;

    // Calculate total revenue from product sales
    for (int i = 0; i < productCount; i++) {
        totalRevenue += products[i].price * products[i].quantity;
    }

    // Calculate total expenses
    for (int i = 0; i < expenseCount; i++) {
        totalExpenses += expenses[i].amount;
    }

    // Calculate profit
    double profit = totalRevenue - totalExpenses;

    cout << "Finance Management Summary:" << endl;
    cout << "Total Revenue: Rs" << totalRevenue << endl;
    cout << "Total Expenses: Rs" << totalExpenses << endl;
    cout << "Profit: Rs" << profit << endl;
}


int main() {
    cout << "Welcome to the Management System!" << endl;

    int choice;
    do {
        cout << "Menu:\n1. Add Product\n2. Display Products\n3. Search Product by ID\n4. Update Product Price\n5. Manage Expenses\n6. Display Expenses\n7. Manage Finance\n8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                displayProducts();
                break;
            case 3:
                searchProductByID();
                break;
            case 4:
                updateProductPrice();
                break;
            case 5:
                manageExpenses();
                break;
            case 6:
                displayExpenses();
                break;
            case 7:
                manageFinance();
                break;
            case 8:
                cout << "Exiting the program...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 8);

    return 0;
}
/*Products:
Laptops: Dell Inspiron 15, HP Pavilion x360, Lenovo ThinkPad
Smartphones: iPhone 12 Pro, Samsung Galaxy S21, Google Pixel 5
Office Supplies: Pens, Notebooks, Staplers, Sticky Notes
Groceries: Milk, Bread, Eggs, Vegetables, Fruits
Clothing: T-shirts, Jeans, Dresses, Shoes

Expenses:
Rent: Monthly rental payment for office space or warehouse
Salaries: Payments to employees, including salaries, wages, and bonuses
Utilities: Electricity, water, internet, and phone bills
Supplies: Purchases of office supplies, stationery, and consumables
Marketing: Advertising expenses, promotional materials, and campaigns
Maintenance: Repairs and maintenance for equipment, vehicles, and facilities*/