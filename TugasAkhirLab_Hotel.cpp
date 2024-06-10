#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

struct dataTanggal {
    int tanggal, bulan, tahun;
};

struct dataCheckIn {
    string nama, tipe, CS, responsibility;
    long long NIK;
    int NomorKamar, bed, jumlahKamar;
    dataTanggal tanggalCheckIn;
};

struct Room {
    string tipe;
    int availability;
};

struct FasilitasKolamRenang {
    string nama;
    int hargaPerJam;
    bool hasPelampung;
    int hargaPelampung;
};

struct MenuItem {
    string nama;
    int harga;
};

class Menu {
public:
    void addItem(const MenuItem& item) {
        items.push_back(item);
    }

    void displayMenu() {
        cout << "Menu Makanan dan Minuman:\n";
        for (size_t i = 0; i < items.size(); ++i) {
            cout << i + 1 << ". " << items[i].nama << " - Rp. " << items[i].harga << "\n";
        }
    }

    int selectItems() {
        int pilihan, jumlah, totalHarga = 0;
        while (true) {
            cout << "Masukkan nomor item (0 untuk selesai): ";
            cin >> pilihan;
            if (pilihan == 0) break;
            if (pilihan > 0 && pilihan <= items.size()) {
                cout << "Masukkan jumlah: ";
                cin >> jumlah;
                totalHarga += items[pilihan - 1].harga * jumlah;
            } else {
                cout << "Pilihan tidak valid.\n";
            }
        }
        return totalHarga;
    }

private:
    vector<MenuItem> items;
};

void CustomerServiceInput() {
    ifstream file("CustomerService_Data.txt");
    string nomorCS, nomorCSReal, namaCS;

    cout << "Masukkan ID Customer Service yang Aktif (Anda) : ";
    cin >> nomorCS;

    bool found = false;
    while (file >> nomorCSReal >> namaCS) {
        if (nomorCSReal == nomorCS) {
            system("cls");
            cout << "Nama : " << namaCS << "\nKode : " << nomorCSReal << endl << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Nomor Customer Service Anda tidak terdaftar" << endl;
    }
    file.close();
}

void CetakKeteranganKamar(char kodeKamar) {
    string fileData_Kamar;
    if (tolower(kodeKamar) == 'd')
        fileData_Kamar = "Deluxe_F_R.txt";
    else if (tolower(kodeKamar) == 's')
        fileData_Kamar = "Superior_F_R.txt";
    else if (tolower(kodeKamar) == 'r')
        fileData_Kamar = "Reguler_F_R.txt";
    else {
        cout << "Maaf kode kamar Anda tidak terdaftar" << endl;
        return;
    }

    ifstream file(fileData_Kamar);
    if (file) {
        stringstream buffer;
        buffer << file.rdbuf();
        cout << buffer.str() << endl;
    } else {
        cout << "File kamar tidak ditemukan" << endl;
    }
    file.close();
}

void PilihKolamRenang() {
    system("cls");
    vector<FasilitasKolamRenang> fasilitas = {
        {"Kolam Renang Reguler (Outdoor)", 85000, true, 15000},
        {"Kolam Renang Anak (Outdoor)", 55000, true, 10000},
        {"Kolam Renang VIP (Indoor)", 112000, true, 20000}
    };

    cout << "Pilih fasilitas kolam renang:\n";
    for (size_t i = 0; i < fasilitas.size(); ++i) {
        cout << i + 1 << ". " << fasilitas[i].nama << " - Rp. " << fasilitas[i].hargaPerJam << "/jam\n";
    }

    int pilihan, jumlah_orang;
    float jam;
    cout << "Masukkan pilihan Anda (1-" << fasilitas.size() << "): ";
    cin >> pilihan;

    cout << "Masukkan jumlah orang: ";
    cin >> jumlah_orang;

    cout << "Masukkan total jam yang diinginkan: ";
    cin >> jam;

    if (pilihan >= 1 && pilihan <= fasilitas.size()) {
        int totalHargaKolam = fasilitas[pilihan - 1].hargaPerJam * jam * jumlah_orang;

        bool inginPelampung = false;
        int totalHargaPelampung = 0;

        cout << endl;
        cout << "Harga extra perlengkapan berenang\n";
        cout << "1. Pelampung Reguler      = Rp. 15.000" << endl;
        cout << "2. Pelampung Anak         = Rp. 10.000" << endl;
        cout << "3. Pelampung (khusus VIP) = Rp. 20.000" << endl;

        if (fasilitas[pilihan - 1].hasPelampung) {
            char pelampungPilihan;
            cout << "Apakah Anda ingin menggunakan pelampung? (y/n): ";
            cin >> pelampungPilihan;
            inginPelampung = (tolower(pelampungPilihan) == 'y') ? true : false;

            if (inginPelampung) {
                totalHargaPelampung = fasilitas[pilihan - 1].hargaPelampung * jumlah_orang;
            }
        }

        int totalHarga = totalHargaKolam + totalHargaPelampung;

        ofstream file("kolamrenang.txt", ios::app);
        file << "Fasilitas Kolam Renang: " << fasilitas[pilihan - 1].nama << "\n";
        file << "Jumlah Jam: " << jam << "\n";
        file << "Jumlah Orang: " << jumlah_orang << "\n";
        file << "Biaya Kolam Renang: Rp. " << totalHargaKolam << "\n";
        if (inginPelampung) {
            file << "Menggunakan Pelampung: Ya\n";
            file << "Biaya Pelampung: Rp. " << totalHargaPelampung << "\n";
        }
        file << "Total Biaya: Rp. " << totalHarga << "\n";
        file << "-------------------------------------\n";
        file.close();

        cout << "Anda telah memilih " << fasilitas[pilihan - 1].nama << " untuk " << jam << " jam dengan total harga Rp. " << totalHarga << ".\n";
    } else {
        cout << "Pilihan tidak valid.\n";
    }
}

void CheckIn(char kodeKamar) {
    dataCheckIn data;
    char slash1, slash2;
    string namaFile, tipeKamar, tipe, jawaban;
    int availability;
    long long harga;

    if (kodeKamar == 'd') {
        namaFile = "Check_In_D.txt";
        tipeKamar = "Deluxe Room";
        harga = 700000;
    }
    else if (kodeKamar == 's') {
        namaFile = "Check_In_S.txt";
        tipeKamar = "Superior Room";
        harga = 600000;
    }
    else if (kodeKamar == 'r') {
        namaFile = "Check_In_R.txt";
        tipeKamar = "Reguler Room";
        harga = 400000;
    }

    cout << "*Silahkan Memasukkan Data Tamu untuk Check-In*\n";
    getchar();
    cout << "Nama                 : ";
    getline(cin, data.nama);
    cout << "Tanggal (dd/mm/yyyy) : ";
    cin >> data.tanggalCheckIn.tanggal >> slash1 >> data.tanggalCheckIn.bulan >> slash2 >> data.tanggalCheckIn.tahun;
    cout << "NIK                  : ";
    cin >> data.NIK;
    cout << "\n*Silahkan Memasukkan Data Kamar*\n";
    cout << "Jumlah Kamar " << tipeKamar << " yang dipesan : ";
    cin >> data.jumlahKamar;
    cout << "Extra Bed : ";
    cin >> data.bed;
    cout << "Harga Kamar              : "
         << "Rp. " << harga * data.jumlahKamar << ",00" << endl;
    cout << "Harga Extra Bed          : "
         << "Rp. " << 150000 * data.bed << ",00" << endl;
    cout << "Uang Deposit Hotel (50%) : "
         << "Rp. " << harga * data.jumlahKamar / 2 << ",00" << endl;
    cout << "Harga Total              : "
         << "Rp. " << harga * data.jumlahKamar * 3 / 2 + 150000 * data.bed << ",00" << endl;
    cout << "Jika Pembayaran Sudah Berhasil, tekan Enter ";
    getline(cin, jawaban);
    getchar();
    if (jawaban.empty()) {
        cout << "Nomor Kamar Anda : \n";
        cout << "Selamat Menikmati!";
    }
    else {
        cout << "Pembayaran belum selesai. Silakan selesaikan pembayaran terlebih dahulu." << endl;
    }

    ofstream file1(namaFile, ios::app);
    file1 << "Nama : " << data.nama << endl;
    file1 << "Tanggal Check-In (dd/mm/yyyy) : " << data.tanggalCheckIn.tanggal << "/" << data.tanggalCheckIn.bulan << "/" << data.tanggalCheckIn.tahun << endl;
    file1 << "NIK  : " << data.NIK << endl;
    file1 << "Harga Kamar : " << harga * data.jumlahKamar;

    file1 << "-------------------------------------" << endl;
    file1.close();

    ifstream file2("Check_Kamar.txt");
    vector<Room> rooms;

    while (getline(file2, tipe) && file2 >> availability)
    {
        file2.ignore();
        rooms.push_back({tipe, availability});
    }
    file2.close();

    for (auto &room : rooms)
    {
        if (room.tipe == tipeKamar)
        {
            room.availability -= data.jumlahKamar;
            break;
        }
    }

    ofstream outFile("Check_Kamar.txt");
    for (const auto &room : rooms)
    {
        outFile << room.tipe << endl;
        outFile << room.availability << endl;
    }
    outFile.close();
}

void CheckKamar(const string &namaFile)
{
    ifstream file("check_Kamar.txt");
    vector<Room> rooms;
    string tipeKamar;
    int availability;

    while (getline(file, tipeKamar) && file >> availability)
    {
        file.ignore();
        rooms.push_back({tipeKamar, availability});
    }
    file.close();

    cout << "\n#Room Availability#\n\n";
    for (auto &room : rooms)
    {
        if (room.tipe == "Deluxe Room")
            cout << "-> " << room.tipe << "    [" << room.availability << "]"
                 << "  <Rp. 700.000,00" << endl;
        else if (room.tipe == "Superior Room")
            cout << "-> " << room.tipe << "  [" << room.availability << "]"
                 << "  <Rp. 600.000,00" << endl;
      else if (room.tipe == "Reguler Room")
            cout << "-> " << room.tipe << "   [" << room.availability << "]"
                 << "   <Rp. 400.000,00" << endl;
    }
    cout << "=*=Push Any Button to Continue=*=";
}

//Badan pemrograman utama
int main() {
    system("cls");
    char kodeKamar;
    string kegiatan;
    Menu menu;

    menu.addItem({"Nasi Goreng", 25000});
    menu.addItem({"Mie Goreng", 20000});
    menu.addItem({"Ayam Goreng", 30000});
    menu.addItem({"Es Teh", 5000});
    menu.addItem({"Es Jeruk", 7000});

    CustomerServiceInput();
    getchar();

    cout << "Input Kegiatan [Check In, Check Out, Check Room, Swim, Extra menu food and drink, or Quit] : ";
    getline(cin, kegiatan);

    for (char &c : kegiatan) {
        c = tolower(c);
    }

    if (kegiatan == "check in") {
        cout << "Which Room to Reserve? [Deluxe(D)/Reguler(R)/Superior(S)]: ";
        cin >> kodeKamar;
        kodeKamar = tolower(kodeKamar);
        if (kodeKamar == 'd' || kodeKamar == 'r' || kodeKamar == 's') {
            CetakKeteranganKamar(kodeKamar);
            CheckIn(kodeKamar);
        } else {
            cout << "Kode Kamar tidak valid";
        }
    } else if (kegiatan == "check room") {
        CheckKamar("Check_Kamar.txt");
    } else if (kegiatan == "swim") {
        PilihKolamRenang();
    } else if (kegiatan == "food and drink menu") {
        menu.displayMenu();
        int totalHarga = menu.selectItems();
        cout << "Total harga untuk pesanan Anda adalah: Rp. " << totalHarga << endl;
        ofstream file("pesanan_menu.txt", ios::app);
        file << "Total Harga Pesanan: Rp. " << totalHarga << "\n";
        file << "-------------------------------------\n";
        file.close();
    } else if (kegiatan == "quit") {
        cout << "Terima kasih telah menggunakan layanan kami." << endl;
        return 0;
    } else {
        cout << "Kegiatan tidak valid. Silakan coba lagi." << endl;
    }

    return 0;
}