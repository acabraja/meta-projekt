#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<vector>
#include "problemi/3-sat.h"
#include <iomanip>
using namespace std;

int BROJ_ITERACIJA, VEL_JEDINKE, BROJ_ZAGRADA;
int **formula;
double *vjerojatnosti;

//pomoćne varijable i polja
int ub; 		//učitani broj
int **vjer_pom;//polje za računanje vjerojatnosti


void sortiraj_formulu()
{	
	// sortiraj retke od najmanjeg prema većemu (a i -a je svejedno)
	for (int i = 0; i < BROJ_ZAGRADA; i++)
	{
		int pom;
		if(abs(formula[i][0]) > abs(formula[i][1])) 
		{
			pom = formula[i][0];
			formula[i][0] = formula[i][1];
			formula[i][1] = pom;
		}	
		if(abs(formula[i][1]) > abs(formula[i][2])) 
		{
			pom = formula[i][1];
			formula[i][1] = formula[i][2];
			formula[i][2] = pom;
		}	
		if(abs(formula[i][0]) > abs(formula[i][1])) 
		{
			pom = formula[i][0];
			formula[i][0] = formula[i][1];
			formula[i][1] = pom;
		}	
	}
	for(int i=0; i< BROJ_ZAGRADA; i++)
	{
		for(int j=i;j<BROJ_ZAGRADA; j++)
		{
			if(abs(formula[i][0]) > abs(formula[i][1])) 
			{	
				int *pom = formula[i];
				formula[i] = formula[j];
				formula[j] = pom;
			}
		}
	}
}




int main(){

//lista jedinki
list<Jedinka> populacija;

//otvaranje datoteke
	ifstream f("formula2.cnf");
	if(!f.is_open()) 
	{
		cout << "Read error!" << endl; 
		return 0;
	}

//učitavanje prvog reda formule
	f >> BROJ_ITERACIJA;
	f >> VEL_JEDINKE;
	f >> BROJ_ZAGRADA;

//inicijalizacija polja
	formula  = new int*[BROJ_ZAGRADA];
	for(int i = 0; i < BROJ_ZAGRADA; i++){
  		formula[i]  = new int[3];
		}

	vjerojatnosti = new double[VEL_JEDINKE];
	
	vjer_pom = new int*[VEL_JEDINKE];
	for(int i = 0; i < VEL_JEDINKE; i++){
		vjer_pom[i] = new int[2];
			vjer_pom[i][0] = vjer_pom[i][1] = 0;
		}

//učitavanje cijele formula i vjer_pom
	for (int i=0; i<BROJ_ZAGRADA; i++)
		for (int j=0; j<3; j++)
		{
		if(!f.good()) cout << "KRAJ PRIJE KRAJA!" << endl; 

			f >> ub;
			formula[i][j] = ub;
			if (ub>0) vjer_pom[ub-1][1]++;  
			if (ub<0) vjer_pom[-ub-1][0]++; 
			if (ub==0) cout << "varijabla 0!" << endl;
		}
		sortiraj_formulu(); // sortiranje formule u svrhu analize (mogucnost paralelizacije)
	//računanje vjerojatnosti
	for (int i=0; i<VEL_JEDINKE; i++)
		vjerojatnosti[i]=(double)vjer_pom[i][1]/(vjer_pom[i][0]+vjer_pom[i][1]);

//ispisi...
/*
for (int i=0; i<BROJ_ZAGRADA; i++)
	cout << formula[i][0] << " " << formula[i][1] << " "<< formula[i][2] << endl;

for (int i=0; i<VEL_JEDINKE; i++)
	cout << i << ": " << vjer_pom[i][0] << " " << vjer_pom[i][1] << endl;

for (int i=0; i<VEL_JEDINKE; i++)
	cout << vjerojatnosti[i] << endl;

int a;
cin >> a;
*/
f.close();


//algoritam

stvori_novu_populaciju(populacija, PRAZNA);

//if (populacija.front().dobrota == 1)
	//cout << populacija.front().dobrota << endl;

//for(list<Jedinka>::iterator i=populacija.begin();i!=populacija.end();i++)
//	cout << (*i).dobrota << endl;
int i;
for ( i=0; i<BROJ_ITERACIJA; i++)
	{
	stvori_novu_populaciju(populacija, IZ_POSTOJECE);
	
	cout<<setprecision(16) << populacija.front().dobrota << endl;
	if (populacija.front().dobrota == 1)
		cout << "NADJENDA!" << endl;
	}

return 0;
}

