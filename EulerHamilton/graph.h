////////////////////////////////////////////
///         PLIK NAGŁÓWKOWY GRAFU
///                graph.h
////////////////////////////////////////////



///         TO-DO LIST
//  -uzupełnić deklaracje funkcji klasy grafu [DONE]
//  -uzupełnić funkcje szkieletu programu (zegarek, obsługa plików) [PRZENIESIONE DO MAINA]
//  -dodać stosy i tablicę do wyszukiwania cykli[DONE]
//


using namespace std;

///BIBLIOTEKI
#include<iostream>  //do operacji wej-wyj
#include<time.h>    //do liczb pseudolosowych i mierzenia czasu
#include<fstream>
#include<cstdlib>
#include<stack>
#include<list>
//#include<vector>






///KLASA GRAFU
class graf
{
    public:                                                 //oznacza, że można z tego co poniżej można korzystać poza klasą

        int n;                                              //liczba wierzchołków

        bool *visited;                                      //deklaracja tablicy odwiedzonych
        bool test = false;                                  //czy odnaleziono cykl hamiltona?
        int zero;                                           //izolowany wierzchołek
        typedef list<int> nast;                             //definicja listy następników pojedynczego wierzchołka
        nast* lista;                                        //tablica list
        stack<int> stos;                                    //stos pomocniczy do eulera
        stack<int> euler;                                   //stos zawierający cykl eulera
        stack<int> hamilton;



        graf(int liczba)                                    //konstruktor klasy, tworzy jej instancję (obiekt) o podanych parametrach
        {
            n=liczba;                                       //przypisujemy liczbę w argumencie jako ilość wierzchołków
            visited = new bool[n];
            lista = new nast[n];
            for(int i = 0; i<n; i++)
                visited[i] = false;                     //czyścimy tablicę odwiedzonych
        }

        void CreateGraph(int nasycenie);                    //tworzy listę następników o podanym nasyceniu
        void FindEuler(int v,nast* kopia);                  //funkcja znajdująca cykl eulera
        bool FindHamilton(int wierzcholek);                 //funkcja znajdująca cykl hamiltona
        void CreateGraphB(int nasycenie);                   //tworzy graf niespójny (zadanie B)
        void Erease();
};
