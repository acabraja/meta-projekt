using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SolverForSatProblem
{
    public static class GenetskiAlgoritam
    {
        //pronalazi zagrade za podskup varijabli koje prima genetski algoritam
        public static List<Zagrada> mojeZagrade(List<int> varijable, Dictionary<int, List<Zagrada>> veze_var_zagrada)
        {
            List<Zagrada> mojDioFormule = new List<Zagrada>();
            for (int i = 0; i < varijable.Count; i++)
            {
                if(veze_var_zagrada.ContainsKey(varijable[i]))
                {
                    for(int j = 0; j < veze_var_zagrada[varijable[i]].Count; j++) if(!mojDioFormule.Contains(veze_var_zagrada[varijable[i]][j])) mojDioFormule.Add(veze_var_zagrada[varijable[i]][j]);
                }
                if(veze_var_zagrada.ContainsKey(-varijable[i]))
                {
                    for(int j = 0; j < veze_var_zagrada[-varijable[i]].Count; j++) if(!mojDioFormule.Contains(veze_var_zagrada[-varijable[i]][j])) mojDioFormule.Add(veze_var_zagrada[-varijable[i]][j]);
                }
            }
            return mojDioFormule;
        }

        public static void azurirajVjerojatnosti(double[] vjarojatnosti, List<int> varijable, Dictionary<int, List<Zagrada>> veze_var_zagrada)
        {
            double brojPoz;
            double ukupanBroj;
            for (int i = 0; i < varijable.Count; i++)
            {
                brojPoz = 0;
                ukupanBroj = 0;
                if (veze_var_zagrada.ContainsKey(varijable[i]))
                {
                    for (int j = 0; j < veze_var_zagrada[varijable[i]].Count; j++)
                    {
                        ukupanBroj += (double)veze_var_zagrada[varijable[i]][j].tezina;
                        brojPoz += (double)veze_var_zagrada[varijable[i]][j].tezina;
                    }
                }
                if (veze_var_zagrada.ContainsKey(-varijable[i]))
                {
                    for (int j = 0; j < veze_var_zagrada[-varijable[i]].Count; j++) ukupanBroj += (double)veze_var_zagrada[-varijable[i]][j].tezina;
                }
                if (ukupanBroj != 0) vjarojatnosti[i] = brojPoz / ukupanBroj;
                else vjarojatnosti[i] = 0;
            }
        }

        //vraca polje boolova velicine varijable.Count
        public static bool[] genetskiAlgoritam(int velicinaPopulacije, int brojGeneracija, double vjrojatnostKrizanja, double vjerojatnostMutacije, bool rouletteWheel, bool uniformno, List<int> varijable, List<Zagrada> Formula, Dictionary<int, List<Zagrada>> veze_var_zagrada)
        {
            Random rand = new Random();
            Populacija trenutna = new Populacija(velicinaPopulacije,varijable.Count,varijable,veze_var_zagrada,rand);
            List<Zagrada> mojDioFormule = mojeZagrade(varijable, veze_var_zagrada);
            double[] vjerojatnosti = new double[varijable.Count];
            for (int i = 1; i <= brojGeneracija; i++)
            {
                trenutna.EvaluirajPopulacijuSTezinom1(mojDioFormule, varijable, veze_var_zagrada);
                if (trenutna.populacija[0].dobrota == 1) 
				{
					Console.WriteLine("pronasao sam\n");
					return trenutna.populacija[0].bitovi;
				}
                azurirajVjerojatnosti(vjerojatnosti,varijable,veze_var_zagrada);
                Populacija novaGeneracija = new Populacija(velicinaPopulacije);
                trenutna.KopirajElitu(novaGeneracija, 2, vjerojatnosti, varijable, veze_var_zagrada, rand);
                for (int j = 2; j < velicinaPopulacije; j += 2)
                {
                    Jedinka prviRoditelj = trenutna.OdaberiRoditelja(true, rand);
                    Jedinka drugiRoditelj = trenutna.OdaberiRoditelja(true, rand);
                    Jedinka prvoDijete = new Jedinka(varijable.Count);
                    Jedinka drugoDijete = new Jedinka(varijable.Count);
                    trenutna.Krizanje(vjrojatnostKrizanja, prviRoditelj, drugiRoditelj, prvoDijete, drugoDijete, false, veze_var_zagrada, varijable, rand);
                    prvoDijete.Mutacija(vjerojatnostMutacije, varijable, veze_var_zagrada, rand);
                    drugoDijete.Mutacija(vjerojatnostMutacije, varijable, veze_var_zagrada, rand);
                    novaGeneracija.populacija[j] = prvoDijete;
                    novaGeneracija.populacija[j + 1] = drugoDijete;
                }
                trenutna = novaGeneracija;
            }
            trenutna.EvaluirajPopulacijuSTezinom1(mojDioFormule, varijable, veze_var_zagrada);
            if (trenutna.populacija[0].dobrota == 1) 
			{
				Console.WriteLine("pronasao sam\n");
				return trenutna.populacija[0].bitovi;
			}
			bool[] ret = null;
             return ret;
        }
    }
}
