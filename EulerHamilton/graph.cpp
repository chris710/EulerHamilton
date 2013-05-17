///////////////////////////////////////////////////////////////////////////////////////////
///         PLIK FUNKCYJNY(TUTAJ ZAMIESZCZAMY KODY FUNKCJI ZADEKLAROWANYCH W HEADERZE)
///                                         graph.cpp
///////////////////////////////////////////////////////////////////////////////////////////

///         TO-DO LIST
//  -funkcja tworząca graf o podanym nasyceniu spełniający warunki zadania
//
//




///POTRZEBNE PLIKI
#include"graph.h"

/////////////////////////////////////////////////////////////
///      TWORZY LISTĘ NASTĘPNIKÓW O PODANEJ GĘSTOŚCI
/////////////////////////////////////////////////////////////
void graf::CreateGraph(int nasycenie)                   //tworzenie metody klasy graph
{
    srand(NULL);

    ///tworzenie macierzy sąsiedztwa o podanych właściwościach

    int **macierz=new int*[n];   //macierz sąsiedztwa
    for(int i=0;i<n;i++)        //tworzymy ją i zerujemy
    {
        macierz[i]=new int[n];  //jest to dwuwymiarowa tablica dynamiczna (dlatego tak dziwnie)
        for(int j=0;j<n;j++)    macierz[i][j]=0;
    }

    float tmp=((n*(n-1))/2)*(float)nasycenie/100;//(nasycenie/100);            //obliczamy ile jedynek znajdzie się w macierzy
    int ilosc_jedynek=/*(n*(n-1)/2)*/(int)tmp/*(nasycenie/100)*/;      //(jeszcze zanim przerobimy ją na graf nieskierowany)


    //TWORZYMY GRAF SPÓJNY
    for(int i=0;i<n-1;i++)
    {

        macierz[i][i+rand()%(n-i-1)+1]=1;     //losowy element z wiersza staje się jedynką
        ilosc_jedynek--;                     //zmniejszamy ilość pozostałych jedynek
    }


    //TWORZYMY MACIERZ GÓRNOTRÓJKĄTNĄ O PODANYM NASYCENIU
    for(;ilosc_jedynek>=0;)
    {
        int i=rand()%(n-1);     //losujemy wiersz macierzy
        if(!macierz[i][i+rand()%(n-i-1)+1])     //jeżeli wylosowane pole jest puste
        {
            macierz[i][i+rand()%(n-i-1)+1]=1;
            ilosc_jedynek--;
        }
    }

    //ZMIENIAMY GRAF NA NIESKIEROWANY
    for(int i=0;i<n;i++)
    {
        for(int j=1;j<n;j++)
        {
            if(i<j && macierz[i][j])    macierz[j][i]=1;
        }
    }

    ///tworzymy listę następników z macierzy
    vertex* lista=new vertex[n];

    for(int i=0;i<n;i++)
    {
        lista[i].next=new vertex;
        vertex* nnext = &lista[i];

        for(int j=0;j<n;j++)
        {
            /*if(macierz[i][j] && lista[i].next==NULL)
            {
                lista[i].id=j;
            }
            else*/ if(macierz[i][j])
            {
                nnext->id=j;
                nnext->next=new vertex;
                nnext=nnext->next;
            }
        }
        if(nnext) nnext->next=NULL;
    }


    ///wyświetla macierz na ekranie
    cout<<"Macierz sasiedztwa:"<<endl;
    for(int i=0;i<n;i++)       //rząd
    {
        for(int j=0;j<n;j++)   //kolumna
        {
            cout<<macierz[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

    ///wyświetla listę na ekranie
    cout<<"Lista następników:"<<endl;
    for(int i=0;i<n;i++)
    {
        vertex* nnext=lista[i].next;
        cout<<i<<"->"<<lista[i].id;
        while(nnext->next!=NULL)
        {
            cout<<"->"<<nnext->id;
            nnext=nnext->next;
        }
        cout<<endl;
    }
    cout<<endl;

}
