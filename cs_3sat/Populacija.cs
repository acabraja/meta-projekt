using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SolverForSatProblem
{
    public class Populacija
    {
        public Jedinka[] populacija;
        public int velicinaPopulacije;
        public double dobrotaPopulacije;

        public Populacija(int velicinaPopulacije)
        {
            this.velicinaPopulacije = velicinaPopulacije;
            this.populacija = new Jedinka[velicinaPopulacije];
        }

        public Populacija(int velicinaPopulacije, int brojVarijabli, List<int> varijable, Dictionary<int, List<Zagrada>> veze_var_zagrada, Random rand)
        {
            this.velicinaPopulacije = velicinaPopulacije;
            this.populacija = new Jedinka[velicinaPopulacije];
            this.dobrotaPopulacije = 0;
            for (int i = 0; i < velicinaPopulacije; i++)
            {
                this.populacija[i] = new Jedinka(brojVarijabli, varijable, veze_var_zagrada, rand);
            }
        }

        public void EvaluirajPopulacijuSTezinom1(List<Zagrada> Formula, List<int> varijable, Dictionary<int, List<Zagrada>> veze_var_zagrada)
        {
            for (int i = 0; i < velicinaPopulacije; i++)
            {
                this.populacija[i].RacunajDobrotuSTezinom1(Formula.Count, varijable, Formula, veze_var_zagrada);
                this.dobrotaPopulacije += this.populacija[i].dobrota;
            }
            Array.Sort(this.populacija);
        }

        public void EvaluirajPopulacijuSTezinama(List<Zagrada> Formula, List<int> varijable, Dictionary<int, List<Zagrada>> veze_var_zagrada)
        {
            for (int i = 0; i < velicinaPopulacije; i++)
            {
                populacija[i].RacunajDobrotuSTezinama(Formula.Count, Formula, varijable, veze_var_zagrada);
                dobrotaPopulacije += populacija[i].dobrota;
            }
            Array.Sort(this.populacija);
        }


        public void KopirajElitu(Populacija novaGeneracija, int velicinaElite, double[] vjerojatnosti, List<int> varijable, Dictionary<int, List<Zagrada>> veze_var_zagrada, Random rand)
        {
            for (int i = 0; i < velicinaElite; i += 2)
            { 
                novaGeneracija.populacija[i] = this.populacija[i];
                Jedinka pomocna = this.populacija[i];
                pomocna.UsmjerenaMutacija(vjerojatnosti, varijable, veze_var_zagrada, rand);
                novaGeneracija.populacija[i + 1] = pomocna;
            }
        }

        public Jedinka OdaberiRoditelja(bool rouletteWheel, Random rand)
        {
            Jedinka[] kandidatiZaRoditelja = new Jedinka[3];
            for (int i = 0; i < 3; i++)
            {
                double random = rand.NextDouble();
                double sumaDobrote = 0;
                for (int j = 0; j < populacija.Length; j++)
                {
                    sumaDobrote += populacija[j].dobrota / this.dobrotaPopulacije;
                    if (random <= sumaDobrote)
                    {
                        if (rouletteWheel) return populacija[j];
                        kandidatiZaRoditelja[i] = populacija[j];
                        break;
                    }
                }
            }
            Array.Sort(kandidatiZaRoditelja);
            return kandidatiZaRoditelja[0];
        }

        public void Krizanje(double vjerojatnostKrizanja, Jedinka prviRoditelj, Jedinka drugiRoditelj, Jedinka prvoDijete, Jedinka drugoDijete, bool krizanjeJednomTockom, Dictionary<int,List<Zagrada>> veze_var_zagrada, List<int> varijable, Random rand)
        {
            int ukupanBrojBitova = prviRoditelj.bitovi.Length;
            if (krizanjeJednomTockom)
            {
                if (rand.NextDouble() <= vjerojatnostKrizanja)
                {
                    int tockaPrijeloma = rand.Next(ukupanBrojBitova + 1);
                    for (int i = 0; i < tockaPrijeloma; i++)
                    {
                        prvoDijete.bitovi[i] = prviRoditelj.bitovi[i];
                        drugoDijete.bitovi[i] = drugiRoditelj.bitovi[i];
                    }
                    for (int i = tockaPrijeloma; i < ukupanBrojBitova; i++)
                    {
                        prvoDijete.bitovi[i] = drugiRoditelj.bitovi[i];
                        drugoDijete.bitovi[i] = prviRoditelj.bitovi[i];
                    }
                }
                else
                {
                    for (int i = 0; i < ukupanBrojBitova; i++)
                    {
                        prvoDijete.bitovi[i] = prviRoditelj.bitovi[i];
                        drugoDijete.bitovi[i] = drugiRoditelj.bitovi[i];
                    }
                }
            }
            else
            {
                bool[] r = new bool[ukupanBrojBitova];
                bool[] rKomp = new bool[ukupanBrojBitova];
                for (int i = 0; i < ukupanBrojBitova; i++)
                {
                    if (rand.Next(2) == 1)
                    {
                        r[i] = true;
                        rKomp[i] = false;
                    }
                    else
                    {
                        r[i] = false;
                        rKomp[i] = true;
                    }
                }
                bool prviAndDrugiRoditelj;
                bool prviXorDrugiRoditelj;
                for (int i = 0; i < ukupanBrojBitova; i++)
                {
                    prviAndDrugiRoditelj = (bool)(prviRoditelj.bitovi[i] & drugiRoditelj.bitovi[i]);
                    prviXorDrugiRoditelj = (bool)(prviRoditelj.bitovi[i] ^ drugiRoditelj.bitovi[i]);
                    if (!veze_var_zagrada.ContainsKey(varijable[i]) || (veze_var_zagrada.ContainsKey(varijable[i]) && veze_var_zagrada[varijable[i]].Count == 0)) prvoDijete.bitovi[i] = false;
                    else if (!veze_var_zagrada.ContainsKey(varijable[i]) || (veze_var_zagrada.ContainsKey(-varijable[i]) && veze_var_zagrada[-varijable[i]].Count == 0)) prvoDijete.bitovi[i] = true;
                    else prvoDijete.bitovi[i] = (bool)(prviAndDrugiRoditelj | (bool)(r[i] & prviXorDrugiRoditelj));
                    if (!veze_var_zagrada.ContainsKey(varijable[i]) || (veze_var_zagrada.ContainsKey(varijable[i]) && veze_var_zagrada[varijable[i]].Count == 0)) drugoDijete.bitovi[i] = false;
                    else if (!veze_var_zagrada.ContainsKey(varijable[i]) || (veze_var_zagrada.ContainsKey(-varijable[i]) && veze_var_zagrada[-varijable[i]].Count == 0)) drugoDijete.bitovi[i] = true;
                    else drugoDijete.bitovi[i] = (bool)(prviAndDrugiRoditelj | (bool)(rKomp[i] & prviXorDrugiRoditelj));
                }
            }
        }

    }

}
