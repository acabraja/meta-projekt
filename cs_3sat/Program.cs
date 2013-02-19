using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.IO;

namespace SolverForSatProblem
{
    class MainClass
    {
        public static List<Zagrada> Zagrade = new List<Zagrada>();
        public static List<int> varijable = new List<int>();
        public static Dictionary<int, List<int>> veze_varijabli = new Dictionary<int, List<int>>();
        public static Dictionary<int, List<Zagrada>> veza_var_zagrada = new Dictionary<int, List<Zagrada>>();
        public static List<List<int>> nezavisni_skupovi = new List<List<int>>();

        public static void PripremiFormulu()
        {
            try
            {
                /* Read cnf from txt file*/
                using (StreamReader sr = new StreamReader("../../formule/formula.txt"))
                {
                    String line;
                    int[] elements = new int[3];
                    int k, a = 0, b = 0, c = 0;
                    while ((line = sr.ReadLine()) != null)
                    {
                        k = 0;
                        string pom_str = string.Empty;
                        for (int i = 0; i < line.Length; i++)
                        {
                            if (Char.IsDigit(line[i]) || line[i] == '-')
                                pom_str += line[i];

                            if (pom_str.Length > 0 && (i+1 >= line.Length || line[i + 1] == ' '))
                            {
                                elements[k++] = int.Parse(pom_str);
                                if( 0 == varijable.Find(x => x == Math.Abs(elements[k - 1])))
                                    varijable.Add(Math.Abs(elements[k -1]));
                                pom_str = "";
                            }
                        }
                        try
                        {
                            a = Math.Abs(elements[0]); b = Math.Abs(elements[1]); c = Math.Abs(elements[2]);
                            // izbacuje zagrade koje su tautologije (ako je tautologija nemoj tu zagradu uzet u obzir)
                            if (!((Math.Abs(a) == Math.Abs(b) && a != b) || (Math.Abs(a) == Math.Abs(c) && a != c) || (Math.Abs(b) == Math.Abs(c) && b != c)))
                            {
                                Zagrade.Add(new Zagrada(elements[0], elements[1], elements[2]));
                                if (!veza_var_zagrada.ContainsKey(a))
                                    veza_var_zagrada.Add(a, new List<Zagrada>());
                                if (!veza_var_zagrada.ContainsKey(b))
                                    veza_var_zagrada.Add(b, new List<Zagrada>());
                                if (!veza_var_zagrada.ContainsKey(c))
                                    veza_var_zagrada.Add(c, new List<Zagrada>());
                           
                                veza_var_zagrada[a].Add(new Zagrada(elements[0], elements[1], elements[2]));
                                veza_var_zagrada[b].Add(new Zagrada(elements[0], elements[1], elements[2]));
                                veza_var_zagrada[c].Add(new Zagrada(elements[0], elements[1], elements[2]));
                            }
                        }
                        catch (Exception e)
                        {
                            Console.WriteLine("Greska kod ubacivanja Zagrada:");
                            Console.WriteLine(e.Message);
                        }

                        /*mapa svih varijabli s kojim je neka varijabla vezana*/
                        if (!veze_varijabli.ContainsKey(a))
                        {
                            List<int> pom = new List<int>();
                            pom.Add(b);
                            pom.Add(c);
                            veze_varijabli.Add(a, pom);
                        }
                        else
                        {
                            if (0 == veze_varijabli[a].Find(x => x == b))
                                veze_varijabli[a].Add(b);
                            if (0 == veze_varijabli[a].Find(x => x == c))
                                veze_varijabli[a].Add(c);
                        }

                        if (!veze_varijabli.ContainsKey(b))
                        {
                            List<int> pom = new List<int>();
                            pom.Add(a);
                            pom.Add(c);
                            veze_varijabli.Add(b, pom);
                        }
                        else
                        {
                            if (0 == veze_varijabli[b].Find(x => x == a))
                                veze_varijabli[b].Add(a);
                            if (0 == veze_varijabli[b].Find(x => x == c))
                                veze_varijabli[b].Add(c);
                        }

                        if (!veze_varijabli.ContainsKey(c))
                        {
                            List<int> pom = new List<int>();
                            pom.Add(b);
                            pom.Add(a);
                            veze_varijabli.Add(c, pom);
                        }
                        else
                        {
                            if (0 == veze_varijabli[c].Find(x => x == b))
                                veze_varijabli[c].Add(b);
                            if (0 == veze_varijabli[c].Find(x => x == a))
                                veze_varijabli[c].Add(a);
                        }
                    }

                }
            }
            catch (Exception e)
            {
                Console.WriteLine("The file could not be read:");
                Console.WriteLine(e.Message);
            }

            /*Algoritam za nalazenje nezavisnih skupova*/

            Stack<int> stog = new Stack<int>();
            List<int> pomocni_skup = new List<int>();

            while( veze_varijabli.Count != 0)
            {
                int lk = 0;
                foreach (int k in veze_varijabli.Keys)
                {
                    lk = k;
                    break;
                }
                
                stog.Push(lk);
                while (0 != stog.Count)
                {
                    int sa_stoga;
                    sa_stoga = stog.Peek();
                    stog.Pop();
                    if (0 == pomocni_skup.Find(x => x == sa_stoga))
                    {
                        pomocni_skup.Add(sa_stoga);
                        foreach (int s in veze_varijabli[sa_stoga])
                            if (0 == pomocni_skup.Find(x => x == s))
                                stog.Push(s);
                    }
                    veze_varijabli.Remove(sa_stoga);
                }
                nezavisni_skupovi.Add(new List<int>(pomocni_skup));
                pomocni_skup.Clear();
            }
        }

        public static void Main(string[] args)
        {
            PripremiFormulu();
            List<Zagrada> zagrada = new List<Zagrada>();

            /*foreach (List<int> l in nezavisni_skupovi)
            {
                foreach (int i in l)
                    Console.Write("{0} ", i);
                Console.Write("\n");
            }
            Console.WriteLine(veze_varijabli.Count);
            
            foreach (var pair in veze_varijabli)
            {
                Console.WriteLine("Kljuc : {0}",pair.Key);
                foreach(int elem in pair.Value)
                    Console.Write("{0}, ",elem);
                Console.Write("\n");
            }*/
            varijable.Sort();
            Console.WriteLine("\nIspis svih varijabli");
            Console.WriteLine("---------------------");
            foreach (int ele in varijable)
                Console.Write("{0} ", ele);
            Console.Write("\n");

            Console.WriteLine("\nIspis svih zagrada");
            Console.WriteLine("---------------------");
            foreach(Zagrada i in Zagrade){
                foreach (int ele in i.varijable)
                    Console.Write("{0} ", ele);
                Console.Write("\n");
            }
            Console.WriteLine("\nTko je s kim povezan:");
            Console.WriteLine("---------------------");
            foreach (var k in veza_var_zagrada)
            {
                Console.WriteLine("Ja sam {0} i povezana sam sa :", k.Key);
                foreach (Zagrada i in k.Value)
                {
                    foreach (int ele in i.varijable)
                        Console.Write("{0} ", ele);
                    Console.Write("\n");
                }
            }
            //varijable.Sort();
            //zagrada = Rezolucija.RezolucijaFormule1(Zagrade, veza_var_zagrada, varijable, 0);
            Console.WriteLine(veza_var_zagrada.Count);
            bool[] interpretacija;
            interpretacija = GenetskiAlgoritam.genetskiAlgoritam(50, 100, 0.7, 0.05, true, true, varijable, Zagrade, veza_var_zagrada);

            Console.WriteLine("Dobivena interpretacija");
            foreach (bool ine in interpretacija)
                Console.Write("{0} ", ine);

            Console.Write("\n \n \nPress any key to continue . . . ");
            Console.ReadKey(true);
        }

    }
}
