#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

// struct untuk menampung data produk.
struct Product {
    string name;
    int stock;
};
bool is_primeNumber(int &);
void showMenu(vector<Product> &);
void addToArray(vector<Product> &, Product &, string &, int &);
void addProduct(vector<Product> &, Product &, int &);
void updateStockProduct(vector<Product> &, string);
void showPrimeNumber(int &);
void createLove(int &);
void saveToFile(vector<Product> &, fstream &);
void readFromFile(vector<Product> &, fstream &, Product &, string &, int &);

int main() {
    string productName, temp, strStock;
    int choice, productStock, height_love, total_loop;
    Product product;
    fstream file;

    //  inisisasi data produk
    vector<Product> arrayProduct;  // vector untuk menampung struct Product

    file.open("product.txt");
    file.close();
    if (file) {
        readFromFile(arrayProduct, file, product, productName, productStock);
    } else {
        // data 1
        productName = "Sport Drink";
        productStock = 60;
        addToArray(arrayProduct, product, productName, productStock);  // add data 1 to vector
        // data 2
        productName = "Roti Q";
        productStock = 40;
        addToArray(arrayProduct, product, productName, productStock);
        saveToFile(arrayProduct, file);
    }

    do {
        system("cls");
        cout << "=====MENU=====" << endl
             << "1. Tampilkan Data" << endl
             << "2. Tambahkan Data" << endl
             << "3. Pengurangan Data" << endl
             << "4. Bilangan Prima" << endl
             << "5. Gambar Love" << endl
             << "0. Keluar" << endl
             << endl
             << "Pilih Menu : ";
        cin >> choice;
        cout << endl;
        if (choice == 1) {
            cout << "///// Daftar Menu /////" << endl
                 << endl;
            showMenu(arrayProduct);
            cout << endl;
            cout << "///// ============ /////" << endl;
        } else if (choice == 2) {
            cout << "1. Tambahkan Jumlah Barang" << endl
                 << "2. Tambahkan Barang Baru" << endl
                 << "Pilih Menu : ";
            cin >> choice;
            cout << endl;
            if (choice == 1) {
                updateStockProduct(arrayProduct, "add");
            } else if (choice == 2) {
                addProduct(arrayProduct, product, total_loop);
            }
        } else if (choice == 3) {
            updateStockProduct(arrayProduct, "minus");
        } else if (choice == 4) {
            cout << "Masukkan banyaknya nilai : ";
            cin >> total_loop;
            showPrimeNumber(total_loop);
        } else if (choice == 5) {
            cout << "Masukkan Tinggi Love (kelipatan 2) : ";
            cin >> height_love;
            cout << endl;
            createLove(height_love);
        } else if (choice != 0) {
            cout << "Pilihan tidak ada." << endl;
            cin.get();
        }
        cin.get();

    } while (choice != 0);

    return 0;
}

void showMenu(vector<Product> &arrayProduct) {
    for (int i = 0; i < arrayProduct.size(); i++) {
        if (!arrayProduct[i].name.empty()) {
            cout << i + 1 << ". " << arrayProduct[i].name << " : " << arrayProduct[i].stock << endl;
        }
    }
    cin.get();
}

void addToArray(vector<Product> &arrayProduct, Product &product, string &productName, int &productStock) {
    product.name = productName;
    product.stock = productStock;
    arrayProduct.push_back(product);
}

void addProduct(vector<Product> &arrayProduct, Product &product, int &total_loop) {
    fstream file;
    string productName;
    int productStock;
    cout << "Jumlah Data : ";
    cin >> total_loop;
    for (int i = 0; i < total_loop; i++) {
        cout << "Nama Barang : ";
        cin.ignore();
        getline(cin, productName);
        cout << "Banyak : ";
        cin >> productStock;
        addToArray(arrayProduct, product, productName, productStock);
        saveToFile(arrayProduct, file);
    }
    cin.ignore();
}

void updateStockProduct(vector<Product> &arrayProduct, string typeMode) {
    fstream file;
    string productName, stringTypeMode;
    int productStock, amountStock, indexArray;
    if (typeMode == "add") {
        stringTypeMode = "ditambahkan";
    } else if (typeMode == "minus") {
        stringTypeMode = "dikurangi";
    }
    showMenu(arrayProduct);
    cout << "Pilih Menu yang ingin " << stringTypeMode << " : ";
    cin >> indexArray;
    cout << endl;
    indexArray -= 1;
    if (indexArray >= 0 && indexArray < arrayProduct.size()) {
        productName = arrayProduct[indexArray].name;
        productStock = arrayProduct[indexArray].stock;
        if (!productName.empty()) {
            cout << "Anda memilih " << productName << endl;
            cout << "Jumlah " << productName << " saat ini : " << productStock << endl;
            cout << "Masukkan Jumlah : ";
            cin >> amountStock;
            amountStock = typeMode == "minus" ? amountStock * -1 : amountStock;
            productStock += amountStock;
            arrayProduct[indexArray].stock = productStock;
            cout << "Stok berhasil " << stringTypeMode << " menjadi : " << productStock << endl;
            saveToFile(arrayProduct, file);
        } else {
            cout << "Gagal menambahkan Stok." << endl;
        }
    } else {
        cout << "Pilihan tidak ada." << endl;
    }
    cin.ignore();
}

bool is_primeNumber(int &number) {
    if (number < 2) {  // bilangan kurang dari 2 : bukan prima
        return false;
    } else if (number == 2) {  // bilangan sama dengan 2 : prima
        return true;
    } else if (number % 2 == 0) {  // bilangan kelipatan 2 : bukan prima
        return false;
    }

    for (int i = 3; i < number; i += 2) {
        if (number % i == 0) {  // bilangan habis dibagi i : bukan prima,
            return false;       // return false, dan break the loop
        }
    }
    return true;
}

void showPrimeNumber(int &total_loop) {
    int number_loop = 0, total_primeNumber = 0;
    // looping hingga prima yang ditampilkan sesuai dengan input user
    while (total_primeNumber < total_loop) {
        if (is_primeNumber(number_loop)) {
            // jika prima, tampilkan bilangan dan increment total_primenumber
            cout << number_loop << " ";
            total_primeNumber += 1;
        }
        number_loop += 1;
    }
    cout << endl;
    cin.ignore();
}

void createLove(int &heightLove) {
    float love_bot = heightLove % 2 ? heightLove + 1 : heightLove;
    love_bot = love_bot - 2;
    int love_top = love_bot / 2;
    for (int i = 0; i < love_top; i++) {
        if (i < love_bot / 4) {
            continue;
        }
        for (int j = 0; j < love_top - i; j++) {
            cout << "  ";
        }
        for (int j = 0; j < i; j++) {
            cout << " *  ";
        }
        for (int j = 0; j < love_top - i; j++) {
            cout << "    ";
        }
        for (int j = 0; j < i; j++) {
            cout << " *  ";
        }
        cout << endl;
    }

    for (int i = love_bot; i > 0; i--) {
        if (i == love_bot) {
            continue;
        }
        for (int j = 0; j < love_bot - i; j++) {
            cout << "  ";
        }
        for (int j = 0; j < i; j++) {
            cout << " *  ";
        }
        cout << endl;
    }
    cin.ignore();
}

void saveToFile(vector<Product> &arrayProduct, fstream &file) {
    file.open("product.txt", ios::out);
    for (int i = 0; i < arrayProduct.size(); i++) {
        if (!arrayProduct[i].name.empty()) {
            file << arrayProduct[i].name << "\n";
            file << arrayProduct[i].stock << "\n";
        }
    }
    file.close();
}

void readFromFile(vector<Product> &arrayProduct, fstream &file, Product &product, string &productName, int &productStock) {
    string strStock;
    file.open("product.txt", ios::in);
    for (int i = 0; i > -1; i += 2) {
        getline(file, productName);
        if (productName.empty()) {
            break;
        }
        getline(file, strStock);
        stringstream intStock(strStock);
        intStock >> productStock;
        addToArray(arrayProduct, product, productName, productStock);
    }
}
