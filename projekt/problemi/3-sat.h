//#ifndef 3-SAT.H
//#ifdef  3-SAT.H

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <math.h>
#include "../mtrand/mtrand.h"

using namespace std;

#define VEL_POP 500     // samo privremeno inace se to cita iz testnih datoteka
#define VEL_JEDINKE 100 // samo privremeno inace ce se to citat iz formule
#define PRAZNA 1        
#define IZ_POSTOJECE 2
#define BROJ_ZAGRADA 5  // samo privremeno cita se iz formule

class Zagrada;

class Varijabla
{
  public:
  map <bool,set<Zagrada*> > zagrade;     //lista zagrada u kojima je varijabla sa negacijom i u kojima je bez negacije
  double vjerojatnostMutacije;		        //vjerojatnost prelaska iz 0 u 1	
};

class Zagrada
{
    public:
    //indeksi varijabli  globalnom polju,a mozemo i polje pointera na varijable koje su u zagradi
	int varijeble[3];
	double tezina;	     
};

class Jedinka
{
	public:
	vector<bool> bitVektor;	
	double dobrota;
	Jedinka();// stvara slucajnu jedniku
	Jedinka(vector<bool> bv); // stvara jedinku bez dobrote
	Jedinka(vector<bool> bv,double fitt):bitVektor(bv),dobrota(fitt){}
};


void stvori_novu_populaciju(list<Jedinka>& populacija,int status);

double racunaj_dobrotu(vector<bool>& jedinka);

//#endif
