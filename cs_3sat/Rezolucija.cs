using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SolverForSatProblem
{
    public static class Rezolucija
    {
        public static bool Tautologija(Zagrada a)
        {
            for (int i = 0; i < a.varijable.Count; i++)
            {
                if (a.varijable.Contains(-a.varijable[i])) return true;
            }
            return false;
        }

        public static Zagrada SpojiZagrade(Zagrada a, Zagrada b, int varijabla, Dictionary<int, List<Zagrada>> veze_var_zagrada,List<Zagrada> Formula,List<int> varijable)
        {
            Zagrada nova = new Zagrada();
            for (int i = 0; i < a.varijable.Count; i++)
            {
                if (a.varijable[i] != varijabla && a.varijable[i] != (-varijabla) && (!nova.varijable.Contains(a.varijable[i]))) nova.varijable.Add(a.varijable[i]);
            }
            for (int i = 0; i < b.varijable.Count; i++)
            {
                if (b.varijable[i] != varijabla && b.varijable[i] != (-varijabla) && (!nova.varijable.Contains(b.varijable[i]))) nova.varijable.Add(b.varijable[i]);
            }
            if (!Tautologija(nova))
            {
                for (int i = 0; i < nova.varijable.Count; i++) veze_var_zagrada[nova.varijable[i]].Add(nova);
            }
            nova.tezina = 1;
            popraviVeze(a, b, veze_var_zagrada, varijable);
            Formula.Remove(a);
            Formula.Remove(b);
            return nova;
        }

        public static void popraviVeze(Zagrada a, Zagrada b, Dictionary<int, List<Zagrada>> veze_var_zagrada,List<int> varijable)
        {
            for (int i = 0; i < varijable.Count; i++)
            {
                if (veze_var_zagrada.ContainsKey(varijable[i]) && veze_var_zagrada[varijable[i]].Contains(a)) veze_var_zagrada[varijable[i]].Remove(a);
                if (veze_var_zagrada.ContainsKey(-varijable[i]) && veze_var_zagrada[-varijable[i]].Contains(a)) veze_var_zagrada[-varijable[i]].Remove(a);
                if (veze_var_zagrada.ContainsKey(varijable[i]) && veze_var_zagrada[varijable[i]].Contains(b)) veze_var_zagrada[varijable[i]].Remove(b);
                if (veze_var_zagrada.ContainsKey(-varijable[i]) && veze_var_zagrada[-varijable[i]].Contains(b)) veze_var_zagrada[-varijable[i]].Remove(b);
            }
        }

        //rekurzivni poziv za svaku zagradu
        public static List<Zagrada> RezolucijaFormule1(List<Zagrada> Formula, Dictionary<int, List<Zagrada>> veze_var_zagrada, List<int> varijable, int index)
        {
            if (index == Formula.Count || Formula.Count == 1) return Formula;
            for (int i = 0; i < Formula[index].varijable.Count; i++)
            {
                if (veze_var_zagrada.ContainsKey(-Formula[index].varijable[i]) && veze_var_zagrada[-Formula[index].varijable[i]].Count != 0)
                {
                    Zagrada nova = SpojiZagrade(Formula[index], veze_var_zagrada[-Formula[index].varijable[i]].First(), Formula[index].varijable[i], veze_var_zagrada, Formula,varijable);
                    if (!Tautologija(nova)) Formula.Add(nova);
                    index--;
                    break;
                }
            }
            RezolucijaFormule1(Formula, veze_var_zagrada, varijable, index + 1);
            return Formula;
        }

    }
}
