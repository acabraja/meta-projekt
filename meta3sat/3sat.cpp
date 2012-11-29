//funkcija koja vraca skup zagrada koje obraduje genetski algoritam
set<int> pronadi_zagrade( vector<int>& varijable )
{
  set<int> zagrade;
	set<int>::iterator j;
	for(int i = 0; i < varijable.size(); i++)
	{
		for( j = veze_var_zagrada[varijable[i]].begin(); j != veze_var_zagrada[varijable[i]].end(); j++)	zagrade.insert(*j);
		for( j = veze_var_zagrada[-varijable[i]].begin(); j != veze_var_zagrada[-varijable[i]].end(); j++)	zagrade.insert(*j);
	}
	return zagrade;
}
//azurira vjerojatnosti nakon svake generacije
void azuriraj_vjerojatnosti( vector<int>& varijable )
{
	set<int>::iterator j;
	int ukupnaTezina=0;
	int tezinaPozitivnih=0;
	for( int i = 0; i < varijable.size(); i++  )
	{
		for( j = veze_var_zagrada[varijable[i]].begin() ; j != veze_var_zagrada[varijable[i]].end() ; j++ )
		{
			tezinaPozitivnih += tezine[*j];
			ukupnaTezina += tezine[*j];
		}
		for( j = veze_var_zagrada[-varijable[i]].begin() ; j != veze_var_zagrada[-varijable[i]].end() ; j++ ) ukupnaTezina += tezine[*j];
		vjerojatnosti[varijable[i]-1] = (double)tezinaPozitivnih/ukupnaTezina; 
	}
}

//provjerava je li zagrada zadovoljena
bool zadovoljena(int ID,vector<bool>& bitVektor,vector<int>& varijable)
{
	list<Zagrada>::iterator i = Formula.begin();
	advance(i,ID);
	list<int>::iterator j;
	int k;
	int index;
	for( j = i->varijable.begin(); j != i->varijable.end(); j++)
	{
		for( k = 0; k < varijable.size(); k++)
		{
			if( varijable[k] == (*j));
			index = k;
			break;
		}
		if(bitVektor[index]== 0 && veze_var_zagrada[-(*j)] != veze_var_zagrada[-(*j)].end()) return true;
		else if(bitVektor[index]== 1 && veze_var_zagrada[(*j)] != veze_var_zagrada[(*j)].end()) return true;
	}
	return false;
}

// racuna dobrotu 
double racunaj_dobrotu( vector<bool>& bitVektor , vector<int>& varijable , set<int>& zagrade )
{
	int ukupna_tezina=0;
	int tezina_zadovoljenih=0;
	set<int>::iterator i;
	list<int>::iterator j;
	for( i = zagrade.begin(); i != zagrade.end(); i++)
	{
		ukupna_tezina += tezine[*i];
		if(zadovoljena(*i,bitVektor,varijable))	tezina_zadovoljenih += tezine[*i];   
	}
	return (double)tezina_zadovoljenih/ukupna_tezina;
}