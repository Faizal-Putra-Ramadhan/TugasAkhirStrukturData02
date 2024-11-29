#include <iostream>
#include <string>
#include <fstream>

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
		void masukanBarang(string nama);
		void kirimBarang();
		int cariIdTerakhir(string namaBarang);
        void terimaRefund(string);
};



int Penjual::cariIdTerakhir(string namaBarang) {
    ifstream file("dataBarang.txt");
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
    cout << "Masukkan nama barang: ";
    
    getline(cin, brg.namaBarang);
    cout << "Masukkan harga: ";
    cin >> brg.harga;

    // Cari ID terakhir dan tambahkan 1
    brg.id = cariIdTerakhir(brg.namaBarang) + 1;

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


class Pembeli{

	public :
		void cariBarang(string namaBarang);	
		void beliBarang(string, int );	
        void Refund(string);
        void Checkout(string);
		
};

void Pembeli::Checkout(string namaPembeli){
    ifstream brg(namaPembeli + "_barang.txt");
    string namaProduk[100];
    string harga1[100];
    string namaPenjual[100];

    int jml = 0;
    while (getline(brg,namaBaca, ',')){
        namaProduk[jml] = namaBaca;
        getline(brg,namaBaca,',');
        harga1[jml] = namaBaca;
        getline(brg,namaBaca);
        namaPenjual[jml] = namaBaca;
        jml++;
    }
    brg.close();

    
    

    for(int j = 0; j<jml; j++){
        cout<<j+1<<". "<<namaProduk[j]<<", Rp."<<harga1[j]<<endl;
    }

    cout<<"Checkout Barang (y/n) ? : ";
    char pil;
    cin>>pil;
    
    if(pil == 'y' or pil == 'Y'){
        
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
        
        
        cout<<"barang berhasil dibeli"<<endl;
    }else {
        cout<<"Barang tidak dibeli"<<endl;
    }

}


void Pembeli::beliBarang(string namaPembeli, int pil) {
    ofstream DataBeli(namaPembeli + "_barang.txt", ios::app);
    
    if (pil - 1 < 0 || pil - 1 >= jumlahBarang) {
        cout << "Pilihan barang tidak valid!" << endl;
        return;
    }

    // Cek apakah stok tersedia
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
        } else {
            cout << "Gagal membuka file untuk menulis ulang." << endl;
        }
    } else {
        cout << "Stok barang habis!" << endl;
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

void daftar(){
	string Cnama, nama1, pass1;
	
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



void login(){
	string Tnama, nama1, pass1, Tpass;
	
	cout<<"Masukan nama : ";
	getline(cin,nama1);

	cout<<"Masukan pass : ";
	cin>>pass1;
	
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
			cout<<"Password anda Benar"<<endl;
		}else {
			cout<<"Password anda salah"<<endl;
		}
		
	}
	
	
}



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
                penjual[jumlahID++] = namaBaca;

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
            penjual[jumlahID++] = namaBaca;
            getline(brg, namaBaca);
            nomorBarang[stok[jumlahBarang]-1] = stoi(namaBaca);
            jumlahBarang++;
        }
    }
    brg.close();
    
    
//	daftar();
//	login();
	
//	Penjual pjl;
//	pjl.masukanBarang("faisal");

	 Pembeli pbl;
	//  pbl.cariBarang("  ");
	// pbl.beliBarang("tes", 3);
//    pbl.Refund("tes");
	// Penjual pjl;
	// pjl.terimaRefund("faisal");
    pbl.Checkout("tes");
	return 0;
}
