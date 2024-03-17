using System;

namespace Test
{
    public class Program
    {
        public static void Main()
        {
            int N = int.Parse(Console.ReadLine());
            int[] ints = new int[N];

            for (int i = 0; i < N; i++)
            {
                ints[i] = int.Parse(Console.ReadLine());
            }

            double avg = Math.Round((double)ints.Sum() / (double)ints.Count());

            

            Console.WriteLine((int)avg);

            Array.Sort(ints);

            Console.WriteLine(ints[ints.Count() / 2]);

            int[] nums = new int[8001];

            for (int i = 0; i < ints.Count(); i++)
            {
                nums[ints[i] + 4000]++;
            }

            int max = nums.Max();

            List<int> list = new List<int>();

            for (int i = 0; i < nums.Count(); i++)
            {
                if (max == nums[i])
                {
                    list.Add(i - 4000);
                }
            }

            if (list.Count() == 1)
            {
                Console.WriteLine(list[0]);
            }
            else
            {
                Console.WriteLine(list[1]);
            }

            Console.WriteLine(ints[ints.Count() - 1] - ints[0]);
        }
    }
}