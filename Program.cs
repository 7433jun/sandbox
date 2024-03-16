using System;
using System.Collections;
using System.Text;

namespace Test
{
    public class Program
    {
        public static void Main(string[] args)
        {
            int N = int.Parse(Console.ReadLine());
            int[] A = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
            int M = int.Parse(Console.ReadLine());
            int[] B = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);

            
            List<int> listA = A.ToList();
            listA.Sort();

            StringBuilder stringBuilder = new StringBuilder();

            foreach (int num in B)
            {
                if (listA.BinarySearch(num) < 0)
                {
                    stringBuilder.Append("0\n");
                }
                else
                {
                    stringBuilder.Append("1\n");
                }
            }

            Console.WriteLine(stringBuilder);
        }
    }
}