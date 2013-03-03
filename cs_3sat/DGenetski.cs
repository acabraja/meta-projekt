using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SolverForSatProblem;
using MPI;

namespace SolverForSatProblem
{
    class DinamickiGenetski : GenetskiAlgoritam
    {
        public static bool[] genetskiAlgoritamSekvencijalni(int velicinaPopulacije, int brojGeneracija, double vjrojatnostKrizanja, double vjerojatnostMutacije, bool rouletteWheel, bool uniformno, List<int> varijable, List<Zagrada> Formula, Dictionary<int, List<Zagrada>> veze_var_zagrada)
        {
            double epsilon = 0.000002;
            int counter = 0;
            double bestOne, bestTwo;
            Random rand = new Random();
            Populacija trenutna = new Populacija(velicinaPopulacije, varijable.Count, varijable, veze_var_zagrada, rand);
            List<Zagrada> mojDioFormule = mojeZagrade(varijable, veze_var_zagrada);
            trenutna.EvaluirajPopulacijuSTezinama(mojDioFormule, varijable, veze_var_zagrada);
            if (trenutna.populacija[0].dobrota == 1) return trenutna.populacija[0].bitovi;
            double[] vjerojatnosti = new double[varijable.Count];
            for (int i = 1; i <= brojGeneracija; i++)
            {
                azurirajVjerojatnosti(vjerojatnosti, varijable, veze_var_zagrada);
                Populacija novaGeneracija = new Populacija(velicinaPopulacije);
                trenutna.KopirajElitu(novaGeneracija, 2, vjerojatnosti, varijable, veze_var_zagrada, rand);
                bestOne = trenutna.VratiNajboljuDobrotu();
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
                novaGeneracija.EvaluirajPopulacijuSTezinama(mojDioFormule, varijable, veze_var_zagrada);
                trenutna = novaGeneracija;
                bestTwo = trenutna.VratiNajboljuDobrotu();
                Console.WriteLine("{0}\n", bestTwo - bestOne);
                if (trenutna.populacija[0].dobrota == 1) return trenutna.populacija[0].bitovi;

                if (Math.Abs(bestOne - bestTwo) < epsilon*0.0001)
                    counter++;
                else
                    counter = 0;

                if (counter > (int)(0.001 * brojGeneracija))
                {
                    Console.WriteLine("Vec 15% generacija dobrota se krece u intervalu ispod zadanog epsilona");
                    Console.WriteLine("Zelite li mozda korigirati neke parametre prije nastavka?");
                    Console.WriteLine("U slucaju da ne zelite mjenjati postojece stanje upiste NO inace YES");
                    if (Console.ReadLine() == "YES")
                    {
                        Console.Write(" Unesite novu vjerojatnost za krizanje : ");
                        vjrojatnostKrizanja = double.Parse(Console.ReadLine());
                        Console.Write("\n Unesite novu vjerojatnost ua mutaciju : ");
                        vjerojatnostMutacije = double.Parse(Console.ReadLine());
                        counter = 0;
                    }
                }
            }
            bool[] ret = null;
            return ret;
        }


        public static bool[] genetskiAlgoritamParalelno(Intracommunicator comm, int MyRank,int brojEmigranata, int velicinaPopulacije, int brojGeneracija, double vjrojatnostKrizanja, double vjerojatnostMutacije, bool rouletteWheel, bool uniformno, List<int> varijable, List<Zagrada> Formula, Dictionary<int, List<Zagrada>> veze_var_zagrada)
        {
            Random rand = new Random();
            double postotak = 0.1;
            int count = 0;
            int PaziOdKudaIdeNova;
            Populacija trenutna = new Populacija(velicinaPopulacije, varijable.Count, varijable, veze_var_zagrada, rand);
            List<Zagrada> mojDioFormule = mojeZagrade(varijable, veze_var_zagrada);
            trenutna.EvaluirajPopulacijuSTezinama(mojDioFormule, varijable, veze_var_zagrada);
            if (trenutna.populacija[0].dobrota == 1) return trenutna.populacija[0].bitovi;
            double[] vjerojatnosti = new double[varijable.Count];
            for (int i = 1; i <= brojGeneracija; i++)
            {
                PaziOdKudaIdeNova = brojEmigranata;
                azurirajVjerojatnosti(vjerojatnosti, varijable, veze_var_zagrada);
                Populacija novaGeneracija = new Populacija(velicinaPopulacije);
                trenutna.KopirajElitu(novaGeneracija, brojEmigranata, vjerojatnosti, varijable, veze_var_zagrada, rand);
                if (count > (int)brojGeneracija * postotak)
                {
                    Console.WriteLine(MyRank);
                    count = 0;
                    postotak += 0.1;
                    PaziOdKudaIdeNova = 2 * brojEmigranata;
                    for (int k = brojEmigranata, l = 0; k < 2 * brojEmigranata ; k++, l++)
                    {
                        if (MyRank == 0)
                        {
                            comm.Send(novaGeneracija.populacija[l].bitovi, 1, 0);
                            comm.Send(novaGeneracija.populacija[l].brojVarijabli, 1, 0);
                            comm.Send(novaGeneracija.populacija[l].brojZadovoljenihZagrada, 1, 0);
                            comm.Send(novaGeneracija.populacija[l].dobrota, 1, 0);

                            bool[] b = new bool[varijable.Count];
                            double fit;
                            int brZagovoljenih, brVar;
                            comm.Receive(comm.Size - 1, 0, ref b);
                            brVar = comm.Receive<int>(comm.Size - 1, 0);
                            brZagovoljenih = comm.Receive<int>(comm.Size - 1, 0);
                            fit = comm.Receive<double>(comm.Size - 1, 0);
                            novaGeneracija.populacija[k] = new Jedinka(b, fit, brZagovoljenih, brVar);
                        }
                        else
                        {
                            bool[] b = new bool[varijable.Count];
                            double fit;
                            int brZagovoljenih, brVar;
                            comm.Receive(MyRank - 1, 0, ref b);
                            brVar = comm.Receive<int>(MyRank - 1, 0);
                            brZagovoljenih = comm.Receive<int>(MyRank - 1, 0);
                            fit = comm.Receive<double>(MyRank - 1, 0);
                            novaGeneracija.populacija[k] = new Jedinka(b, fit, brZagovoljenih, brVar);

                            comm.Send(novaGeneracija.populacija[l].bitovi, (MyRank + 1) % comm.Size, 0);
                            comm.Send(novaGeneracija.populacija[l].brojVarijabli, (MyRank + 1) % comm.Size, 0);
                            comm.Send(novaGeneracija.populacija[l].brojZadovoljenihZagrada, (MyRank + 1) % comm.Size, 0);
                            comm.Send(novaGeneracija.populacija[l].dobrota, (MyRank + 1) % comm.Size, 0);
                        }
                    }
                    if (MyRank == 1) Console.WriteLine("Sad sam razmijenio podatke");
                }
                count++;
                for (int j = PaziOdKudaIdeNova ; j < velicinaPopulacije; j += 2)
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
                novaGeneracija.EvaluirajPopulacijuSTezinama(mojDioFormule, varijable, veze_var_zagrada);
                trenutna = novaGeneracija;
                if (MyRank == 1) Console.WriteLine(trenutna.VratiNajboljuDobrotu());
                if (trenutna.populacija[0].dobrota == 1) return trenutna.populacija[0].bitovi;
            }
            bool[] ret = null;
            return ret;
        }
    }
}
