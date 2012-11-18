//#ifndef 3-SAT.H
//#ifdef  3-SAT.H

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include "../mtrand/mtrand.h"

using namespace std;

#define VEL_POP 500     // samo privremeno inace se to cita iz testnih datoteka
#define VEL_JEDINKE 100 // samo privremeno inace ce se to citat iz formule
#define PRAZNA 1        
#define IZ_POSTOJECE 2


class Zagrada;

class Varijabla
{
  map < bool,set<Zagrada*> > zagrade;     //lista zagrada u kojima je varijabla sa negacijom i u kojima je bez negacije
	double vjerojatnostMutacije;		        //vjerojatnost prelaska iz 0 u 1	
};

class Zagrada
{
	int varijeble[3];         //indeksi varijabli  globalnom polju,a mozemo i polje pointera na varijable koje su u zagradi
	double tezina;	     
};

class Jedinka
{
	vector<bool> bitVektor;	
	double dobrota;
	public:
	Jedinka();// stvara slucajnu jedniku
	Jedinka(vector<bool> bv); // stvara jedinku bez dobrote
	Jedinka(vector<bool> bv,double fitt):bitVektor(bv),dobrota(fitt){}
};


void stvori_novu_populaciju(Jedinka& populacija,int status);


//#endif
