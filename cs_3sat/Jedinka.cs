using System;
using System.Collections.Generic;
using System.Text;


namespace SolverForSatProblem
{
    public class Jedinka : IComparable
    {
        public bool[] bitovi;
        public double dobrota;
        public int brojZadovoljenihZagrada;
        public int brojVarijabli;

        public Jedinka(int brojVarijabli ,List<int> varijable,Dictionary<int, List<Zagrada>> veze_var_zagrada, Random rand)
        {
            this.brojVarijabli = brojVarijabli;
            this.bitovi = new bool[brojVarijabli];
            for (int i = 0; i < this.brojVarijabli; i++)
            {
                if (veze_var_zagrada[varijable[i]].Count == 0) bitovi[i] = false;
                else if (veze_var_zagrada.ContainsKey(-varijable[i]) && veze_var_zagrada[-varijable[i]].Count == 0) bitovi[i] = true;
                else
                {
                    if (rand.Next(2) == 1) bitovi[i] = true;
                    else bitovi[i] = false;
                }
            }
            this.dobrota = 0;
            this.brojZadovoljenihZagrada = 0;
        }

        public Jedinka(int brojVarijabli)
        {
            this.brojVarijabli = brojVarijabli;
            this.bitovi = new bool[brojVarijabli];
            this.dobrota = 0;
            this.brojZadovoljenihZagrada = 0;
        }

        public int CompareTo(object obj)
        {
            Jedinka druga = (Jedinka)obj;
            if (this.dobrota < druga.dobrota) return 1;
            if (this.dobrota > druga.dobrota) return -1;
            return 0;
        }

        //dobrota obzirom na tezine zagrada
        public void RacunajDobrotuSTezinama(int ukupanBrojZagrada, List<Zagrada> zagrade, List<int> varijable, Dictionary<int, List<Zagrada>> veze_var_zagrada)
        {
            double brojZadovoljenih = 0;
            double tezinaSvih = 0;
            for (int i = 0; i < zagrade.Count; i++)
            {
                if (zagrade[i].zadovoljena(bitovi,varijable, veze_var_zagrada)) brojZadovoljenih += (double)zagrade[i].tezina;
                else zagrade[i].tezina++;
                tezinaSvih += (double)zagrade[i].tezina;
            }
            this.brojZadovoljenihZagrada = (int)brojZadovoljenih;
            this.dobrota = brojZadovoljenih / tezinaSvih;
        }

        //dobrota obzirom na broj zadovoljenih zagrada
        public void RacunajDobrotuSTezinom1(int ukupanBrojZagrada,List<int> varijable, List<Zagrada> zagrade, Dictionary<int, List<Zagrada>> veze_var_zagrada)
        {
            double brojZadovoljenih = 0;
            double tezinaSvih = 0;
            for (int i = 0; i < zagrade.Count; i++)
            {
                if (zagrade[i].zadovoljena(bitovi,varijable, veze_var_zagrada)) brojZadovoljenih++;
                else zagrade[i].tezina++;
                tezinaSvih ++;
            }
            this.brojZadovoljenihZagrada = (int)brojZadovoljenih;
            this.dobrota = brojZadovoljenih / tezinaSvih;
        }


        public void Mutacija(double vjerojatnostMutacije, List<int> varijable, Dictionary<int, List<Zagrada>> veze_var_zagrada, Random rand)
        {
            if (rand.NextDouble() <= vjerojatnostMutacije)
            {
                for (int i = 0; i < this.brojVarijabli; i++)
                {
                    if (!veze_var_zagrada.ContainsKey(varijable[i]) || veze_var_zagrada[varijable[i]].Count == 0) bitovi[i] = false;
                    else if (!veze_var_zagrada.ContainsKey(-varijable[i]) || veze_var_zagrada[-varijable[i]].Count == 0) bitovi[i] = true;
                    else
                    {
                        if (rand.Next(2) == 1) bitovi[i] = true;
                        else bitovi[i] = false;
                    }
                }
            }
        }

        //mutacija obzirom na tezine zagrada
        public void UsmjerenaMutacija(double[] vjerojatnosti, List<int> varijable, Dictionary<int, List<Zagrada>> veze_var_zagrada, Random rand)
        {
            for (int i = 0; i < this.brojVarijabli; i++)
            {
                if (!veze_var_zagrada.ContainsKey(varijable[i]) || veze_var_zagrada[varijable[i]].Count == 0) bitovi[i] = false;
                else if (!veze_var_zagrada.ContainsKey(-varijable[i]) || veze_var_zagrada[-varijable[i]].Count == 0) bitovi[i] = true;
                else
                {
                    if (bitovi[i] == false)
                    {
                        if (rand.NextDouble() <= vjerojatnosti[i]) bitovi[i] = !bitovi[i];
                    }
                    else
                    {
                        if (rand.NextDouble() <= (1 - vjerojatnosti[i])) bitovi[i] = !bitovi[i];
                    }
                } 
            }
            
        }

    }
}
