#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>

//#include "Faisal.h"
#include "Header/adit.h"


#define MAX_BARANG 100

using namespace std;








int main (){
	for(int i = 0; i<MAX_BARANG; i++){
		harga[i] = 0;
	}
	for(int i = 0; i<MAX_BARANG; i++){
		stok[i] = 0;
	}
    ifstream brg("dataBarang.txt");

    // Membaca file dan mengisi array
    while (getline(brg, namaBaca, ',')) {
        bool ditemukan = false;
        for (int i = 0; i < jumlahBarang; i++) {
            if (nama[i] == namaBaca) {
                
                ditemukan = true;
                getline(brg, namaBaca, ',');
                harga[i] = stoi(namaBaca);
                getline(brg, namaBaca, ',');
                penjual[i] = namaBaca;

                getline(brg, namaBaca);
                nomorBarang[stok[i]] = stoi(namaBaca);
                stok[i]++;
                break;
            }
        }
        if (!ditemukan) {
            nama[jumlahBarang] = namaBaca;
            stok[jumlahBarang] = 1;

            getline(brg, namaBaca, ',');
            harga[jumlahBarang] = stoi(namaBaca);

            getline(brg, namaBaca, ',');
            penjual[jumlahBarang] = namaBaca;
            getline(brg, namaBaca);
            nomorBarang[stok[jumlahBarang]-1] = stoi(namaBaca);
            jumlahBarang++;
        }
    }
    brg.close();
    

     int pil;
    while(true){
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;

        cout<<"Masukan pilihan anda : ";
        cin>>pil;
        switch(pil){
            case 1:
                login();
                system("cls");
                break;
            case 2:
                daftar();
                system("cls");
                break;  
            default:
                cout << "Pilihan tidak valid!!" << endl;
                system("pause");
                system("cls");
        }
    }
		
	
	return 0;
}
