#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <Windows.h>
#include <String.h>

#define kiri -1
#define kanan 1

using namespace std;


//================= INISIALISASI VARIABEL =============================

bool menang = false;
int jumlahplayer;
int giliran = 1;
int roll;
char bebas;

//=====================================================================



//========================= COLORS =====================================

HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
int color(int a){
	switch(a){
		//WHITE
		case 0:
			SetConsoleTextAttribute(h,0x0001|0x0002|0x0004|0x0008);
			break;
		//BLUE
		case 1:
			SetConsoleTextAttribute(h,0x0001|0x0008);
			break;
		//GREEN	
		case 2:
			SetConsoleTextAttribute(h,0x0002|0x0008);
			break;
		//RED
		case 3:
			SetConsoleTextAttribute(h,0x0004|0x0008);
			break;
		//CYAN	
		case 4:
			SetConsoleTextAttribute(h,0x0001|0x0002|0x0008);
			break;
		//YELLOW	
		case 5:
			SetConsoleTextAttribute(h,0x0002|0x0004|0x0008);
			break;
		//PINK	
		case 6:
			SetConsoleTextAttribute(h,0x0004|0x0001|0x0008);
			break;
		//DARK BLUE
		case 7:
			SetConsoleTextAttribute(h,0x0001);
			break;
		//DARK GREEN	
		case 8:
			SetConsoleTextAttribute(h,BACKGROUND_GREEN);
			break;
		//DARK RED
		case 9:
			SetConsoleTextAttribute(h,BACKGROUND_RED);
			break;
		//DARK CYAN	
		case 10:
			SetConsoleTextAttribute(h,0x0001|0x0002);
			break;
		//DARK YELLOW	
		case 11:
			SetConsoleTextAttribute(h,0x0002|0x0004);
			break;
		//DARK PINK
		case 12:
			SetConsoleTextAttribute(h,0x0004|0x0001);
			break;
			//GRAY
		case 13:
			SetConsoleTextAttribute(h,0x0001|0x0002|0x0004);
			break;
	}
}

//============================-o0o-=======================================



//============================= PLAYER ===================================

struct posisi{
	int x;
	int y;
};

struct player{
	
	int arah = kanan;
	posisi pos;
	string nama;
	bool menang = false;
	bool aktif = false;
	
};
//Inisialisasi 4 player
player p[4];


//===============================-o0o-====================================



//============================ MAP =================================================================================================================================


//Ini adalah char berisi map, ditaruh diluar main agar dapat di akses oleh segala fungsi
char map[16][41] = {
	
'/','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=',
'|','4','1',' ','|','4','2',' ','|','4','3',' ','|',' ','e',' ','|','4','5',' ','|','4','6',' ','|','4','7',' ','|','4','8',' ','|','U','a',' ','|','5','0',' ',';',
'|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ',';',
'+','-',' ','-','+','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','+',
'(','4','0',' ','|','3','9',' ','|','3','8',' ','|','3','7',' ','|','3','6',' ','|','U','b',' ','|',' ','f',' ','|','3','3',' ','|','3','2',' ','|','3','1',' ','|',
'(',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',
'+','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','-',' ','-','+',
'|','U','c',' ','|','2','2',' ','|','2','3',' ','|','T','e',' ','|','2','5',' ','|','2','6',' ','|','2','7',' ','|','T','f',' ','|',' ','a',' ','|','3','0',' ',')',
'|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ',')',
'+','-',' ','-','+','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','+',
'(','2','0',' ','|','1','9',' ','|','1','8',' ','|','1','7',' ','|','1','6',' ','|',' ','c',' ','|',' ','d',' ','|','1','3',' ','|','1','2',' ','|','1','1',' ','|',
'(',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',
'+','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','+','-',' ','-','+',
' ','1',' ','o','|','2',' ',' ','|','3',' ',' ','|',' ','b',' ','|','T','d',' ','|','6',' ',' ','|','7',' ',' ','|','8',' ',' ','|','9',' ',' ','|','1','0',' ',')',
' ','o','o','o','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ',')',
'=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','/'

};


//=============================-o0o-=================================================================================================================================



//===================== DADU ================
char mukadadu[6][5][9]=
	{ 
		' ','-','-','-','-','-','-','-',' ', 													
		'|',' ',' ',' ',' ',' ',' ',' ','|',
		'|',' ',' ',' ','o',' ',' ',' ','|',
		'|',' ',' ',' ',' ',' ',' ',' ','|',
		' ','-','-','-','-','-','-','-',' ',
		
		' ','-','-','-','-','-','-','-',' ',
		'|',' ',' ',' ',' ',' ',' ',' ','|',
		'|',' ',' ','o',' ','o',' ',' ','|',	
		'|',' ',' ',' ',' ',' ',' ',' ','|',
 		' ','-','-','-','-','-','-','-',' ',
 		
		' ','-','-','-','-','-','-','-',' ',
		'|',' ',' ',' ','o',' ',' ',' ','|',
		'|',' ',' ',' ','o',' ',' ',' ','|',
		'|',' ',' ',' ','o',' ',' ',' ','|',
		' ','-','-','-','-','-','-','-',' ',
		
		' ','-','-','-','-','-','-','-',' ',
		'|',' ',' ','o',' ','o',' ',' ','|',
		'|',' ',' ',' ',' ',' ',' ',' ','|',
		'|',' ',' ','o',' ','o',' ',' ','|',
		' ','-','-','-','-','-','-','-',' ',
		 
		' ','-','-','-','-','-','-','-',' ',
		'|',' ',' ','o',' ','o',' ',' ','|',
		'|',' ',' ',' ','o',' ',' ',' ','|',
		'|',' ',' ','o',' ','o',' ',' ','|',
		' ','-','-','-','-','-','-','-',' ',
		
		' ','-','-','-','-','-','-','-',' ',
		'|',' ',' ','o',' ','o',' ',' ','|',
		'|',' ',' ','o',' ','o',' ',' ','|',
		'|',' ',' ','o',' ','o',' ',' ','|',
		' ','-','-','-','-','-','-','-',' ',

	
	};
	
//================== -o0o- =================



//========================== TITLE & CONGRATS =================================
void title(){
	color(2);
	cout<<" ___ ___ __                _______                               \n";
 	cout<<"|   Y   |  .---.-.----.   |       .---.-.-----.-----.-----.---.-.\n";
 	color(3);
 	cout<<"|.  |   |  |  _  |   _|   |.|   | |  _  |     |  _  |  _  |  _  |\n";
 	cout<<"|.  |   |__|___._|__|     `-|.  |-|___._|__|__|___  |___  |___._|\n";
 	color(4);
 	cout<<"|:  1   |                   |:  |             |_____|_____|      \n";
 	cout<<"|::.. . |                   |::.|                                \n";
 	color(5);
 	cout<<"`-------'                   `---'                                \n";
 	cout<<"-----------------------------------------------------------------\n";
}

void congrats(){
	color(2);
	cout<<" _______                              __         __       __   __             \n";
 	cout<<"|   _   .-----.-----.-----.----.---.-|  |_.--.--|  .---.-|  |_|__.-----.-----.\n";
 	color(3);
 	cout<<"|.  1___|  _  |     |  _  |   _|  _  |   _|  |  |  |  _  |   _|  |  _  |     |\n";
 	cout<<"|.  |___|_____|__|__|___  |__| |___._|____|_____|__|___._|____|__|_____|__|__|\n";
 	color(4);
 	cout<<"|:  1   |           |_____|                                                   \n";
 	cout<<"|::.. . |                                                                     \n";
 	color(5);
 	cout<<"`-------'\n";
 	cout<<"------------------------------------------------------------------------------\n";
}
//=============================== -o0o- =======================================



//=========================== PAWN CHECK =================================

//Fungsi ini mengecek apakah player itu aktif. jika tidak, maka fungsi ini mematikan bidak player
int pawncheck(){
	
	for(int i=0; i<4; i++){
		if(p[i].aktif == false){
			map[p[i].pos.y][p[i].pos.x] = ' ';
		}
	}
	
}

//========================================================================



//============================ PRINT =====================================

//Fungsi ini mem-print seluruh isi map dengan  fungsi for
void print(){
	system("CLS");
	pawncheck();
	color(0);
	cout <<"                                    FINISH\n";
	for(int a=0; a<16; a++){
		for(int b=0; b<41; b++){
			
			
			
			
			//Kode dibawa ini memasukkan "setiap kelipatan" pada variabel c dan d
			int c = b%4;
			int d = a%3;
			
			
			//===========================
			//Set warna hijau
			if(d==1 && c==3){
				color(2);
			}
			//Set warna merah
			else if(d==2 && c==3){
				color(3);
			}
			//Set warna cyan
			else if(d==2 && c==2){
				color(4);
			}
			//Set warna kuning
			else if(d==2 && c==1){
				color(5);
			}
			
			//=-=-=-=-=-=-=-=
			else if( (map[a][b] == 'U') || (map[a][b] == 'a') || (map[a][b] == 'b') || (map[a][b] == 'c') ){
				color(9);
			}
			
			else if( (map[a][b] == 'T') || (map[a][b] == 'd') || (map[a][b] == 'e') || (map[a][b] == 'f') ){
				color(8);
			}
			//=-=-=-=-=-=-=-=
			
			
			//Set warna default
			else{
				color(13);
			}
			//==========================
			
			
			
			//Kode dibawah ini mem-print isi map sesuai baris ke - a, kolom ke - b.
			cout << map[a][b];
		}
		cout << endl;
	}
	color(0);
	cout<<"START\n\n";
	color(9);
	cout << "U: Ular,   memindahkan player ke huruf yang sama\n";
	color(8);
	cout << "T: Tangga, memindahkan player ke huruf yang sama\n\n";
	//Kode dibawah ini menjabarkan player - player yang sedang bermain
	for(int i = 0; i < jumlahplayer; i++){
	color(i+2);
	cout<<"Player "<<i+1<<": " << p[i].nama << endl;
	}

}



//==============================-o0o-=====================================



//============================= GERAK ====================================

void checkArah(int a){
	int e = p[a].pos.y % 6;
	if( (e==1)||(e==2) ){
		p[a].arah = 1;
	}	
	else{
		p[a].arah = -1;
	}
}

//Fungsi ini menggerakkan bidak player
void gerak(int a){
	checkArah(a);
	//Di loop sebanyak angka dadu
	for(int i = 0; i < roll; i++){
		//Set posisi bidak menjadi kosong
		map[p[a].pos.y][p[a].pos.x] = ' ';
		//Jika di kiri / kanan bidak terdapat karakter ( / ), maka naikkan ke atas
		if(  (map[p[a].pos.y][p[a].pos.x+(4-(p[a].pos.x%4))] == ')')  ||  (map[p[a].pos.y][p[a].pos.x-(p[a].pos.x%4)] == '(')      ){
			//Set petak di atas menjadi bidak player
			map[p[a].pos.y-3][p[a].pos.x] = 'o';
			//Set posisi y baru dan set arah baru
			p[a].pos.y = p[a].pos.y - 3;
			p[a].arah = p[a].arah * (-1);
		}
		//Jika di kiri / kanan bidak terdapat karakter ; , maka balikkan arah bidak, jalankan, lalu balikkan arahnya lagi
		else if(  (map[p[a].pos.y][p[a].pos.x+(4-(p[a].pos.x%4))] == ';')  ||  (map[p[a].pos.y][p[a].pos.x-(p[a].pos.x%4)] == ';')      ){
			p[a].arah = p[a].arah * -1;
			for(int j=i; j<roll; j++){
				map[p[a].pos.y][p[a].pos.x] = ' ';
				map[p[a].pos.y][p[a].pos.x+(4*p[a].arah)] = 'o';
				p[a].pos.x = p[a].pos.x + (4*p[a].arah);
			}
			p[a].arah = p[a].arah * -1;
			i = roll;
			
		}
		//Jika tidak terdapat karakter apa apa maka jalankan sesuai arah
		else{
			map[p[a].pos.y][p[a].pos.x+(4*p[a].arah)] = 'o';
			p[a].pos.x = p[a].pos.x + (4*p[a].arah);	
		}

		print();
	}
}

//========================================================================



//=========================================== CHECK MENANG ======================================

//Fungsi ini mengecek jika di kanan / kiri posisi player terdapat karakter ; , maka game berakhir
void checkmenang(){
	if(  (map[p[giliran-1].pos.y][p[giliran-1].pos.x+(4-(p[giliran-1].pos.x%4))] == ';')  ||  (map[p[giliran-1].pos.y][p[giliran-1].pos.x-(p[giliran-1].pos.x%4)] == ';')      ){
		p[giliran-1].menang = true;
		menang = true;	
	}
}

//===============================================================================================



//================= DADU ===================
void PrintDadu(int muka){

	for(int a=0; a < 5; a ++){
		for(int b=0; b < 9; b++){
			cout << mukadadu[muka-1][a][b];
		}
		cout << endl;
	}
}

int Roll()
{ 
	int roll;
	for(int i=0;i<40;i++){
		system("CLS");
		cout << "\n\n\n\n\n\n\n\n\n\n";
		color(giliran+1);
		//print();
		roll=(rand()%6)+1;
		PrintDadu(roll);
	}
	 	
	return roll;
}
//================= -o0o- ==================



//======================================== ULAR & TANGGA ==========================================

void checkUT(int a){
	int x = p[a].pos.x;
	int y = p[a].pos.y;
	int z = 0;
	
	//================= ULAR ==================
	//Ua
	if(( (x>32)&&(x<36) ) && ( (y>0)&&(y<3) )){
		map[p[a].pos.y][p[a].pos.x] = ' ';
		map[p[a].pos.y+6][p[a].pos.x] = 'o';
		p[a].pos.y = p[a].pos.y + 6;
		p[a].pos.x = p[a].pos.x;
		z = 1;
	}
	//Ub
	else if(( (x>20)&&(x<24) ) && ( (y>3)&&(y<6) )){
		map[p[a].pos.y][p[a].pos.x] = ' ';
		map[p[a].pos.y+9][p[a].pos.x-8] = 'o';
		p[a].pos.y = p[a].pos.y + 9;
		p[a].pos.x = p[a].pos.x - 8;
		z = 1;
	}
	//Uc
	else if(( (x> 0)&&(x< 4) ) && ( (y>6)&&(y<9) )){
		map[p[a].pos.y][p[a].pos.x] = ' ';
		map[p[a].pos.y+3][p[a].pos.x+20] = 'o';
		p[a].pos.y = p[a].pos.y + 3;
		p[a].pos.x = p[a].pos.x + 20;
		z = 1;
	}
	
	//================ TANGGA ===================
	//Td
	else if(( (x>16)&&(x<20) ) && ( (y>12)&&(y<15) )){
		map[p[a].pos.y][p[a].pos.x] = ' ';
		map[p[a].pos.y-3][p[a].pos.x+8] = 'o';
		p[a].pos.y = p[a].pos.y - 3;
		p[a].pos.x = p[a].pos.x + 8;
		z = 2;
	}
	//Te
	else if(( (x>12)&&(x<16) ) && ( (y>6)&&(y<9) )){
		map[p[a].pos.y][p[a].pos.x] = ' ';
		map[p[a].pos.y-6][p[a].pos.x] = 'o';
		p[a].pos.y = p[a].pos.y - 6;
		p[a].pos.x = p[a].pos.x;
		z = 2;
	}
	//Tf
	else if(( (x>28)&&(x<32) ) && ( (y>6)&&(y<9) )){
		map[p[a].pos.y][p[a].pos.x] = ' ';
		map[p[a].pos.y-3][p[a].pos.x-4] = 'o';
		p[a].pos.y = p[a].pos.y - 3;
		p[a].pos.x = p[a].pos.x - 4;
		z = 2;
	}
	
	
	//=========== TEXT =============
	switch(z){
		case 1 :
			color(3);
			cout << "\nKamu menginjak Ular!";
			sleep(1);
			break;
		case 2 :
			color(2);
			cout << "\nKamu menginjak Tangga!";
			sleep(1);
			break;
	}
}

//============================================ -o0o- ==============================================



int main(){

//======= RANDOM SEED ============
	srand((unsigned)time(0)); 
//================================

	title();
	color(6);
	cout << "\nMasukkan jumlah pemain (Maksimal 4 pemain): ";
	cin >> jumlahplayer;
	if (jumlahplayer > 4){
		jumlahplayer = 4;
	}
	color(4);
	cout << "\nAnda mendaftarkan " << jumlahplayer << " pemain!\n";
	//Untuk memasukkan nama player
	cin.ignore();
	for(int i = 0; i < jumlahplayer; i++){
		color(i+2);
		cout <<"\nMasukkan nama player ke " << i + 1 <<endl;
		getline(cin, p[i].nama);
		//cin >> p[i].nama;
		p[i].aktif = true;
	}
// Ini inisialisasi koordinat awal
//==============
p[0].pos.x = 3;
p[0].pos.y = 13;
p[1].pos.x = 3;
p[1].pos.y = 14;
p[2].pos.x = 2;
p[2].pos.y = 14;
p[3].pos.x = 1;
p[3].pos.y = 14;
//==============

	cout << endl;
	do{
		print();
		color(giliran+1);
		cout << "\nSekarang giliran " << p[giliran-1].nama <<"!";
		color(0);
		
		//================= Komentarkan agar Otomatis ====================
		//cout << "\nSilahkan ketik apapun untuk mengocok dadu!";
		//cin >> bebas;	
		//============================-o0o-===============================
		//cout << "\nMengocok dadu";
		//sleep(1); cout << '.'; sleep(1); cout << '.'; sleep(1); cout << '.'; 
		roll = Roll(); 
		color(0);
		cout << "\n\nKamu mendapatkan angka "; color(6); cout << roll; 
		sleep(1); cout << "\n\nMengerakkan..."; print(); sleep(1);
		gerak(giliran-1);
		checkUT(giliran-1);
		checkmenang();
		//Jika belum menang, maka giliran akan tetap dilanjutkan
		if(!menang){
		
			if(giliran == jumlahplayer){
				giliran = 1;
			}
			else{
				giliran = giliran + 1;
			}
		}
		sleep(1);
		
	
	}while(!menang);
	
	system("CLS");
	congrats();
	color(0);
	cout << "SELAMAT, ";
	color(giliran+1);
	cout << p[giliran-1].nama;
	color(0);
	cout << " MENANG!!";
}
