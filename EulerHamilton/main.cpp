////////////////////////////////////////////////////////////////////////////////////////
///             PLIK GŁÓWNY (TUTAJ WYKORZYSTUJEMY STWORZONE FUNKCJE)
///                                     main.cpp
////////////////////////////////////////////////////////////////////////////////////////


///         TO-DO LIST:
//  -interfejs(do sprawdzenia czy algorytm działa)
//  -części A i B zadania
//  -pomiar czasów zadań
//  -obsługa plików
//


///POTRZEBNE PLIKI
#include"graph.h"

int main()
{
    int nasycenie,n;
    cout<<"podaj liczbe wierzcholkow i nasycenie: "<<endl;
    cin>>n>>nasycenie;
    graf graph(n);



    graph.CreateGraph(nasycenie);   //metody klasy po kropce
    graph.FindEuler(0,graph.lista);
    graph.FindHamilton(0);

    return 0;
}
