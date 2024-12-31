#ifndef FAISAL_H
#define FAISAL_H

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>

// Faizal Putra Ramadhan (2300018199)

#define MAX_BARANG 100

using namespace std;

template<class T>
class Penjualan{
	private:
		T* array;
		int ukuran;
	public:
		Penjualan<T>(int ukuran = 0);
		T& operator [] (int i){return array[i];}
		Penjualan<T>& operator =(T a);
};



template<class T>
Penjualan<T>::Penjualan(int a){
	ukuran = a;
	array = new T[ukuran];
}

template<class T>
Penjualan<T>& Penjualan<T>::operator=(T a){
	array = a;
	return *this;
}


Penjualan<string> nama(MAX_BARANG);
Penjualan<int> harga(MAX_BARANG);
Penjualan<int> stok(MAX_BARANG) ; // Array stok, diinisialisasi 0
Penjualan<string> penjual(MAX_BARANG);
Penjualan<int> nomorBarang(MAX_BARANG);
int jumlahBarang = 0;      // Jumlah jenis barang yang terdata
int jumlahID = 0;
string namaBaca;


struct Barang{
	string namaBarang;
	int id;
	long long harga;
};


class Penjual{
	private:
		Barang brg;
	public:
        void utama1(string nama);
		void masukanBarang(string nama);
		void kirimBarang(string namaPenjual);
		int cariIdTerakhir(string namaBarang, string data);
        void terimaRefund(string);
};

void Penjual::utama1(string nama){
    Penjual pjl;
    bool ulang = true;
    while(ulang){
        system("cls");
        cout<<"1. Masukan barang"<<endl;
        cout<<"2. Kirim Barang"<<endl;
        cout<<"3. Cek Refund"<<endl;
        cout<<"4. Keluar"<<endl;

        int pil;
        cout<<"Masukan pilihan anda : ";
        cin>>pil;
        switch(pil){
            case 1:
                pjl.masukanBarang(nama);
                break;
            case 2:
                pjl.kirimBarang(nama);
                break;
            case 3:
                pjl.terimaRefund(nama);
                break;
            case 4:
                ulang = false;
                break;
            default:
                cout<<"Pilihan anda tidak valid"<<endl;
                system("pause");
        }
    }
}



int Penjual::cariIdTerakhir(string namaBarang, string data) {
    ifstream file(data);
    string line, nama1;
    int idTerakhir = 0;
    int tempId;
    string tempNamaPenjual;

     if (file.is_open()) {
        while (getline(file, nama1, ',')) { // Baca nama barang
            if (nama1 == namaBarang) {
            	getline(file, nama1, ',');
            	getline(file,nama1,',');
            	
                // Jika nama barang cocok, baca ID, harga, dan nama penjual pada baris berikutnya
                if (file>>tempId) {
                    idTerakhir = tempId; // Set id terakhir sesuai dengan id yang ditemukan
                }
                // Hapus sisa karakter pada baris berikutnya untuk menghindari konflik saat membaca nama di iterasi berikutnya
                file.ignore();
            } else {
                // Jika nama barang tidak cocok, abaikan baris berikutnya
                getline(file, line); // skip line
            }
        }
        file.close();
    }
    return idTerakhir;
}


	
void Penjual::masukanBarang(string namaPenjual) {
    cin.ignore();
    cout << "Masukkan nama barang: ";
    
    getline(cin, brg.namaBarang);
    cout << "Masukkan harga: ";
    cin >> brg.harga;

    // Cari ID terakhir dan tambahkan 1
    brg.id = cariIdTerakhir(brg.namaBarang,"dataBarang.txt") + 1;

    // Simpan ke file
    ofstream file("dataBarang.txt", ios::app);
    if (file.is_open()) {
        file << brg.namaBarang << "," << brg.harga << "," << namaPenjual << "," << brg.id << endl;
        file.close();
        cout << "Barang berhasil ditambahkan dengan ID: " << brg.id << endl;
    } else {
        cout << "Gagal membuka file untuk menambahkan barang." << endl;
    }
}

void Penjual::terimaRefund(string namaPenjual){
    ifstream brg ("Refund/" + namaPenjual + "_refund.txt");
    string namaProduk[MAX_BARANG],namaPembeli[MAX_BARANG];
    int hargaProduk[MAX_BARANG];
    int jml = 0;
    while(getline(brg,namaBaca,',')){
        namaProduk[jml] = namaBaca;
        getline(brg,namaBaca,',');
        hargaProduk[jml] = stoi(namaBaca);
        getline(brg,namaBaca);
        namaPembeli[jml] = namaBaca;
        jml++;
    }
    brg.close();

    cout<<"1. Produk : "<<namaProduk[0]<<", harga : "<<hargaProduk[0]<<", Pembeli : "<<namaPembeli[0]<<endl;
    if(jml-1 != 0){
        cout<<"dan "<<jml-1<<" lainnya...\n";
    }

    char pil;
    cout<<"terima refund (y/n) ? : ";
    cin>>pil;

    if(pil == 'y' or 'Y'){
        for(int i = 0; i<jml-1; i++){
                namaProduk[i] = namaProduk[i+1];
                namaPembeli[i] = namaPembeli[i+1];
                hargaProduk[i] = hargaProduk[i+1];
        }
        jml--;
        ofstream brg1 ("Refund/" + namaPenjual + "_refund.txt", ios::trunc);
        cout<<"Barang berhasil di refund!!"<<endl;
        for(int i = 0; i<jml; i++){
            brg1<<namaProduk[i]<<","<<hargaProduk[i]<<","<<namaPembeli[i]<<endl;
        }
        brg1.close();
    }else {
        cout<<"Produk tidak di refund!"<<endl;
    }

}

void Penjual::kirimBarang(string namaPenjual){
	ifstream antrian1("Antrian/antrian.txt");
	string temp[MAX_BARANG];
	int no = 0;
	while(getline(antrian1,temp[no])){
		no++;
	}
	
	
    ifstream brg ("Kirim/" + namaPenjual + "_kirim.txt");
    string namaProduk[MAX_BARANG],namaPembeli[MAX_BARANG];
    int hargaProduk[MAX_BARANG];
    int jml = 0;
    while(getline(brg,namaBaca,',')){
        namaProduk[jml] = namaBaca;
        getline(brg,namaBaca,',');
        hargaProduk[jml] = stoi(namaBaca);
        getline(brg,namaBaca);
        namaPembeli[jml] = namaBaca;
        jml++;
    }
    brg.close();

    cout<<"1. Produk : "<<namaProduk[0]<<", harga : "<<hargaProduk[0]<<", Pembeli : "<<namaPembeli[0]<<endl;
    if(jml-1 != 0){
        cout<<"dan "<<jml-1<<" lainnya...\n";
    }

    char pil;
    cout<<"Kirim Barang? (y/n) ? : ";
    cin>>pil;

    if(pil == 'y' or 'Y'){
        for(int i = 0; i<jml-1; i++){
                namaProduk[i] = namaProduk[i+1];
                namaPembeli[i] = namaPembeli[i+1];
                hargaProduk[i] = hargaProduk[i+1];
        }
        jml--;
        
        ofstream brg1 ("Kirim/" + namaPenjual + "_kirim.txt", ios::trunc);
        cout<<"Barang telah di kirim!!"<<endl;
        for(int i = 0; i<jml; i++){
            brg1<<namaProduk[i]<<","<<hargaProduk[i]<<","<<namaPembeli[i]<<endl;
        }
        brg1.close();
        
        for(int i = 0; i<no-1; i++){
        	temp[i] = temp[i+1];
		}
		no--;
        
        ofstream antrian("Antrian/antrian.txt", ios::trunc);
        for(int i = 0; i<no; i++){
        	antrian<<temp[i]<<endl;
		}
    }else {
        cout<<"barang tidak di kirim!"<<endl;
    }
}

#endif // FAISAL_H