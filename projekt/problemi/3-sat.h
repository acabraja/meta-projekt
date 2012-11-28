#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <math.h>
#include <cmath>
#include <list>
#include <time.h>
#include "../mtrand/mtrand.h"

using namespace std;

#define VEL_POP 500     // samo privremeno inace se to cita iz testnih datoteka
#define PRAZNA 1        
#define IZ_POSTOJECE 2


//#ifndef 3-SAT.H
//#ifdef  3-SAT.H
//globalne varijable
extern int BROJ_ITERACIJA, VEL_JEDINKE, BROJ_ZAGRADA;
extern int **formula;
extern double *vjerojatnosti;

//map<int,pair<vector<int>, int> > formula

class Zagrada{
	list<int> el_zagrade
	int tezina;
};

//pomoćne varijable i polja
extern int ub; 		//učitani broj
extern int **vjer_pom;//polje za računanje vjerojatnosti


//#endif

class Jedinka
{
	public:
	vector<bool> bitVektor;	
	double dobrota;
	Jedinka(){}
	Jedinka(int ident);// stvara slucajnu jedniku
	Jedinka(vector<bool> bv); // stvara jedinku bez dobrote
	Jedinka(vector<bool> bv,double fitt):bitVektor(bv),dobrota(fitt){}
};


void stvori_novu_populaciju(list<Jedinka>& populacija,int status);
double racunaj_dobrotu(vector<bool>& jedinka);
void mutacija(Jedinka& J1, double vjer_mut);
void krizanje(Jedinka& R1,Jedinka& R2,Jedinka& D1,Jedinka& D2,double vjer_kriz,bool uniformno);
bool po_dobroti(Jedinka a, Jedinka b);

