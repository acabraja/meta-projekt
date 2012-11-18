#include<iostream>
#include<string>
#include<cstdlib>
#include<vector>
#include "problemi/3-sat.h"

using namespace std;

int main( int argc, char* argv[])
{
  vector<Jedinka> populacija(VEL_POP);
  
  stvori_novu_populaciju(populacija,PRAZNA);
  
  return 0;
}
