///////////////////////////////////////////////////////////////////////////////////////////
///         PLIK FUNKCYJNY(TUTAJ ZAMIESZCZAMY KODY FUNKCJI ZADEKLAROWANYCH W HEADERZE)
///                                         graph.cpp
///////////////////////////////////////////////////////////////////////////////////////////

///         TO-DO LIST
//  -funkcja tworząca graf o podanym nasyceniu spełniający warunki zadania [DONE]
//  -funkcja znajdująca cykl eulera
//  -funkcja znajdująca cykl hamiltona
//  -funkcja tworząca graf niespójny [DONE]
//  -DFS [DONE]




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

    float tmp=((n*(n-1))/2)*(float)nasycenie/100;   //obliczamy ile jedynek znajdzie się w macierzy
    int ilosc_jedynek=(int)tmp;      //(jeszcze zanim przerobimy ją na graf nieskierowany)
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
    macierz[n-1][0]=1;              //aby graf był hamiltonowski łączymy ostatni element z pierwszym
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
        if(parzystosc%2==1)             //jeżeli wierzchołek jest nieparzysty
        {
            int j = rand()%n;
            while(i==j || j==i+1 || (i==0 && j==n-1) || (i==n-1 && j==0)) j = rand()%n;
                                            //szukamy j tak długo aż spełnia wszystkie warunki miejsca

            if(macierz[i][j]==1 && parzystosc>1)        //jeżeli miejsce jest zajęte to je zerujemy
            {
                macierz[i][j]=0;
                macierz[j][i]=0;
            }
            else                                        //a jeżeli jest puste to zapełniamy
            {
                macierz[i][j]=1;
                macierz[j][i]=1;
            }
        }
    }


    ///tworzymy listę następników z macierzy
    for(int i=0;i<n;i++)
    {
        lista[i].next=new vertex;
        vertex* nnext = &lista[i];

        for(int j=0;j<n;j++)
        {
            if(macierz[i][j])
            {
                nnext->id=j;
                nnext->next=new vertex;
                nnext=nnext->next;
            }
        }
        if(nnext) nnext->next=NULL;
    }

    ///wyświetla macierz i listę na ekranie
    /*cout<<"Macierz sasiedztwa:"<<endl;
    for(int i=0;i<n;i++)       //rząd
    {
        for(int j=0;j<n;j++)   //kolumna
        {
            cout<<macierz[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
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
    cout<<endl;*/
}

/////////////////////////////////////////////////////////////
///     FUNKCJA ZNAJDUJĄCA CYKL EULERA
/////////////////////////////////////////////////////////////
void graf::FindEuler(int wierzcholek,vertex* kopia)             //operację wyszukiwania cyklu wykonujemy na kopii listy następników
{
    //STUB
}

////////////////////////////////////////////////////////////
///     FUNKCJA ZNAJDUJĄCA CYKL HAMILTONA
////////////////////////////////////////////////////////////
void graf::FindHamilton(int wierzcholek)
{
    //STUB
}

////////////////////////////////////////////////////////////
///     DFS LISTY NASTĘPNIKÓW
////////////////////////////////////////////////////////////
void graf::DFS(int wierzcholek)                                     //sortowanie topologiczne dla listy następników
{
    visited[wierzcholek]=true;                //oznaczamy wierzchołek jako odwiedzony

    vertex *temp=lista[wierzcholek].next;      //ustawiamy tymczasowy wierzchołek na pierwszego nastepnika
    while(temp->next)                     //dopóki jest jakiś sąsiad to go odwiedzamy
    {
        if(!visited[temp->id]) DFS(temp->id); //jesli nastepnik nie byl odwiedzony to odwiedzamy
        temp=temp->next; //kolejny nastepnik
    }
}

////////////////////////////////////////////////////////////
///     FUNKCJA TWORZĄCA GRAF NIESPÓJNY (ZADANIE B)
////////////////////////////////////////////////////////////
void graf::CreateGraphB(int nasycenie)
{
    srand(NULL);

    ///tworzenie macierzy sąsiedztwa o podanych właściwościach

    int **macierz=new int*[n];   //macierz sąsiedztwa
    for(int i=0;i<n;i++)        //tworzymy ją i zerujemy
    {
        macierz[i]=new int[n];  //jest to dwuwymiarowa tablica dynamiczna (dlatego tak dziwnie)
        for(int j=0;j<n;j++)    macierz[i][j]=0;
    }

    float tmp=((n*(n-1))/2)*(float)nasycenie/100;   //obliczamy ile jedynek znajdzie się w macierzy
    int ilosc_jedynek=(int)tmp;      //(jeszcze zanim przerobimy ją na graf nieskierowany)
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
    macierz[n-1][0]=1;              //aby graf był hamiltonowski łączymy ostatni element z pierwszym
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
        if(parzystosc%2==1)             //jeżeli wierzchołek jest nieparzysty
        {
            int j = rand()%n;
            while(i==j || j==i+1 || (i==0 && j==n-1) || (i==n-1 && j==0)) j = rand()%n;
                                            //szukamy j tak długo aż spełnia wszystkie warunki miejsca

            if(macierz[i][j]==1 && parzystosc>1)        //jeżeli miejsce jest zajęte to je zerujemy
            {
                macierz[i][j]=0;
                macierz[j][i]=0;
            }
            else                                        //a jeżeli jest puste to zapełniamy
            {
                macierz[i][j]=1;
                macierz[j][i]=1;
            }
        }
    }

    //PO WSZYSTKICH KROKACH NA MACIERZY ZERUJEMY LOSOWY WIERZCHOŁEK
    int i=rand()%n;
    for(int j=0;j<n;j++)
    {
        macierz[i][j]=0;
        macierz[j][i]=0;
    }


    ///tworzymy listę następników z macierzy
    //vertex* lista=new vertex[n];
    for(int i=0;i<n;i++)
    {
        lista[i].next=new vertex;
        vertex* nnext = &lista[i];

        for(int j=0;j<n;j++)
        {
            if(macierz[i][j])
            {
                nnext->id=j;
                nnext->next=new vertex;
                nnext=nnext->next;
            }
        }
        if(nnext) nnext->next=NULL;
    }
}


