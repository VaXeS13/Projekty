/*
Metoda Newtona oraz siecznych wyznaczania pierwiastków funkcji
Na potrzeby przedmiotu Wstęp do metod numerycznych WMiI UMK
*/

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <windows.h>
#include <ctime>

using namespace std;

int stopien = 0;

void obliczPochodna(double fun[], double pochodna[]){
	for(int i=0; i < stopien + 1; i++){
		pochodna[i] = i+1 * fun[i+1];
		if(i == stopien){
            pochodna[i] = 0;
		}
	}
}


double Oblicz_wartosc_funkcji(double fun[], double p){
	double wartosc = 0;

	for(int i=0; i< stopien+1; i++){
		wartosc += fun[i]*(pow(p,i));
	}
	return wartosc;
}

double Newton(double fun[], double df[], double p0, double delta, double epsilon, int maks){
    double pn, err, ypn;
    for(int i=0; i<maks; i++){
        pn=p0 - Oblicz_wartosc_funkcji(fun, p0)/ (Oblicz_wartosc_funkcji(df, p0));
        err = abs(pn-p0);
        p0 = pn;
        ypn = Oblicz_wartosc_funkcji(fun, pn);
        if(err < delta || abs(ypn) < epsilon){
            return pn;
        }
    }
    return pn;
}

double Secant(double f[], double p0, double p1,double delta,double epsilon,int maks){
    double pn, err, ypn;
    for(int i=0; i<maks; i++){
        pn=p1-Oblicz_wartosc_funkcji(f,p1)*(p1-p0)/(Oblicz_wartosc_funkcji(f,p1)-Oblicz_wartosc_funkcji(f,p0));
        err=abs(pn-p1);
        p0=p1;
        p1=pn;
        ypn=Oblicz_wartosc_funkcji(f,pn);
        if (err<delta || abs(ypn)<epsilon){
            return pn;
        }
    }
    return pn;
}

int main(){
    double f_tmp, p0, delta, epsilon, maks;
    cout << "\n\n###############################" << endl;
    cout << "\n";
    cout << "Obslugiwane sa: \t" << endl;
    cout << "sqrt(x) \t\t" << endl;
    cout << "loga(b) \t\t" << endl;
    cout << "\ta - podstawa \t" << endl;
    cout << "\tb - costam \t" << endl;
    cout << "a^x \t\t\t" << endl;
    cout << "\n";
    cout << "###############################" << endl;

    cout << "\nPodaj stopien funkcji: ";
    cin >> stopien;

    string funkcja[stopien + 1];

    cout<<"Podaj funkcje: \n\n" ;
    for(int i=stopien; i >= 0; i--){
        cout << i << " stopien: ";
        cin >> funkcja[i];
    }
    cout<<endl;
    for(int i=stopien; i >= 0; i--){
        if(funkcja[i][0] != '0'){
        if(funkcja[i][0] == '-'){
            cout << " " << funkcja[i] << "x^" << i;
        }
        else{
            cout << " + " << funkcja[i] << "x^" << i;
        }

            }
    }

    cout<<endl<<endl;
    double funkcjaZWartosciami[stopien+1];
    double pochodna[stopien+1];
    for(int i=stopien; i >= 0; i--){
        if(funkcja[i][0] == 's' && funkcja[i][1] == 'q' && funkcja[i][2] == 'r' && funkcja[i][3] == 't'){
            string tmp = "";
            for(int j=5; j < funkcja[i].length()-1; j++){
                tmp += funkcja[i][j];
            }
            if(strtof((tmp).c_str(), 0) < 0){
                cout<< " Warto�� pod pierwiastkiem nie moze byc ujemna! ";
            }
            funkcjaZWartosciami[i] = sqrt(strtof((tmp).c_str(), 0));
        }
        else if(funkcja[i][0] == 'l' && funkcja[i][1] == 'o' && funkcja[i][2] == 'g'){
            string podstawa = "";
            string costam = "";
            int z = 3;
            while(funkcja[i][z] != '('){
                podstawa += funkcja[i][z];
                z++;
            }
            z++;
            while(funkcja[i][z] != ')'){
                costam += funkcja[i][z];
                z++;
            }
            double podstawaDouble = strtof((podstawa).c_str(), 0);
            double costamDouble = strtof((costam).c_str(), 0);
            double wynik =  log(podstawaDouble) / log(costamDouble) ;

            funkcjaZWartosciami[i] = wynik;

        }
        else{
            funkcjaZWartosciami[i] = strtof((funkcja[i]).c_str(), 0);
        }
    }

	obliczPochodna(funkcjaZWartosciami, pochodna);

	double wynik = Newton(funkcjaZWartosciami, pochodna, 8, 0.0001, 0.0001, 3);
	cout << "Newton: " << wynik << endl;
	wynik = Secant(funkcjaZWartosciami, 2, 8, 0.0001, 0.0001, 4);
	cout << "Secant: " << wynik << endl;

	system("pause");
    return 0;
}
