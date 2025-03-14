#include <iostream>
#include <iomanip>
using namespace std;

int index_terbesar=0;


struct Lagu{
    string judulLagu;
    string penyanyi;
    string genre;
    int tahun;
};Lagu song[100];

void quicksort(Lagu array[], int low, int high) {
    int awal = low;
    int akhir = high;
    string pivot = array[(awal + akhir) / 2].judulLagu;
    do {
        while (array[awal].judulLagu < pivot) {
            awal++;
        }
        while (array[akhir].judulLagu > pivot) {
            akhir--;
        }
        if (awal <= akhir) {
            swap(array[awal], array[akhir]);
            awal++;
            akhir--;
        }
    } while (awal <= akhir);

    if (low < akhir) {
        quicksort(array, low, akhir);
    }
    if (awal < high) {
        quicksort(array, awal, high);
    }
}

void tambah() {
	int jumlahInput = 0;
	while (true)
	{
		cout << "Masukkan jumlah lagu untuk diinput : ";
		cin >> jumlahInput;

		if (jumlahInput > 0) {
			break;
		}
		else {
			cout << "jumlah input tidak valid, ulangi!" << endl;
		}
	}

	string judul, penyanyi, genre;
	int tahun;
	Lagu temp;

	for (int i = 0; i < jumlahInput; i++)
	{   cout << "Input ke - " << i + 1 << endl;
		cout << "Masukan judul		: ";
		cin.ignore();
		getline(cin, judul);
		cout << "Masukan penyanyi	: ";
		getline(cin, penyanyi);
		cout << "Masukan genre		: ";
		getline(cin, genre);
		cout << "Masukan tahun		: ";
		cin >> tahun;

		temp = { judul, penyanyi, genre, tahun };

		song[index_terbesar] = temp;
		index_terbesar++;
	}
	cout << endl;

	quicksort(song, 0, index_terbesar - 1);
}

int binary_search(string pencarian) {
	int index_awal = 0;
	int index_akhir = index_terbesar;
	bool search = false;
	while (search == false && index_awal <= index_akhir) {
		int mid = (index_awal + index_akhir) / 2;
		if (song[mid].judulLagu == pencarian) {
			cout << "Data ditemukan!" << endl;
			cout << "	judul		: " << song[mid].judulLagu << endl;
			cout << "	penyanyi	: " << song[mid].penyanyi << endl;
			cout << "	genre		: " << song[mid].genre << endl;
			cout << "	tahun		: " << song[mid].tahun << endl;
			cout << endl;
			return mid;
		}
		else
		{
			if (pencarian < song[mid].judulLagu) {
				index_akhir = mid - 1;
			}
			else {
				index_awal = mid + 1;
			}
		}
	}
	cout << "Data tidak ditemukan" << endl;
	return -1;

}

void cari() {
    bool kondisi=true;
    char pilihan;
    string pencarian;

    while(kondisi){
        cout << "Masukkan judul lagu yang ingin dicari : ";
        cin.ignore();
        getline(cin, pencarian);
        binary_search(pencarian);
        cout << "Apakah ingin mencari lagi? (y/n) : ";
        cin >> pilihan;
        if(pilihan == 'n'){
            kondisi = false;
            cout << "\n\n";
        }
    }
}


int main(){
    bool again = true;
    string lagunya;
    int jumlahLagu = 0; 
    do{

    cout << "Playlist Lagu" << endl;
    cout << setfill('=') << setw(15) << "=" << endl;

    for (int i = 0; i < index_terbesar; i++)
	{
		cout << i + 1 << ". " << song[i].judulLagu << " - " << song[i].penyanyi << "(" << song[i].tahun << ")" << endl;
	}

    cout << setfill('=') << setw(15) << "=" << endl;
    cout << setfill(' ') << setw(3) << "1. " << "Tambah lagu" << endl;
    cout << setfill(' ') << setw(3) << "2. " << "Cari Lagu" << endl;
    cout << setfill(' ') << setw(3) << "3. " << "Keluar" << endl << endl;
    cout << "Pilih Menu: ";
    int menu;
    cin >> menu;


    switch (menu){
        case 1:
            tambah();
            break;

        case 2:
            cari();
            break;

        case 3:
            cout << endl << "Keluar dari Program" << endl;
            again = false; 
            break;

        default:
            cout << "Menu tidak tersedia" << endl;
            break;

        }
        
    }while( again); 
    return 0;
}