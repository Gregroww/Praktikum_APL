#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

struct Investasi {
    string nama;
    float jumlah;
    float harga;
};

Investasi portofolio[100]; // Array untuk menyimpan portofolio investasi
int jumlahInvestasi = 0; // Variabel untuk menyimpan jumlah investasi saat ini


void tambah_portofolio() {
    cout << "Masukkan Nama Investasi: ";
    cin.ignore();
    getline(cin, portofolio[jumlahInvestasi].nama);
    cout << "Masukkan Jumlah/item: ";
    while (!(cin >> portofolio[jumlahInvestasi].jumlah)) {
        cout << "Harus berupa angka,Ulangi lagi: ";
        cin.clear(); // Menghapus error flag pada cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Membersihkan buffer
    }
    cout << "Masukkan Harga/item: ";
    while (!(cin >> portofolio[jumlahInvestasi].harga)) {
        cout << "Harus berupa angka,Ulangi lagi: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    jumlahInvestasi++;
    cout << "Berhasil Membuat Portofolio\n";
}

bool tampilkan_portofolio() { // Awalnya dari Prosedur menjadi Fungsi menggunakan Tipe data boolean
    if (jumlahInvestasi == 0) {
        cout << "\nTidak Ada Investasi\n";
        return false;
    } else {
        cout << "\nPortofolio Investasi\n";
        for (int i = 0; i < jumlahInvestasi; ++i) {
            cout << i + 1 << ". Nama: " << portofolio[i].nama << ", Jumlah: " << portofolio[i].jumlah << ", Harga: " << portofolio[i].harga << endl;
        }
        return true;
    }
}

void update_portofolio() {
    tampilkan_portofolio();
    if (jumlahInvestasi > 0) {
        int indeks;
        cout << "Pilih Nomor Investasi yang ingin diubah: ";
        cin >> indeks;
        if (indeks >= 1 && indeks <= jumlahInvestasi) {
            cout << "Masukkan Nama yang Baru: ";
            cin.ignore();
            getline(cin, portofolio[indeks - 1].nama);
            cout << "Masukkan Jumlah yang Baru: ";
            while (!(cin >> portofolio[indeks - 1].jumlah)) {
                cout << "Harus berupa angka,Ulangi lagi: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            }
            cout << "Masukkan Harga yang Baru: ";
            while (!(cin >> portofolio[indeks - 1].harga)) {
                cout << "Harus berupa angka,Ulangi lagi: ";
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            }
            cout << "Berhasil Memperbarui Portofolio\n";
        } else {
            cout << "Nomor investasi tidak valid\n";
        }
    }
}

bool menghapus_portofolio() { // Awalnya dari Prosedur menjadi Fungsi menggunakan Tipe data boolean
    tampilkan_portofolio();
    if (jumlahInvestasi > 0) {
        int indeks;
        cout << "Pilih Nomor Investasi yang ingin dihapus: ";
        cin >> indeks;
        if (indeks >= 1 && indeks <= jumlahInvestasi) {
            for (int i = indeks - 1; i < jumlahInvestasi - 1; ++i) {
                portofolio[i] = portofolio[i + 1];
            }
            jumlahInvestasi--;
            cout << "Berhasil Menghapus Portofolio\n";
            return true;
        } else {
            cout << "Nomor Portofolio tidak valid\n";
        }
    }
    return false;
}

int total_portofolio(int indeks) { // Menggunakan Fungsi Rekursif
    if (indeks < 0) { 
        return 0;
    } else {
        return portofolio[indeks].jumlah * portofolio[indeks].harga + total_portofolio(indeks - 1);
    }
}

int main() 
{
    //MEMBUAT MENU LOGIN USER
    string nama = "Rafif Zahran Haryadi";
    string nim = "2309106029";
    int login_attempts = 0;
    cout << "Selamat datang di Program Portofolio Keuangan\n" << endl;

    while (login_attempts < 3)
    {
        cout << "Menu Login" << endl;
        string input_nama, input_nim;
        cout << "Masukkan Nama: ";
        getline(cin,input_nama);
        cout << "Masukkan NIM: ";
        getline(cin,input_nim);

        if (input_nama == nama && input_nim == nim)
        {
            cout << "Berhasil Masuk. Selamat datang, " << nama << "!" << endl;
            break;
        }
        else
        {
            cout << "Nama atau NIM salah!\n" << endl;
            login_attempts++;
        }
    }
    
    if (login_attempts == 3)
    {
        cout << "Anda telah mencoba login sebanyak 3 kali. Akun anda diblokir!" << endl;
        return 0;
    }


    while (true)
    {
        cout << "\n MENU PORTOFOLIO KEUANGAN " << endl;
        cout << "1. Menambahkan  Portofolio" << endl;
        cout << "2. Melihat Portofolio Baru" << endl;
        cout << "3. Mengedit Portofolio" << endl;
        cout << "4. Menghapus Portofolio" << endl;
        cout << "5. Total Investasi" << endl;
        cout << "6. Keluar" << endl;

        int pilihan;
        cout << "Pilihan: ";
        while (!(cin >> pilihan) || pilihan < 1 || pilihan > 5) { // Agar selain input angka tidak crash/error
            cout << "Pilihan tidak valid. Masukkan nomor pilihan yang sesuai: ";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (pilihan == 6) break; //keluar dari program 

        switch(pilihan) 
        {
            case 1:
                tambah_portofolio();
                break;
            case 2:
                tampilkan_portofolio();
                break;
            case 3:
                update_portofolio();
                break;
            case 4:
                menghapus_portofolio();
                break;
            case 5:
                cout << "Total Jumlah Uang yang diInvestasikan: Rp." << total_portofolio(jumlahInvestasi - 1) << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    }       
}
