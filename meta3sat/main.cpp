#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<fstream>
#include<cmath>
#include<map>
#include<set>
#include "3sat.h"
#include<cstdlib>
#include<pthread.h>


using namespace std;



//GLOBALNE VARIJABLE
// moze i drugacije
vector<int> tezine;
vector<int> pomocne_tezine;
map<int, set<int> > veze_var_zagrada;
map<int, set<int> > veze_varijabli;
list<Zagrada> Formula;
vector<set<int> > nezavisni_skupovi;

void *thread_main(int *const d)
{
  //svaka dretva zna index d gdje se u vektoru nezavisni_skupovi nalazi skup koji ona treba obraditi
  // genetski
  // egzaktno
}




int main()
{

ifstream formula("formula.cnf");
if(! formula.is_open() )
{
cout<<"Greska kod otvaranja"<<endl;
exit(-1);
}	
       int count = 0;
while(1)
{
int a, b, c;
formula>> a;
if( !formula.good() ) break; // pretpostavljena sturktura 3-3-3-3-3-3 treba napravit bolju analizu za greske
formula>> b;
formula>> c;

// izbacujemo zagrade koje su tautologije
if( (abs(a) == abs(b) && a != b) || (abs(a) == abs(c) && a != c) || (abs(b) == abs(c) && b != c)) continue;

Formula.push_back( Zagrada( a, b, c,count) );
//tezine.push_back(1);
pomocne_tezine.push_back(1);
// veze varijabli i zagrada
veze_var_zagrada[a].insert(count);
veze_var_zagrada[b].insert(count);
veze_var_zagrada[c].insert(count);


// veze između varijabli
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

count++;
}

// Raspodijela poslova po dretvama prema nezavisnim skupovima

list<int> stog;
set<int> pomocni_skup;

while( !veze_varijabli.empty())
{
stog.push_front(veze_varijabli.begin()->first);
while(!stog.empty())
{
int sa_stoga;
sa_stoga = stog.front();
stog.pop_front();
if(pomocni_skup.insert(sa_stoga).second)
{
set<int>::iterator s;
for(s = (veze_varijabli.find(sa_stoga)->second).begin(); s != (veze_varijabli.find(sa_stoga)->second).end(); s++ )
{
if( pomocni_skup.end() == pomocni_skup.find(*s))
stog.push_front(*s);
}
}
veze_varijabli.erase(sa_stoga);
}
nezavisni_skupovi.push_back(pomocni_skup);
pomocni_skup.clear();
}

// threding
int P = nezavisni_skupovi.size();
pthread_t *pth;

if (!(pth = (pthread_t*)malloc(P * sizeof(pthread_t))))
  {
      cout<<"Greska pri stvaranju dretvi!"<<endl;
      return EXIT_FAILURE;
  }
 
  for(int i=0; i<nezavisni_skupovi.size(); i++)
  {
    if (pthread_create(pth + i, NULL, (void*(*)(void*))thread_main, &i))
    {
      cout<<"Greska pri pokretanju dretve!"<<endl;
      return EXIT_FAILURE;
    }
  }
  
   for (int i = 0; i < P; ++i)
   {
    if (pthread_join(pth[i], NULL))
    {
      cout<<"Join error!"<<endl;
      return EXIT_FAILURE;
    }
   }
 
  
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
    vector<bool> rjesenje = genetski(1000 ,100, *mapa , 0.05 , 0.7);
    for( int i = 0 ; i <rjesenje.size();i++) cout<<rjesenje[i]<<" ";
  }
  

  
  return 0;
}