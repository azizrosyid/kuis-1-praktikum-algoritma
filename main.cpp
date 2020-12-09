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

// declaration function
bool is_primeNumber(int &);
void showMenu();
void addToArray();
void addProduct(int &);
void updateStockProduct(string);
void showPrimeNumber(int &);
void createLove(int &);
void saveToFile();
void readFromFile();

//  inisisasi data produk
// vector yang didalamnya berisi struct product
vector<Product> arrayProduct;

// Insisiasi stuct product
Product product;

// inisiasi fstream
fstream file;

// inisiasi variable global
string productName;
int productStock;

int main() {
    string temp, strStock;
    int choice, height_love, total_loop;

    file.open("product.txt");
    file.close();
    if (file) {          // jika file sudah ada maka
        readFromFile();  // read data from file product.txt
    } else {
        // data 1
        productName = "Sport Drink";
        productStock = 60;
        addToArray();  // add data 1 to vector
        // data 2
        productName = "Roti Q";
        productStock = 40;
        addToArray();
        saveToFile();
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
            showMenu();  // menampilkan menu yang ada
            cout << endl;
            cout << "///// ============ /////" << endl;
        } else if (choice == 2) {
            cout << "1. Tambahkan Jumlah Barang" << endl
                 << "2. Tambahkan Barang Baru" << endl
                 << "Pilih Menu : ";
            cin >> choice;
            cout << endl;
            if (choice == 1) {
                updateStockProduct("add");
            } else if (choice == 2) {
                addProduct(total_loop);
            }
        } else if (choice == 3) {
            updateStockProduct("minus");
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

// fungsi untuk melooping vector kemudian menampilkan menu
void showMenu() {
    for (int i = 0; i < arrayProduct.size(); i++) {                                                   //looping vector
        if (!arrayProduct[i].name.empty()) {                                                          // jika tidak empty
            cout << i + 1 << ". " << arrayProduct[i].name << " : " << arrayProduct[i].stock << endl;  // menampilkan element vector
        }
    }
    cin.get();
}

// fungsi untuk menambahkan struct ke vector
void addToArray() {
    product.name = productName;  // input productname to struct
    product.stock = productStock;
    arrayProduct.push_back(product);  // menambahkan struct ke vector
}

// fungsi untuk menambahkan product baru
void addProduct(int &total_loop) {
    cout << "Jumlah Data : ";
    cin >> total_loop;
    for (int i = 0; i < total_loop; i++) {
        cout << "Nama Barang : ";
        cin.ignore();
        getline(cin, productName);
        cout << "Banyak : ";
        cin >> productStock;
        addToArray();
        saveToFile();
    }
    cin.ignore();
}

// fungsi untuk update stok
void updateStockProduct(string typeMode) {
    string productNameVector, stringTypeMode;
    int productStockVector, amountStock, indexArray;
    if (typeMode == "add") {
        stringTypeMode = "ditambahkan";
    } else if (typeMode == "minus") {
        stringTypeMode = "dikurangi";
    }
    showMenu();
    cout << "Pilih Menu yang ingin " << stringTypeMode << " : ";
    cin >> indexArray;
    cout << endl;
    indexArray -= 1;
    if (indexArray >= 0 && indexArray < arrayProduct.size()) {
        productNameVector = arrayProduct[indexArray].name;
        productStockVector = arrayProduct[indexArray].stock;
        if (!productNameVector.empty()) {
            cout << "Anda memilih " << productNameVector << endl;
            cout << "Jumlah " << productNameVector << " saat ini : " << productStockVector << endl;
            cout << "Masukkan Jumlah : ";
            cin >> amountStock;                                                  // input jumlah stock yang akan ditambahkan
            amountStock = typeMode == "minus" ? amountStock * -1 : amountStock;  // jika mode minus maka stok yang akan ditambah dikali -1
            productStockVector += amountStock;
            arrayProduct[indexArray].stock = productStockVector;  // update nilai di vector
            cout << "Stok berhasil " << stringTypeMode << " menjadi : " << productStockVector << endl;
            saveToFile();  //update data di file
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

void saveToFile() {
    file.open("product.txt", ios::out);  //open file
    for (int i = 0; i < arrayProduct.size(); i++) {
        if (!arrayProduct[i].name.empty()) {  // jika product name tidak kosong maka save to file
            file << arrayProduct[i].name << "\n";
            file << arrayProduct[i].stock << "\n";
        }
    }
    file.close();
}

void readFromFile() {
    string strStock;
    file.open("product.txt", ios::in);  // open file
    for (int i = 0; i > -1; i += 2) {   // infinite loop akses isi file
        getline(file, productName);     // mendapatkan productname
        if (productName.empty()) {      // jika product name empty maka
            break;                      //break the loop
        }
        getline(file, strStock);          // mendapatkan stock berbentuk str
        stringstream intStock(strStock);  // inisiasi stringstream
        intStock >> productStock;         // convert str ke int
        addToArray();
    }
}
