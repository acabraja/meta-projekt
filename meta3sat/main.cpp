#include "3sat.h"

                     /*Globalne varijable s podacima o formuli*/
                     
vector<int> tezine;                   // vektor tezina zagrada, uredjen prema id zagrade
vector<int> pomocne_tezine; 
map<int, set<int> > veze_var_zagrada; // za svaku varijablu znamo skup zagrada u kojima se javlja
map<int, set<int> > veze_varijabli;   // za svaku varijablu zanamo s kojim varijablama je povezana
list<Zagrada> Formula;                // predstavlja formulu kao listu zagrada 
vector<set<int> > nezavisni_skupovi;  // vektor nezavisnik skupova varijabli



                                /* Glavna funkcija*/

int main(int argc, char* argv[]) 
{
  int count = 0; // broji koliko ima zagrada i odreduje id zagrade
            
            /* Citanje iz datoteke */
  
  ifstream formula("../projekt/formula2.cnf");
  
  if(! formula.is_open() )
  {
    cout<<"Greska kod otvaranja"<<endl;
    return EXIT_FAILURE;
  }	
  
  while( formula.good() )
  {
    int a, b, c; // za varijable u zagradi
    
    //pretpostavka je da je dobro zadana 3CNF 
    formula>> a;
    formula>> b;
    formula>> c;

    // izbacuje zagrade koje su tautologije (ako je tautologija nemoj tu zagradu uzet u obzir)
    if(! ((abs(a) == abs(b) && a != b) || (abs(a) == abs(c) && a != c) || (abs(b) == abs(c) && b != c)))
    {
      Formula.push_back( Zagrada( a, b, c, count) );
      //tezine.push_back(1);
      pomocne_tezine.push_back(1);
      
      // veze varijabli i zagrada
      veze_var_zagrada[a].insert(count);
      veze_var_zagrada[b].insert(count);
      veze_var_zagrada[c].insert(count);
    }
    count++; 
    
    // veze izmedu varijabli
		a = abs(a); b = abs(b); c = abs(c);
		
		if( veze_varijabli.find(a) == veze_varijabli.end() )
		{
		    set<int> pom;
        pom.insert(b); pom.insert(c);
        veze_varijabli.insert(pair<int,set<int> >(a,pom));
    }
    else
    {
      veze_varijabli.find(a)->second.insert(b);
      veze_varijabli.find(a)->second.insert(c);
    }
    
    if( veze_varijabli.find(b) == veze_varijabli.end() )
    {
      set<int> pom;
      pom.insert(a); pom.insert(c);
      veze_varijabli.insert(pair<int,set<int> >(b,pom));
    }
    else
    {
      veze_varijabli.find(b)->second.insert(a);
      veze_varijabli.find(b)->second.insert(c);
    }
    
    if( veze_varijabli.find(c) == veze_varijabli.end() )  
    {
      set<int> pom;
      pom.insert(a); pom.insert(b);
      veze_varijabli.insert(pair<int,set<int> >(c,pom));
    }
    else
    {
      veze_varijabli.find(c)->second.insert(a);
      veze_varijabli.find(c)->second.insert(b);
    }
  }
  
                 /* Algoritam za trazenje nezavisnih skupova */
  
  list<int> stog;
  set<int> pomocni_skup;

  while( !veze_varijabli.empty() )
  {
    stog.push_front( veze_varijabli.begin()->first );
    while( !stog.empty() )
    {
      int sa_stoga;
      sa_stoga = stog.front();
      stog.pop_front();
      if( pomocni_skup.insert( sa_stoga ).second )
      {
        set<int>::iterator s;
        for( s = ( veze_varijabli.find( sa_stoga )->second ).begin(); s != ( veze_varijabli.find( sa_stoga )->second ).end(); s++ )
        {
          if( pomocni_skup.end() == pomocni_skup.find(*s) )
            stog.push_front( *s );
        }
      }
      veze_varijabli.erase( sa_stoga );
    }
    nezavisni_skupovi.push_back( pomocni_skup );
    pomocni_skup.clear();
  }

                /*Raspodjela posla po dretvama */
                
  /*int P = nezavisni_skupovi.size();
  pthread_t *pth;

  if( !(pth = ( pthread_t* )malloc( P * sizeof(pthread_t) ) ) )
  {
      cout<<"Greska pri stvaranju dretvi!"<<endl;
      return EXIT_FAILURE;
  }
 
  for( int i = 0; i < nezavisni_skupovi.size(); i++ )
  {
    if( pthread_create( pth + i, NULL, (void*(*)(void*) )thread_main, &i ) )
    {
      cout<<"Greska pri pokretanju dretve!"<<endl;
      return EXIT_FAILURE;
    }
  }
  
  for( int i = 0; i < P; ++i )
  {
    if(pthread_join( pth[i], NULL ) ) 
    {
      cout<<"Join error!"<<endl;
      return EXIT_FAILURE;
    }
  }*/
 
                               /* testiranje rada funkcija */
  // PRAVILO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // Sva svoja testiranja stavite u komentare
  
  
  // ispisuje nezavisne skupove
  vector<set<int> >::iterator mapa;
  set<int>::iterator skup;
  int sl=0;
  for(mapa=nezavisni_skupovi.begin(); mapa != nezavisni_skupovi.end(); mapa++)
  {
    cout<<"Ovo je "<< 1 + sl++ <<". nezavisan skup"<<endl;
    cout<<"( ";
    for(skup = (*mapa).begin(); skup != (*mapa).end(); skup++)
      cout<<*skup<<", ";
    cout<<")"<<endl;
    vector<bool> rjesenje = genetski(100 ,500, *mapa , 0.05 , 0.6);
    for( int i = 0 ; i <rjesenje.size();i++) cout<<rjesenje[i]<<" ";
    cout<<endl;
  }

  return 0;
}
