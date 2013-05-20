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



///KLASA GRAFU
class graf
{
    public:                                                 //oznacza, że można z tego co poniżej można korzystać poza klasą

        int n;                                              //liczba wierzchołków

        struct vertex                                       //struktura wierzchołka (do listy następników)
        {
            int id;                                         //numer wierzchołka
            vertex* next;                                   //następna pozycja na liście
        };
        bool *visited = new bool[n];                        //deklaracja tablicy odwiedzonych
        vertex* lista=new vertex[n];                        //lista następników


        graf(int liczba)                                    //konstruktor klasy, tworzy jej instancję (obiekt) o podanych parametrach
        {
            n=liczba;                                       //przypisujemy liczbę w argumencie jako ilość wierzchołków
        }



        void CreateGraph(int nasycenie);                    //tworzy listę następników o podanym nasyceniu
        void FindEuler(int wierzcholek,vertex* kopia);      //funkcja znajdująca cykl eulera
        void FindHamilton(int wierzcholek);                 //funkcja znajdująca cykl hamiltona
        void CreateGraphB(int nasycenie);                   //tworzy graf niespójny (zadanie B)
        void DFS(int wierzcholek);                         //sortowanie topologiczne dla listy następników


};
