#include<iostream>
#include<cstdlib>
#include<string>
#include<vector>
#include<list>
#include<fstream>
#include<cmath>
#include<map>
#include<cstdio>
#include"mtrand/mtrand.h"
#include<time.h>
#include<set>
#include<pthread.h>
using namespace std;

/**********EXTERN********************/
class Zagrada;

extern vector<int> tezine;
extern vector<int> pomocne_tezine;
extern map<int, set<int> > veze_var_zagrada;
extern vector<double> vjerojatnosti; 
extern list<Zagrada> Formula;

/************************************/


                                      /* K L A S E */ 
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
    }	
};

class Jedinka
{
public:
	vector<bool> bitVektor;
	double dobrota;

	Jedinka(vector<int>& varijable , vector<double>& vjerojatnosti);
	Jedinka(){}

};

class Populacija
{
public:
	list<Jedinka> jedinke;
	double ukupnaDobrota;

	Populacija(){};
	Populacija(int velicinaPopulacije , vector<int>& varijable, vector<double>& vjerojatnosti); //napravi konstruktor
	void evaluirajPopulaciju(vector<int>& varijable , set<int>& zagrade); //treba napisati
};


                                        /* F U N K C I J E */

void *thread_main(int *const d); 

vector<bool> genetski( int velicina_populacije , int broj_generacija , set<int>& varijable , double vjerojatnost_mutacije , double vjerojatnost_krizanja );

set<int> pronadi_zagrade( vector<int>& varijable );

void azuriraj_vjerojatnosti( vector<int>& varijable , vector<double>& vjerojatnosti, bool prviPut);

double racunaj_dobrotu( vector<bool>& bitVektor , vector<int>& varijable , set<int>& zagrade );

bool zadovoljena(int ID,vector<bool>& bitVektor,vector<int>& varijable);  //provjerava je li zagrada zadovoljena

void mutacija(Jedinka& j,double vjerojatnostMutacije , vector<double>& vjerojatnosti);

void krizanje(Jedinka& prviRoditelj , Jedinka& drugiRoditelj , Jedinka& prvoDijete , Jedinka& drugoDijete , double vjerojatnostKrizanja,vector<double>& vjerojatnosti ,bool uniformno);

void kopiraj_elitu(Populacija &p , Populacija &q , vector<int>& varijable , set<int>& zagrade , vector<double>& vjerojatnosti);

Jedinka odaberiRoditelja(Populacija &p);

bool po_dobroti(Jedinka first,Jedinka second);














