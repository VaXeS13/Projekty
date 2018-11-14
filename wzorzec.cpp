/*
Marcin Hinc
TJF - zadanie domowe
Implementacja algorytmu Boyera-Moore'a
Wyszukiwawnie wzorca
*/
#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;
//Funkcja wypisujaca na ekran wzorzec, nazwe pliku, tekst z pliku, ilosc wystapien wzorca oraz na jakiej pozycji
void Wypisz(int z, int indeksy[], string wzorzec, string tekst){
	int s = 0;	//zmienna za pomoca ktorej wiemy jaki znak kolorowac na zielono
	if(tekst.length() != 0){
	
		cout << "\n\nWzorinzec: " << wzorzec << endl;
		cout << "W pliku: " << "plik.txt" << endl;
		for(int i=0 ; i < tekst.length(); i++){
			if(i >= indeksy[s] && i<= indeksy[s+1]){
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), FOREGROUND_GREEN | FOREGROUND_INTENSITY );
				s = s + 1;
			}else{
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), FOREGROUND_INTENSITY);
			}
			cout<< tekst[i];
			
		}
		//cout << "\nTekst: '" << tekst << "'\n"<< endl;
		cout << "\nIlosc wystapien wzorca: " << z/2 << endl;
	}
}

//Funkcja zwracajaca najwiekszy element
int maksymalna(int a, int b){
	if(a > b){
		return a;
	}
	return b;
}

//Funkcja sprawdzajaca czy wystapil wzorzec w tekscie
void Wyznacz(int &znakPierwszejLitery, int &znakOstatniejLitery, string wzorzec, string tekst, int dlWzorca, int dlTekstu){
	int i, tmp, j;
	int z = 0;					//zmienna, zliczajaca ilosc indeksów. Dokladniej z/2 = ilosc wystapien
	int indeksy[255];			//do tablicy s¹ zapisywane indeksy wystapien wzorca
	i = 0;
	tmp = 0;
	//tablica ostatnich pozycji wszystkich znaków alfabetu we wzorcu
	int Pi[znakOstatniejLitery - znakPierwszejLitery + 1];
	
	//wype³nienie tablicy wartoscia -1
	for(int i = 0; i <= znakOstatniejLitery - znakPierwszejLitery; i++){
		Pi[i] = -1;
	}
	
	//
	for(int i = 0; i < dlWzorca; i++){
		Pi[wzorzec[i] - znakPierwszejLitery] = i;
		
	}
	
	//glowny element programu, tutaj jest sprawdzanie dopasowania wzorca z tekstem
	while(i <= dlTekstu - dlWzorca){
		j = dlWzorca - 1;
		while((j > -1) && (wzorzec[j] == tekst[i + j])) 
			j--;
		if(j == -1){
			while(tmp < i){
				tmp++;	//pozycja wzorca
			}
			tmp++; 
			indeksy[z] = tmp - 1;
			
			indeksy[z + 1] = tmp - 1 + dlWzorca - 1;
			z += 2;
			i++;
		}
		else 
			i = i + maksymalna(1, j - Pi[tekst[i + j] - znakPierwszejLitery]);
	}
	
	//wywolanie funkcji wypisujacej na ekran
	Wypisz(z, indeksy, wzorzec, tekst);
}

//funkcja obliczajaca najmniejsza i najwiêksza litera z wzorca i tekstu korzystaj¹c z tablicy ASCII
void Wylicz(int &znakPierwszejLitery, int &znakOstatniejLitery, string wzorzec, string tekst, int dlWzorca, int dlTekstu){
	int minW, maxW;				//minimalna litera, maksymalna litera we wzorcu
	int minT, maxT;				//minimalna litera, maksymalna litera w tekscie
	
	minW = (char)wzorzec[0];
	maxW = (char)wzorzec[0];
	
	//wyszukanie najmniejszej i najwiêkszej litery we wzorcu
	for(int i = 1; i< dlWzorca; i++){
		if(wzorzec[i] < minW)
			minW = wzorzec[i];
		if(wzorzec[i] > maxW)
			maxW = wzorzec[i];
	}
  
	minT = (char)tekst[0];
	maxT = (char)tekst[0];
  
	//wyszukanie najmniejszej i najwiêkszej litery w tekscie
	for(int i = 1; i< dlTekstu; i++){
		if(tekst[i] < minT)
			minT = tekst[i];
		if(tekst[i] > maxT)
			maxT = tekst[i];
	}

	//sprawdzenie minimalnej i maksymalnej wartosci miedzy wzorcem a tekstem
	if(minW > minT)
		znakPierwszejLitery = minT;
	else
		znakPierwszejLitery = minW;
  
	if(maxW > maxT)
		znakOstatniejLitery = maxW;
	else
		znakOstatniejLitery = maxT;
	
	Wyznacz(znakPierwszejLitery, znakOstatniejLitery, wzorzec, tekst, dlWzorca, dlTekstu);
}

int main()
{
	

	string wzorzec, tekst;		//zmienne odpowienio wzorzec, tekst
	int dlWzorca, dlTekstu;		//dlugoœæ wzorca oraz dlugoœæ tekstu
	int znakPierwszejLitery, znakOstatniejLitery;	//w tych zmiennych zanduj¹ sie odowienio najmniejsza, najwiêksza litera z wzorca i tekstu. Korzystaj¹c z tablicy ASCII wyznaczana jest ta wartoœæ
  	
  
  	fstream plik;				
  	plik.open("plik.txt", ios::in);	//otworzenie plliku do odczytu
	
	cout << "Podaj wzorzec: ";
	cin >> wzorzec;
	dlWzorca = wzorzec.length();
	
	while(!plik.eof()){
		getline(plik, tekst);		//zapisanie zawartoœci pliku zmiennej tekst
		
		dlTekstu = tekst.length();
		//wywolanie funkcji sprawdzajacej czy wystapil wzorzec w tekscie
		Wylicz(znakPierwszejLitery, znakOstatniejLitery, wzorzec, tekst, dlWzorca, dlTekstu);
	}
	
	plik.close();
	return 0;
} 
