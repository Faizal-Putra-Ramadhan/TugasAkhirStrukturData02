#ifndef ADIT_H
#define ADIT_H
#include "Faisal.h"
#include "Sam.h"

// Aditya Dwi Nugroho (2300018201)

void topUp(string nama1){
    ifstream data (nama1 + ".txt");
	string nama,pass;
	getline(data,nama);
	getline(data,pass);
	long long uang;
	data>>uang;
	data.close();
	
	long long duit;
	long long temp = 0;
	cout<<"Masukan nominal Top up : ";cin>>duit;
	
	temp = uang + duit;
	ofstream data2 (nama1 + ".txt", ios::trunc);
	
	data2<<nama<<endl;
	data2<<pass<<endl;
	data2<<temp<<endl;
	data2.close();
}

void infoUser(){
    ifstream data ("akun.txt");
    string arr[1000];
    string temp;
    int jml = 0;
    while(!data.eof()){
        getline(data,arr[jml]);
        jml++;
    }
    data.close();

    for(int i = 0; i<jml-1; i++){
        ifstream data1 (arr[i] + ".txt");
        getline(data1, temp);
        getline(data1, temp);
        cout<<i+1<<". Username : "<< arr[i] << ", Password : "<< temp<<endl;
       
        data1.close();
    }
}

void admin(){
    bool ulang = true;
    while(ulang){
        system("cls");
        cout<<"1. tampilkan informasi user"<<endl;
        cout<<"2. keluar"<<endl;
        int pil;
        cout<<"Masukan pilihan anda : ";
        cin>>pil;
        switch(pil){
            case 1:
                infoUser();
                system("pause");
                break;
            case 2:
                ulang = false;
                system("cls");
                break;
            default:
                cout<<"Pilihan anda salah"<<endl;
                system("pause");
        }
    }
}

void daftar(){
	string Cnama, nama1, pass1;
	cin.ignore();
	cout<<"Masukan nama : ";
	getline(cin,nama1);
	cout<<"Masukan pass : ";
	cin>>pass1;
	
	ofstream Dakun;
	Dakun.open("akun.txt",ios::app); // inputan akan membuat dan masuk ke dalam file akun.txt
	
	ifstream Cakun("akun.txt");
	while(!Cakun.eof()){
		getline(Cakun,Cnama);
		if(nama1 == Cnama){
			cout<<"username sudah ada, silahkan cari username lain"<<endl;
			return;
		}
	}
	Cakun.close();
	
	Dakun<<nama1<<endl; // file akun.txt hanya akan berisi username dari inputan
	Dakun.close();
	
	
	
	ofstream akun;
	akun.open(nama1 + ".txt", ios::app); // setiap user atau username memiliki file txt masing masing
	akun<<nama1<<endl;
	akun<<pass1<<endl;
	akun<<0<<endl;
	akun.close();

}

void Utama(string nama){
    ifstream ambilSaldo (nama + ".txt");
    string temp;
    int angka;
    getline(ambilSaldo,temp);
    getline(ambilSaldo,temp);
    ambilSaldo>>angka;

    bool ulang = true;
    while(ulang){
        system("cls");
        cout<<"Selamat datang "<< nama<<endl;
        cout<<"Saldo Anda : Rp."<<angka<<endl;
    
        cout<<"\n1. Jual Barang"<<endl;
        cout<<"2. Beli Barang"<<endl;
        cout<<"3. Top up"<<endl;
        cout<<"4. Keluar"<<endl;
        int pil;
        cout<<"Masukan pilihan anda : ";
        cin>>pil;
        switch(pil){
            case 1:
                {
                    Penjual pjl;
                    pjl.utama1(nama);
                    system("cls");
                }
                break;
            case 2:
                {
                    Pembeli pbl;
                    pbl.utama(nama);
                    system("pause");
                    system("cls");
                    ulang = false;
                }
                break;
            case 3:
                topUp(nama);
                ulang = false;
                break;
            case 4:
                ulang = false;
                break;
            default:
                cout<<"Pilihan tidak valid!!"<<endl;
                system("pause");
                
        }
    }
}



void login(){
	string Tnama, nama1, pass1, Tpass;
	cin.ignore();
	cout<<"Masukan nama : ";
	getline(cin,nama1);

	cout<<"Masukan pass : ";
	cin>>pass1;

    if(nama1 == "admin" and pass1 == "admin"){
        admin();
    }
	
	ifstream Dakun;
	Dakun.open("akun.txt");
	bool cek = false;
	while(!Dakun.eof() and cek == false){
		
		getline(Dakun,Tnama);
		if(Tnama == nama1){
			cek = true;
		}
	}
	Dakun.close();
	
	
	
	if(cek){
		Dakun.open(nama1 + ".txt");
			getline(Dakun,Tpass);
			getline(Dakun,Tpass);
		cout<<Tpass<<endl;
		
		if(Tpass == pass1){
			Utama(nama1);
		}else {
			cout<<"Password anda salah"<<endl;
		}
		
	}
	
	
}
#endif // FAISAL_H