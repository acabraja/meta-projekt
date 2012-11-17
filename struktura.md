Rješavanje našeg problema izvodit će se u nekoliko koraka.

Korak 1.
Potpuno definirati probleme MAX-SAT, 3SAT te  MAX-3SAT. Dakle treba nam jedan pdf sa definicijom problema i sa načinom realizacije danih problema. 

Korak 2.
Definiranje faza izrade projekta. Jedan od prijedloga je sljedeći:

Upravo definirane faze sastojat će se od nekoliko pod faza.

Faza 1 (rješavanje problema 3SAT)
       
       Faza 1.1 Kodiranje problema u jeziku c++ u odvojenim fragmenitima prema dodjeljenim zadacima
       Faza 1.2 Paralelizacija koda prema dogovoru
       Faza 1.3 Testiranje poznatih primjera
       Faza 1.4 Grafika za solver
Faza 2 (rješenje problema MAX-SAT)
      -> bit će definirano nakon rješenje prve faze tj. naknadno 

Zamislila sam da problem 3 sat rjesavamo ovako:

U mainu na osnovu logicke formule stvorimo vektor varijabli i vektor zagrada.
Indeski u vektoru varijabli se poklapaju s indeksima u bitVektoru jedinke.
Sutra sam planirala jos napraviti kako ce se racunati vjerojatnost mutacije za pojedinu varijabu,odnosno bit u bitVektoru jedinke.

Tezina zagrade bi se povecavala ukoliko je zagradu tesko zadovoljiti odnosno ukoliko onda nije zadovoljena u prosloj generaciji.

Vrednovanje bi bilo lako napraviti,samo provjerimo jesu li sve zagrade jednake 1.
