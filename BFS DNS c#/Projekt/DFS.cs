using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;
namespace Projekt
{
    class DFS
    {
        private int[] Pi;                          
        private int j, pocz, koni, m;
        private int[,] G;
        Stack myStack = new Stack();
        private char[] kolor;
        private int[] t;
        private int[] f;
        private int time;
        public DFS(int[,] G, int u, int v, int m)
        {
            this.G = new int[m,m];
            this.G = G;
            this.m = m;
            pocz = u;
            koni = v;
            this.j = 0;
            Pi = new int[m];
            t = new int[m];
            f = new int[m];
            time = 0;
            kolor = new char[m];
            for (int i = 0; i < m; i++)
            {
                Pi[i] = -1;
            }
            DFS_licz1(G, pocz);
            Wypisz();

            Console.Write("Droga z {0} do {1} : ",pocz, koni);
            while (koni != -1)
            {                       //Główna pętla wyznaczająca odległość między u - v. Wykunouje się dopóki v != -1. Jest to najważniejsza pętla w tej funkcji, która wyznacza droge z u do v
                t[j] = koni;                       //Pod tablice t jest podstawiany obecny wierzcholek v
                koni = Pi[koni];                      //Pod zmienna v podstawiana jest wartość tablicy Pi o indeksie v
                j++;                            //Inkrementacja zmiennej j, aby w następnych obiegach pętli odwoływać się do następnych indeksów tablicy
            }

            for (int i = j - 1; i >= 0; i--)
            {   /*Pętla służąca do wyświetlenia tablicy t od indeksu najwyzszego do 0. j-1, ponieważ w ostatnim obiegu pętli while zmienne j ulegla inkrementacji, co oznacza że */
                Console.Write("{0}",t[i]);               //należy od niej odjąć wartość 1
                if (i != 0)
                {
                    Console.Write(" -> ");
                }
            }
        }
        void DFS_licz1(int [,] G, int pocz)
        {
            for (int i = 0; i < m; i++)
            {      
                kolor[i] = 'B';
                t[i] = -20;
                f[i] = -20;
            }
            myStack.Push(pocz);
            
            DFS_licz2(pocz);
            //tablice_dfs(kolor, t, Pi, f);       
        }

        void DFS_licz2(int pocz)
        {
            int licz = 0;
            
            int sasiad = -20;
            int glowa;
            kolor[pocz] = 'S';
            time++;
            t[pocz] = time;
            for (int i = 0; i < m; i++)
            {
                if (G[pocz, i] == 1)
                {
                    sasiad = i;
                    myStack.Push(sasiad);
                    licz = 1;
                }

                if (licz == 1)
                {
                    glowa = Convert.ToInt32(myStack.Peek());

                    if (kolor[glowa] == 'B')
                    {
                        Pi[glowa] = pocz;
                        DFS_licz2(glowa);
                    }
                }
            }

            kolor[pocz] = 'C';
            time++;                             
            f[pocz] = time;                        
            myStack.Pop();
        }

        public void Wypisz()
        {
                //Funkcja wyświetlająca zawartość tablic kolor, t, Pi, f

                Console.Write("kolor =\t[");
                for (int i = 0; i < m; i++)
                {                                       //Pętla wyświetlająca na ekran zawartość tablicy kolor
                Console.Write(kolor[i]);
                    if (i != m - 1)
                    {                                                   //Jeżeli i będzie równe przedostatniemu indeksowi, to wtedy nie dopisuje ","
                    Console.Write(",");
                    }

                }
                 Console.Write("]\n");

                 Console.Write("t =\t[");
                for (int i = 0; i < m; i++)
                {                                       //Pętla wyświetlająca na ekran zawartość tablicy t
                    Console.Write("{0}",t[i]);
                    if (i != m - 1)
                    {                                                   //Jeżeli i będzie równe przedostatniemu indeksowi, to wtedy nie dopisuje ","
                        Console.Write(",");
                    }
                }
                Console.Write("]\n");

                Console.Write("Pi =\t[");
                for (int i = 0; i < m; i++)
                {                                       //Pętla wyświetlająca na ekran zawartość tablicy Pi
                    Console.Write("{0}",Pi[i]);
                    if (i != m - 1)
                    {                                                   //Jeżeli i będzie równe przedostatniemu indeksowi, to wtedy nie dopisuje ","
                        Console.Write(",");
                    }
                }
                Console.Write("]\n");

                Console.Write("f =\t[");
                for (int i = 0; i < m; i++)
                {                                       //Pętla wyświetlająca na ekran zawartość tablicy f
                    Console.Write("{0}",f[i]);
                    if (i != m - 1)
                    {                                                   //Jeżeli i będzie równe przedostatniemu indeksowi, to wtedy nie dopisuje ","
                        Console.Write(",");
                    }
                }
            Console.Write("]\n\n");
            
        }
    }
}
