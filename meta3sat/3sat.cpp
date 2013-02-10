#include"3sat.h"


              /* MTRADN za generiranje slucajnih brojeva
                Koristi time() kao pomocni pseudo slucaj */
unsigned long init[4] = {0x123, 0x234, 0x345, 0x456}, length = 4;
MTRand_int32 irand(init, length); // irand() slucajni int
MTRand drand(time(0));            // drand() slucajni  double iz (0,1)


                    /* prima index vektora nezavisni_skupovi i obraduje dani skup*/

void *thread_main(int *const d)
{
  //svaka dretva zna index d gdje se u vektoru nezavisni_skupovi nalazi skup koji ona treba obraditi
  // genetski
  // egzaktno
}

                       /* Sortiranje populacije*/
   /* populacija list<Jedinka> pop i poziv sa pop.sort(po_dobroti) sortira silazno*/

bool po_dobroti(Jedinka first,Jedinka second)
{
  if(first.dobrota > second.dobrota) return true;
  return false;
}

               /* vraca skup zagrada koje obraduje genetski algoritam*/

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



//vraca je li zagrada zadovoljena
bool zadovoljena(int ID,vector<bool>& bitVektor,vector<int>& varijable)
{
  //cout<<bitVektor.size()<<endl;
	list<Zagrada>::iterator i;
	for(i = Formula.begin(); i != Formula.end();i++) if(i->id == ID) break;
	list<int>::iterator j;
	int k;
	int var;
	for( j = i->varijable.begin(); j != i->varijable.end(); j++)
	{
	  int index = -1;
		if((*j) < 0 ) var = -(*j);
		else var = (*j);
		//cout<<var<<"varijabla"<<endl;
		for( k = 0; k < varijable.size(); k++)
		{
			if( varijable[k] == var)
			{
			index = k;
			break;
			}
			//if(ID == 1020)cout<<"prije "<<var<<" "<<index<<endl;
		}
		if(index != -1 && bitVektor[index] == 0 && (*j) < 0)
		{
		//cout<<"prosao "<<ID<<endl;
		return true;
		}
		if(index != -1 && bitVektor[index]== 1 && (*j) > 0)
		{
		  //cout<<"prosao "<<ID<<endl;
		  return true;
		}
	}
	//cout<<"prosao "<<ID<<endl;
	return false;
}

// racuna dobrotu
double racunaj_dobrotu( vector<bool>& bitVektor , vector<int>& varijable , set<int>& zagrade )
{
    int tezina_zadovoljenih = 0;
    set<int>::iterator i;
	  list<int>::iterator j;
	  int ukupna_tezina = zagrade.size();
	for( i = zagrade.begin(); i != zagrade.end(); i++ )
	{
		if(zadovoljena(*i,bitVektor,varijable))	tezina_zadovoljenih++;
	}
	return (double)tezina_zadovoljenih/(double)ukupna_tezina;
}

Jedinka::Jedinka(vector<int>& varijable)
{
	for(int i=0; i < varijable.size(); i++)
	{
			if(veze_var_zagrada[varijable[i]].size() == 0) bitVektor[i].push_back(false);
			else if(veze_var_zagrada[-varijable[i]].size()== 0) bitVektor[i].push_back(true);
			else 
			{
			if((int)(drand()*irand()) % 10 < 5) bitVektor.push_back(false);
			else bitVektor.push_back(true);
			}
	}
}


void mutacija(Jedinka& j,double vjerojatnostMutacije)
{

		for(int i=0; i < j.bitVektor.size(); i++) if(drand() < vjerojatnostMutacije) j.bitVektor[i] = !(j.bitVektor[i]);	
}


Jedinka odaberiRoditelja(Populacija &p)
{
	double sumaDobrote = 0;
	list<Jedinka> potencijalniRoditelji;
	list<Jedinka>::iterator i;
	for(int j=0;j < 3; j++)
	{
		double random=drand();
		for(i = p.jedinke.begin(); i != p.jedinke.end() ; i++)
		{
			sumaDobrote += i->dobrota;
			if( (sumaDobrote/p.ukupnaDobrota) >= random )
			{
				potencijalniRoditelji.push_back(*i);
				break;
			}
		}
	}
	potencijalniRoditelji.sort(po_dobroti);
	return *(potencijalniRoditelji.begin());

}


void krizanje(Jedinka prviRoditelj , Jedinka drugiRoditelj , Jedinka& prvoDijete , Jedinka& drugoDijete , double vjerojatnostKrizanja ,bool uniformno)
{
	if(drand() < vjerojatnostKrizanja)
	{
		if(uniformno)
		{
			vector<bool> r;
			vector<bool> rComp;
                        for(int i = 0; i < prviRoditelj.bitVektor.size(); i++)
			{
			if((int)(irand()*drand()*10) % 10 < 5)
			{
				r.push_back(false);
				rComp.push_back(true);
			}
			else
			{
				r.push_back(true);
				rComp.push_back(false);
			}
			}
			bool prviIdrugi;
			bool prviILIdrugi;
			for(int i = 0; i < prviRoditelj.bitVektor.size(); i++)
			{
				prviIdrugi = prviRoditelj.bitVektor[i] && drugiRoditelj.bitVektor[i]; //logicko I
				prviILIdrugi = (prviRoditelj.bitVektor[i] + drugiRoditelj.bitVektor[i]) % 2; //ekskluzivno ILI
				prvoDijete.bitVektor.push_back(prviIdrugi || (r[i] && prviILIdrugi)); //D1=R1*R2 + R*(R1 # R2)
				drugoDijete.bitVektor.push_back(prviIdrugi || (rComp[i] && prviILIdrugi)); // D2=R1*R2 + Rcomp*(R1 # R2) # je iskljucivo ili
			}

		}
		else{
		int tockaPrekida = (irand() % prviRoditelj.bitVektor.size());
		for(int i = 0 ; i < prviRoditelj.bitVektor.size() ; i++)
		{
			if( i < tockaPrekida )
			{
				prvoDijete.bitVektor.push_back(prviRoditelj.bitVektor[i]);
				drugoDijete.bitVektor.push_back(drugiRoditelj.bitVektor[i]);
			}
			else
			{
				drugoDijete.bitVektor.push_back(prviRoditelj.bitVektor[i]);
				prvoDijete.bitVektor.push_back(drugiRoditelj.bitVektor[i]);
			}
		}
	}
	}
	else
	{
		prvoDijete.bitVektor = prviRoditelj.bitVektor;
		prvoDijete.dobrota = prviRoditelj.dobrota;
		drugoDijete.bitVektor = drugiRoditelj.bitVektor;
		drugoDijete.dobrota = drugiRoditelj.dobrota;
	}
}

//prve dvije jedinke te njihovi sigurno mutirani klonovi idu direktno u drugu populaciju
void kopiraj_elitu(Populacija &p , Populacija &q , vector<int>& varijable , set<int>& zagrade)
{
	list<Jedinka>::iterator i = p.jedinke.begin();
	Jedinka m1,m2;
	q.jedinke.push_back(*i);
	m1.bitVektor = (*i).bitVektor;
	advance(i,1);
	q.jedinke.push_back(*i);
	m2.bitVektor = (*i).bitVektor;
	mutacija(m1 , 1);
	m1.dobrota = racunaj_dobrotu(m1.bitVektor , varijable , zagrade);
	mutacija(m2 , 1);
	q.jedinke.push_back(m1);
	m2.dobrota = racunaj_dobrotu(m2.bitVektor , varijable , zagrade);
	q.jedinke.push_back(m2);
	q.jedinke.push_back(Jedinka(varijable));
}

Populacija::Populacija(int velicinaPopulacije , vector<int>& varijable)
{
	for(int i = 0; i< velicinaPopulacije; i++)
	{
		Jedinka j(varijable);
		jedinke.push_back(j);
	}

}

void Populacija::evaluirajPopulaciju(vector<int>& varijable , set<int>& zagrade)
{
	list<Jedinka>::iterator i;
	ukupnaDobrota = 0;
	for(i = jedinke.begin(); i != jedinke.end() ; i++ )
	{
		i->dobrota = racunaj_dobrotu(i->bitVektor,varijable,zagrade);
		ukupnaDobrota += i->dobrota;
	}
	jedinke.sort(po_dobroti);

}


vector<bool> genetski( int velicina_populacije , int broj_generacija , set<int>& skupVarijabli ,double vjerojatnost_mutacije ,double vjerojatnost_krizanja)
{
	set<int>:: iterator i;
	vector<int> varijable;
	set<int> zagrade;
	bool uniformno = 1;
	//kopira skup varijabli u vektor
	for( i = skupVarijabli.begin() ; i != skupVarijabli.end() ; i++ ) varijable.push_back(*i);
	cout<<varijable[80]<<endl;
	//trazi zagrade koje obraduje ovaj genetski algoritam
	zagrade = pronadi_zagrade(varijable);
	//azirarmo vjerojatnosti mutacije
	Populacija populacija(velicina_populacije,varijable);
	//cout<<populacija.jedinke.size()<<endl;
	populacija.evaluirajPopulaciju(varijable,zagrade);
	//ako smo pronasli rjesenje vratimo tu interpretaciju
	if(populacija.jedinke.begin()->dobrota == 1) return populacija.jedinke.begin()->bitVektor;
	//cout<<"prosao"<<endl;
	//cout<<populacija.jedinke.begin()->dobrota<<endl;
	//for(int i = 0; i < populacija.jedinke.begin()->bitVektor.size();i++) cout<<populacija.jedinke.begin()->bitVektor[i]<<" ";
	Populacija pomocna;
	for(int i = 2 ; i < broj_generacija + 1 ; i++)
	{
	//cout<<"prva"<<endl;
		kopiraj_elitu(populacija,pomocna,varijable,zagrade);
		for(int k = 6 ; k < velicina_populacije ; k+=2)
		{
		//cout<<"druga"<<endl;
			Jedinka prvoDijete;
			Jedinka drugoDijete;
			krizanje(odaberiRoditelja(populacija),odaberiRoditelja(populacija),prvoDijete,drugoDijete,vjerojatnost_krizanja,uniformno);
			mutacija(prvoDijete,vjerojatnost_mutacije);
			pomocna.jedinke.push_back(prvoDijete);
			mutacija(drugoDijete , vjerojatnost_mutacije);
			pomocna.jedinke.push_back(drugoDijete);
		}
		pomocna.evaluirajPopulaciju(varijable,zagrade);
		if(pomocna.jedinke.begin()->dobrota > 0.99 ) return pomocna.jedinke.begin()->bitVektor;
		populacija.jedinke = pomocna.jedinke;
		populacija.ukupnaDobrota = pomocna.ukupnaDobrota;
		cout<<populacija.jedinke.begin()->dobrota<<endl;
		pomocna.jedinke.clear();
		pomocna.ukupnaDobrota = 0;
	}
	vector<bool> prazan;
	return prazan;
}


