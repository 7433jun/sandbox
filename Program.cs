using System;

namespace Test
{
    public class Program
    {

        static void Print<T>(params T[] args)
        {
            foreach(var e in args)
            {
                Console.WriteLine(e);
            }
        }

        static void Main(string[] args)
        {
            Program program = new Program();
            Program.Print(1, 'a', 3.14);
        }
    }
}