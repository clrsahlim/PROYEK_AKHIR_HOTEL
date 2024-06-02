#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
using namespace std;

struct dataTanggal
{
    int tanggal,bulan,tahun;
};

struct checkIn
{
    string nama, tipe, CS, responsibility;
    long long NIK;
    int NomorKamar, Bed;
    dataTanggal tanggalCheckIn;
};

void CustomerServiceInput () 
{
    ifstream file("CustomerService_Data.txt");
    string nomorCS, nomorCSReal, namaCS;

    cout << "Masukkan Nomor Customer Service (case-sensitive): ";
    cin >> nomorCS;

    bool found = false;
    while (file >> nomorCSReal >> namaCS) 
    {
        if (nomorCSReal == nomorCS) {
            cout << "Nama: " << namaCS << "\nKode: " << nomorCSReal << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Nomor Customer Service Anda tidak terdaftar";
    }
    file.close();
}

void Cetak_Keterangan_Kamar(char kodeKamar) 
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
    cout << fileContents << endl <<endl; // Menampilkan isi file ke layar
}
 
void CheckIn (char kodeKamar) 
{
    checkIn data;
    char slash1,slash2;
    string namaFile,kamar,jenisKamar;
    int sisaKamar;

    if (kodeKamar == 'd')
    {namaFile = "Check_In_D.txt"; kamar = "Deluxe Room";}
    else if (kodeKamar == 's')
    {namaFile = "Check_In_S.txt"; kamar = "Superior Room";}
    else if (kodeKamar == 'r')
    {namaFile = "Check_In_R.txt"; kamar = "Reguler Room";}

    ofstream file1 (namaFile, ios::app);
    cout << "Silahkan Memasukkan Data untuk Check-In\n";
    getchar();
    cout << "Nama                 : ";
    getline (cin, data.nama);
    cout << "Tanggal (dd/mm/yyyy) : ";
    cin  >> data.tanggalCheckIn.tanggal >> slash1 >> data.tanggalCheckIn.bulan >> slash2 >> data.tanggalCheckIn.tahun;
    cout << "NIK                  : ";
    cin  >> data.NIK;

    file1 << "Nama : "<< data.nama << endl;
    file1 << "Tanggal Check-In (dd/mm/yyyy) : "<< data.tanggalCheckIn.tanggal << "/" << data.tanggalCheckIn.bulan << "/" << data.tanggalCheckIn.tahun << endl;
    file1 << "NIK : "<< data.NIK << endl;

    file1 << "-------------------------------------" << endl;
    file1.close();

    ifstream file2("Check_Kamar.txt");
    ofstream tempFile("temp.txt");
    bool found = false;

    while (file2 >> jenisKamar >> sisaKamar) {
        if (jenisKamar == kamar) {
            sisaKamar -= 1;
            found = true;
        }
        tempFile << jenisKamar << " " << sisaKamar << endl;
    }
    file2.close();
    tempFile.close();

    if (!found) {
        cout << "Jenis kamar tidak terdaftar";
        remove("temp.txt");
        return;
    }

    remove("Check_Kamar.txt");
    rename("temp.txt", "Check_Kamar.txt");
    cout << "Check-in berhasil. Sisa kamar untuk " << kamar << " adalah " << sisaKamar << endl;
}


int CheckKamar ()
{
    ifstream file("Check_Kamar.txt");
    string nomorCS, nomorCSReal, namaCS;

    cout << "Masukkan Nomor Customer Service (case-sensitive): ";
    cin >> nomorCS;

    bool found = false;
    while (file >> nomorCSReal >> namaCS) 
    {
        if (nomorCSReal == nomorCS) {
            cout << "Nama: " << namaCS << "\nKode: " << nomorCSReal << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Nomor Customer Service Anda tidak terdaftar";
    }
    file.close();
}


int main() 
{
    char kodeKamar;

    CustomerServiceInput();

    cout << "Masukkan kode kamar: ";
    cin >> kodeKamar;
    kodeKamar = tolower(kodeKamar);
    
    if (kodeKamar == 'd' || kodeKamar == 'r' || kodeKamar == 's')
    {
    Cetak_Keterangan_Kamar(kodeKamar);
    CheckIn(kodeKamar);
    }

    else 
    cout << "Kode Kamar tidak valid";

    return 0;

}