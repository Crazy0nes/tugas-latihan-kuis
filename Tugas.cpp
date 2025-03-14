#include <iostream>
#include <iomanip>
using namespace std;

int index_terbesar = 0;

struct Lagu {
    string judulLagu;
    string penyanyi;
    string genre;
    int tahun;
}; Lagu song[100];

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

void saveSongList() {
    FILE *outFile = fopen("song_list.dat", "wb");
    if (outFile != NULL) {
        fwrite(&index_terbesar, sizeof(index_terbesar), 1, outFile);
        for (int i = 0; i < index_terbesar; i++) {
            int judulLaguLength = song[i].judulLagu.length();
            fwrite(&judulLaguLength, sizeof(int), 1, outFile);
            fwrite(song[i].judulLagu.c_str(), sizeof(char), judulLaguLength, outFile);
        }
        fclose(outFile);
    } else {
        cout << "Error opening file for writing song list." << endl;
    }
}

void editSong() {
    string pencarian;
    cout << "Masukkan judul lagu yang ingin diedit: ";
    cin.ignore();
    getline(cin, pencarian);

    int index = binary_search(pencarian);
    if (index != -1) {
        cout << "Masukkan detail baru untuk lagu ini:" << endl;
        cout << "Masukan judul baru        : ";
        getline(cin, song[index].judulLagu);
        cout << "Masukan penyanyi baru    : ";
        getline(cin, song[index].penyanyi);
        cout << "Masukan genre baru        : ";
        getline(cin, song[index].genre);
        cout << "Masukan tahun baru        : ";
        cin >> song[index].tahun;

        quicksort(song, 0, index_terbesar - 1);
        saveData();
        cout << "Lagu berhasil diedit." << endl;
    } else {
        cout << "Lagu tidak ditemukan." << endl;
    }
}

void saveSongDetails() {
    FILE *outFile = fopen("song_details.dat", "wb");
    if (outFile != NULL) {
        for (int i = 0; i < index_terbesar; i++) {
            int penyanyiLength = song[i].penyanyi.length();
            int genreLength = song[i].genre.length();
            fwrite(&penyanyiLength, sizeof(int), 1, outFile);
            fwrite(song[i].penyanyi.c_str(), sizeof(char), penyanyiLength, outFile);
            fwrite(&genreLength, sizeof(int), 1, outFile);
            fwrite(song[i].genre.c_str(), sizeof(char), genreLength, outFile);
            fwrite(&song[i].tahun, sizeof(int), 1, outFile);
        }
        fclose(outFile);
    } else {
        cout << "Error opening file for writing song details." << endl;
    }
}

void saveData() {
    saveSongList();
    saveSongDetails();
}

void loadData() {
    FILE *inFile = fopen("song_list.dat", "rb");
    if (inFile != NULL) {
        fread(&index_terbesar, sizeof(index_terbesar), 1, inFile);
        for (int i = 0; i < index_terbesar; i++) {
            int judulLaguLength;
            char buffer[100];
            fread(&judulLaguLength, sizeof(int), 1, inFile);
            fread(buffer, sizeof(char), judulLaguLength, inFile);
            buffer[judulLaguLength] = '\0';
            song[i].judulLagu = buffer;
        }
        fclose(inFile);
    } else {
        cout << "Error opening file for reading song list." << endl;
    }

    inFile = fopen("song_details.dat", "rb");
    if (inFile != NULL) {
        for (int i = 0; i < index_terbesar; i++) {
            int penyanyiLength, genreLength;
            char buffer[100];
            fread(&penyanyiLength, sizeof(int), 1, inFile);
            fread(buffer, sizeof(char), penyanyiLength, inFile);
            buffer[penyanyiLength] = '\0';
            song[i].penyanyi = buffer;
            fread(&genreLength, sizeof(int), 1, inFile);
            fread(buffer, sizeof(char), genreLength, inFile);
            buffer[genreLength] = '\0';
            song[i].genre = buffer;
            fread(&song[i].tahun, sizeof(int), 1, inFile);
        }
        fclose(inFile);
    } else {
        cout << "Error opening file for reading song details." << endl;
    }
}

void tambah() {
    int jumlahInput = 0;
    while (true) {
        cout << "Masukkan jumlah lagu untuk diinput : ";
        cin >> jumlahInput;

        if (jumlahInput > 0) {
            break;
        } else {
            cout << "jumlah input tidak valid, ulangi!" << endl;
        }
    }

    string judul, penyanyi, genre;
    int tahun;
    Lagu temp;

    for (int i = 0; i < jumlahInput; i++) {
        cout << "Input ke - " << i + 1 << endl;
        cout << "Masukan judul        : ";
        cin.ignore();
        getline(cin, judul);
        cout << "Masukan penyanyi    : ";
        getline(cin, penyanyi);
        cout << "Masukan genre        : ";
        getline(cin, genre);
        cout << "Masukan tahun        : ";
        cin >> tahun;

        temp = {judul, penyanyi, genre, tahun};

        song[index_terbesar] = temp;
        index_terbesar++;
    }
    cout << endl;

    quicksort(song, 0, index_terbesar - 1);
    saveData();
}

int binary_search(string pencarian) {
    int index_awal = 0;
    int index_akhir = index_terbesar;
    bool search = false;
    while (search == false && index_awal <= index_akhir) {
        int mid = (index_awal + index_akhir) / 2;
        if (song[mid].judulLagu == pencarian) {
            cout << "Data ditemukan!" << endl;
            cout << "    judul        : " << song[mid].judulLagu << endl;
            cout << "    penyanyi    : " << song[mid].penyanyi << endl;
            cout << "    genre        : " << song[mid].genre << endl;
            cout << "    tahun        : " << song[mid].tahun << endl;
            cout << endl;
            return mid;
        } else {
            if (pencarian < song[mid].judulLagu) {
                index_akhir = mid - 1;
            } else {
                index_awal = mid + 1;
            }
        }
    }
    cout << "Data tidak ditemukan" << endl;
    return -1;
}

void cari() {
    bool kondisi = true;
    char pilihan;
    string pencarian;

    while (kondisi) {
        cout << "Masukkan judul lagu yang ingin dicari : ";
        cin.ignore();
        getline(cin, pencarian);
        binary_search(pencarian);
        cout << "Apakah ingin mencari lagi? (y/n) : ";
        cin >> pilihan;
        if (pilihan == 'n') {
            kondisi = false;
            cout << "\n\n";
        }
    }
}

void tampilkan(){
    cout << "Daftar Lagu" << endl;
    cout << setfill('=') << setw(15) << "=" << endl;
    for (int i = 0; i < index_terbesar; i++) {
        cout << i + 1 << ". " << song[i].judulLagu << " - " << song[i].penyanyi << "(" << song[i].tahun << ")" << endl;
    }
}

int main() {
    loadData();
    bool again = true;
    string lagunya;
    int jumlahLagu = 0;
    do {
        cout << "Playlist Lagu" << endl;
        cout << setfill('=') << setw(15) << "=" << endl;

        

        cout << setfill('=') << setw(15) << "=" << endl;
        cout << setfill(' ') << setw(3) << "1. " << "Tambah lagu" << endl;
        cout << setfill(' ') << setw(3) << "2. " << "Cari Lagu" << endl;
        cout << setfill(' ') << setw(3) << "3. " << "Tampilkan Daftar Lagu" << endl;
        cout << setfill(' ') << setw(3) << "4. " << "Edit Lagu" << endl;
        cout << setfill(' ') << setw(3) << "5. " << "Keluar" << endl << endl;
        cout << "Pilih Menu: ";
        int menu;
        cin >> menu;

        switch (menu) {
        case 1:
            tambah();
            system("pause");
            system("cls");
            break;

        case 2:
            cari();
            system("pause");
            system("cls");
            break;

        case 3:
        tampilkan();
        system("pause");
        system("cls");
            break;

        case 4:
        editSong();
        system("pause");
        system("cls");
        break;

        case 5:
         cout << endl << "Keluar dari Program" << endl;
         again = false;
            break;

        default:
            cout << "Menu tidak tersedia" << endl;
            break;
        }

    } while (again);
    return 0;
}