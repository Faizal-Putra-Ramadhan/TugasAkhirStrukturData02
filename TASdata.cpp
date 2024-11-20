#include <iostream>
#include <fstream>

using namespace std;

	const int MAX_BARANG = 100; // Maksimal jumlah jenis barang
    string nama[MAX_BARANG];
    int harga[MAX_BARANG] = {0};
    int stok[MAX_BARANG] = {0}; // Array stok, diinisialisasi 0
    string id[MAX_BARANG];
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
};

void Penjual::masukanBarang(string nama){
	cout<<"Masukan nama barang : ";
	getline(cin,brg.namaBarang);
	cout<<"Masukan harga : ";
	cin>>brg.harga;
	
	brg.id = cariIdTerakhir(brg.namaBarang) + 1;

    
    ofstream file("dataBarang.txt", ios::app);
    if (file.is_open()) {
        file << brg.namaBarang << "\n"<< brg.harga << " " << nama << endl;
        file.close();
        cout << "Barang berhasil ditambahkan" << endl;
    } else {
        cout << "Gagal membuka file." << endl;
    }
}


int Penjual::cariIdTerakhir(string namaBarang) {
    ifstream file("dataBarang.txt");
    string line, nama;
    int idTerakhir = 0;
    int tempId;
    long long tempHarga;
    string tempNamaPenjual;

     if (file.is_open()) {
        while (getline(file, nama)) { // Baca nama barang
            if (nama == namaBarang) {
                // Jika nama barang cocok, baca ID, harga, dan nama penjual pada baris berikutnya
                if (file >> tempId >> tempHarga >> tempNamaPenjual) {
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

class Pembeli{

	public :
		void cariBarang(string namaBarang);	
		void beliBarang(string, int );	
		
};


class CariBarang{
	private:
		string* nama;
		int ukuran;
		
	public:
		CariBarang(int ukuran = 0);
		
		CariBarang(const CariBarang& c);
		CariBarang& operator=(const CariBarang& c);
		string operator[](int i){return nama[i];};
};

CariBarang::CariBarang(int a){
	ukuran = a;
	nama = new string[ukuran];
}

CariBarang::CariBarang(const CariBarang& c){
	ukuran = c.ukuran;
	for(int i = 0; i<ukuran; i++){
		nama[i] = c.nama[i];
	}
}

CariBarang& CariBarang::operator=(const CariBarang& c){
	if(this != &c){
		this->ukuran = c.ukuran;
		delete [] nama;
		
		this->nama = new string[ukuran];
		for(int i = 0; i<ukuran; i++){
			this->nama[i] = c.nama[i];
		}
	}
	
	return *this;
}

void Pembeli::beliBarang(string namaPembeli, int pil){
	ofstream DataBeli (namaPembeli + "_barang.txt", ios::app);	
	ofstream Rewrite("dataBarang.txt", ios::trunc);
	for(int i = 0; i<jumlahBarang; i++){
		if(pil-1 == i){
			DataBeli<<nama[i]<<" Rp."<<harga[i]<<endl;
			stok[i]--;
		}
	}
	for(int i = 0; i<jumlahBarang; i++){
		
		for(int j = 0; j<stok[i]; j++){
			Rewrite<<nama[i]<<"\n"<<harga[i]<<id[j]<<endl;
		}

	}
	DataBeli.close();
	
	
}

void Pembeli::cariBarang(string namaBarang){
	string temp;
	for(int i = 0; i<jumlahID-1; i++){
		for(int j = 0; j<jumlahID-i-1; j++){
			if(id[i] != id[i+1]){ // jika di dalam id terdapat kata dalam kurung yang sama di suatu kalimat berikutnya, maka melakukan argumennya
			temp = id[i+1];
			id[i+1] = id[i];
			id[i] = temp;
			
		}
		}
	}

	for(int i = 0; i<jumlahID; i++){
		cout<<"( "<<id[i]<<" )"<<endl;
	}
    // Jika namaBarang kosong, tampilkan semua barang
    if (namaBarang == "" || namaBarang == " ") {
        for (int i = 0; i < jumlahBarang; i++) {
            cout<<i+1<<". " << nama[i] << ", stok: " << stok[i] << endl;
            
        }
    } else { // Jika namaBarang spesifik, cari dan tampilkan stoknya
        bool ditemukan = false;
        for (int i = 0; i < jumlahBarang; i++) {
            if (nama[i] == namaBarang) {
                cout<<i+1<<". " << nama[i] << ", stok: " << stok[i] << endl;
                ditemukan = true;
                break;
            }
        }
        if (!ditemukan) {
            cout << "Barang tidak ada." << endl;
        }
    }
}

void daftar(){
	string Cnama, nama, pass;
	
	cout<<"Masukan nama : ";
	getline(cin,nama);
	cout<<"Masukan pass : ";
	cin>>pass;
	
	ofstream Dakun;
	Dakun.open("akun.txt",ios::app); // inputan akan membuat dan masuk ke dalam file akun.txt
	
	ifstream Cakun("akun.txt");
	while(!Cakun.eof()){
		getline(Cakun,Cnama);
		if(nama == Cnama){
			cout<<"username sudah ada, silahkan cari username lain"<<endl;
			return;
		}
	}
	Cakun.close();
	
	Dakun<<nama<<endl; // file akun.txt hanya akan berisi username dari inputan
	Dakun.close();
	
	
	
	ofstream akun;
	akun.open(nama + ".txt", ios::app); // setiap user atau username memiliki file txt masing masing
	akun<<nama<<endl;
	akun<<pass<<endl;
	akun<<0<<endl;
	akun.close();

}



void login(){
	string Tnama, nama, pass, Tpass;
	
	cout<<"Masukan nama : ";
	getline(cin,nama);

	cout<<"Masukan pass : ";
	cin>>pass;
	
	ifstream Dakun;
	Dakun.open("akun.txt");
	bool cek = false;
	while(!Dakun.eof() and cek == false){
		
		getline(Dakun,Tnama);
		if(Tnama == nama){
			cek = true;
		}
	}
	Dakun.close();
	
	
	
	if(cek){
		Dakun.open(nama + ".txt");
			getline(Dakun,Tpass);
			getline(Dakun,Tpass);
		cout<<Tpass<<endl;
		
		if(Tpass == pass){
			cout<<"Password anda Benar"<<endl;
		}else {
			cout<<"Password anda salah"<<endl;
		}
		
	}
	
	
}

int main (){
	ifstream brg("dataBarang.txt");
	int i = 0;

    // Membaca file dan mengisi array
    while (getline(brg, namaBaca)) {
        // Mencari apakah barang sudah ada di array
        bool ditemukan = false;
        for (int i = 0; i < jumlahBarang; i++) {
            if (nama[i] == namaBaca) {
                stok[i]++; // Jika ditemukan, tambahkan stok
                ditemukan = true;
                brg>>harga[jumlahBarang];
                getline(brg, namaBaca);
        		id[jumlahID++] = namaBaca;
                break;
            }
            
        }
        if (!ditemukan) { // Jika tidak ditemukan, tambahkan ke array
            nama[jumlahBarang] = namaBaca;
            stok[jumlahBarang] = 1;
            brg>>harga[jumlahBarang];
            jumlahBarang++;
            
            getline(brg, namaBaca);
        	id[jumlahID++] = namaBaca;
        }
        
    }
    brg.close();
    
    
//	daftar();
//	login();
	
//	Penjual pjl;
//	pjl.masukanBarang("faisal");

	 Pembeli pbl;
//	 pbl.cariBarang("");
	pbl.beliBarang("tes", 2);
	return 0;
}
