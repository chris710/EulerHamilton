////////////////////////////////////////////
///         PLIK NAGŁÓWKOWY GRAFU
///                graph.h
////////////////////////////////////////////



///         TO-DO LIST
//  -uzupełnić deklaracje funkcji klasy grafu [DONE]
//  -uzupełnić funkcje szkieletu programu (zegarek, obsługa plików) [PRZENIESIONE DO MAINA]
//  -dodać stosy i tablicę do wyszukiwania cykli
//


using namespace std;

///BIBLIOTEKI
#include<iostream>  //do operacji wej-wyj
#include<time.h>    //do liczb pseudolosowych i mierzenia czasu
#include<cstdlib>
#include<stack>
#include<list>
//#include<vector>






///KLASA GRAFU
class graf
{
    public:                                                 //oznacza, że można z tego co poniżej można korzystać poza klasą

        int n;                                              //liczba wierzchołków

        //struct vertex                                       //struktura wierzchołka (do listy następników)
        //{
        //    int id;                                         //numer wierzchołka
        //   vertex* next;                                   //następna pozycja na liście
        //};
        bool *visited;                                      //deklaracja tablicy odwiedzonych
        //vector<list<vertex*> > lista;

        //list<vertex*> neigh;                                //lista następników
        //typedef list<vertex*> nast;
        typedef list<int> nast;
        nast* lista;
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

};
