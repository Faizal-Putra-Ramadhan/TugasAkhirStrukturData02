#ifndef SAM_H
#define SAM_H

// Mohc. Sam Ramadhani (2300018200)

#include "Faisal.h"
#include "adit.h"

class Pembeli{

	public :
        void utama(string nama);
		void cariBarang(string namaBarang);	
		void beliBarang(string, int );	
        void Refund(string);
        void Checkout(string);
        void lihatAntrian(string);
        void hapusBarangKeranjang(string);
};

void Pembeli::hapusBarangKeranjang(string namaPembeli) {
    ifstream brg(namaPembeli + "_barang.txt");
    string namaProduk[MAX_BARANG];
    string harga1[MAX_BARANG];
    string namaPenjual[MAX_BARANG];

    int i = 0;
    while (getline(brg, namaBaca, ',')) {
        namaProduk[i] = namaBaca;
        getline(brg, namaBaca, ',');
        harga1[i] = namaBaca;
        getline(brg, namaBaca);
        namaPenjual[i] = namaBaca;
        i++;
    }
    brg.close();

    if (i == 0) {
        cout << "Keranjang kosong. Tidak ada barang untuk dihapus." << endl;
        system("pause");
        return;
    }

    cout << "Barang di keranjang:" << endl;
    for (int j = 0; j < i; j++) {
        cout << j + 1 << ". " << namaProduk[j] << ", Rp." << harga1[j] << endl;
    }

    cout << "Masukkan nomor barang yang ingin dihapus: ";
    int pil;
    cin >> pil;

    if (pil - 1 < 0 || pil - 1 >= i) {
        cout << "Pilihan tidak valid!" << endl;
    } else {
        ofstream Rewrite(namaPembeli + "_barang.txt", ios::trunc);
        for (int j = 0; j < i; j++) {
            if (j != pil - 1) {
                Rewrite << namaProduk[j] << "," << harga1[j] << "," << namaPenjual[j] << endl;
            }
        }
        Rewrite.close();
        cout << "Barang berhasil dihapus dari keranjang." << endl;
    }

    system("pause");
}


void Pembeli::utama(string nama){
    Pembeli pbl;
    bool ulang = true;
    while(ulang){
        system("cls");
        cout<<"1. Cari barang"<<endl;
        cout<<"2. Tambah barang"<<endl;
        cout<<"3. Checkout"<<endl;
        cout<<"4. Refund"<<endl;
        cout<<"5. Lihat Antrian"<<endl;
        cout<<"6. Hapus barang"<<endl;
        cout<<"7. Keluar"<<endl;

        string cari_barang;
        int pil;
        int pil1;
        cout<<"Masukan pilihan anda : ";
        cin>>pil;
        switch(pil){
            case 1:
                system("cls");
                cout<<"Masukan nama barang yang ingin anda cari : ";
                cin.ignore();
                getline(cin,cari_barang);
                pbl.cariBarang(cari_barang);

            
                cout<<"\n\n1. beli barang"<<endl;
                cout<<"2. keluar"<<endl;
                
                cout<<"Masukan pilihan anda :";
                cin>>pil1;
                if(pil1 == 1){
                    int pilihan;
                    cout<<"\n\nMasukan pilihan barang anda : ";
                    cin>>pilihan;
                    pbl.beliBarang(nama, pilihan);
                    system("pause");
                }else {
                    continue;
                }
                break;
            case 2:
                pbl.cariBarang("");

            
                cout<<"\n\n1. beli barang"<<endl;
                cout<<"2. keluar"<<endl;
                
                cout<<"Masukan pilihan anda :";
                cin>>pil1;
                if(pil1 == 1){
                    int pilihan;
                    cout<<"\nMasukan pilihan barang anda : ";
                    cin>>pilihan;
                    pbl.beliBarang(nama, pilihan);
                    system("pause");
                }else {
                    continue;
                }
                break;
            case 3:
                pbl.Checkout(nama);
                ulang = false;
                break;
            case 4:
                pbl.Refund(nama);
                break;
            case 5:
                pbl.lihatAntrian(nama);
                
                break;
            case 6:
                pbl.hapusBarangKeranjang(nama);
                break;
            case 7:
                ulang = false;
                break;
            default:
                cout<<"Pilihan anda tidak valid"<<endl;
                system("pause");
        }
    }
}

void Pembeli::lihatAntrian(string namaPembeli){
	int antri;
	string temp;
	int nomor = 1;
	ifstream antrian("Antrian/antrian.txt");
	while(getline(antrian,temp,',')){
		if(temp == namaPembeli){
			getline(antrian,temp,',');
			cout<<nomor<<". Pembelian tanggal : "<<temp<<", nomor antrian : ";
			getline(antrian,temp);
			cout<<temp<<endl;
			
			nomor++;
		}
	}
    system("pause");
}

void Pembeli::Checkout(string namaPembeli){
    ifstream ambilDuit(namaPembeli + ".txt");
    string nama,pass;
	getline(ambilDuit,nama);
	getline(ambilDuit,pass);
	long long uang;
	ambilDuit>>uang;
    ambilDuit.close();
    

	auto now = chrono::system_clock::now();

    // Convert to time_t for easy human-readable formatting
    time_t now_time_t = chrono::system_clock::to_time_t(now);
    
    string bulan[12] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};

    
	
	
	
    ifstream brg(namaPembeli + "_barang.txt");
    string namaProduk[100];
    string harga1[100];
    string namaPenjual[100];

    int hargaTotal = 0;
    int jml = 0;
    while (getline(brg,namaBaca, ',')){
        namaProduk[jml] = namaBaca;
        getline(brg,namaBaca,',');
        harga1[jml] = namaBaca;
        hargaTotal = hargaTotal + stoi(namaBaca);
        getline(brg,namaBaca);
        namaPenjual[jml] = namaBaca;
        jml++;
    }
    brg.close();

    
    

    for(int j = 0; j<jml; j++){
        cout<<j+1<<". "<<namaProduk[j]<<", Rp."<<harga1[j]<<endl;
    }

    cout<<"Total harga : Rp."<<hargaTotal<<endl;
    cout<<"Checkout Barang (y/n) ? : ";
    char pil;
    cin>>pil;
    
    if(jml == 0){
        cout<<"belum ada barang yang ditambahkan"<<endl;
    }else {
        if (pil == 'y' || pil == 'Y') {
    if (uang >= hargaTotal) {
        // Proses barang
        for (int cek = 0; cek < jml; cek++) {
            if (namaPenjual[cek] != "") {
                ofstream brg1("Kirim/" + namaPenjual[cek] + "_kirim.txt", ios::app);
                for (int i = 0; i < jml; i++) {
                    if (namaPenjual[i] == namaPenjual[cek]) {
                        brg1 << namaProduk[i] << "," << harga1[i] << "," << namaPembeli << endl;
                        namaPenjual[i] = "";
                    }
                }
                brg1.close();
            }
        }

        // Update saldo
        uang -= hargaTotal;
        ofstream data2(namaPembeli + ".txt", ios::trunc);
        data2 << nama << endl;
        data2 << pass << endl;
        data2 << uang << endl;
        data2.close();

        // Tambahkan ke antrian
        int antri = 1;
        string temp;
        ifstream antrian("Antrian/antrian.txt");
        while (getline(antrian, temp, ',')) {
            getline(antrian, temp, ',');
            getline(antrian, temp);
            antri = stoi(temp) + 1;
        }
        antrian.close();

        // Penulisan ke file antrian (hanya sekali)
        ofstream antrian1("Antrian/antrian.txt", ios::app);
        tm* local_time = localtime(&now_time_t);
        int month_index = local_time->tm_mon;
        string tempBulan = bulan[month_index];
        antrian1 << namaPembeli << "," << put_time(localtime(&now_time_t), "%d ") << tempBulan 
                 << put_time(localtime(&now_time_t), " %Y ") << put_time(localtime(&now_time_t), "Jam : %H.%M") 
                 << "," << antri << endl;
        antrian1.close();

        cout << "Barang berhasil dibeli." << endl;
        cout << "Nomor antrian anda: " << antri << endl;

        ofstream hapusBarang (namaPembeli + "_barang.txt", ios::trunc);
        hapusBarang.close();
    } else {
        cout << "Saldo anda tidak cukup." << endl;
    }
} else {
    cout << "Barang tidak dibeli." << endl;
}
    }

    

}


void Pembeli::beliBarang(string namaPembeli, int pil) {
    ofstream DataBeli(namaPembeli + "_barang.txt", ios::app);
    
    if (pil - 1 < 0 || pil - 1 >= jumlahBarang) {
        cout << "Pilihan barang tidak valid!" << endl;
        return;
    }

    // Cek apakah stok tersedia
    if(namaPembeli != penjual[pil-1]){
        if (stok[pil - 1] > 0) {
        // Proses LIFO: Barang terakhir yang masuk akan diambil
        DataBeli << nama[pil - 1] << "," << harga[pil - 1]<<","<<penjual[pil-1]<< endl;
        stok[pil - 1]--; // Kurangi stok barang
        cout << "Barang berhasil dibeli: " << nama[pil - 1] << " Rp." << harga[pil - 1] << endl;

        // Perbarui file dataBarang.txt
        ofstream Rewrite("dataBarang.txt", ios::trunc);
        if (Rewrite.is_open()) {
            for (int i = 0; i < jumlahBarang; i++) {
                // Menulis data dengan ID dan stok yang tepat
                for(int j = 0; j<stok[i]; j++){
                	Rewrite << nama[i] << "," << harga[i] << "," << penjual[i] << "," << nomorBarang[j] << endl;
				}
            }
            Rewrite.close();
            }   else {
                cout << "Gagal membuka file untuk menulis ulang." << endl;
            }
        } else {
            cout << "Stok barang habis!" << endl;
        }
    }else{
        cout<<"Pembeli tidak dapat membeli barangnya sendiri!!"<<endl;
    }

    DataBeli.close();
}


void Pembeli::cariBarang(string namaBarang){

//	for(int i = 0; i<jumlahID-1; i++){
//		for(int j = 0; j<jumlahID-i-1; j++){
//			if(penjual[i] != penjual[i+1]){ // jika di dalam id terdapat kata dalam kurung yang sama di suatu kalimat berikutnya, maka melakukan argumennya
//			temp = penjual[i+1];
//			penjual[i+1] = penjual[i];
//			penjual[i] = temp;
//			
//		}
//		}
//	}
//
//	for(int i = 0; i<jumlahID; i++){
//		cout<<"( "<<penjual[i]<<", "<< nomorBarang[i]<< " )"<<endl;
//	}
    // Jika namaBarang kosong, tampilkan semua barang
    if (namaBarang == "" || namaBarang == " ") {
        for (int i = 0; i < jumlahBarang; i++) {
            cout<<i+1<<". " << nama[i] << ", stok: " << stok[i] <<" Rp."<< harga[i] << endl;
            
        }
    } else { // Jika namaBarang spesifik, cari dan tampilkan stoknya
        bool ditemukan = false;
        for (int i = 0; i < jumlahBarang; i++) {
            if (nama[i] == namaBarang) {
                cout<<i+1<<". " << nama[i] << ", stok: " << stok[i] <<" Rp."<< harga[i] << endl;
                ditemukan = true;
                break;
            }
        }
        if (!ditemukan) {
            cout << "Barang tidak ada." << endl;
        }
    }
}

void Pembeli::Refund(string namaPembeli){
    ifstream brg(namaPembeli + "_barang.txt");
    string namaProduk[100];
    string harga1[100];
    string namaPenjual[100];

    int i = 0;
    while (getline(brg,namaBaca, ',')){
        namaProduk[i] = namaBaca;
        getline(brg,namaBaca,',');
        harga1[i] = namaBaca;
        getline(brg,namaBaca);
        namaPenjual[i] = namaBaca;
        i++;
    }
    brg.close();

    ofstream Rewrite(namaPembeli + "_barang.txt", ios::trunc);
    

    for(int j = 0; j<i; j++){
        cout<<j+1<<". "<<namaProduk[j]<<", Rp."<<harga1[j]<<endl;
    }

    cout<<"Masukan pilihan barang yang ingin di refund : ";
    int pil;
    cin>>pil;
    if(pil-1 < 0  ||  pil-1 >= i){
        cout<<"Pilihan tidak valid!"<<endl;
    }else {
        for(int j = 0; j<i; j++){
            if(pil-1 != j){
                Rewrite<<namaProduk[j]<<","<<harga1[j]<<","<<namaPenjual[j]<<endl;
            }
        }
        ofstream tulisRefund("Refund/" + namaPenjual[pil-1] + "_refund.txt", ios::app);
        tulisRefund << namaProduk[pil-1] << "," << harga1[pil-1] << "," << namaPembeli << endl;
        tulisRefund.close();
        cout<<"Refund barang akan diproses"<<endl;
        
    }
    Rewrite.close();

    
}
#endif 