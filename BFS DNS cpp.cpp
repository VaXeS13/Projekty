/*
Marcin Hinc 
Funkcje dotycz¹ce stosu zaczerpn¹³em z zajêæ podstaw programowania, które razem z prowadz¹cym napisaliœmy
Dla u³atwienia pos³u¿y³em siê gotow¹ bibliotek¹ queue, dziêki której mog³em tworzyæ kolejkê i z funkcji zawartych w bibliotecê odwo³ywaæ siê do niej

Opis wyjaœniaj¹cy przedstawiony przyk³ad:
Jako przyk³ad u¿y³em grafu zaimplementowanego jako macierz s¹siedztwa. Stara³em siê dobraæ tak¹ macierz, aby by³o wyraŸnie widaæ jaka jest ró¿nica miêdzy
algorytmami DFS a BFS. DFS wyznaczy drogê miêdzy wierzcholkiem u - v, a BFS najkrótsz¹ drogê z u do v. 

Oznaczenia tablicy kolor:
B - Bia³y; S - Szary; C - Czarny

Literatura:
G³ównie pos³ugiwa³em siê w³asn¹ wiedz¹, ale sczególnie pomog³y mi notatki z wyk³adu oraz prezentacja umieszczona na moodle Pani Miros³awy Skowroñskiej.
Z pomoc¹ przysz³a mi równie¿ strona http://eduinf.waw.pl/inf/utils/011_2011/0105.php, pomog³a mi szczegó³owo zrozumieæ jak dzia³a algorytm DFS i BFS


*/

#include <iostream>
#include <queue>

using namespace std;

const int m = 5;			/*Rozmiar macie¿y s¹siedztwa G[m][m]. Dziêki tej zmiennej uzyskujê uniewarsalnoœæ w razie, gdy u¿ytkownik chcia³by wprowadziæ w³asn¹
							macierz s¹siedztwa, nie musi w ka¿dej funkcji zmieniaæ rozmiary tablic*/
int time = 0;				//Globalna zmienna time

struct element {			//Struktura dziêki której operujemy na wskaŸnikach stosu
    int klucz;
    element * nast;			//wskaŸnik do nastêpnego elementu stosu
};

element * p;				//Tworzenie zmiennej p jako wskaŸnik na strukturze element

void dodaj(int k){			//Funkcja dodaj¹ca nowy element k do stosu	
    element * nowy = new element;
    nowy -> klucz = k;
    nowy -> nast = p;
    p = nowy;
}

int head(){					//Funkcja zwracaj¹ca pierwszy element stosu
    element * glowa;
    glowa = p;
    return glowa -> klucz;
}

int zdejmij(){				//Funkcja usuwaj¹ca element ze stosu
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

void tablice_dfs(char kolor[m], int t[m], int Pi[m], int f[m]){			//Funkcja wyœwietlaj¹ca zawartoœæ tablic kolor, t, Pi, f

	cout << "kolor =\t[";
	for(int i = 0 ; i < m ; i++){										//Pêtla wyœwietlaj¹ca na ekran zawartoœæ tablicy kolor
		cout << kolor[i];
		if(i != m-1){													//Je¿eli i bêdzie równe przedostatniemu indeksowi, to wtedy nie dopisuje ","
			cout << ",";
		}
		
	}
	cout << "]\n";
	
	cout<<"t =\t[";
	for(int i = 0 ; i < m ; i++){										//Pêtla wyœwietlaj¹ca na ekran zawartoœæ tablicy t
		cout << t[i];
		if(i != m-1){													//Je¿eli i bêdzie równe przedostatniemu indeksowi, to wtedy nie dopisuje ","
			cout << ",";
		}
	}
	cout << "]\n";
	
	cout << "Pi =\t[";
	for(int i = 0 ; i < m ; i++){										//Pêtla wyœwietlaj¹ca na ekran zawartoœæ tablicy Pi
		cout << Pi[i];
		if(i != m-1){													//Je¿eli i bêdzie równe przedostatniemu indeksowi, to wtedy nie dopisuje ","
			cout << ",";
		}
	}
	cout << "]\n";
	
	cout << "f =\t[";
	for(int i = 0 ; i < m ; i++){										//Pêtla wyœwietlaj¹ca na ekran zawartoœæ tablicy f
		cout << f[i];
		if(i != m-1){													//Je¿eli i bêdzie równe przedostatniemu indeksowi, to wtedy nie dopisuje ","
			cout << ",";
		}
	}
	cout << "]\n\n";
}

void DFS_VISIT(int G[m][m], int u, char kolor[m], int t[m], int Pi[m], int f[m]){	/*Funkcja rekurencyjna, która jako argument przyjmuje graf(macierz s¹siedztwa), wierzcho³ek startowy, tablicê kolor, t, Pi, f.
																					Jest odpowiedzialna za wyznaczenie wartoœci wy¿ej wymienionych tablic.*/
	int licz = 0;																		
	int sasiad = -20;
	kolor[u] = 'S';						//Do tablicy kolor o indeksie startowym (u) zapisujemy "S"
	time++;
	t[u] = time;						//Do tablicy t o indeksie startowym (u) zapisujemy wartoœæ zmiennej time
	for(int i = 0 ; i < m ; i++){		//pêtla sprawdzaj¹ca s¹siadów wierzcho³ka u, 
		if(G[u][i] == 1){				/*Je¿eli w macierzy o indeksach G[u][i], gdzie i jest inkrementowane co obieg pêtli, a u jest wierzcho³kiem startowym wystêpuje "1" oznacza to, ¿e*/
			sasiad = i;					/*wystêpuje s¹siedztwo pomiedzy wierzcho³kiem u i. Wtedy do stosu dodaje wierzcho³ek s¹siedni u, czyli i*/
			dodaj(sasiad);				//Dodanie do stosu wierzcho³ka s¹siedniego u
			licz = 1;					//Dziêki temu licznikowi wiemy czy pêtla ni¿ej ma siê wykonaæ
		}				
		
		if(licz == 1){							//Je¿eli jest s¹siad do u wtedy wykonuje operacje poni¿ej
			if(kolor[head()] == 'B'){			//Je¿eli w tablicy kolor o indeksie, którym jest g³owa stosu ma wartoœæ B, czyli Bia³y
				Pi[head()] = u;					//Do tablicy Pi o indeksie, którym jest g³owa stosu
				DFS_VISIT(G, head(), kolor, t, Pi, f);	//Wywo³anie funkcji DFS_VISIT (rekurencja), która jako argument przyjmuje g³owê stosu zamiast elementu startowego u
			}
		}
	}
	kolor[u] = 'C';
	time++;								//Inkrementacja zmiennej time
	f[u] = time;						//Zapisanie do tablicy f o indeksie u wartoœæ zmiennej time
	zdejmij();							//Zdejmowanie ze stosu g³owy
}

void DFS(int G[m][m], int u, int Pi[m]){	
	char kolor[m];
	int t[m];
	int f[m];
	for(int i = 0 ; i < m ; i++){		//Wype³nienie tablicy kolor, t, f wartoœciami widocznymi w pêtli
		kolor[i] = 'B';
		t[i] = -20;
		f[i] = -20;
	}
	dodaj(u);							//Dodanie do stosu elementu startowego u
	DFS_VISIT(G, u, kolor, t, Pi, f); 	//Wywy³anie funkcji DFS-VISIdnych zmiennychT z przekazaniem niezbê
	tablice_dfs(kolor, t, Pi, f);		//Wywy³anie funkcji tablice_dfs, aby wyœwietliæ na ekran wynikowe tablice kolor, t, Pi, f
}


void tablice_bfs(char kolor[m], int Pi[m], int d[m]){
	cout << "kolor =\t[";
	for(int i = 0 ; i < m ; i++){		//Pêtla wyœwietlaj¹ca na ekran zawartoœæ tablicy kolor
		cout << kolor[i];
		if(i != m-1){					//Je¿eli i bêdzie równe przedostatniemu indeksowi, to wtedy nie dopisuje ","
			cout << ",";
		}
	}
	cout << "]\n";
												
	cout << "Pi =\t[";
	for(int i = 0 ; i < m ; i++){		//Pêtla wyœwietlaj¹ca na ekran zawartoœæ tablicy Pi
		cout << Pi[i];
		if( i != m-1 ){					//Je¿eli i bêdzie równe przedostatniemu indeksowi, to wtedy nie dopisuje ","
			cout << ",";
		}
	}
	cout << "]\n";
	
	cout << "d =\t[";
	for(int i = 0 ; i < m ; i++){		//Pêtla wyœwietlaj¹ca na ekran zawartoœæ tablicy d
		cout << d[i];
		if( i != m-1 ){					//Je¿eli i bêdzie równe przedostatniemu indeksowi, to wtedy nie dopisuje ","
			cout << ",";
		}
	}
	cout << "]\n\n";
}

void BFS(int G[m][m], int s, int Pi[m]){/*Funkcja, która jako argument przyjmuje graf (macierz s¹siedztwa), wierzcho³ek startowy oraz tablicê Pi.
										Jest odpowiedzialna za wyznaczenie wartoœci tablic takich jak: Pi, kolor, d.*/
	char kolor[m];						//Tablica typu char, w której trzymamy wartoœci o tym, czy dany wierzcho³ek by³ odwiedzony, czy ma jeszcze jakichœ s¹siadów
	int d[m];							//W tej tablicy znajduj¹ siê informacja ile kroków jest potrzebnych aby dojœæ z wierzcho³ka startowego u do inne wierzcholka(indeks tablicy to wierzcho³ek)
	int licz = 0, sasiad, u, v;
	queue<int> kolejka;					//Utworzenie kolejki o nazwie kolejka
	
	for(int i = 0 ; i < m ; i++){		//Pêtla wype³nia tablice kolor, d widocznymi poni¿ej wartoœciami
		kolor[i] = 'B';
		d[i] = -20;
	}
	kolor[s] = 'S';						//Do tablicy kolor o indeksie s (wierzcho³ek startowy) jest nadpisywana wartoœæ 'B'
	d[s] = 0;							//Do tablicy d o indeksie s (wierzcho³ek startowy) jest nadpisywana wartoœæ '0'
	Pi[s] = -1;							//Do tablicy kolor o indeksie s (wierzcho³ek startowy) jest nadpisywana wartoœæ -1
	kolejka.push(s);					//Dodanie do kolejki zmiennej s, czyli wierzcho³ka startowego
	while(kolejka.empty() != true){		//Wykonywanie siê pêtli dopóki kolejka nie jest pusta

		u = kolejka.front();			//Do zmiennej u zapisywany jest pierwszy element kolejki (g³owa kolejki)
		licz = 0;
		sasiad = -20;
		for(int i = 0 ; i < m ; i++){	//pêtla sprawdzaj¹ca s¹siadów wierzcho³ka u, 
										/*Je¿eli w macierzy o indeksach G[u][i], gdzie i jest inkrementowane co obieg pêtli, a u jest wierzcho³kiem startowym wystêpuje "1" oznacza to, ¿e*/
			if(G[u][i] == 1){			//Je¿eli wystêpuje s¹siedztwo pomiedzy wierzcho³kiem u i. Wtedy do koleji dodaje wierzch³lek s¹siedni u, czyli i
				sasiad = i;	
				kolejka.push(sasiad);	//Dodanie do kolejki wierzcho³ka s¹siad (i)
				licz = 1;
			}
		
			if(sasiad != -20){			//Je¿eli zaistnia³o s¹siedztwo miedzy G[u][i], to pod te indeksy podstawiana jest wartoœæ 0, aby w przysz³oœci unikn¹æ zapêtlenia siê
				G[u][sasiad] = 0;
				G[sasiad][u] = 0;
			}
			
			if (kolor[sasiad] == 'B'){	//Je¿eli kolor[sasiad] bêdzie bia³y (nie odwiedzony), to wykonywania jest pêtla poni¿ej
		
				for(int i = 0 ; i < licz ; i++){	//Pêtla siê wykonuje, je¿eli licz=1 
					kolor[sasiad] = 'S';			//Kolor o indeksie sasiad jest szary, czyli odwiedzony
					d[sasiad] = d[u] + 1;			//Do tablicy d o indeksie sasiad jest przypisana wartoœæ tablicy d o indeksie u i do tej wartoœci dodana 1
					Pi[sasiad] = u;					//Do tablicy Pi po indeksie sasiad przypisujemt wartoœæ zmiennej u (g³owa kolejki)
					kolejka.push(sasiad);			//Do kolejki dodajemy zmienna sasiad
				}
			}
		}
		kolor[u] = 'C';								//Po obiegu pêli sprawdzaj¹cej s¹siadów wierzcho³ka u, ustawiamy wartoœæ tablicy kolor o indeksie u na czarmy, czyli odwiedzony bez s¹siadów do sprawdzenia
		kolejka.pop();								//Zdjêcie z kolejki elementu pierwszego
	}
	tablice_bfs(kolor, Pi, d);						//Wyœwietlenie na ekran tablic kolor, Pi, d
}

void odczytanie_sciezki_DFS(int G[m][m], int u, int v){	//Funkcja s³u¿¹ca do odczytania œcie¿ki z u do v. Jej argumentami jest macierz, wierzcho³ek startowy i wierzcho³ek docelowy
	int Pi[m];							//Tworzenie tablicy Pi, która pozni¿ej pos³u¿y nam do wyznaczenia drogi z u do v
	int t[m], j=0;						//Tablica t pos³u¿y nam do przechowywanie informacji o wyznaczonej drodze z u do v. Dziêki zmiennej j wiemy ile znajduje siê elementów w tablicy t
	for(int i = 0 ; i < m ; i++){		//Wype³nienie tablicy Pi wartoœci¹ -1
		Pi[i] = -1;
	}
	DFS(G, u, Pi);						//Wywo³anie funkcji DFS i przekazuje macierz s¹siedztwa, wierzcho³ek startowy i tablice Pi
	cout << "Droga z " << u << " do " << v << ": ";	
	while(v != -1){						//G³ówna pêtla wyznaczaj¹ca odleg³oœæ miêdzy u - v. Wykunouje siê dopóki v != -1. Jest to najwa¿niejsza pêtla w tej funkcji, która wyznacza droge z u do v
		t[j] = v;						//Pod tablice t jest podstawiany obecny wierzcholek v
		v = Pi[v];						//Pod zmienna v podstawiana jest wartoœæ tablicy Pi o indeksie v
		j++;							//Inkrementacja zmiennej j, aby w nastêpnych obiegach pêtli odwo³ywaæ siê do nastêpnych indeksów tablicy
	}

	for(int i = j-1 ; i >= 0; i--){	/*Pêtla s³u¿¹ca do wyœwietlenia tablicy t od indeksu najwyzszego do 0. j-1, poniewa¿ w ostatnim obiegu pêtli while zmienne j ulegla inkrementacji, co oznacza ¿e */
		cout << t[i];				//nale¿y od niej odj¹æ wartoœæ 1
		if( i != 0 ){
			cout << " -> ";
		}			
	}	
}

void odczytanie_sciezki_BFS(int G[m][m], int u, int v){		//Funkcja s³u¿¹ca do odczytania œcie¿ki z u do v. Jej argumentami jest macierz, wierzcho³ek startowy i wierzcho³ek docelowy
	int Pi[m];							//Tworzenie tablicy Pi, która pozni¿ej pos³u¿y nam do wyznaczenia drogi z u do v
	int t[m], j = 0;					//Tablica t pos³u¿y nam do przechowywanie informacji o wyznaczonej drodze z u do v. Dziêki zmiennej j wiemy ile znajduje siê elementów w tablicy t
	for(int i = 0 ; i < m ; i++){		///Wype³nienie tablicy Pi wartoœci¹ -1
		Pi[i] = -1;
	}
	BFS(G, u, Pi);						//Wywo³anie funkcji BFS i przekazuje macierz s¹siedztwa, wierzcho³ek startowy i tablice Pi
	cout << "Droga z " << u << " do " << v << ": ";	
	while(v != -1){						//G³ówna pêtla wyznaczaj¹ca odleg³oœæ miêdzy u - v. Wykunouje siê dopóki v != -1. Jest to najwa¿niejsza pêtla w tej funkcji, która wyznacza droge z u do v
		t[j] = v;						//Pod tablice t jest podstawiany obecny wierzcholek v
		v = Pi[v];						//Pod zmienna v podstawiana jest wartoœæ tablicy Pi o indeksie v
		j++;							//Inkrementacja zmiennej j, aby w nastêpnych obiegach pêtli odwo³ywaæ siê do nastêpnych indeksów tablicy
	}

	for(int i = j-1 ; i >= 0 ; i--){	/*Pêtla s³u¿¹ca do wyœwietlenia tablicy t od indeksu najwyzszego do 0. j-1, poniewa¿ w ostatnim obiegu pêtli while zmienne j ulegla inkrementacji, co oznacza ¿e nale¿y od niej odj¹æ wartoœæ 1*/
		cout << t[i];
		if( i != 0 ){
			cout << " -> ";
		}
	}
}

int main(void) {
    int u, v;						//Zmienna wybor - s³u¿y do wyboru BFS, a DFS;	u - element startowy grafu;	v - element docelowy grafu
    int G[m][m] = { {0,1,0,0,0} , {1,0,1,1,0} , {0,1,0,0,0} , {0,1,0,0,1} , {0,0,0,1,0} };


    cout<<"Reprezentacja macierzy sasiedztwa:\n\n";
    cout<<"| 0 1 0 0 1 0 | \n";
    cout<<"| 1 0 1 0 1 0 | \n";
    cout<<"| 0 1 0 1 0 0 | \n";
    cout<<"| 0 0 1 0 0 1 | \n";
    cout<<"| 1 1 0 0 0 1 | \n";
    cout<<"| 0 0 0 1 1 0 | \n";
    cout<<"\n";

    u = 0 ;								//wierzcho³ek startowy w grafie
	v = 4 ;								//wierzcho³ek do którego chcemy dotrzeæ

    cout<<"\tDFS: \n";
	odczytanie_sciezki_DFS(G, u, v);	//Wywo³anie funkcji, która wyznacza drogê z u do v za pomoc¹ DFS
   	
	cout<<"\n\n";
   	
	cout<<"\tBFS: \n";
	odczytanie_sciezki_BFS(G, u, v);	//Wywo³anie funkcji, która wyznacza drogê(najkrótsz¹) z u do v za pomoc¹ BFS
    
	
	return 0;
}
