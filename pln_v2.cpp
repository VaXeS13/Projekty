#include <iostream>

using namespace std;

//Tworzenie klasy PLN
class PLN{
    //zmienne
    protected:
    float wysokosc, szerokosc;

    //2 funkcje wirtualne
    public:

    virtual float oblicz_powierzchnie() = 0;

    //settery
    void ustaw_wysokosc(float wysokosc){
        this -> wysokosc = wysokosc;
    }
    void ustaw_szerokosc(float szerokosc){
        this -> szerokosc = szerokosc;
    }

    //gettery
    float wypisz_wysokosc(){
        return this -> wysokosc;
    }
    float wypisz_szerokosc(){
        return this -> szerokosc;
    }

    //konstruktory
    PLN();
    PLN(float wysokosc, float szerokosc){
        //ustawienie wartosci zmiennych wysokosc oraz szerokosc
        ustaw_wysokosc(wysokosc);
        ustaw_szerokosc(szerokosc);
    }

    //metoda sprawdzajaca czy powierzchnia jest za duza od ograniczenia(argument metody)
    bool za_duza_powierzchnia(float ograniczenie){
        if(oblicz_powierzchnie() > ograniczenie){
            cout << "Za duze pole powierzchni!";
            return true;
        }
        else{
            cout<<"Akceptowalne pole powierzchni!";
            return false;
        }
    }
};

// Tworzymy klase Banknot, która dziedziczy od PLN
class Banknot:public PLN{
    private:
    //zmienne
    int wys, sze;
    public:
    //konstruktory
    Banknot();
    Banknot(float wys, float sze):PLN(wysokosc, szerokosc){
        //ustawienie wartosci zmiennych wysokosc oraz szerokosc
        this -> wysokosc = wys;
        this -> szerokosc = sze;
    }

    //metoda obliczajaca powierzchnie
    float oblicz_powierzchnie(){
			return wysokosc*szerokosc;
    };
};

int main(){
    //Tworzenie nowych obiektow i wywolanie konstruktora
    Banknot b_10 = Banknot(120,60);


    //Wykorzystanie metoby oblicz_powierzchnie
    cout << 1000000/ b_10.oblicz_powierzchnie() <<  "| Banknot 10zl" << endl;

    return 0;
}
