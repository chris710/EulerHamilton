///////////////////////////////////////////////////////////////////////////////////////////
///         PLIK FUNKCYJNY(TUTAJ ZAMIESZCZAMY KODY FUNKCJI ZADEKLAROWANYCH W HEADERZE)
///                                         graph.cpp
///////////////////////////////////////////////////////////////////////////////////////////

///         TO-DO LIST
//  -funkcja tworząca graf o podanym nasyceniu spełniający warunki zadania [DONE]
//  -funkcja znajdująca cykl eulera[DONE]
//  -funkcja znajdująca cykl hamiltona[DONE]
//  -funkcja tworząca graf niespójny [DONE]
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
    for(int k=0;k<n;k++)
    {
        for(int i=0;i<n;i++)
        {
            int parzystosc=0;       //zmienna do sprawdzania czy stopień jest parzysty

            for(int j=0;j<n;j++)            //sprawdzamy jaki jest stopień krawędzi
            {
                if (macierz[i][j]==1)   parzystosc++;
            }
            if(parzystosc%2==1)             //jeżeli wierzchołek jest nieparzysty
            {
                int j = rand()%n;
                while(i==j || j==i+1 || j==i-1 || (i==0 && j==n-1) || (i==n-1 && j==0)) j = rand()%n;
                                                //szukamy j tak długo aż spełnia wszystkie warunki miejsca

                if(macierz[i][j]==1) //&& parzystosc>1)        //jeżeli miejsce jest zajęte to je zerujemy
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
    }


    ///tworzymy listę następników z macierzy
    for(int i=0;i<n;i++)
    {
        //lista[i].next=new vertex;
        //vertex* nnext = &lista[i];
        //lista[i]=NULL;
        //lista[i].push_back(new vertex);
        for(int j=0;j<n;j++)
        {
            if(macierz[i][j])
            {
                //lista.back().
                lista[i].push_back(j);
                //neigh.back()->id=j;
                //nnext=nnext->next;
                //nnext->next=NULL;
            }
        }
        //if(nnext) nnext->next=NULL;
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
        cout<<i;
        for(list<int>::iterator it = lista[i].begin(); it!=lista[i].end(); it++)
        //vertex* nnext=lista[i].next;
            cout<<"->"<< *it; //lista[i].id;
        //while(nnext->next!=NULL)
        //{
        //    cout<<"->"<<    //nnext->id;
            //nnext=nnext->next;
        //}
        cout<<endl;
    }
    cout<<endl<<endl;
    */
}

/////////////////////////////////////////////////////////////
///     FUNKCJA ZNAJDUJĄCA CYKL EULERA
/////////////////////////////////////////////////////////////
void graf::FindEuler(int v, nast* kopia)             //operację wyszukiwania cyklu wykonujemy na kopii listy następników
{
    for(int i = 0; i<n; i++)
                visited[i] = false;

    int wierzcholek=v;
    //stos.push(wierzcholek);                     //wrzucamy na stos tymczasowy wierzchołek podany jako argument
    stos.push(v);
    list<int>::iterator tmp=kopia[wierzcholek].begin();
    //vertex* tmp=&kopia[v];//[wierzcholek];
    while(!stos.empty())                        //tak długo aż nie opróżnimy stosu
    {
        wierzcholek=stos.top();                 //ostatni ze stosu staje się przeglądanym wierzchołkiem

        //if(tmp!=lista[i].end && visited[*tmp])
          //  tmp++;
        if(!lista[wierzcholek].empty())   //jeżeli są jeszcze jakieś krawędzie
        {
            tmp=kopia[wierzcholek].begin();
            stos.push(*tmp);                               //to wrzucamy je na stos
            //tmp++;
            //visited[*tmp]=true;
            kopia[*tmp].remove(wierzcholek);            //i usuwamy
            kopia[wierzcholek].erase(tmp);              //w obie strony
            wierzcholek=*tmp;
            //visited[wierzcholek]=true;
            //tmp=kopia[wierzcholek].begin();
        }
        else                                                        //jeżeli krawędzie się skończyły
        {
            //wierzcholek=stos.top();
            euler.push(stos.top());//wierzcholek);               //stos euler tworzymy poprzez odwrócenie elementów stosu tymczasowego
            stos.pop();
        }
    }
    ///wyświetlanie stosu z cyklem eulera
    /*
    cout<<"Cykl Eulera: "<<endl;
    while(!euler.empty())
    {
        cout<<euler.top()<<" ";
        euler.pop();
    }
    cout<<endl<<endl;
    */
}

////////////////////////////////////////////////////////////
///     FUNKCJA ZNAJDUJĄCA CYKL HAMILTONA
////////////////////////////////////////////////////////////
bool graf::FindHamilton(int wierzcholek)
{
    /*
    visited[wierzcholek]=true; // odznaczamy jako odwiedzony
    hamilton.push(wierzcholek);  // wkladamy na stos
    list<int>::iterator tmp=lista[wierzcholek].begin();

    int length=hamilton.size(); // mierzymy dlugosc stosu

    //if(tmp==lista[wierzcholek].end())   cout<<"dupa";   cout<<*(lista[wierzcholek].end());
    //if(lista[wierzcholek].empty())  cout<<"dupa2";

    while(tmp != lista[wierzcholek].end() ) // przechodzimy po sasiadach
    {
        if(*tmp==wierzcholek) // jezeli obecny wierzcholek jest rowny startowemu
        {
            if(length==n-1) // to sprawdzamy czy zostaly uzyte wszystkie wierzcholki
            {
                hamilton.push(*tmp);         // jezeli tak to wkladamy go na stos
                                                // jako ostatni element zeby zrobic ladny odczyt ;D

                cout<<"Cykl Hamiltona: "<<endl;     // odczytujemy na ekran nasz cykl
                while(!hamilton.empty() )
                {
                    cout<<hamilton.top()<<endl;
                    hamilton.pop();
                }
                cout<<endl<<endl;
                return true; // zwracam  wiadomosc ze znalezlismy
            }
        }
        if(!visited[*tmp]) // jesli nie jest jeszcze odwiedzony
        {
            if(FindHamilton(*tmp) ) // i nie znelziono cyklu to wykonujemy dalej
            return false;//true;
        }
        tmp++; // przechodzimy do nastepnego wierzcholka
    }
    visited[wierzcholek]=false;
    hamilton.pop();
    return false;
    */




    hamilton.push(wierzcholek);         //wrzucamy pierwszy wierzchołek na stos
    if(hamilton.size()==n)              //jeżeli mamy w stosie wszystkie wierzchołki (rozmiar stosu jest równy ilości wierzchołków)
    {
        for(list<int>::iterator i = lista[wierzcholek].begin(); i != lista[wierzcholek].end(); i++)     //przeglądamy całą listę
            if((*i) == 0)                                   //sprawdzając czy zatoczyliśmy cykl (od zera zaczynamy cykl) CHEAT ŚMIECIU!
            {
                test=true;                                  //kończymy rekurencje
                hamilton.push(0);                           //wrzucamy na stos pierwszy wierzchołek aby wyszedł cykl ZNOWU CHEAT!
                return true;                                //operacja zakończona sukcesem!
            }
    }
    else
    {
        visited[wierzcholek] = true;                        //oznaczamy wierzchołek jako przejrzany
        for(list<int>::iterator x = lista[wierzcholek].begin(); x != lista[wierzcholek].end(); x++) //przeglądamy całą listę
        {
            if(!visited[*x] && !test)                                       //w poszukiwaniu nieprzejrzanych wierzchołków
                if(FindHamilton(*x))                                        //wywołujemy rekurencyjnie
                {                                                           //jeżeli znaleźliśmy cykl
                    /*
                    cout<<"Cykl Hamiltona: "<<endl;                         //to wypisujemy go na ekran
                    while(!hamilton.empty() )
                    {
                        cout<<hamilton.top()<<" ";
                        hamilton.pop();
                    }
                    cout<<endl<<endl;
                    */
                    return false; // zwracam  wiadomosc ze znalezlismy i że nie trzeba go więcej wypisywać
                }
        }

        visited[wierzcholek] = false;       //gdy się cofamy odznaczamy wierzchołek jako nietknięty
    }
    hamilton.pop();                         //wyrzucamy ze stosu jeżeli się cofamy
    return false;
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
    for(int i=0;i<n;i++)
    {
        //lista[i].next=new vertex;
        //vertex* nnext = &lista[i];
        //lista[i]=NULL;
        //lista[i].push_back(new vertex);
        for(int j=0;j<n;j++)
        {
            if(macierz[i][j])
            {
                //lista.back().
                lista[i].push_back(j);
                //neigh.back()->id=j;
                //nnext=nnext->next;
                //nnext->next=NULL;
            }
        }
        //if(nnext) nnext->next=NULL;
    }

    ///wyświetla macierz i listę na ekranie
    /*
    cout<<"Macierz sasiedztwa z izolowanym wierzcholkiem: "<<endl;
    for(int i=0;i<n;i++)       //rząd
    {
        for(int j=0;j<n;j++)   //kolumna
        {
            cout<<macierz[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<"Lista nastepnikow z izolowanym wierzcholkiem: "<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<i;
        for(list<int>::iterator it = lista[i].begin(); it!=lista[i].end(); it++)
        //vertex* nnext=lista[i].next;
            cout<<"->"<< *it; //lista[i].id;
        //while(nnext->next!=NULL)
        //{
        //    cout<<"->"<<    //nnext->id;
            //nnext=nnext->next;
        //}
        cout<<endl;
    }
    cout<<endl<<endl;
    */

}

////////////////////////////////////////////////////////////
///     CZYSZCZENIE KLASY
////////////////////////////////////////////////////////////
void graf::Erease()
{

    for(int i = 0; i<n; i++)
        visited[i] = false;                     //czyścimy tablicę odwiedzonych

    for(int i = 0; i<n; i++)
        delete &lista[i];                     //czyścimy tablicę odwiedzonych

    if(!hamilton.empty() )                //czyścimy stos hamiltona
    {
        while(!hamilton.empty() )
        {
            hamilton.pop();
        }
    }

    if(!euler.empty() )                //czyścimy stos eulera
    {
        while(!euler.empty() )
        {
            euler.pop();
        }
    }
    if(!stos.empty() )                //czyścimy stos eulera
    {
        while(!stos.empty() )
        {
            stos.pop();
        }
    }
    visited = new bool[n];
    lista = new nast[n];
    test=false;
}
