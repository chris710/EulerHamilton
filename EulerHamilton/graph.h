////////////////////////////////////////////
///         PLIK NAGŁÓWKOWY GRAFU
///                graph.h
////////////////////////////////////////////



///         TO-DO LIST
//  -uzupełnić funkcje klasy grafu
//  -uzupełnić funkcje szkieletu programu (zegarek, obsługa plików)
//




///BIBLIOTEKI
#include<iostream>  //do operacji wej-wyj
#include<time.h>    //do liczb pseudolosowych i mierzenia czasu
#include<cstdlib>



///KLASA GRAFU
class graf
{
    public:                                                 //oznacza, że można z tego co poniżej można korzystać poza klasą
        int n;                                              //liczba wierzchołków
        void CreateGraph(int nasycenie);                    //tworzy listę następników o podanym nasyceniu

};