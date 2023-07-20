#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class GroceryStore {
private:
    int productCode;
    float price;
    float discount;
    string productName;

public:
    void menu();
    void adminMenu();
    void buyerMenu();
    void addProduct();
    void modifyProduct();
    void deleteProduct();
    void listProducts();
    void generateReceipt();
};

void GroceryStore::menu() {
    int choice;
    string email;
    string password;

    while (true) {
        cout << "                                     \n";
        cout << "|*********Grocery Store Menu**********|\n";
        cout << "                                     \n";
        cout << "         1. Administrator            \n";
        cout << "         2. Buyer                    \n";
        cout << "         3. Exit                     \n";
        cout << "\n";
        cout << "Please Select : ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Please enter Email: ";
                cin >> email;
                cout << "Please enter Password: ";
                cin >> password;

                if (email == "ycce@ycce" && password == "ycce") {
                    cout <<"**********Welcome**********\n";
                    cout <<"\n";
                    adminMenu();
                } else {
                    cout << "Invalid Email/Password";
                }
                break;
            case 2:
                buyerMenu();
                break;
            case 3:
                exit(0);
            default:
                cout << "Invalid choice";
                break;
        }
    }
}

void GroceryStore::adminMenu() {
    int choice;

    while (true) {
        cout << "     Administrator Menu       \n";
        cout << "     1. Add Product          \n";
        cout << "     2. Modify Product       \n";
        cout << "     3. Delete Product       \n";
        cout << "     4. Back to main menu    \n\n";
        cout << "Please Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                modifyProduct();
                break;
            case 3:
                deleteProduct();
                break;
            case 4:
                return;
            default:
                cout << "     Please Enter Valid Choice \n";
                break;
        }
    }
}

void GroceryStore::buyerMenu() {
    int choice;

    while (true) {
        cout << "\n";
        cout << "\n";
        cout << "     1. Buy Product      \n";
        cout << "     2. Go back          \n\n";
        cout << "Enter your choice : ";
        cin >> choice;

        switch (choice) {
            case 1:
                listProducts();
                generateReceipt();
                break;
            case 2:
                return;
            default:
                cout << " Invalid Choice      \n";
                break;
        }
    }
}

void GroceryStore::addProduct() {
    fstream data;
    int code;
    int token = 0;
    int c;
    float p;
    float d;
    string n;

    while (true) {
        cout << "   * Add new product *     \n";
        cout << "Please enter product code  : ";
        cin >> code;

        cout << "Please enter product name  : ";
        cin >> productName;

        cout << "Please enter product price : ";
        cin >> price;

        cout << "Discount on product        : ";
        cin >> discount;

        data.open("database.txt", ios::in);
        if (!data) {
            data.open("database.txt", ios::in | ios::out);
            data << " " << code << " " << productName << " " << price << " " << discount << "\n";
            data.close();
        } else {
            data >> c >> n >> p >> d;
            while (!data.eof()) {
                if (c == code) {
                    token++;
                }
                data >> c >> n >> p >> d;
            }
            data.close();
        }
        if (token == 1) {
            cout << "Product code already exists! Please try again.\n";
        } else {
            data.open("database.txt", ios::in | ios::out | ios::app);
            data << " " << code << " " << productName << " " << price << " " << discount << "\n";
            data.close();
            cout << "Record Inserted\n";
            break;
        }
    }
}

void GroceryStore::modifyProduct() {
    fstream data, data1;
    int productCode;
    int token = 0;
    int c;
    float p;
    float d;
    string n;

    cout << "Modify the record\n";
    cout << "Product Code: ";
    cin >> productCode;

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "File does not exist\n";
    } else {
        data1.open("database1.txt", ios::app | ios::out);

        while (data >> c >> n >> p >> d) {
            if (productCode == c) {
                cout << "Product new code: ";
                cin >> c;
                cout << "Name of the product: ";
                cin >> n;
                cout << "Price: ";
                cin >> p;
                cout << "Discount: ";
                cin >> d;
                data1 << " " << c << " " << n << " " << p << " " << d << "\n";
                cout << "Record Edited\n";
                token++;
            } else {
                data1 << " " << c << " " << n << " " << p << " " << d << "\n";
            }
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0) {
            cout << "Record not found in the database\n";
        }
    }
}

void GroceryStore::deleteProduct() {
    int productCode;
    int token = 0;

    cout << "Delete product\n";
    cout << "Product code: ";
    cin >> productCode;

    fstream data, data1;
    data.open("database.txt", ios::in);
    data1.open("database1.txt", ios::out);

    if (!data) {
        cout << "File does not exist\n";
    } else {
        int c;
        float p;
        float d;
        string n;

        while (data >> c >> n >> p >> d) {
            if (productCode == c) {
                cout << "Product deleted successfully\n";
                token++;
            } else {
                data1 << " " << c << " " << n << " " << p << " " << d << "\n";
            }
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0) {
            cout << "Record does not exist\n";
        }
    }
}

void GroceryStore::listProducts() {
    fstream data;
    data.open("database.txt", ios::in);
    cout << "\n\n___________________________________________________________________________________________________________________________________________________________\n";
    cout << "Product Code\tProduct Name\tPrice\n";
    while (data >> productCode >> productName >> price >> discount) {
        cout << productCode << "\t\t" << productName << "\t\t" << price << "\n";
    }
    data.close();
}

void GroceryStore::generateReceipt() {
    m:
    fstream data;

    int arrc[100];
    int arrq[100];
    char choice;
    int c = 0;
    float amount = 0;
    float dis = 0;
    float total = 0;

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "Empty database\n";
    } else {
        data.close();

        cout << "           \n";
        cout << "                                                   \n";
        cout << "           *********Please Place Your Order*********\n";
        cout << "          \n";
        cout << "         \n";

        do {
            cout << "Enter product code: ";
            cin >> arrc[c];
            cout << "Enter product quantity: ";
            cin >> arrq[c];

            for (int i = 0; i < c; i++) {
                if (arrc[c] == arrc[i]) {
                    cout << "Duplicate code! Please try again later.\n";
                    goto m;
                }
            }
            c++;

            cout << "Do you want to buy another product? (y/n): ";
            cin >> choice;
        } while (choice == 'y' || choice == 'Y');
        cout << "---------------------------------------------------------------------------------------------------------------";
        cout << "                                            Receipt\n";
        cout << "---------------------------------------------------------------------------------------------------------------";
        cout << "\nProduct Code\tProduct Name\tProduct Quantity\tPrice\t\tAmount\t\tAmount with discount\n";

        for (int i = 0; i < c; i++) {
            data.open("database.txt", ios::in);
            while (data >> productCode >> productName >> price >> discount) {
                if (productCode == arrc[i]) {
                    amount = price * arrq[i];
                    dis = (amount * discount / 100);
                    total += (amount - dis);
                    cout << "\n" << productCode << "\t\t" << productName << "\t\t" << arrq[i] << "\t\t\t" << price << "\t\t" << amount << "\t\t" << dis << endl;
                }
            }
            data.close();
        }
    }

    cout << "\n\n-----------------------------------------------------------------------------------------------------------\n";
    
    cout << "Total amount: " << total << endl;
}

int main() {
    GroceryStore store;
    store.menu();
    return 0;
}
