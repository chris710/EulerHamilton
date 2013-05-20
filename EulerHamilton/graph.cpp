///////////////////////////////////////////////////////////////////////////////////////////
///         PLIK FUNKCYJNY(TUTAJ ZAMIESZCZAMY KODY FUNKCJI ZADEKLAROWANYCH W HEADERZE)
///                                         graph.cpp
///////////////////////////////////////////////////////////////////////////////////////////

///         TO-DO LIST
//  -funkcja tworząca graf o podanym nasyceniu spełniający warunki zadania [DONE]
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
    int* stopien=new int[n];        //do sprawdzania parzystości wierzchołka
    for(int i=0;i<n;i++)    stopien[i]=0; //zerujemy tablicę stopni

    //TWORZYMY GRAF SPÓJNY I HAMILTONOWSKI
    for(int i=0;i<n-1;i++)
    {
        macierz[i][i+1]=1;     //losowy element z wiersza staje się jedynką
        ilosc_jedynek--;                     //zmniejszamy ilość pozostałych jedynek
        stopien[i]++;
        stopien[i+1]++;
    }
    macierz[n-1][0]=1;
    stopien[n-1]=1;
    stopien[0]++;
    ilosc_jedynek--;

    //TWORZYMY MACIERZ GÓRNOTRÓJKĄTNĄ O PODANYM NASYCENIU
    for(;ilosc_jedynek>0;)
    {
        int i=rand()%(n-1);     //losujemy wiersz macierzy
        int j=i+rand()%(n-i-1)+1;
        if(!macierz[i][j])//i+rand()%(n-i-1)+1])     //jeżeli wylosowane pole jest puste
        {
            macierz[i][j]=1;//i+rand()%(n-i-1)+1]=1;
            ilosc_jedynek--;
        }

    }



    /*int i=n-2;
    for(;ilosc_jedynek>0;)
    {
        //int i=n-1; //rand()%(n-2);     //losujemy wiersz macierzy

        int parzystosc=0;       //zmienna do sprawdzania czy stopień jest parzysty

        for(int j=i;j<n;j++)            //sprawdzamy jaki jest stopień krawędzi
        {
            if (macierz[i][j]==1)   parzystosc++;
        }

        //int j=(i+rand()%(n-i)+1);
        int j;//=i+1;
        //while(macierz[i][j] && j<=n)            //póki trafiamy na 1
        do
        {
            j=(i+rand()%(n-i-1)+1);
        }
        while(macierz[i][j] && parzystosc<(n-i+1));

        if(!macierz[i][j] && stopien[i]%2==1)//(parzystosc%2)==1)     //jeżeli wylosowane pole jest puste a stopień nieparzysty
        {
            macierz[i][j]=1;
            stopien[i]++;
            stopien[j]++;
            ilosc_jedynek--;
            parzystosc++;
            break;
        }
        else if(!macierz[i][j] && stopien[i]<(n-2) && parzystosc<(n-i) )    //jeżeli stopień jest parzysty to dodajemy od razu 2
        {
            macierz[i][j]=1;
            stopien[i]++;
            stopien[j]++;
            ilosc_jedynek--;
            parzystosc++;

            do
            {
                j=(i+rand()%(n-i-1)+1);
            }
            while(macierz[i][j] && parzystosc<(n-i+1));

            if(!macierz[i][j])              //sprawdzamy czy są pełne
            {
                macierz[i][j]=1;
                stopien[i]++;
                stopien[j]++;
                ilosc_jedynek--;
                break;
            }
            break;
        }

        //j++;//=(i+rand()%(n-i)+1);     //losujemy nowe pola
        if(i>0)
            i--;
        else    i=n-2;
    }*/

    //ZMIENIAMY GRAF NA NIESKIEROWANY
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if( macierz[i][j])    macierz[j][i]=1;
        }
    }


    //I Z PARZYSTYMI STOPNIAMI WSZYSTKICH WIERZCHOŁKÓW
    for(int i=0;i<n-1;i++)
    {
        int parzystosc=0;       //zmienna do sprawdzania czy stopień jest parzysty

        for(int j=0;j<n;j++)            //sprawdzamy jaki jest stopień krawędzi
        {
            if (macierz[i][j]==1)   parzystosc++;
        }
        if(parzystosc%2==1)
        {
            int j = rand()%n;
            while(i==j || j==i+1 || (i==0 && j==n-1) || (i==n-1 && j==0)) j = rand()%n;
            if(macierz[i][j]==1 && parzystosc>1)
            {
                macierz[i][j]=0;
                macierz[j][i]=0;
            }
            else
            {
                macierz[i][j]=1;
                macierz[j][i]=1;
            }
        }
//        if(stopien[i]%2==1 )//&& parzystosc>1)//parzystosc%2==1 && parzystosc>1)
//        {
//            int j=(i+rand()%(n-i-1)+1);
//            if(macierz[i][j] && (j!=i+1) && parzystosc!=1)
//            {
//                macierz[i][j]=0;
//                parzystosc--;
//                stopien[i]--;
//            }
//            else// if(!(parzystosc>1))
//            {
//                macierz[i][j]=1;
//                macierz[j][i]=1;
//                stopien[i]++;
//                stopien[j]++;
//            }
//        }
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
    cout<<"Lista nastepnikow:"<<endl;
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
