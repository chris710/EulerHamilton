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
    fstream plike;
    fstream plikh;
    plikh.open("testh.txt",ios::out | ios::trunc);
    plike.open("teste.txt",ios::out | ios::trunc);
    plik.open("test.txt",ios::out | ios::trunc);


    int nasycenie,n;
    //cout<<"podaj liczbe wierzcholkow i nasycenie: "<<endl;
    //cin>>n>>nasycenie;




    ///
    ///CZĘŚĆ A ZADANIA
    ///
    nasycenie=30;
    plikh<<"Hamilton dla 30%"<<endl;
    plike<<"Euler dla 30%"<<endl;
    cout<<"Rozpoczynam testy dla hamiltona i eulera dla 30%"<<endl;
    for(int i=1; i<11;i++)
    {
        graf graphA(200*i);
        graphA.CreateGraph(nasycenie);   //metody klasy po kropce


        start=clock();
        graphA.FindHamilton(0);              //szukamy cyklu hamiltona
        end=clock();
        czas=(float)(end-start)/CLOCKS_PER_SEC;     //wyświetlanie czasu
        plikh<<czas<<endl;
        graphA.Erease();

        cout<<"Hamilton "<<200*i<<" wierzcholkow"<<endl;

        start=clock();
        graphA.FindEuler(0,graphA.lista);     //i eulera
        end=clock();
        czas=(float)(end-start)/CLOCKS_PER_SEC;     //wyświetlanie czasu
        plike<<czas<<endl;
        graphA.Erease();

        cout<<"Euler "<<200*i<<" wierzcholkow"<<endl;
    }
    plike<<endl<<endl;
    plikh<<endl<<endl;

    nasycenie=70;
    plikh<<"Hamilton dla 70%"<<endl;
    plike<<"Euler dla 70%"<<endl;
    cout<<"Rozpoczynam testy dla hamiltona i eulera dla 70%"<<endl;
    for(int i=1; i<11;i++)
    {
        graf graphA(200*i);
        graphA.CreateGraph(nasycenie);   //metody klasy po kropce


        start=clock();
        graphA.FindHamilton(0);              //szukamy cyklu hamiltona
        end=clock();
        czas=(float)(end-start)/CLOCKS_PER_SEC;     //wyświetlanie czasu
        plikh<<czas<<endl;
        graphA.Erease();

        cout<<"Hamilton "<<200*i<<" wierzcholkow"<<endl;

        start=clock();
        graphA.FindEuler(0,graphA.lista);     //i eulera
        end=clock();
        czas=(float)(end-start)/CLOCKS_PER_SEC;     //wyświetlanie czasu
        plike<<czas<<endl;
        graphA.Erease();

        cout<<"Euler "<<200*i<<" wierzcholkow"<<endl;
    }
    plike<<endl<<endl;
    plikh<<endl<<endl;


    ///
    ///CZĘŚĆ B ZADANIA
    ///
    nasycenie=50;
    plik<<"Hamilton dla grafu niespójnego 50%"<<endl;
    cout<<"Rozpoczynam testy dla niespojnego hamiltona"<<endl;
    for(int i=5; i<15;i++)
    /*{
        graf graphB(i);
        graphB.CreateGraphB(nasycenie);   //tworzymy graf niespójny

        int v=rand()%(n-1);
        while(v==graphB.zero)
            v=rand()%(n-1);

        start=clock();
        graphB.FindHamilton(0);              //szukamy cyklu hamiltona
        end=clock();
        czas=(float)(end-start)/CLOCKS_PER_SEC;     //wyświetlanie czasu
        plik<<czas<<endl;
        graphB.Erease();

        cout<<"Ukonczono testy dla "<<i<<endl;
    }*/
    plik<<endl<<endl;
    //graf graphB(n);
    //graphB.CreateGraphB(nasycenie);      //tworzymy wybrakowany graf
    //graphB.FindHamilton(2); //i szukamy w nim cyklu hamiltona, którego nie znajdziemy

    plikh.close();
    plike.close();
    plik.close();
    return 0;
}
