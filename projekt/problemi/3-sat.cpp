#include "3-sat.h"

// Grnerator speudoslucajnih brojeva
unsigned long init[4] = {0x123, 0x234, 0x345, 0x456}, length = 4;
MTRand_int32 irand(init, length);
MTRand drand(time(0));

//Konstruktor klase Jedinka

Jedinka::Jedinka()
{
  for(int i = 0; i < VEL_JEDINKE; ++i)
  {
    if((int)(irand()*drand()*10) % 10 < 5)
      this->bitVektor.push_back(false); 
    else
      this->bitVektor.push_back(true);
  }
  
  this->dobrota = racunaj_dobrotu(bitVektor);
}


Jedinka::Jedinka(vector<bool> vb)
{
  this->bitVektor = vb;
  this->dobrota = racunaj_dobrotu(bitVektor);
}
/* funkcija stvori_novu_populaciju()
/* parametri: Jedinka&, int
/* povratna vrijednost: void
/* opis: puni vektor populacija sa jedinkama na 2 nacina ovisno o statusu. Ako je status PRAZNA onda puni sve na slucajan nacin
/*       ako je status IZ_POSTOJECE onda vrsi selekciju prema funckiji dobrote i uzima odredjni postotak najboljih.
/* moguce dopune: prvenstveno funkcija u slucaju IZ_POSTOJECE vrati nepotpun vektor jedinki gdje treba dodati mutaciju i krizanje
/*                pa bi se moglo sloziti da se to automatski radi u ovoj funckciji što bi main ucinilo trivijalnim
/************************************************************************************/
void stvori_novu_populaciju(list<Jedinka>& populacija,int status)
{
  if( status == PRAZNA )
    for(int i = 0; i < VEL_POP; ++i)
      populacija.push_back(Jedinka());
  else if( status == IZ_POSTOJECE )
  {
    // tu imam sortiranu listu
		// ostavljamo one koji imaju dobrotu ne lošiju od 15% od najbolje
		list<Jedinka> pom;
		double fitt = populacija.front()*0.85;
		while(!populacija.empty()
		{
			if(populacija.front().dobrota > fitt)
			{
				pom.push_back(populacija.front());
				populacija.pop_front();
			}
			else
				break;
		}
		while(pom.size() < VEL_POP)
		{
			//uzmi nekoga i napravi krizanje
			// napravi mutaciju 
			// stavi u pom.
		}
	}
	populacija.sort(po_dobroti);
}

double racunaj_dobrotu(vector<bool>& jedinka)
{
  // racunam na to da je formula globalno dvodim. polje jer svi ju samo citaju pa nema problema
  // i to polje formula[BROJ_ZAGRADA][3]
	
	int count = 0;
 
	for(int i = 0; i < BROJ_ZAGRADA; i++)
	{
		if(formula[i][0] > 0 && formula[i][1] > 0 && formula[i][2] > 0)
		{
			if(jedinka[formula[i][0]] == 1 || jedinka[formula[i][1]] == 1 || jedinka[forumla[i][2] == 1)
				count++
		}
		else if((formula[i][0] < 0 && jadinka[abs(formula[i][0])] == 0) || 
					(forumla[i][1] < 0 && jedinka[abs(formula[i][1])] == 0) ||
					(formula[i][2] < 0 && jedinka[abs(formula[i][2])] == 0)){
        count++ 	
				}
	}
	
  return count/BROJ_ZAGRADA;
}

bool po_dobroti(Jedinka first,Jedinka second)
{
	if(first.dobrota > second.dobrota) return true;  //ovaj sort ti radi,stavis da je populacija list<Jedinka> pop i pozoves sa pop.sort(po_dobroti),sortira ti silazno
	return false;
}

void mutacija(Jedinka& j,double vjerojatnost_mutacije)
{
	if(drand() < vjerojatnost_mutacije)
	{
		double vjerojatnost;
		for(int i=0;i < VEL_JEDINKE;i++)
		{
			if(j.bitVektor[i]==false) vjerojatnost=vjerojatnosti[i];
			else vjerojatnost = 1-vjerojatnosti[i];
			if(drand() < vjerojatnost) j.bitVektor[i] = !(j.bitVektor[i]);
		}
	}
}

void krizanje(Jedinka& R1,Jedinka& R2,Jedinka& D1,Jedinka& D2,double vjerojatnost_krizanja,bool uniformno)	
{
	if(drand()<vjerojatnost_krizanja)
	{
		if(uniformno)				
		{
			vector<bool> r;				
			vector<bool> rComp;			
			for(int i = 0; i < VEL_JEDINKE; i++)
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
			for(int i = 0; i < VEL_JEDINKE; i++)
			{
				prviIdrugi = R1.bitVektor[i] && R2.bitVektor[i];		//logicko I 
				prviILIdrugi = (R1.bitVektor[i] + R2.bitVektor[i]) % 2;		//ekskluzivno ILI
				D1.bitVektor.push_back(prviIdrugi || (r[i] && prviILIdrugi));   //D1=R1*R2 + R*(R1 # R2)
				D2.bitVektor.push_back(prviIdrugi || (rComp[i] && prviILIdrugi));            // D2=R1*R2 + Rcomp*(R1 # R2) # je iskljucivo ili
			}
		}
		else					//tu sam mijenjala prve i zadnje razlike kak smo se dog
		{
			for(int i=0;i<VEL_JEDINKE;i++)
			{
				if(R1.bitVektor[i] != R2.bitVektor[i])
				{
					R1.bitVektor[i] = !(R1.bitVektor[i]);
					R2.bitVektor[i] = !(R2.bitVektor[i]);
					break;
				}
			}
			for(int i=VEL_JEDINKE-1;i>=0;i--)
			{
				if(R1.bitVektor[i] != R2.bitVektor[i])
				{
					R1.bitVektor[i] = !(R1.bitVektor[i]);
					R2.bitVektor[i] = !(R2.bitVektor[i]);
					break;
				}
			}
		}
	}
	else
	{
		D1.bitVektor = R1.bitVektor;
		D1.dobrota=R1.dobrota;
		D2.bitVektor = R2.bitVektor;
		D2.dobrota=R2.dobrota;
	}
	
}


