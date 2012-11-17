#include <iostream>
#include <map>
#include <vector>
#include <set>

using namespace std;

class Zagrada;

class Varijabla
{
  map < bool,set<Zagrada*> > zagrade;     //lista zagrada u kojima je varijabla sa negacijom i u kojima je bez negacije
	double vjerojatnostMutacije;		//vjerojatnost prelaska iz 0 u 1
	
	
};

class Zagrada
{
	int varijeble[3];                    //indeksi varijabli  globalnom polju,a mozemo i polje pointera na varijable koje su u zagradi
	double tezina;	     
};

class Jedinka
{
	vector<bool> bitVektor;	
	double dobrota;
	
};

