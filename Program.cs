using System;
using System.Text;

namespace Test
{
    public class Program
    {
        public static void Main(string[] args)
        {
            StringBuilder sb = new StringBuilder();

            int T = int.Parse(Console.ReadLine());

            for (int i = 0; i < T; i++)
            {
                int k = int.Parse(Console.ReadLine());
                int n = int.Parse(Console.ReadLine());

                sb.AppendLine($"{FuncClass.Function(k, n)}");
            }

            Console.WriteLine(sb);
        }
    }

    public class FuncClass
    {
        static public int Function(int k, int n)
        {
            if (k == 0)
                return n;

            if (n == 1)
                return 1;

            return Function(k - 1, n) + Function(k, n - 1);
        }
    }


}