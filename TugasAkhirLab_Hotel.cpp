#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cctype>
#include <vector>

using namespace std;

struct dataTanggal
{
    int tanggal,bulan,tahun;
};

struct dataCheckIn
{
    string nama, tipe, CS, responsibility;
    long long NIK;
    int NomorKamar, bed, jumlahKamar;
    dataTanggal tanggalCheckIn;
};

struct Room {
    string tipe;
    int availability;
};

void CustomerServiceInput () 
{
    ifstream file("CustomerService_Data.txt");
    string nomorCS, nomorCSReal, namaCS;

    cout << "Masukkan ID Customer Service yang Aktif (Anda) : ";
    cin >> nomorCS;

    bool found = false;
    while (file >> nomorCSReal >> namaCS) 
    {
        if (nomorCSReal == nomorCS) {
            system ("cls");
            cout << "Nama : " << namaCS << "\nKode : " << nomorCSReal << endl << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Nomor Customer Service Anda tidak terdaftar";
    }
    file.close();
}

void CetakKeteranganKamar(char kodeKamar) 
{
    string kamar,fileData_Kamar;
    ifstream file;
    if (tolower (kodeKamar) == 'd')
    fileData_Kamar = "Deluxe_F_R.txt"; 
    else if (tolower (kodeKamar) == 's')
    fileData_Kamar = "Superior_F_R copy.txt"; 
    else if (tolower (kodeKamar) == 'r')
    fileData_Kamar = "Reguler_F_R copy.txt"; 
    else
    cout << "Maaf kode kamar Anda tidak terdaftar";

    file.open (fileData_Kamar);
    stringstream buffer;
    buffer << file.rdbuf();
    string fileContents = buffer.str();

    file.close();
    system ("cls");
    cout << fileContents << endl; 
}
 
void CheckIn (char kodeKamar) 
{
    dataCheckIn data;
    char slash1,slash2;
    string namaFile,kamar,tipeKamar,tipe,jawaban;
    int availability;
    long long harga;

    if (kodeKamar == 'd'){
        namaFile = "Check_In_D.txt"; 
        tipeKamar = "Deluxe Room";
        harga = 700000;
    }
    else if (kodeKamar == 's'){
        namaFile = "Check_In_S.txt"; 
        tipeKamar = "Superior Room";
        harga = 600000;
    }
    else if (kodeKamar == 'r'){
        namaFile = "Check_In_R.txt"; 
        tipeKamar = "Reguler Room";
        harga = 400000;
    }

    cout << "*Silahkan Memasukkan Data Tamu untuk Check-In*\n";
    getchar();
    cout << "Nama                 : ";
    getline (cin, data.nama);
    cout << "Tanggal (dd/mm/yyyy) : ";
    cin  >> data.tanggalCheckIn.tanggal >> slash1 >> data.tanggalCheckIn.bulan >> slash2 >> data.tanggalCheckIn.tahun;
    cout << "NIK                  : ";
    cin  >> data.NIK;
    cout << "\n*Silahkan Memasukkan Data Kamar*\n";
    cout << "Jumlah Kamar " << tipeKamar << " yang dipesan : ";
    cin  >> data.jumlahKamar;
    cout << "Extra Bed : ";
    cin  >> data.bed;
    cout << "Harga Kamar              : " << "Rp. " << harga*data.jumlahKamar << ",00" << endl;
    cout << "Harga Extra Bed          : " << "Rp. " << 150000 * data.bed << ",00" << endl;
    cout << "Uang Deposit Hotel (50%) : " << "Rp. " << harga*data.jumlahKamar/2 << ",00" << endl;
    cout << "Harga Total              : " << "Rp. " << harga*data.jumlahKamar*3/2 +  150000 * data.bed  << ",00" << endl;
    cout << "Jika Pembayaran Sudah Berhasil, tekan Enter "; getline(cin, jawaban); getchar();
    if (jawaban.empty()){
        cout << "Nomor Kamar Anda : \n";
        cout << "Selamat Menikmati!";
    }
    else {
        cout << "Pembayaran belum selesai. Silakan selesaikan pembayaran terlebih dahulu." << endl;
    }

    ofstream file1 (namaFile, ios::app);
    file1 << "Nama : " << data.nama << endl;
    file1 << "Tanggal Check-In (dd/mm/yyyy) : "<< data.tanggalCheckIn.tanggal << "/" << data.tanggalCheckIn.bulan << "/" << data.tanggalCheckIn.tahun << endl;
    file1 << "NIK  : " << data.NIK << endl;
    file1 << "Harga Kamar : " << harga*data.jumlahKamar;

    file1 << "-------------------------------------" << endl;
    file1.close();

    ifstream file2 ("Check_Kamar.txt");
    vector<Room> rooms;

    while (getline(file2,tipe) && file2 >> availability) {
        file2.ignore();
        rooms.push_back({tipe, availability});
    }
    file2.close();
    
    bool roomFound = false;
    for (auto& room : rooms) {
        if (room.tipe == tipeKamar){
        room.availability -= data.jumlahKamar;
        roomFound = true;
        break;
        }
    }

    ofstream outFile("Check_Kamar.txt");
    for (const auto& room : rooms) {
        outFile << room.tipe << endl;
        outFile << room.availability << endl;
    }
    outFile.close();

}

void CheckKamar (const string& namaFile)
{
    ifstream file (namaFile);
    vector <Room> rooms;
    string tipeKamar;
    int availability;

    while (getline (file, tipeKamar) && file >> availability){
        file.ignore ();
        rooms.push_back({tipeKamar, availability});
    }
    file.close();

    bool roomFound = false;
    cout << "\n#Room Availability#\n\n";
    for (auto& room : rooms) {
        if (room.tipe == "Deluxe Room")
            cout << "-> " << room.tipe << "    [" << room.availability  << "]" << "  <Rp. 700.000,00" << endl;
        else if (room.tipe == "Superior Room")
            cout << "-> " << room.tipe << "  [" << room.availability  << "]" << "  <Rp. 600.000,00" << endl;
        else if (room.tipe == "Reguler Room")
            cout << "-> " << room.tipe << "   [" << room.availability  << "]" << "   <Rp. 400.000,00" << endl;  
        }
    cout << "=*=Push Any Button to Continue=*=";
}


int main() 
{
    system("cls");
    char kodeKamar;
    string kegiatan;
    int ulang;

    CustomerServiceInput();
    getchar();

    do {
    cout << "Input Kegiatan [Check In, Check Out, Check Room, or Quit] : ";
    getline (cin,kegiatan);


    for (char &c : kegiatan) {
        c = std::tolower(c);
    }

    if (kegiatan == "check in")
    {
        cout << "Which Room to Reserve? [Deluxe(D)/Reguler(R)/Superior(S)]: ";
        cin >> kodeKamar;
        kodeKamar = tolower(kodeKamar);
        if (kodeKamar == 'd' || kodeKamar == 'r' || kodeKamar == 's')
        {
            CetakKeteranganKamar(kodeKamar);
            CheckIn(kodeKamar);
        }

        else 
        cout << "Kode Kamar tidak valid";
    }
    
    else if (kegiatan == "check room") 
    CheckKamar("Check_Kamar.txt");

    else if (kegiatan == "quit") {
        cout << "Terima kasih, sampai jumpa!" << endl;
        ulang = 0;
    } 

    else {
        cout << "Kegiatan Anda Tidak Terdaftar dalam Sistem. Mohon Input Ulang!\n";
        getchar();
        ulang = 1;
    }
    }
    while (ulang != 0);

    return 0;
}