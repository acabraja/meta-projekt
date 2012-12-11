#include<cstdlib>
#include<pthread.h>
#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<fstream>
#include<cmath>
#include<map>
#include<set>
using namespace std;

class Zagrada;

// KLASE

bool manji(int a, int b)
{
	if(abs(a) <= abs(b)) return true;
	else return false;
}

/*bool manja_zagrada(Zagrada A, Zagrada B)
{
	if( A.varijable.first() <= B.varijable.first() ) return true;
	else return false;
}*/

class Zagrada{
public:
	int id;
	list<int> varijable;
	int tezina;
	
	Zagrada(int a, int b, int c, int ID)
	{
		this->tezina = 1;
		this->id = ID;
		// odmah sortiramo listu
		this->varijable.push_back(a);
		this->varijable.push_back(b);
		this->varijable.push_back(c);
		this->varijable.sort(manji);
	}	
};


// LISTA FUNKCIJA
// funkcije za genetski algoritam
vector<bool> genetski( int velicina_populacije , int broj_generacija , set<int>& varijable );
set<int> pronadi_zagrade( set<int>& varijable );
void azuriraj_vjerojatnosti( set<int>& varijable );
double racunaj_dobrotu( vector<bool>& bitVektor , vector<int>& varijable , set<int>& zagrade );
bool zadovoljena(int ID,vector<bool>& bitVektor,vector<int>& varijable);  //provjerava je li zagrada zadovoljena
   // redukcija
   // mutacija
   // krizanje
   // selekcija
   // dobrota
// TODO Racunaj_egzaktno()
  //redukcija
  //egzaktni racun
//vector<int> Vrati_vektor_varijabli(list<Zagrada>::iterator i, list<Zagrada>::iterator j);

