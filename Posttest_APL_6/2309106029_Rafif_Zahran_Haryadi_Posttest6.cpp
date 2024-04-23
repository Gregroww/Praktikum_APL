#include <iostream>
#include <iomanip>
#include <limits>

// MAAF JIKA PROGRAM INI AGAK RUWET APALAGI PARAMETERNYA, DIKARENAKAN KE TINDIH" OLEH TUGAS" SEBELUMNYA
// Terutama tugas parameter pointer yang bikin rumit,mohon dimaklumi, saya aja pusing lihatnya wkwk
using namespace std;

struct Investasi { // Nested struct untuk menyimpan data investasi
    string nama;
    float jumlah;
    float harga;
};

struct Portofolio {     // Struct untuk menyimpan portofolio investasi dari pengguna
    Investasi portofolio[100]; // Array untuk menyimpan portofolio investasi
    int jumlahInvestasi = 0; // Variabel untuk menyimpan jumlah investasi saat ini
};

Portofolio portofolio; // Deklarasi variabel portofolio

void tambah_portofolio(Portofolio* ptr_portofolio) { // Menggunakan pointer diference melihat nilai yang tersimpan pada alamat memori.
    cout << "Masukkan Nama Investasi: ";
    cin.ignore();
    getline(cin, ptr_portofolio->portofolio[ptr_portofolio->jumlahInvestasi].nama);
    cout << "Masukkan Jumlah/item: ";
    while (!(cin >> ptr_portofolio->portofolio[ptr_portofolio->jumlahInvestasi].jumlah)) {
        cout << "Harus berupa angka,Ulangi lagi: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Masukkan Harga/item: ";
    while (!(cin >> ptr_portofolio->portofolio[ptr_portofolio->jumlahInvestasi].harga)) {
        cout << "Harus berupa angka,Ulangi lagi: ";
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    }
    ptr_portofolio->jumlahInvestasi++;
    cout << "Berhasil Membuat Portofolio\n";
}

bool tampilkan_portofolio(Portofolio* ptr_portofolio) { // Menggunakan pointer diference melihat nilai yang tersimpan pada alamat memori.
    if (ptr_portofolio->jumlahInvestasi == 0) { 
        cout << "\nTidak Ada Investasi\n";
        return false;
    } else {
        cout << "\nPortofolio Investasi\n";
        for (int i = 0; i < ptr_portofolio->jumlahInvestasi; ++i) {
            cout << i + 1 << ". Nama: " << (ptr_portofolio->portofolio[i]).nama // Menggunakan pointer diference melihat nilai yang tersimpan pada alamat memori.
                 << ", Jumlah: " << (ptr_portofolio->portofolio[i]).jumlah               // -------------------------//
                 << ", Harga: " << (ptr_portofolio->portofolio[i]).harga << endl;        // -------------------------//
        }
        return true;
    }
}


void update_portofolio() {
    tampilkan_portofolio(&portofolio); //Memakai address of &portofolio untuk mendapatkan/melihat alamat memori yang dimiliki oleh variabel tampilkan_portofolio
    if (portofolio.jumlahInvestasi > 0) {
        int indeks;
        cout << "Pilih Nomor Investasi yang ingin diubah: ";
        cin >> indeks;
        if (indeks >= 1 && indeks <= portofolio.jumlahInvestasi) {
            cout << "Masukkan Nama yang Baru: ";
            cin.ignore();
            getline(cin, portofolio.portofolio[indeks - 1].nama);
            cout << "Masukkan Jumlah yang Baru: ";
            while (!(cin >> portofolio.portofolio[indeks - 1].jumlah)) {
                cout << "Harus berupa angka,Ulangi lagi: ";
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            }
            cout << "Masukkan Harga yang Baru: ";
            while (!(cin >> portofolio.portofolio[indeks - 1].harga)) {
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
    tampilkan_portofolio(&portofolio); //Memakai address of &portofolio untuk mendapatkan/melihat alamat memori yang dimiliki oleh variabel tampilkan_portofolio
    if (portofolio.jumlahInvestasi > 0) {
        int indeks;
        cout << "Pilih Nomor Investasi yang ingin dihapus: ";
        cin >> indeks;
        if (indeks >= 1 && indeks <= portofolio.jumlahInvestasi) {
            for (int i = indeks - 1; i < portofolio.jumlahInvestasi - 1; ++i) {
                portofolio.portofolio[i] = portofolio.portofolio[i + 1];
            }
            portofolio.jumlahInvestasi--;
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
        return portofolio.portofolio[indeks].jumlah * portofolio.portofolio[indeks].harga + total_portofolio(indeks - 1);
    }
}

void bubbleSort(Investasi arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].nama > arr[j + 1].nama) {
                Investasi temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void insertionSort(Investasi arr[], int n) {
    for (int i = 1; i < n; i++) {
        Investasi key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].jumlah < key.jumlah) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void shellSort(Investasi arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Investasi temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap].harga > temp.harga; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

int binarySearch(Investasi arr[], int l, int r, string key) {
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (arr[mid].nama == key) 
            return mid;
        if (arr[mid].nama < key) 
            l = mid + 1;
        else
            r = mid - 1;
    }
    return -1;
}

// Fungsi untuk melakukan pencarian interpolasi
int interpolationSearch(Investasi arr[], int n, float key) {
    int awal = 0;
    int akhir = n - 1;
    
    while (awal <= akhir && key <= arr[awal].jumlah && key >= arr[akhir].jumlah) {
        int pos = awal + ((key - arr[awal].jumlah) * (akhir - awal)) / (arr[akhir].jumlah - arr[awal].jumlah);
        if (arr[pos].jumlah == key)
            return pos;
        if (arr[pos].jumlah < key)
            akhir = pos - 1;
        else
            awal = pos + 1;
    }
    return -1;
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
        cout << "6. Buble Sorting Nama Investasi" << endl;
        cout << "7. Insertion Sorting Jumlah Investasi" << endl;
        cout << "8. Shell Sorting Harga Investasi" << endl;
        cout << "9. Binary Search Nama Investasi" << endl;
        cout << "10.Interpolation Search Jumlah Investasi" << endl;
        cout << "11. Keluar" << endl;

        int pilihan;
        cout << "Pilihan: ";
        while (!(cin >> pilihan) || pilihan < 1 || pilihan > 12) { // Agar selain input angka tidak crash/error
            cout << "Pilihan tidak valid. Masukkan nomor pilihan yang sesuai: ";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }

        if (pilihan == 11) break; //keluar dari program 

        switch(pilihan) 
        {
            case 1:
                tambah_portofolio(&portofolio); // Memakai address of untuk melihat nilai yang tersimpan pada alamat memori.
                break;
            case 2:
                tampilkan_portofolio(&portofolio); // Memakai address of untuk melihat nilai yang tersimpan pada alamat memori.
                break;
            case 3:
                update_portofolio();
                break;
            case 4:
                menghapus_portofolio();
                break;
            case 5:
                cout << "Total Jumlah Uang yang diInvestasikan: Rp." << total_portofolio(portofolio.jumlahInvestasi - 1) << endl;
                break;
            case 6:
                bubbleSort(portofolio.portofolio, portofolio.jumlahInvestasi);
                cout << "Portofolio Investasi diurutkan berdasarkan nama(ascending):" << endl;
                tampilkan_portofolio(&portofolio);
                break;
            case 7:
                insertionSort(portofolio.portofolio, portofolio.jumlahInvestasi);
                cout << "Portofolio Investasi diurutkan berdasarkan jumlah(descending):" << endl;
                tampilkan_portofolio(&portofolio);
                break;
            case 8:
                shellSort(portofolio.portofolio, portofolio.jumlahInvestasi);
                cout << "Portofolio Investasi diurutkan berdasarkan harga (ascending):" << endl;
                tampilkan_portofolio(&portofolio);
                break;
            case 9: {
                bubbleSort(portofolio.portofolio, portofolio.jumlahInvestasi);

                string namaCari;
                cout << "Masukkan nama yang ingin dicari: ";
                cin.ignore();
                getline(cin, namaCari);
                
                int index = binarySearch(portofolio.portofolio, 0, portofolio.jumlahInvestasi - 1, namaCari);
                if (index != -1) {
                    cout << "Nama \"" << namaCari << "\" ditemukan pada indeks " << index << endl;
                    cout << "Detail Investasi:" << endl;
                    cout << "Nama: " << portofolio.portofolio[index].nama << ", Jumlah: " << portofolio.portofolio[index].jumlah << ", Harga: " << portofolio.portofolio[index].harga << endl;
                } else {
                    cout << "Nama \"" << namaCari << "\" tidak ditemukan dalam portofolio investasi." << endl;
                }
                break;
            }
            case 10: {
                insertionSort(portofolio.portofolio, portofolio.jumlahInvestasi);

                float jumlahCari;
                cout << "Masukkan jumlah yang ingin dicari: ";
                cin >> jumlahCari;
                int indeks = -1;
                for (int i = 0; i < portofolio.jumlahInvestasi; ++i) {
                    if (portofolio.portofolio[i].jumlah == jumlahCari) {
                        indeks = i;
                        break;
                    } else if (portofolio.portofolio[i].jumlah < jumlahCari) {
                        break; 
                    }
                }

                if (indeks != -1) {
                    cout << "Jumlah \"" << jumlahCari << "\" ditemukan pada indeks " << indeks << endl;
                    cout << "Detail Investasi:" << endl;
                    cout << "Nama: " << portofolio.portofolio[indeks].nama << ", Jumlah: " << portofolio.portofolio[indeks].jumlah << ", Harga: " << portofolio.portofolio[indeks].harga << endl;
                } else {
                    cout << "Jumlah \"" << jumlahCari << "\" tidak ditemukan dalam portofolio investasi." << endl;
                }
                break;
            }
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    }       
}

// MAAF JIKA PROGRAM INI AGAK RUWET APALAGI PARAMETERNYA, DIKARENAKAN KE TINDIH" OLEH TUGAS" SEBELUMNYA
// Terutama tugas parameter pointer yang bikin rumit,mohon dimaklumi, saya aja pusing lihatnya wkwk
