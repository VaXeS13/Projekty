/*
Marcin Hinc 
Funkcje dotycz�ce stosu zaczerpn��em z zaj�� podstaw programowania, kt�re razem z prowadz�cym napisali�my
Dla u�atwienia pos�u�y�em si� gotow� bibliotek� queue, dzi�ki kt�rej mog�em tworzy� kolejk� i z funkcji zawartych w bibliotec� odwo�ywa� si� do niej

Opis wyja�niaj�cy przedstawiony przyk�ad:
Jako przyk�ad u�y�em grafu zaimplementowanego jako macierz s�siedztwa. Stara�em si� dobra� tak� macierz, aby by�o wyra�nie wida� jaka jest r�nica mi�dzy
algorytmami DFS a BFS. DFS wyznaczy drog� mi�dzy wierzcholkiem u - v, a BFS najkr�tsz� drog� z u do v. 

Oznaczenia tablicy kolor:
B - Bia�y; S - Szary; C - Czarny

Literatura:
G��wnie pos�ugiwa�em si� w�asn� wiedz�, ale sczeg�lnie pomog�y mi notatki z wyk�adu oraz prezentacja umieszczona na moodle Pani Miros�awy Skowro�skiej.
Z pomoc� przysz�a mi r�wnie� strona http://eduinf.waw.pl/inf/utils/011_2011/0105.php, pomog�a mi szczeg�owo zrozumie� jak dzia�a algorytm DFS i BFS


*/

#include <iostream>
#include <queue>

using namespace std;

const int m = 5;			/*Rozmiar macie�y s�siedztwa G[m][m]. Dzi�ki tej zmiennej uzyskuj� uniewarsalno�� w razie, gdy u�ytkownik chcia�by wprowadzi� w�asn�
							macierz s�siedztwa, nie musi w ka�dej funkcji zmienia� rozmiary tablic*/
int time = 0;				//Globalna zmienna time

struct element {			//Struktura dzi�ki kt�rej operujemy na wska�nikach stosu
    int klucz;
    element * nast;			//wska�nik do nast�pnego elementu stosu
};

element * p;				//Tworzenie zmiennej p jako wska�nik na strukturze element

void dodaj(int k){			//Funkcja dodaj�ca nowy element k do stosu	
    element * nowy = new element;
    nowy -> klucz = k;
    nowy -> nast = p;
    p = nowy;
}

int head(){					//Funkcja zwracaj�ca pierwszy element stosu
    element * glowa;
    glowa = p;
    return glowa -> klucz;
}

int zdejmij(){				//Funkcja usuwaj�ca element ze stosu
    if( p != NULL ){
        element * tmp = p;
        p = p -> nast;
        int a = tmp -> klucz;
        delete tmp;
        return a;
    }
    else {	
        return -1;     
	}
}

void tablice_dfs(char kolor[m], int t[m], int Pi[m], int f[m]){			//Funkcja wy�wietlaj�ca zawarto�� tablic kolor, t, Pi, f

	cout << "kolor =\t[";
	for(int i = 0 ; i < m ; i++){										//P�tla wy�wietlaj�ca na ekran zawarto�� tablicy kolor
		cout << kolor[i];
		if(i != m-1){													//Je�eli i b�dzie r�wne przedostatniemu indeksowi, to wtedy nie dopisuje ","
			cout << ",";
		}
		
	}
	cout << "]\n";
	
	cout<<"t =\t[";
	for(int i = 0 ; i < m ; i++){										//P�tla wy�wietlaj�ca na ekran zawarto�� tablicy t
		cout << t[i];
		if(i != m-1){													//Je�eli i b�dzie r�wne przedostatniemu indeksowi, to wtedy nie dopisuje ","
			cout << ",";
		}
	}
	cout << "]\n";
	
	cout << "Pi =\t[";
	for(int i = 0 ; i < m ; i++){										//P�tla wy�wietlaj�ca na ekran zawarto�� tablicy Pi
		cout << Pi[i];
		if(i != m-1){													//Je�eli i b�dzie r�wne przedostatniemu indeksowi, to wtedy nie dopisuje ","
			cout << ",";
		}
	}
	cout << "]\n";
	
	cout << "f =\t[";
	for(int i = 0 ; i < m ; i++){										//P�tla wy�wietlaj�ca na ekran zawarto�� tablicy f
		cout << f[i];
		if(i != m-1){													//Je�eli i b�dzie r�wne przedostatniemu indeksowi, to wtedy nie dopisuje ","
			cout << ",";
		}
	}
	cout << "]\n\n";
}

void DFS_VISIT(int G[m][m], int u, char kolor[m], int t[m], int Pi[m], int f[m]){	/*Funkcja rekurencyjna, kt�ra jako argument przyjmuje graf(macierz s�siedztwa), wierzcho�ek startowy, tablic� kolor, t, Pi, f.
																					Jest odpowiedzialna za wyznaczenie warto�ci wy�ej wymienionych tablic.*/
	int licz = 0;																		
	int sasiad = -20;
	kolor[u] = 'S';						//Do tablicy kolor o indeksie startowym (u) zapisujemy "S"
	time++;
	t[u] = time;						//Do tablicy t o indeksie startowym (u) zapisujemy warto�� zmiennej time
	for(int i = 0 ; i < m ; i++){		//p�tla sprawdzaj�ca s�siad�w wierzcho�ka u, 
		if(G[u][i] == 1){				/*Je�eli w macierzy o indeksach G[u][i], gdzie i jest inkrementowane co obieg p�tli, a u jest wierzcho�kiem startowym wyst�puje "1" oznacza to, �e*/
			sasiad = i;					/*wyst�puje s�siedztwo pomiedzy wierzcho�kiem u i. Wtedy do stosu dodaje wierzcho�ek s�siedni u, czyli i*/
			dodaj(sasiad);				//Dodanie do stosu wierzcho�ka s�siedniego u
			licz = 1;					//Dzi�ki temu licznikowi wiemy czy p�tla ni�ej ma si� wykona�
		}				
		
		if(licz == 1){							//Je�eli jest s�siad do u wtedy wykonuje operacje poni�ej
			if(kolor[head()] == 'B'){			//Je�eli w tablicy kolor o indeksie, kt�rym jest g�owa stosu ma warto�� B, czyli Bia�y
				Pi[head()] = u;					//Do tablicy Pi o indeksie, kt�rym jest g�owa stosu
				DFS_VISIT(G, head(), kolor, t, Pi, f);	//Wywo�anie funkcji DFS_VISIT (rekurencja), kt�ra jako argument przyjmuje g�ow� stosu zamiast elementu startowego u
			}
		}
	}
	kolor[u] = 'C';
	time++;								//Inkrementacja zmiennej time
	f[u] = time;						//Zapisanie do tablicy f o indeksie u warto�� zmiennej time
	zdejmij();							//Zdejmowanie ze stosu g�owy
}

void DFS(int G[m][m], int u, int Pi[m]){	
	char kolor[m];
	int t[m];
	int f[m];
	for(int i = 0 ; i < m ; i++){		//Wype�nienie tablicy kolor, t, f warto�ciami widocznymi w p�tli
		kolor[i] = 'B';
		t[i] = -20;
		f[i] = -20;
	}
	dodaj(u);							//Dodanie do stosu elementu startowego u
	DFS_VISIT(G, u, kolor, t, Pi, f); 	//Wywy�anie funkcji DFS-VISIdnych zmiennychT z przekazaniem niezb�
	tablice_dfs(kolor, t, Pi, f);		//Wywy�anie funkcji tablice_dfs, aby wy�wietli� na ekran wynikowe tablice kolor, t, Pi, f
}


void tablice_bfs(char kolor[m], int Pi[m], int d[m]){
	cout << "kolor =\t[";
	for(int i = 0 ; i < m ; i++){		//P�tla wy�wietlaj�ca na ekran zawarto�� tablicy kolor
		cout << kolor[i];
		if(i != m-1){					//Je�eli i b�dzie r�wne przedostatniemu indeksowi, to wtedy nie dopisuje ","
			cout << ",";
		}
	}
	cout << "]\n";
												
	cout << "Pi =\t[";
	for(int i = 0 ; i < m ; i++){		//P�tla wy�wietlaj�ca na ekran zawarto�� tablicy Pi
		cout << Pi[i];
		if( i != m-1 ){					//Je�eli i b�dzie r�wne przedostatniemu indeksowi, to wtedy nie dopisuje ","
			cout << ",";
		}
	}
	cout << "]\n";
	
	cout << "d =\t[";
	for(int i = 0 ; i < m ; i++){		//P�tla wy�wietlaj�ca na ekran zawarto�� tablicy d
		cout << d[i];
		if( i != m-1 ){					//Je�eli i b�dzie r�wne przedostatniemu indeksowi, to wtedy nie dopisuje ","
			cout << ",";
		}
	}
	cout << "]\n\n";
}

void BFS(int G[m][m], int s, int Pi[m]){/*Funkcja, kt�ra jako argument przyjmuje graf (macierz s�siedztwa), wierzcho�ek startowy oraz tablic� Pi.
										Jest odpowiedzialna za wyznaczenie warto�ci tablic takich jak: Pi, kolor, d.*/
	char kolor[m];						//Tablica typu char, w kt�rej trzymamy warto�ci o tym, czy dany wierzcho�ek by� odwiedzony, czy ma jeszcze jakich� s�siad�w
	int d[m];							//W tej tablicy znajduj� si� informacja ile krok�w jest potrzebnych aby doj�� z wierzcho�ka startowego u do inne wierzcholka(indeks tablicy to wierzcho�ek)
	int licz = 0, sasiad, u, v;
	queue<int> kolejka;					//Utworzenie kolejki o nazwie kolejka
	
	for(int i = 0 ; i < m ; i++){		//P�tla wype�nia tablice kolor, d widocznymi poni�ej warto�ciami
		kolor[i] = 'B';
		d[i] = -20;
	}
	kolor[s] = 'S';						//Do tablicy kolor o indeksie s (wierzcho�ek startowy) jest nadpisywana warto�� 'B'
	d[s] = 0;							//Do tablicy d o indeksie s (wierzcho�ek startowy) jest nadpisywana warto�� '0'
	Pi[s] = -1;							//Do tablicy kolor o indeksie s (wierzcho�ek startowy) jest nadpisywana warto�� -1
	kolejka.push(s);					//Dodanie do kolejki zmiennej s, czyli wierzcho�ka startowego
	while(kolejka.empty() != true){		//Wykonywanie si� p�tli dop�ki kolejka nie jest pusta

		u = kolejka.front();			//Do zmiennej u zapisywany jest pierwszy element kolejki (g�owa kolejki)
		licz = 0;
		sasiad = -20;
		for(int i = 0 ; i < m ; i++){	//p�tla sprawdzaj�ca s�siad�w wierzcho�ka u, 
										/*Je�eli w macierzy o indeksach G[u][i], gdzie i jest inkrementowane co obieg p�tli, a u jest wierzcho�kiem startowym wyst�puje "1" oznacza to, �e*/
			if(G[u][i] == 1){			//Je�eli wyst�puje s�siedztwo pomiedzy wierzcho�kiem u i. Wtedy do koleji dodaje wierzch�lek s�siedni u, czyli i
				sasiad = i;	
				kolejka.push(sasiad);	//Dodanie do kolejki wierzcho�ka s�siad (i)
				licz = 1;
			}
		
			if(sasiad != -20){			//Je�eli zaistnia�o s�siedztwo miedzy G[u][i], to pod te indeksy podstawiana jest warto�� 0, aby w przysz�o�ci unikn�� zap�tlenia si�
				G[u][sasiad] = 0;
				G[sasiad][u] = 0;
			}
			
			if (kolor[sasiad] == 'B'){	//Je�eli kolor[sasiad] b�dzie bia�y (nie odwiedzony), to wykonywania jest p�tla poni�ej
		
				for(int i = 0 ; i < licz ; i++){	//P�tla si� wykonuje, je�eli licz=1 
					kolor[sasiad] = 'S';			//Kolor o indeksie sasiad jest szary, czyli odwiedzony
					d[sasiad] = d[u] + 1;			//Do tablicy d o indeksie sasiad jest przypisana warto�� tablicy d o indeksie u i do tej warto�ci dodana 1
					Pi[sasiad] = u;					//Do tablicy Pi po indeksie sasiad przypisujemt warto�� zmiennej u (g�owa kolejki)
					kolejka.push(sasiad);			//Do kolejki dodajemy zmienna sasiad
				}
			}
		}
		kolor[u] = 'C';								//Po obiegu p�li sprawdzaj�cej s�siad�w wierzcho�ka u, ustawiamy warto�� tablicy kolor o indeksie u na czarmy, czyli odwiedzony bez s�siad�w do sprawdzenia
		kolejka.pop();								//Zdj�cie z kolejki elementu pierwszego
	}
	tablice_bfs(kolor, Pi, d);						//Wy�wietlenie na ekran tablic kolor, Pi, d
}

void odczytanie_sciezki_DFS(int G[m][m], int u, int v){	//Funkcja s�u��ca do odczytania �cie�ki z u do v. Jej argumentami jest macierz, wierzcho�ek startowy i wierzcho�ek docelowy
	int Pi[m];							//Tworzenie tablicy Pi, kt�ra pozni�ej pos�u�y nam do wyznaczenia drogi z u do v
	int t[m], j=0;						//Tablica t pos�u�y nam do przechowywanie informacji o wyznaczonej drodze z u do v. Dzi�ki zmiennej j wiemy ile znajduje si� element�w w tablicy t
	for(int i = 0 ; i < m ; i++){		//Wype�nienie tablicy Pi warto�ci� -1
		Pi[i] = -1;
	}
	DFS(G, u, Pi);						//Wywo�anie funkcji DFS i przekazuje macierz s�siedztwa, wierzcho�ek startowy i tablice Pi
	cout << "Droga z " << u << " do " << v << ": ";	
	while(v != -1){						//G��wna p�tla wyznaczaj�ca odleg�o�� mi�dzy u - v. Wykunouje si� dop�ki v != -1. Jest to najwa�niejsza p�tla w tej funkcji, kt�ra wyznacza droge z u do v
		t[j] = v;						//Pod tablice t jest podstawiany obecny wierzcholek v
		v = Pi[v];						//Pod zmienna v podstawiana jest warto�� tablicy Pi o indeksie v
		j++;							//Inkrementacja zmiennej j, aby w nast�pnych obiegach p�tli odwo�ywa� si� do nast�pnych indeks�w tablicy
	}

	for(int i = j-1 ; i >= 0; i--){	/*P�tla s�u��ca do wy�wietlenia tablicy t od indeksu najwyzszego do 0. j-1, poniewa� w ostatnim obiegu p�tli while zmienne j ulegla inkrementacji, co oznacza �e */
		cout << t[i];				//nale�y od niej odj�� warto�� 1
		if( i != 0 ){
			cout << " -> ";
		}			
	}	
}

void odczytanie_sciezki_BFS(int G[m][m], int u, int v){		//Funkcja s�u��ca do odczytania �cie�ki z u do v. Jej argumentami jest macierz, wierzcho�ek startowy i wierzcho�ek docelowy
	int Pi[m];							//Tworzenie tablicy Pi, kt�ra pozni�ej pos�u�y nam do wyznaczenia drogi z u do v
	int t[m], j = 0;					//Tablica t pos�u�y nam do przechowywanie informacji o wyznaczonej drodze z u do v. Dzi�ki zmiennej j wiemy ile znajduje si� element�w w tablicy t
	for(int i = 0 ; i < m ; i++){		///Wype�nienie tablicy Pi warto�ci� -1
		Pi[i] = -1;
	}
	BFS(G, u, Pi);						//Wywo�anie funkcji BFS i przekazuje macierz s�siedztwa, wierzcho�ek startowy i tablice Pi
	cout << "Droga z " << u << " do " << v << ": ";	
	while(v != -1){						//G��wna p�tla wyznaczaj�ca odleg�o�� mi�dzy u - v. Wykunouje si� dop�ki v != -1. Jest to najwa�niejsza p�tla w tej funkcji, kt�ra wyznacza droge z u do v
		t[j] = v;						//Pod tablice t jest podstawiany obecny wierzcholek v
		v = Pi[v];						//Pod zmienna v podstawiana jest warto�� tablicy Pi o indeksie v
		j++;							//Inkrementacja zmiennej j, aby w nast�pnych obiegach p�tli odwo�ywa� si� do nast�pnych indeks�w tablicy
	}

	for(int i = j-1 ; i >= 0 ; i--){	/*P�tla s�u��ca do wy�wietlenia tablicy t od indeksu najwyzszego do 0. j-1, poniewa� w ostatnim obiegu p�tli while zmienne j ulegla inkrementacji, co oznacza �e nale�y od niej odj�� warto�� 1*/
		cout << t[i];
		if( i != 0 ){
			cout << " -> ";
		}
	}
}

int main(void) {
    int u, v;						//Zmienna wybor - s�u�y do wyboru BFS, a DFS;	u - element startowy grafu;	v - element docelowy grafu
    int G[m][m] = { {0,1,0,0,0} , {1,0,1,1,0} , {0,1,0,0,0} , {0,1,0,0,1} , {0,0,0,1,0} };


    cout<<"Reprezentacja macierzy sasiedztwa:\n\n";
    cout<<"| 0 1 0 0 1 0 | \n";
    cout<<"| 1 0 1 0 1 0 | \n";
    cout<<"| 0 1 0 1 0 0 | \n";
    cout<<"| 0 0 1 0 0 1 | \n";
    cout<<"| 1 1 0 0 0 1 | \n";
    cout<<"| 0 0 0 1 1 0 | \n";
    cout<<"\n";

    u = 0 ;								//wierzcho�ek startowy w grafie
	v = 4 ;								//wierzcho�ek do kt�rego chcemy dotrze�

    cout<<"\tDFS: \n";
	odczytanie_sciezki_DFS(G, u, v);	//Wywo�anie funkcji, kt�ra wyznacza drog� z u do v za pomoc� DFS
   	
	cout<<"\n\n";
   	
	cout<<"\tBFS: \n";
	odczytanie_sciezki_BFS(G, u, v);	//Wywo�anie funkcji, kt�ra wyznacza drog�(najkr�tsz�) z u do v za pomoc� BFS
    
	
	return 0;
}
