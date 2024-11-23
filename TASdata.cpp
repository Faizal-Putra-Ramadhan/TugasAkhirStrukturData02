#include <iostream>
#include <string>
#include <fstream>

using namespace std;

	const int MAX_BARANG = 100; // Maksimal jumlah jenis barang
    string nama[MAX_BARANG];
    int harga[MAX_BARANG] = {0};
    int stok[MAX_BARANG] = {0}; // Array stok, diinisialisasi 0
    string penjual[MAX_BARANG];
    int nomorBarang[MAX_BARANG];
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

int Penjual::cariIdTerakhir(string namaBarang) {
    ifstream file("dataBarang.txt");
    string line, nama;
    int idTerakhir = 0;
    int tempId;
    long long tempHarga;
    string tempNamaPenjual;

     if (file.is_open()) {
        while (getline(file, nama, ',')) { // Baca nama barang
            if (nama == namaBarang) {
            	getline(file, nama, ',');
            	getline(file,nama,',');
            	
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






class Pembeli{

	public :
		void cariBarang(string namaBarang);	
		void beliBarang(string, int );	
		
};


void Pembeli::beliBarang(string namaPembeli, int pil) {
    ofstream DataBeli(namaPembeli + "_barang.txt", ios::app);
    if (pil - 1 < 0 || pil - 1 >= jumlahBarang) {
        cout << "Pilihan barang tidak valid!" << endl;
        return;
    }

    // Cek apakah stok tersedia
    if (stok[pil - 1] > 0) {
        // Proses LIFO: Barang terakhir yang masuk akan diambil
        DataBeli << nama[pil - 1] << " Rp." << harga[pil - 1] << endl;
        stok[pil - 1]--; // Kurangi stok barang
        cout << "Barang berhasil dibeli: " << nama[pil - 1] << " Rp." << harga[pil - 1] << endl;

        // Perbarui file dataBarang.txt
        ofstream Rewrite("dataBarang.txt", ios::trunc);
        if (Rewrite.is_open()) {
            for (int i = 0; i < jumlahBarang; i++) {
                // Menulis data dengan ID dan stok yang tepat
                for(int j = 0; j<stok[i]; j++){
                	Rewrite << nama[i] << "," << harga[i] << "," << penjual[j] << "," << j+1 << endl;
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
	string temp;
	for(int i = 0; i<jumlahID-1; i++){
		for(int j = 0; j<jumlahID-i-1; j++){
			if(penjual[i] != penjual[i+1]){ // jika di dalam id terdapat kata dalam kurung yang sama di suatu kalimat berikutnya, maka melakukan argumennya
			temp = penjual[i+1];
			penjual[i+1] = penjual[i];
			penjual[i] = temp;
			
		}
		}
	}

	for(int i = 0; i<jumlahID; i++){
		cout<<"( "<<penjual[i]<<", "<< nomorBarang[i]<< " )"<<endl;
	}
    // Jika namaBarang kosong, tampilkan semua barang
    if (namaBarang == "" || namaBarang == " ") {
        for (int i = 0; i < jumlahBarang; i++) {
            cout<<i+1<<". " << nama[i] << ", stok: " << stok[i] <<" Rp."<< harga[i] << endl;
            
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
    while (getline(brg, namaBaca, ',')) {
        bool ditemukan = false;
        for (int i = 0; i < jumlahBarang; i++) {
            if (nama[i] == namaBaca) {
                
                ditemukan = true;
                getline(brg, namaBaca, ',');
                harga[i] = stoi(namaBaca);
                getline(brg, namaBaca, ',');
                penjual[stok[i]-1] = namaBaca;

                getline(brg, namaBaca);
                nomorBarang[jumlahID++] = stoi(namaBaca);
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
//	 pbl.cariBarang("");
	pbl.beliBarang("tes", 1);
	return 0;
}
