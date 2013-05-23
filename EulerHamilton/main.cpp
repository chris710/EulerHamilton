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
    clock_t start;
    clock_t end;
    float czas;
    fstream plik;
    plik.open("test.txt");


    int nasycenie,n;
    //cout<<"podaj liczbe wierzcholkow i nasycenie: "<<endl;
    //cin>>n>>nasycenie;




    ///
    ///CZĘŚĆ A ZADANIA
    ///
    nasycenie=30;
    plik<<"Hamilton dla 30%"<<endl;
    cout<<"Rozpoczynam testy dla hamiltona"<<endl;
    for(int i=1; i<11;i++)
    {
        graf graphA(200*i);
        graphA.CreateGraph(nasycenie);   //metody klasy po kropce


        start=clock();
        graphA.FindHamilton(0);              //szukamy cyklu hamiltona
        end=clock();
        czas=(float)(end-start)/CLOCKS_PER_SEC;     //wyświetlanie czasu
        plik<<czas<<endl;
        graphA.Erease();

        cout<<"Ukonczono testy dla "<<200*i<<" wierzcholkow"<<endl;
    }
    plik<<endl<<endl;

    nasycenie=70;
    plik<<"Hamilton dla 70%"<<endl;
    cout<<"Rozpoczynam testy dla hamiltona"<<endl;
    for(int i=1; i<11;i++)
    {
        graf graphA(200*i);
        graphA.CreateGraph(nasycenie);   //metody klasy po kropce


        start=clock();
        graphA.FindHamilton(0);              //szukamy cyklu hamiltona
        end=clock();
        czas=(float)(end-start)/CLOCKS_PER_SEC;     //wyświetlanie czasu
        plik<<czas<<endl;
        graphA.Erease();

        cout<<"Ukonczono testy dla "<<200*i<<" wierzcholkow"<<endl;
    }
    plik<<endl<<endl;


    nasycenie=30;
    plik<<"Euler dla 30%"<<endl;
    cout<<"Rozpoczynam testy dla eulera"<<endl;
    for(int i=1; i<11;i++)
    {
        graf graphA(200*i);
        graphA.CreateGraph(nasycenie);   //metody klasy po kropce


        start=clock();
        graphA.FindEuler(0,graphA.lista);     //i eulera
        end=clock();
        czas=(float)(end-start)/CLOCKS_PER_SEC;     //wyświetlanie czasu
        plik<<czas<<endl;
        graphA.Erease();

        cout<<"Ukonczono testy dla "<<200*i<<" wierzcholkow"<<endl;
    }
    plik<<endl<<endl;


    nasycenie=70;
    plik<<"Euler dla 70%"<<endl;
    cout<<"Rozpoczynam testy dla eulera"<<endl;
    for(int i=1; i<11;i++)
    {
        graf graphA(200*i);
        graphA.CreateGraph(nasycenie);   //metody klasy po kropce


        start=clock();
        graphA.FindEuler(0,graphA.lista);     //i eulera
        end=clock();
        czas=(float)(end-start)/CLOCKS_PER_SEC;     //wyświetlanie czasu
        plik<<czas<<endl;
        graphA.Erease();

        cout<<"Ukonczono testy dla "<<200*i<<" wierzcholkow"<<endl;
    }
    plik<<endl<<endl;



    ///
    ///CZĘŚĆ B ZADANIA
    ///
    nasycenie=50;
    plik<<"Hamilton dla grafu niespójnego 50%"<<endl;
    cout<<"Rozpoczynam testy dla niespojnego hamiltona"<<endl;
    for(int i=1; i<15;i++)
    {
        graf graphB(i);
        graphB.CreateGraphB(nasycenie);   //tworzymy graf niespójny


        start=clock();
        graphB.FindHamilton(0);              //szukamy cyklu hamiltona
        end=clock();
        czas=(float)(end-start)/CLOCKS_PER_SEC;     //wyświetlanie czasu
        plik<<czas<<endl;
        graphB.Erease();

        cout<<"Ukonczono testy dla "<<i<<" wierzcholkow"<<endl;
    }
    plik<<endl<<endl;
    //graf graphB(n);
    //graphB.CreateGraphB(nasycenie);      //tworzymy wybrakowany graf
    //graphB.FindHamilton(2); //i szukamy w nim cyklu hamiltona, którego nie znajdziemy

    return 0;
}
