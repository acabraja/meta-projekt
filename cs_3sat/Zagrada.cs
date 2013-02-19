using System;
using System.Collections.Generic;
using System.Text;

namespace SolverForSatProblem
{
    public class Zagrada
    {
        public List<int> varijable;
        public int tezina;

        public Zagrada(int prvaVarijabla, int drugaVarijabla, int trecaVarijabla)
        {
            varijable = new List<int>();
            this.tezina = 1;
            varijable.Add(prvaVarijabla);
            varijable.Add(drugaVarijabla);
            varijable.Add(trecaVarijabla);
        }

        public Zagrada()
        {
            varijable = new List<int>();
        }

        public bool zadovoljena(bool[] bitovi, List<int> varijable, Dictionary<int, List<Zagrada>> veze_var_zagrada)
        {
            int varijabla;
            for (int i = 0; i < this.varijable.Count; i++)
            {
                if (this.varijable[i] > 0) varijabla = this.varijable[i];
                else varijabla = -this.varijable[i];
                int index = varijable.IndexOf(varijabla);
                if (bitovi[index] == true && veze_var_zagrada.ContainsKey(varijabla) && veze_var_zagrada[varijabla].Contains(this)) return true;
                else if (bitovi[index] == false && veze_var_zagrada.ContainsKey(-varijabla) && veze_var_zagrada[-varijabla].Contains(this)) return true;
            }
            this.tezina++;
            return false;
        }
    }
}
