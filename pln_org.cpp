#include <iostream>
#include <cmath>
#define M_PI 3.14159265358979323846

using namespace std;

enum pieniadz{
	nieznany = 0,
	banknot = 1,
	moneta = 2
};

class PLN{
	protected:
	float rodzaj;
	pieniadz nominal;
	virtual float oblicz_powierzchnie() = 0;

	PLN(pieniadz nominal, float rodzaj){
		this -> nominal = nominal;
		this -> rodzaj = rodzaj;
	}

    public:
	bool za_duza_powierzchnia(float ograniczenie){
		if(oblicz_powierzchnie() < ograniczenie){
			cout<<"Za duze pole powierzchni!";
			return true;
		}
		else{
			cout<<"Akceptowalne pole powierzchni!";
			return false;
		}
	}
};

class Moneta:public PLN{
	public:
	Moneta(pieniadz moneta, float rodzaj_tmp):PLN(nominal, rodzaj){
		this -> nominal = moneta;
		this -> rodzaj = rodzaj_tmp;
	}

	float oblicz_powierzchnie(){
        if(rodzaj == 1){
			return M_PI * pow(16.5/2,2);
		}
		else if(rodzaj == 2){
            return M_PI * pow(18.5/2,2);
		}
		else if(rodzaj == 5){
		    return M_PI * pow(20.5/2,2);
		}
		else if(rodzaj == 10){
		    return M_PI * pow(23/2,2);
		}
		else if(rodzaj == 20){
		    return M_PI * pow(21.5/2,2);
		}
		else if(rodzaj == 50){
            return M_PI * pow(24/2,2);
		}
		else{
            cout<<"Nie prawidlowy nominal";
		}
	}
};

class Banknot:public PLN{
	public:
	Banknot(pieniadz banknot, float rodzaj_tmp):PLN(nominal, rodzaj){
		this -> nominal = banknot;
		this -> rodzaj = rodzaj_tmp;
	}

	float oblicz_powierzchnie(){
        if(rodzaj == 10){
			return 120 * 60;
		}
		else if(rodzaj == 20){
			return 126 * 63;
		}
		else if(rodzaj == 50){
			return 132 * 66;
		}
		else if(rodzaj == 100){
			return 138 * 69;
		}
		else if(rodzaj == 200){
			return 144 * 72;
		}
		else{
            cout<<"Nie prawidlowy nominal";
		}
	}
};

int main(){
	int x = 1000000;

	Banknot x1 = Banknot(banknot,10);
	Banknot x2 = Banknot(banknot,20);
	Banknot x3 = Banknot(banknot,50);
	Banknot x4 = Banknot(banknot,100);
	Banknot x5 = Banknot(banknot,200);

	cout<<"Potrzeba: "<<(int)(x/x1.oblicz_powierzchnie())<<" banknotow 10zl aby uzyskac powierzchnie "<< x <<" mm^2 "<<endl;
	cout<<"Potrzeba: "<<(int)(x/x2.oblicz_powierzchnie())<<" banknotow 20zl aby uzyskac powierzchnie "<< x <<" mm^2 "<<endl;
	cout<<"Potrzeba: "<<(int)(x/x3.oblicz_powierzchnie())<<" banknotow 50zl aby uzyskac powierzchnie "<< x <<" mm^2 "<<endl;
	cout<<"Potrzeba: "<<(int)(x/x4.oblicz_powierzchnie())<<" banknotow 100zl aby uzyskac powierzchnie "<< x <<" mm^2 "<<endl;
	cout<<"Potrzeba: "<<(int)(x/x5.oblicz_powierzchnie())<<" banknotow 200zl aby uzyskac powierzchnie "<< x <<" mm^2 "<<endl;
	cout<<endl;

    Moneta s1 = Moneta(moneta,1);//10 gr
    Moneta s2 = Moneta(moneta,2);//20 gr
	Moneta s3 = Moneta(moneta,5);//50 gr
    Moneta s4 = Moneta(moneta,10);//100 gr = 1 zl
	Moneta s5 = Moneta(moneta,20);//200 gr = 2 zl
    Moneta s6 = Moneta(moneta,50);//500 gr = 5 zl

	cout<<"Potrzeba: "<<x/s1.oblicz_powierzchnie()<<" monet 10gr aby uzyskac powierzchnie "<< x <<" mm^2 "<<endl;
	cout<<"Potrzeba: "<<x/s2.oblicz_powierzchnie()<<" monet 20gr aby uzyskac powierzchnie "<< x <<" mm^2 "<<endl;
	cout<<"Potrzeba: "<<x/s3.oblicz_powierzchnie()<<" monet 50gr aby uzyskac powierzchnie "<< x <<" mm^2 "<<endl;
	cout<<"Potrzeba: "<<x/s4.oblicz_powierzchnie()<<" monet 1zl aby uzyskac powierzchnie "<< x <<" mm^2 "<<endl;
	cout<<"Potrzeba: "<<x/s5.oblicz_powierzchnie()<<" monet 2zl aby uzyskac powierzchnie "<< x <<" mm^2 "<<endl;
	cout<<"Potrzeba: "<<x/s6.oblicz_powierzchnie()<<" monet 5zl aby uzyskac powierzchnie "<< x <<" mm^2 "<<endl;

    x1.za_duza_powierzchnia(10);

	return 0;
}
