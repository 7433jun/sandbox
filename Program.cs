using System;
using System.Text;

namespace Test
{
    public class Program
    {
        public static void Main(string[] args)
        {
            StringBuilder sb = new StringBuilder();

            while (true)
            {
                StreamReader sr = new StreamReader(new BufferedStream(Console.OpenStandardInput()));
                string str = sr.ReadLine();

                if (str == "")
                {
                    continue;
                }

                if (str == ".")
                    break;

                char[] array = str.ToArray();

                Stack<char> balance = new Stack<char>();

                foreach (char c in array)
                {
                    if (c == '(' || c == '[')
                        balance.Push(c);

                    if (c == ')')
                    {
                        if (balance.Count == 0)
                        {
                            balance.Push('x');
                        }

                        if (balance.Peek() == '(')
                            balance.Pop();
                    }

                    if (c == ']')
                    {
                        if (balance.Count == 0)
                        {
                            balance.Push('x');
                        }

                        if (balance.Peek() == '[')
                            balance.Pop();
                    }
                }

                if (balance.Count == 0)
                {
                    sb.AppendLine("yes");
                }
                else
                {
                    sb.AppendLine("no");
                }
            }

            Console.WriteLine(sb);
        }
    }
}