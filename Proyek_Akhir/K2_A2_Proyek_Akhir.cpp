#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <sstream>
#include <unistd.h>
#include <iomanip>
#include <algorithm>
#include <functional>

using namespace std;

void menuawal();

// Struktur data untuk menyimpan detail investasi
struct Investasi {
    int no;
    string jenis;
    string nama;
    float jumlah;
    float harga;

    //Fungsi untuk Shorting nama
    bool operator<(const Investasi& other) const{
    return nama < other.nama;
    }
};

// Struktur data untuk menyimpan detail login
struct Akun {
    string nama;
    string password;
};

string uname;

bool checkLogin(string input_nama, string input_pass) {
    ifstream inFile("datasetlogin.psv");
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string nama, password;
        getline(ss, nama, '|');
        getline(ss, password, '|');
        if (nama == input_nama && password == input_pass) {
            return true;
        }
    }
    inFile.close();
    return false;
}

bool checkUsername(string input_nama) {
    ifstream inFile("datasetlogin.psv");
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string nama, password;
        getline(ss, nama, '|');
        getline(ss, password, '|');
        if (nama == input_nama) {
            return true;
        }
    }
    inFile.close();
    return false;
}

bool login(){
    int login_attempts = 0;
    cout << "Selamat datang di Program Portofolio Keuangan\n" << endl;

    while (login_attempts < 3)
    {
        system("cls");
        string input_nama, input_pass;
        cout << "Menu Login" << endl;
        cout << "Masukkan Nama: ";
        getline(cin,input_nama);
        
        cout << "Masukkan Password: ";
        getline(cin,input_pass);
        
        if (checkLogin(input_nama, input_pass)) {
            cout << "Berhasil Masuk. Selamat datang, " << input_nama << "!" << endl;
            sleep(3);
            uname = input_nama;
            return true;
        } 
        else {
            cout << "Nama atau Password salah!\n" << endl;
            login_attempts++;
            sleep(2);
        }
    }
    
    if (login_attempts == 3)
    {
        cout << "Anda telah mencoba login sebanyak 3 kali. Akun anda diblokir!" << endl;
        exit(0);
    }
    return false;
}

bool registrasi() {
    string input_nama, input_pass;
    cout << "Menu Registrasi" << endl;
    cout << "Masukkan Nama: ";
    getline(cin,input_nama);
    
    while (checkUsername(input_nama)) {
        cout << "Nama pengguna sudah digunakan. Silakan masukkan nama pengguna yang berbeda: ";
        getline(cin,input_nama);
    }
    
    cout << "Masukkan Password: ";
    getline(cin,input_pass);
    
    ofstream outFile("datasetlogin.psv", ios::app);
    outFile << "\n" << input_nama << "|" << input_pass;
    outFile.close();
    
    cout << "Registrasi berhasil. Selamat datang, " << input_nama << "!" << endl;
    sleep(3);
    system ("cls");
    menuawal();
    return true;
}

void menuawal(){
    while (true)
    {
        cout << "______________________________________________\n" << endl;
        cout << "Selamat datang di Program Portofolio Investasi\n" <<endl;
        cout << "__        MENU       __\n";
        cout << "1. Login" << endl;
        cout << "2. Registrasi" << endl;
        cout << "3. Keluar" << endl;
        int pilihan;
        cout << "\n\t Masukkan Pilihan: ";
        while (!(cin >> pilihan) || pilihan < 1 || pilihan > 4) { 
            cout << "Pilihan tidak valid. Masukkan nomor pilihan yang sesuai: ";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
    
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    
        switch(pilihan) 
        {
            case 1:
                if (login()){
                    system("cls");
					return;
                }
                break;
            case 2:
                if (registrasi()) {
                    return;
                }
                break;
            case 3:
                exit(0);
        }
    }
}
// Fungsi untuk mengecheck string atau int
bool check_number(string str) {
    for (int i = 0; i < str.length(); i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

// Fungsi untuk membuat atau membuka file investasi
string buatFileInvestasi(const string& nama_pengguna) {
    string nama_file = "data_investasi_" + nama_pengguna + ".csv";
    ofstream file(nama_file, ios::app); // Membuat file jika belum ada
    file.close(); // Menutup file setelah dibuka
    return nama_file;
}

// Fungsi Menambahkan Investasi dan menyimpan ke dalam file CSV
void tambah_portofolio(const string& nama_file) {
    Investasi investasi;
    cout << "Pilih jenis investasi: " << endl;
    cout << "1. Saham" << endl;
    cout << "2. Crypto" << endl;
    cout << "3. Emas" << endl;
    cout << "4. Kembali ke Menu Investasi" << endl; // Opsi baru

    int jenis;
    cout << "Pilihan: ";
    cin >> jenis;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch(jenis) {
        case 1:
            investasi.jenis = "Saham";
            break;
        case 2:
            investasi.jenis = "Crypto";
            break;
        case 3:
            investasi.jenis = "Emas";
            break;
        case 4: // Opsi untuk kembali ke menu investasi
            return;
        default:
            cout << "Pilihan tidak valid!" << endl;
            // Kembali ke menu utama
            return;
    }

    cout << "Nama " << investasi.jenis << "          : ";
    getline(cin, investasi.nama);
    while (check_number(investasi.nama)) {
        cout << "Harus berupa huruf. Masukkan lagi: ";
        getline(cin, investasi.nama);
    }

    string jumlah, harga;
    cout << "Jumlah" << (jenis == 1 ? "Lembar" : jenis == 2 ? "Coin" : "Gram") << "          : ";
    getline(cin, jumlah);
    while (!check_number(jumlah)) {
        cout << "Harus berupa angka. Masukkan lagi: ";
        getline(cin, jumlah);
    }

    investasi.jumlah = stof(jumlah);
    cout << "Harga/" << (jenis == 1 ? "Saham" : jenis == 2 ? "Coin" : "Emas") << "          : ";
    getline(cin, harga);
    while (!check_number(harga)) {
        cout << "Harus berupa angka. Masukkan lagi: ";
        getline(cin, harga);
    }
    investasi.harga = stof(harga);

    // Baca nomor urut terakhir dari file
    int no = 0;
    ifstream file_in(nama_file);
    if (file_in.is_open()) {
        string line;
        while (getline(file_in, line)) {
            stringstream ss(line);
            string temp;
            getline(ss, temp, ',');
            no = stoi(temp); // Konversi string ke integer
        }
        file_in.close();
    }

    investasi.no = no + 1;
    ofstream file(nama_file, ios::app); // ios::app untuk mode append
    if (file.is_open()) {
        file << fixed << setprecision(0);
        file << investasi.no << "," << uname << "," << investasi.jenis << "," << investasi.nama << "," << investasi.jumlah << "," << investasi.harga << "\n";
        file.close();
        cout << "Data investasi berhasil disimpan dalam file " << nama_file << endl;
    } else {
        cout << "Gagal membuka file untuk disimpan\n";
    }
}

//Fungsi Menampilkan Portofolio
void tampilkan_portofolio(const string& nama_file) {
    ifstream file(nama_file);
    if (file.is_open()) {
        string line;
        cout << "\nPortofolio Investasi\n";
        while (getline(file, line)) {
            stringstream ss(line);
            string no , un, jenis, nama, jumlah, harga;
            getline(ss, no, ',');
            getline(ss, un, ',');
            getline(ss, jenis, ',');
            getline(ss, nama, ',');
            getline(ss, jumlah, ',');
            getline(ss, harga, ',');
            if (un == uname) {
                cout << no << "." << endl; // Menampilkan nomor investasi
                if (jenis == "Saham") {
                    cout << "Jenis Investasi     : Saham" << endl;
                    cout << "Nama Saham          : " << nama << endl;
                    cout << "Jumlah Lembar Saham : " << jumlah << endl;
                    cout << "Harga/Saham         : " << harga << endl;
                } else if (jenis == "Crypto") {
                    cout << "Jenis Investasi     : Crypto" << endl;
                    cout << "Nama Coin           : " << nama << endl;
                    cout << "Jumlah Crypto       : " << jumlah << endl;
                    cout << "Harga/Coin          : " << harga << endl;
                } else if (jenis == "Emas") {
                    cout << "Jenis Investasi     : Emas" << endl;
                    cout << "Jenis Emas          : " << nama << endl;
                    cout << "Jumlah Emas/Gram    : " << jumlah << endl;
                    cout << "Harga Emas          : " << harga << endl;
                }
                cout << "-----------------------------------" << endl;
            }
        }
        file.close();
    } else {
        cout << "Gagal membuka file " << nama_file << endl;
    }
}

// Fungsi Menghapus Portofolio
void menghapus_portofolio(const string& nama_file) {
    int indeks;
	tampilkan_portofolio(nama_file);
    ifstream file_in(nama_file);
    if (file_in.is_open()) {
        vector<string> lines;
        string line;
        while (getline(file_in, line)) {
            lines.push_back(line);
        }
        file_in.close();

		cout << "1.Hapus beberapa data investasi" << endl;
		cout << "2.Kembali ke menu investasi" << endl;
		
		int choose;
		cout << "Pilihan: ";
		cin>>choose;
		
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		switch(choose){
			case 1:
        		cout << "Pilih Nomor Investasi yang ingin dihapus: ";
        		cin >> indeks;
        		break;
        	case 2:
        		return;
        	default:
        		cout << "Pilihan tidak valid!" << endl;
        		// Kembali ke menu utama
        		return;
		}

        bool found = false;
        for (auto it = lines.begin(); it != lines.end(); ++it) {
            stringstream ss(*it);
            string no;
            getline(ss, no, ',');
            if (stoi(no) == indeks) {
                lines.erase(it);
                found = true;
                break;
            }
        }

        if (found) {
            ofstream file_out(nama_file, ios::trunc);
            if (file_out.is_open()) {
                for (const string& l : lines) {
                    file_out << l << "\n";
                }
                file_out.close();
                cout << "Berhasil Menghapus Portofolio\n";
            } else {
                cout << "Gagal membuka file untuk disimpan\n";
            }
        } else {
            cout << "Nomor investasi tidak valid\n";
        }
    } else {
        cout << "Gagal membuka file untuk dibaca\n";
    }
}

// Fungsi untuk memperbarui portofolio
void update_portofolio(const string& nama_file) {
    int no_investasi;
	tampilkan_portofolio(nama_file);
    cout << "1.Update beberapa data investasi" << endl;
	cout << "2.Kembali ke menu investasi" << endl;
		
		int choose;
		cout << "Pilihan: ";
		cin>>choose;
		
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		switch(choose){
			case 1:
        	cout << "Masukkan nomor investasi yang ingin diperbarui: ";
    		cin >> no_investasi;
        	break;
        case 2:
        	return;
        default:
        	cout << "Pilihan tidak valid!" << endl;
        	// Kembali ke menu utama
        	return;
	}

    ifstream file(nama_file);
    if (!file.is_open()) {
        cout << "Gagal membuka file " << nama_file << endl;
        return;
    }

    vector<string> lines;
    string line;
    bool found = false;
    while (getline(file, line)) {
        stringstream ss(line);
        string no, un, jenis, nama, jumlah, harga;
        getline(ss, no, ',');
        getline(ss, un, ',');
        getline(ss, jenis, ',');
        getline(ss, nama, ',');
        getline(ss, jumlah, ',');
        getline(ss, harga, ',');

        if (stoi(no) == no_investasi && un == uname) {
            found = true;
            Investasi investasi;
            investasi.no = stoi(no);
            investasi.jenis = jenis;
            investasi.nama = nama;
            investasi.jumlah = stof(jumlah);
            investasi.harga = stof(harga);

            cout << "Pilih jenis investasi: " << endl;
            cout << "1. Saham" << endl;
            cout << "2. Crypto" << endl;
            cout << "3. Emas" << endl;

            int jenis;
            cout << "Pilihan: ";
            cin >> jenis;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            switch(jenis) {
                case 1:
                    investasi.jenis = "Saham";
                    break;
                case 2:
                    investasi.jenis = "Crypto";
                    break;
                case 3:
                    investasi.jenis = "Emas";
                    break;
                default:
                    cout << "Pilihan tidak valid!" << endl;
                    return;
            }

            cout << "Nama " << investasi.jenis << "          : ";
            getline(cin, investasi.nama);
            while (check_number(investasi.nama)){
                cout << "Harus berupa huruf. Masukkan lagi: ";
                getline(cin, investasi.nama);
            }

            string jumlah, harga;
            cout << "Jumlah " << (jenis == 1 ? "Lembar" : jenis == 2 ? "Coin" : "Gram") << "       : ";
            getline(cin, jumlah);
            while (!check_number(jumlah)) {
                cout << "Harus berupa angka. Masukkan lagi: ";
                getline(cin, jumlah);
            }
            investasi.jumlah = stof(jumlah);

            cout << "Harga/" << (jenis == 1 ? "Saham" : jenis == 2 ? "Coin" : "Emas") << "         : ";
            getline(cin, harga);
            while (!check_number(harga)) {
                cout << "Harus berupa angka. Masukkan lagi: ";
                getline(cin, harga);
            }
            investasi.harga = stof(harga);

            stringstream new_data;
            new_data << fixed << setprecision(0);
            new_data << investasi.no << "," << uname << "," << investasi.jenis << "," << investasi.nama << "," << investasi.jumlah << "," << investasi.harga;
            lines.push_back(new_data.str());
        } else {
            lines.push_back(line);
        }
    }
    file.close();

    if (!found) {
        cout << "Investasi dengan nomor " << no_investasi << " tidak ditemukan." << endl;
        return;
    }

    ofstream file_out(nama_file, ios::trunc);
    if (file_out.is_open()) {
        for (const auto& ln : lines) {
            file_out << ln << "\n";
        }
        file_out.close();
        cout << "Investasi dengan nomor " << no_investasi << " telah diperbarui." << endl;
    } else {
        cout << "Gagal membuka file " << nama_file << endl;
    }
}
// Fungsi Mengitung Total Investasi
void total_portofolio(const string& nama_file) {
    ifstream file(nama_file);
    if (file.is_open()) {
        string line;
        float total = 0;
        while (getline(file, line)) {
            stringstream ss(line);
            string no, un, jenis, nama, jumlah, harga;
            getline(ss, no, ',');
            getline(ss, un, ',');
            getline(ss, jenis, ',');
            getline(ss, nama, ',');
            getline(ss, jumlah, ',');
            getline(ss, harga, ',');
            if (un == uname) {
                total += stof(jumlah) * stof(harga);
            }
        }
        file.close();
        cout << "Total investasi anda adalah: " << fixed << setprecision(2) << total << endl;
    } else {
        cout << "Gagal membuka file " << nama_file << endl;
    }
}

// Fungsi untuk mencari data investasi berdasarkan jenis dan nama portofolio
void searching_portofolio(const string& nama_file) {
    ifstream file(nama_file);
    if (!file.is_open()) {
        cout << "Gagal membuka file " << nama_file << endl;
        return;
    }

    cout << "Cari Portofolio berdasarkan:\n";
    cout << "1. Jenis Investasi\n";
    cout << "2. Nama Investasi\n";
    cout << "3. Kembali ke Menu Utama\n";

    int pilihan;
    while (true) {
        cout << "Pilihan: ";
        cin >> pilihan;
        if (cin.fail() || pilihan < 1 || pilihan > 3) {
            cout << "Pilihan tidak valid. Masukkan nomor pilihan yang sesuai: ";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Menghilangkan karakter newline setelah angka
            break;
        }
    }

    if (pilihan == 3) {
        file.close();
        return; // Kembali ke menu utama
    }

    string keyword;
    cout << "Masukkan yang ingin dicari: ";
    getline(cin, keyword);

    bool found = false;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string no, un, jenis, nama, jumlah, harga;
        getline(ss, no, ',');
        getline(ss, un, ',');
        getline(ss, jenis, ',');
        getline(ss, nama, ',');
        getline(ss, jumlah, ',');
        getline(ss, harga, ',');

        if (un == uname) {
            if ((pilihan == 1 && jenis.find(keyword) != string::npos) ||
                (pilihan == 2 && nama.find(keyword) != string::npos)) {
                cout << no << ". " << jenis << " - " << nama << ", Jumlah : " << jumlah << ", Harga :" << harga << endl;
                found = true;
            }
        }
    }
    if (!found) {
        cout << "Tidak ditemukan portofolio." << endl;
    }
    file.close();
}


void sorting_portofolio(const string& nama_file) {
    ifstream file(nama_file);
    if (!file.is_open()) {
        cout << "Gagal membuka file " << nama_file << endl;
        return;
    }
    vector<Investasi> invest;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Investasi investasi;
        string jumlah, harga, uname_from_file;
        getline(ss, line, ',');
        investasi.no = stoi(line);
        getline(ss, uname_from_file, ',');
        getline(ss, investasi.jenis, ',');
        getline(ss, investasi.nama, ',');
        getline(ss, jumlah, ',');
        investasi.jumlah = stof(jumlah);
        getline(ss, harga, ',');
        investasi.harga = stof(harga);

        if (uname_from_file == uname) {
            invest.push_back(investasi);
        }
    }
    file.close();

    int pilihan;
    while (true) {
        cout << "Urutkan portofolio berdasarkan harga investasi:\n";
        cout << "1. Terendah ke Tertinggi \n";
        cout << "2. Tertinggi ke Terendah \n";
        cout << "3. Kembali ke Menu Utama\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        if (cin.fail()) {
            cout << "Pilihan tidak valid! Masukkan nomor pilihan yang sesuai." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (pilihan < 1 || pilihan > 3) {
            cout << "Pilihan tidak valid! Masukkan nomor pilihan yang sesuai." << endl;
        } else {
            break;
        }
    }

    if (pilihan == 3) {
        return; // Kembali ke menu utama
    }

    if (pilihan == 1) {
        sort(invest.begin(), invest.end(), [](const Investasi& a, const Investasi& b) {
            return a.harga < b.harga;
        });
    } else if (pilihan == 2) {
        sort(invest.begin(), invest.end(), [](const Investasi& a, const Investasi& b) {
            return a.harga > b.harga;
        });
    }

    cout << "\nPortofolio berhasil diurutkan." << endl;
    for (const Investasi& investasi : invest) {
        cout << investasi.no << ". " << investasi.jenis << " - " << investasi.nama
             << ", Jumlah: " << investasi.jumlah << ", Harga : " << fixed << setprecision(2) << investasi.harga << endl;
    }
}


// Fungsi Main
int main(){
	menuawal();
    while (true)
    {
    
        string nama_pengguna;
		string nama_file = buatFileInvestasi(nama_pengguna);
		cout << "\n MENU PORTOFOLIO INVESTASI " << endl;
        cout << "1. Menambahkan  Portofolio" << endl;
        cout << "2. Melihat Portofolio Baru" << endl;
        cout << "3. Mengedit Portofolio" << endl;
        cout << "4. Menghapus Portofolio" << endl;
        cout << "5. Total dari Portofolio" << endl;
        cout << "6. Searching Portofolio"  << endl;
        cout << "7. Sorting Portofolio" << endl;
        cout << "8. Keluar" << endl;

        int pilihan;
        cout << "Pilihan: ";
        while (!(cin >> pilihan) || pilihan < 1 || pilihan > 9) { // Agar selain input angka tidak crash/error
            cout << "Pilihan tidak valid. Masukkan nomor pilihan yang sesuai: ";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }

        if (pilihan == 9) break; //keluar dari program 

        switch(pilihan) 
        {
            case 1:
                tambah_portofolio(nama_file);
                break;
            case 2:
                tampilkan_portofolio(nama_file);
                break;
            case 3:
                update_portofolio(nama_file);
                break;
        	case 4:
                menghapus_portofolio(nama_file);
                break;
            case 5:
                total_portofolio(nama_file);
                break;
            case 6:
                searching_portofolio(nama_file);
                break;
            case 7:
                sorting_portofolio(nama_file);
                break;
            case 8:
                uname ="";
                menuawal();
                    break;
            default:
                cout << "Pilihan tidak valid!" << endl;
    	}
	}
	return 0;       
}
