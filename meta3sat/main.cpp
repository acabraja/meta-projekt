#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<fstream>
#include "3sat.h"
#include<cstdlib>

//GLOBALNE VARIJABLE
// moze i drugacije
vector<int> tezine;
map<int, list<int> > veze_var_zagrada;
vector<double> vjerojatnosti; // TODO posebna funkcija koja racuna vjerojatnosti prije svake generacije (Anamarija)
list<Zagrada> Formula;

int main()
{
	//list<Zagrada> Formula; mozda globalna mozda lokalna
        
	// citanje iz datoteke
	
	ifstream formula("formula.cnf");
	if(! formula.is_open() ) 
	{
		cout<<"Greska kod otvaranja"<<endl;
		exit(-1);
	}	
	int count = 0;
	while(forumla.good())
	{
		int a, b, c;
		formula>> a;
		formula>> b;
		formula>> c;
	        
		// izbacujemo zagrade koje su tautologije	
		if( (abs(a) == abs(b) && a != b) || (abs(a) == abs(c) && a != c) || (abs(b) == abs(c) && b != c)) continue;
		
		Formula.push_back( Zagrada( a, b, c,count) );
		tezine.push_back(1);
		if( veze_var_zagrada.find(a) == veze_var_zagrada.end() ) veze_var_zagrada[a] = list(count);
		else veze_var_zagrada.find(a)->second.push_back(count);
		
		count++;
		
	}
	Formula.sort(manja_zagrada);

	//  TODO raspodjela posla po dretvama (Anto)

	
	return 0;
}

