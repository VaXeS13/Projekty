using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;

namespace Projekt
{
    class BFS
    {
        private int[] Pi;
        private int j, pocz, koni, m;
        private int[,] G;
        private int[] t;
        private char[] kolor;
        private int[] d;
        public BFS(int[,] G, int u, int v, int m)
        {
            this.G = new int[m, m];
            this.G = G;
            this.m = m;
            pocz = u;
            koni = v;
            this.t = new int[m];
            this.Pi = new int[m];
            this.d = new int[m];
            this.kolor = new char[m];
            for (int i = 0; i < m; i++)
            {
                Pi[i] = -1;
            }
            BFS_Licz1(G, pocz);
            Wypisz();
            
            Console.Write("Droga z {0} do {1} : ", pocz, koni);
            while (koni != -1)
            {                       //Główna pętla wyznaczająca odległość między u - v. Wykunouje się dopóki v != -1. Jest to najważniejsza pętla w tej funkcji, która wyznacza droge z u do v
                t[j] = koni;                       //Pod tablice t jest podstawiany obecny wierzcholek v
                koni = Pi[koni];                      //Pod zmienna v podstawiana jest wartość tablicy Pi o indeksie v
                j++;                            //Inkrementacja zmiennej j, aby w następnych obiegach pętli odwoływać się do następnych indeksów tablicy
            }

            for (int i = j - 1; i >= 0; i--)
            {   
                Console.Write("{0}", t[i]);               //należy od niej odjąć wartość 1
                if (i != 0)
                {
                    Console.Write(" -> ");
                }
            }
            Console.WriteLine("");
        }

        void BFS_Licz1(int[,] G, int pocz)
        {
            int licz = 0, sasiad, u, v;
            Queue myQ = new Queue();

            for (int i = 0; i < m; i++)
            {       //Pętla wypełnia tablice kolor, d widocznymi poniżej wartościami
                kolor[i] = 'B';
                d[i] = -20;
            }
            kolor[pocz] = 'S';                     //Do tablicy kolor o indeksie s (wierzchołek startowy) jest nadpisywana wartość 'B'
            d[pocz] = 0;                           //Do tablicy d o indeksie s (wierzchołek startowy) jest nadpisywana wartość '0'
            Pi[pocz] = -1;                         //Do tablicy kolor o indeksie s (wierzchołek startowy) jest nadpisywana wartość -1
            myQ.Enqueue(pocz);                    //Dodanie do kolejki zmiennej s, czyli 
            while (myQ.Count != 0)
            {       //Wykonywanie się pętli dopóki kolejka nie jest pusta

                u = Convert.ToInt32(myQ.Peek());            //Do zmiennej u zapisywany jest pierwszy element kolejki (głowa kolejki)
                licz = 0;
                sasiad = 0;
                for (int i = 0; i < m; i++)
                {
                    //pętla sprawdzająca sąsiadów wierzchołka u, 
                    /*Jeżeli w macierzy o indeksach G[u][i], gdzie i jest inkrementowane co obieg pętli, a u jest wierzchołkiem startowym występuje "1" oznacza to, że*/
                    if (G[u, i] == 1)
                    {           //Jeżeli występuje sąsiedztwo pomiedzy wierzchołkiem u i. Wtedy do koleji dodaje wierzchłlek sąsiedni u, czyli i
                        sasiad = i;
                        myQ.Enqueue(sasiad);    //Dodanie do kolejki wierzchołka sąsiad (i)
                        licz = 1;
                    }

                    if (sasiad != -20)
                    {           //Jeżeli zaistniało sąsiedztwo miedzy G[u][i], to pod te indeksy podstawiana jest wartość 0, aby w przyszłości uniknąć zapętlenia się
                        G[u, sasiad] = 0;
                        G[sasiad, u] = 0;
                    }

                    if (kolor[sasiad] == 'B')
                    {
                    Console.Write("{0} ", sasiad);
                    for (int it = 0; it < licz; it++)
                        {   //Pętla się wykonuje, jeżeli licz=1 
                            kolor[sasiad] = 'S';            //Kolor o indeksie sasiad jest szary, czyli odwiedzony
                            d[sasiad] = d[u] + 1;           //Do tablicy d o indeksie sasiad jest przypisana wartość tablicy d o indeksie u i do tej wartości dodana 1
                            Pi[sasiad] = u;                 //Do tablicy Pi po indeksie sasiad przypisujemt wartość zmiennej u (głowa kolejki)
                            myQ.Enqueue(sasiad);           //Do kolejki dodajemy zmienna sasiad
                        }
                    }
                }
                kolor[u] = 'C';                             //Po obiegu pęli sprawdzającej sąsiadów wierzchołka u, ustawiamy wartość tablicy kolor o indeksie u na czarmy, czyli odwiedzony bez sąsiadów do sprawdzenia
                myQ.Dequeue();                               //Zdjęcie z kolejki elementu pierwszego

            }

        }
        public void Wypisz()
        {
            //Funkcja wyświetlająca zawartość tablic kolor, t, Pi, f

            Console.Write("\n\nkolor =\t[");
            for (int i = 0; i < m; i++)
            {                                       //Pętla wyświetlająca na ekran zawartość tablicy kolor
                Console.Write(kolor[i]);
                if (i != m - 1)
                {                                                   //Jeżeli i będzie równe przedostatniemu indeksowi, to wtedy nie dopisuje ","
                    Console.Write(",");
                }

            }
            Console.Write("]\n");


            Console.Write("Pi =\t[");
            for (int i = 0; i < m; i++)
            {                                       //Pętla wyświetlająca na ekran zawartość tablicy Pi
                Console.Write("{0}", Pi[i]);
                if (i != m - 1)
                {                                                   //Jeżeli i będzie równe przedostatniemu indeksowi, to wtedy nie dopisuje ","
                    Console.Write(",");
                }
            }
            Console.Write("]\n");

            Console.Write("d =\t[");
            for (int i = 0; i < m; i++)
            {                                       //Pętla wyświetlająca na ekran zawartość tablicy f
                Console.Write("{0}", d[i]);
                if (i != m - 1)
                {                                                   //Jeżeli i będzie równe przedostatniemu indeksowi, to wtedy nie dopisuje ","
                    Console.Write(",");
                }
            }
            Console.Write("]\n\n");

        }
    }
}
    /*
    BFS(G, u, Pi);                     
    cout << "Droga z " << u << " do " << v << ": ";	
	while(v != -1){
        t[j] = v;
        v = Pi[v];						
		j++;							
	}

	for(int i = j - 1; i >= 0 ; i--){
		cout << t[i];
		if( i != 0 ){
			cout << " -> ";
		}
	}
    }
}*/
