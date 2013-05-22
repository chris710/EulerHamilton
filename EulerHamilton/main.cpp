////////////////////////////////////////////////////////////////////////////////////////
///             PLIK GŁÓWNY (TUTAJ WYKORZYSTUJEMY STWORZONE FUNKCJE)
///                                     main.cpp
////////////////////////////////////////////////////////////////////////////////////////


///         TO-DO LIST:
//  -interfejs(do sprawdzenia czy algorytm działa)[DONE]
//  -części A i B zadania [DONE, MOŻNA ZAPISAĆ W INTERFEJSIE]
//  -pomiar czasów zadań
//  -obsługa plików do zapisu czasów
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
    graph.FindHamilton(0);              //szukamy cyklu hamiltona
    graph.FindEuler(0,graph.lista);     //i eulera
    graph.CreateGraphB(nasycenie);      //tworzymy wybrakowany graf

    if(!graph.hamilton.empty() )
    {
        while(!graph.hamilton.empty() )
        {
            graph.hamilton.pop();
        }
    }
    cout<<graph.hamilton.empty();
    graph.FindHamilton(rand()%graph.n); //i szukamy w nim cyklu hamiltona, którego nie znajdziemy

    return 0;
}
