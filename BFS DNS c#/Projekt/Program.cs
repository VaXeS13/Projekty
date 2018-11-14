using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Projekt
{
    class Program
    {
        
        static void Main(string[] args)
        {
            const int m = 6;
            int u, v;                       //Zmienna wybor - służy do wyboru BFS, a DFS;	u - element startowy grafu;	v - element docelowy grafu
            int[,] G = new int[m, m] {
                                        {0,1,0,0,1,0} ,
                                        {1,0,1,0,1,0} ,
                                        {0,1,0,1,0,0} ,
                                        {0,0,1,0,1,1} ,
                                        {1,1,0,1,0,0} ,
                                        {0,0,0,1,0,0}
            };

            Console.WriteLine("Reprezentacja macierzy sasiedztwa:\n\n");
            Console.Write("| 0 1 0 0 1 0 | \n");
            Console.Write("| 1 0 1 0 1 0 | \n");
            Console.Write("| 0 1 0 1 0 0 | \n");
            Console.Write("| 0 0 1 0 0 1 | \n");
            Console.Write("| 1 1 0 0 0 1 | \n");
            Console.Write("| 0 0 0 1 1 0 | \n");
            Console.WriteLine("");

            u = 4 ;								//wierzchołek startowy w grafie
	        v = 5 ;								//wierzchołek do którego chcemy dotrzeć
            Console.WriteLine("DFS:");
            DFS x = new DFS(G,u,v,m);
            Console.Write("\nDFS:");
            BFS x1 = new  BFS(G, u, v, m);
        }
    }
}
