#include <iostream>
#include <iomanip>

using namespace std;

int main() 
{
    //MEMBUAT MENU LOGIN USER
    string nama = "Rafif Zahran Haryadi";
    string nim = "2309106029";
    int login_attempts = 0;
    cout << "Selamat datang di Program Konvert Mata Uang\n" << endl;

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
    //MEMBUAT MENU PILIHAN KONVERSI MATA UANG
    int pilihan;
    double nominal; //memakai double ketimbang float agar lebih presisi dalam perhitungan

    // Konversi rupiah
    double rupiah_ke_dollar = 0.00007;
    double rupiah_ke_euro = 0.00006;
    double rupiah_ke_yen = 0.0077;

    // Konversi dollar
    double dollar_ke_rupiah = 15700;
    double dollar_ke_euro = 0.92;
    double dollar_ke_yen = 109.5;

    // Konversi euro
    double euro_ke_rupiah = 17000;
    double euro_ke_dollar = 1.09;
    double euro_ke_yen = 120.5;

    // Konversi yen
    double yen_ke_rupiah = 103;
    double yen_ke_dollar = 0.0091;
    double yen_ke_euro = 0.0083;

    while (true)
    {
        cout << "\n Pilih konversi mata uang: " << endl;
        cout << "1. Rupiah ke (Dollar, Euro, Yen)" << endl;
        cout << "2. Dollar ke (Rupiah, Euro, Yen)" << endl;
        cout << "3. Euro ke (Rupiah, Dollar, Yen)" << endl;
        cout << "4. Yen ke (Rupiah, Dollar, Euro)" << endl;
        cout << "5. Keluar" << endl;
        cout << "Catatan : Konversi mata uang tanggal 02-03-24\n" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        if (pilihan == 5) break; //keluar dari program 

        cout << "Masukkan nominal: ";
        cin >> nominal;

        switch(pilihan) 
        {
            case 1:
                cout << "Rupiah ke Dollar: "<<fixed << setprecision(2) << nominal * rupiah_ke_dollar << endl;
                cout << "Rupiah ke Euro: " << fixed << setprecision(2) << nominal * rupiah_ke_euro << endl;
                cout << "Rupiah ke Yen: " << fixed << setprecision(2) << nominal * rupiah_ke_yen << endl;
                break;
            case 2:
                cout << "Dollar ke Rupiah: " <<fixed << setprecision(2) <<  nominal * dollar_ke_rupiah << endl;
                cout << "Dollar ke Euro: " <<fixed << setprecision(2) << nominal * dollar_ke_euro << endl;
                cout << "Dollar ke Yen: " << fixed << setprecision(2) << nominal * dollar_ke_yen << endl;
                break;
            case 3:
                cout << "Euro ke Rupiah: " << fixed << setprecision(2) << nominal* euro_ke_rupiah << endl;
                cout << "Euro ke Dollar: " << fixed << setprecision(2) << nominal * euro_ke_dollar << endl;
                cout << "Euro ke Yen: " <<fixed << setprecision(2) << nominal * euro_ke_yen << endl;
                break;
            case 4:
                cout << "Yen ke Rupiah: Rp." <<fixed << setprecision(2) << nominal * yen_ke_rupiah << endl;
                cout << "Yen ke Dollar: " <<"$"<<fixed << setprecision(2) << nominal* yen_ke_dollar << endl;
                cout << "Yen ke Euro: " << fixed << setprecision(2) <<nominal * yen_ke_euro << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    }       //Memakai <<fixed<<setprecision(2) agar hasil konversi lebih presisi dan mudah dibaca(agar terbaca jika variabel angkanya banyak)
}
