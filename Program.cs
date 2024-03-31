using System;

namespace Test
{
    public class Program
    {

        static void Print<T>(params T[] args)
        {
<<<<<<< HEAD
            string[] s = Console.ReadLine().Split();
            int a = int.Parse(s[0]);
            int b = int.Parse(s[1]);

            // greatest common divisor / least common multiple
            int gcd;
            int lcm;

            int t1 = a, t2 = b;

            if (a > b)
            {
                t1 = a;
                t2 = b;
            }
            else
            {
                t1 = b;
                t2 = a;
            }

            while (true)
            {
                if (t1 % t2 == 0)
                {
                    gcd = t2;
                    break;
                }
                else
                {
                    int t = t1;
                    t1 = t2;
                    t2 = t % t2;
                }
            }

            lcm = a * b / gcd;

            Console.WriteLine(gcd);
            Console.WriteLine(lcm);
=======
            foreach(var e in args)
            {
                Console.WriteLine(e);
            }
        }

        static void Main(string[] args)
        {
            Program program = new Program();
            Program.Print(1, 'a', 3.14);
>>>>>>> 5b97f0bba2c843aac84ed193bb431f14aef8298f
        }
    }
}