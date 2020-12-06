#include <stdlib.h>

#include <iostream>
using namespace std;

// declaration function
void clearScreen();
void convertInputUser(string &, string (&)[3], int &);
void showMenu(string &, int (&)[2], int &);
bool isPlayAgain(string &);
void showWinner(int (&)[3][3], string (&)[3], int &, int (&)[2]);
bool is_primeNumber(int &);
void showPrimeNumber(int &);
void createLove(int &);

int main() {
    int choice, height_love, total_loop, amount_round;
    srand(1000);  // inisiasi srand dengan seed 1000, untuk membuat fungsi rand()

    // array multidimensi untuk menentukan kemenangan di game
    // 0 = seri, 1 = pemain, 2 = computer
    int tableWinner[3][3] = {{0, 1, 2},
                             {2, 0, 1},
                             {1, 2, 0}};
    int scoreGame[2];                                              // menampung score kedua pihak
    string elementSuit[3] = {"jempol", "telunjuk", "kelingking"};  // array dari element jari di game suit
    int playerNumber, resultWinner;
    string inputUser;

    do {
        clearScreen();
        cout << "=====MENU=====" << endl
             << "1. Permainan Suit" << endl
             << "2. Bilangan Prima" << endl
             << "3. Gambar Love" << endl
             << "0. Keluar" << endl
             << endl
             << "Pilih Menu : ";
        cin >> choice;
        cout << endl;
        if (choice == 1) {
            do {
                clearScreen();
                scoreGame[0] = 0, scoreGame[1] = 0;  // reset score ke 0

                cout << "Ayo Main Suit Sama Aku!" << endl
                     << "Berapa Round? : ";
                cin >> amount_round;  // read input, untuk looping ronde game

                for (int currentRound = 1; currentRound <= amount_round; currentRound++) {
                    while (true) {          // loop hingga pilihan jari benar
                        playerNumber = -1;  // reset pilihan player
                        clearScreen();      // membersihkan console

                        showMenu(inputUser, scoreGame, currentRound);            // menampilkan score sementara, menu, dan input user
                        convertInputUser(inputUser, elementSuit, playerNumber);  // convert input user dari string ke int

                        if (playerNumber >= 0 && playerNumber <= 2) {                       // if number between 0 - 2
                            showWinner(tableWinner, elementSuit, playerNumber, scoreGame);  // menganalisis pemenang dan menampilkannya
                            break;                                                          // break the loop if input is same to condition
                        } else {
                            cout << "Masukkan Pilihan Yang Benar. (nomor / jari)" << endl;  // pesan untuk memasukkan input yang sesuai
                            cin.ignore();
                        }
                    }
                    cin.ignore();
                }
                cout << "Skor Akhir " << endl
                     << "Kamu " << scoreGame[0] << " : " << scoreGame[1] << " Computer" << endl;  // menampilkan skor akhir dari game
                cin.ignore();

            } while (isPlayAgain(inputUser));  // meminta input user untuk melanjutkan atau tidak

            cin.get();

        } else if (choice == 2) {
            cout << "Masukkan banyaknya nilai : ";
            cin >> total_loop;
            showPrimeNumber(total_loop);  // menampilkan deret prima sesuai jumlah input user
        } else if (choice == 3) {
            cout << "Masukkan Tinggi Love (kelipatan 2) : ";
            cin >> height_love;
            cout << endl;
            createLove(height_love);  // menampilkan love dengan tinggi input user
        } else if (choice != 0) {
            cout << "Pilihan tidak ada.";
            cin.get();
        }
        cin.get();

    } while (choice != 0);

    return 0;
}

void showMenu(string &inputUser, int (&scoreGame)[2], int &round) {
    cout << "Skor Sementara " << endl
         << "Kamu " << scoreGame[0] << " : " << scoreGame[1] << " Computer" << endl;  // menampilkan skor sementara
    cout << "Round - " << round << endl                                               // menampilkan ronde saat ini
         << "1. jempol  \n2. telunjuk   \n3. kelingking \n"                           // pilihan input
         << "Pilih Jarimu : ";
    cin >> inputUser;
    cin.ignore();
}

void convertInputUser(string &inputUser, string (&elementSuit)[3], int &playerNumber) {
    if (isdigit(inputUser[0])) {                // detect char pertama dari input, jika digit maka
        playerNumber = inputUser[0] - '0' - 1;  // convert dari char ke int
    } else if (!(isdigit(inputUser[0]))) {      // jika bukan digit maka
        for (int i = 0; i < 3; i++) {           // looping untuk mencari index yang sesuai dengan input
            if (inputUser == elementSuit[i]) {
                playerNumber = i;
                break;
            }
        }
    }
    cout << endl;
}

void showWinner(int (&tableWinner)[3][3], string (&elementSuit)[3], int &playerNumber, int (&scoreGame)[2]) {
    int resultWinner;
    int computerNumber = rand() % 3;  // generate random int from 0-2, for computer choice

    resultWinner = tableWinner[playerNumber][computerNumber];  //mencari pemenang menggunakan array multidimensi

    // 0 = seri, 1 = pemain, 2 = computer
    if (resultWinner == 0) {
        cout << "Hasil Seri! Kamu dan Computer memilih " << elementSuit[playerNumber] << endl;
    } else if (resultWinner == 1) {
        cout << "Kamu Menang! Kamu (" << elementSuit[playerNumber] << ") mengalahkan Computer (" << elementSuit[computerNumber] << ")." << endl;
        scoreGame[0] += 1;  // increment score
    } else if (resultWinner == 2) {
        cout << "Kamu Kalah! Kamu (" << elementSuit[playerNumber] << ") dikalahkan Computer (" << elementSuit[computerNumber] << ")." << endl;
        scoreGame[1] += 1;
    }
}

bool isPlayAgain(string &inputUser) {
    cout << "Apakah kamu ingin bermain lagi ? (Y/N) : ";
    cin >> inputUser;
    return toupper(inputUser[0]) == 'Y';
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
    int checkNumber = 0, total_primeNumber = 0;
    // looping hingga prima yang ditampilkan sesuai dengan input user
    while (total_primeNumber < total_loop) {
        if (is_primeNumber(checkNumber)) {
            // jika prima, tampilkan bilangan dan increment total_primeNumber
            cout << checkNumber << " ";
            total_primeNumber += 1;
        }
        checkNumber += 1;  // increment bilangan yang akan di cek
    }
    cout << endl;
    cin.ignore();
}

void createLove(int &heightLove) {
    float love_bot = heightLove % 2 ? heightLove + 1 : heightLove;  // jika ganjil maka tambah 1

    // membagi dua bagian love, loop atas dan loop bawah
    love_bot = love_bot - 2;
    int love_top = love_bot / 2;
    for (int i = 0; i < love_top; i++) {
        if (i < love_bot / 4) {  // skip agar sisi atas love melengkung
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
        if (i == love_bot) {  // skip agar sisi samping love melengkung
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

void clearScreen() {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)  // jika os windows gunakan cls, lainnya gunakan clear
    system("cls");

#else
    system("clear");
#endif
}