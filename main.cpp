#include<iostream>
#include<cstdlib>
#include<string>
#include<cstdio>
using namespace std;
const int ROZMIAR_TABLICY = 128;

class HashEntry
{
public:
    int klucz;
    int wartosc;
    HashEntry(int klucz, int wartosc)
    {
        this->klucz = klucz;
        this->wartosc = wartosc;
    }
};

/*
 * Deklaracja klasy MapaHashujaca
 */
class MapaHashujaca
{
private:
    HashEntry **tablica;
public:
    MapaHashujaca()
    {
        tablica = new HashEntry * [ROZMIAR_TABLICY];
        for (int i = 0; i< ROZMIAR_TABLICY; i++)
        {
            tablica[i] = nullptr;
        }
    }
    /*
     * Funkcja Haszująca
     */
    int HashFunc(int klucz)
    {
        return klucz % ROZMIAR_TABLICY;
    }
    /*
     * Wprowadź element pod klucz
     */
    void Wprowadz(int klucz, int wartosc)
    {
        int hash = HashFunc(klucz);
        while (tablica[hash] != nullptr && tablica[hash]->klucz != klucz)
        {
            hash = HashFunc(hash + 1);
        }
        if (tablica[hash] != nullptr)
            delete tablica[hash];
        tablica[hash] = new HashEntry(klucz, wartosc);
    }
    /*
     * Szukaj elementu pod kluczem
     */
    int Szukaj(int klucz)
    {
        int  hash = HashFunc(klucz);
        while (tablica[hash] != nullptr && tablica[hash]->klucz != klucz)
        {
            hash = HashFunc(hash + 1);
        }
        if (tablica[hash] == nullptr)
            return -1;
        else
            return tablica[hash]->wartosc;
    }

    /*
     * Usuń element spod klucza
     */
    void Usun(int klucz)
    {
        int hash = HashFunc(klucz);
        while (tablica[hash] != nullptr)
        {
            if (tablica[hash]->klucz == klucz)
                break;
            hash = HashFunc(hash + 1);
        }
        if (tablica[hash] == nullptr)
        {
            cout<<"No Element found at klucz "<<klucz<<endl;
            return;
        }
        else
        {
            delete tablica[hash];
        }
        cout<<"Element Deleted"<<endl;
    }
    ~MapaHashujaca()
    {
        for (int i = 0; i < ROZMIAR_TABLICY; i++)
        {
            if (tablica[i] != nullptr)
                delete tablica[i];
            delete[] tablica;
        }
    }
};
/*
 * Main Contains Menu
 */
int main()
{
    MapaHashujaca hash;
    int klucz, wartosc;
    int wybor;
    while (1)
    {
        cout<<"\n----------------------"<<endl;
        cout<<"Operacje na tablicy haszujacej"<<endl;
        cout<<"\n----------------------"<<endl;
        cout<<"1.Wprowadz element do tablicy"<<endl;
        cout<<"2.Sprawdz element pod kluczem"<<endl;
        cout<<"3.Usun element spod klucza"<<endl;
        cout<<"4.Wyjdz"<<endl;
        cout<<"Wybierz odpowiednia operacje: ";
        cin>>wybor;
        switch(wybor)
        {
            case 1:
                cout<<"Podaj element jaki ma byc wprowadzony: ";
                cin>>wartosc;
                cout<<"Podaj klucz pod ktory ma byc wprowadzony: ";
                cin>>klucz;
                hash.Wprowadz(klucz, wartosc);
                break;
            case 2:
                cout<<"Podaj klucz pod ktorym bedzie szukany element: ";
                cin>>klucz;
                if (hash.Szukaj(klucz) == -1)
                {
                    cout<<"Nie znaleziono zadnego elementu: "<<klucz<<endl;
                    continue;
                }
                else
                {
                    cout<<"Element pod kluczem "<<klucz<<" : ";
                    cout<< hash.Szukaj(klucz)<<endl;
                }
                break;
            case 3:
                cout<<"Podaj klucz spod ktorego będzie usuwany element: ";
                cin>>klucz;
                hash.Usun(klucz);
                break;
            case 4:
                exit(1);
            default:
                cout<<"\nSprawdz swoj wybor\n";
        }
    }
    return 0;
}