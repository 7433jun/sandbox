using System;

namespace Test
{
    class Program
    {
        public static void Main(string[] args)
        {
            int N = int.Parse(Console.ReadLine());

            Man[] mans = new Man[N];

            for (int i = 0; i < N; i++)
            {
                int[] A = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);

                mans[i] = new Man(A[0], A[1]);
            }

            LinkedList<Ranking> rankings = new LinkedList<Ranking>();

            foreach (var man in mans)
            {
                if (rankings.Count == 0)
                {
                    var ranking = new Ranking(1, 1, man.weight, man.height);
                    rankings.AddFirst(ranking);
                    man.rank = 1;
                    man.ranking = ranking; // Man 객체의 ranking을 설정
                    continue;
                }

                bool isCheck = false;
                var node = rankings.First;

                while (node != null)
                {
                    if (man.weight >= node.Value.maxWeight && man.height > node.Value.maxHeight ||
                        man.weight > node.Value.maxWeight && man.height >= node.Value.maxHeight)
                    {
                        rankings.AddBefore(node, new Ranking(node.Value.rank, 1, man.weight, man.height));
                        isCheck = true;
                        break;
                    }
                    else if (man.weight <= node.Value.minWeight && man.height < node.Value.minHeight ||
                             man.weight < node.Value.minWeight && man.height <= node.Value.minHeight)
                    {
                        if (node == rankings.Last)
                        {
                            rankings.AddAfter(node, new Ranking(node.Value.rank + node.Value.count, 1, man.weight, man.height));
                            isCheck = true;
                            break;
                        }
                    }
                    else
                    {
                        man.ranking = node.Value; // Man 객체의 ranking을 설정
                        man.rank = node.Value.rank;
                        node.Value.count++;
                        if (man.weight > node.Value.maxWeight) node.Value.maxWeight = man.weight;
                        if (man.weight < node.Value.minWeight) node.Value.minWeight = man.weight;
                        if (man.height > node.Value.maxHeight) node.Value.maxHeight = man.height;
                        if (man.height < node.Value.minHeight) node.Value.minHeight = man.height;

                        isCheck = true;
                        break;
                    }

                    node = node.Next;
                }

                if (!isCheck)
                {
                    // 맨 끝에 추가되어야 할 때
                    var lastRanking = rankings.Last.Value;
                    rankings.AddAfter(rankings.Find(lastRanking), new Ranking(lastRanking.rank + lastRanking.count, 1, man.weight, man.height));
                    man.rank = lastRanking.rank + lastRanking.count;
                    man.ranking = lastRanking; // Man 객체의 ranking을 설정
                }
            }

            //foreach (var man in mans)
            //{
            //    if(rankings.Count == 0)
            //    {
            //        rankings.AddFirst(new Ranking(1, 1, man.weight, man.height));
            //        man.rank = 1;
            //        continue;
            //    }
            //
            //    bool isCheck = false;
            //
            //    foreach (Ranking ranking in rankings)
            //    {
            //        if (isCheck)
            //        {
            //            ranking.rank++;
            //        }
            //
            //        if (man.weight >= ranking.maxWeight && man.height > ranking.maxHeight || man.weight > ranking.maxWeight && man.height >= ranking.maxHeight)
            //        {
            //            rankings.AddBefore(rankings.Find(ranking), new Ranking(ranking.rank, 1, man.weight, man.height));
            //
            //            isCheck = true;
            //        }
            //        else if (man.weight <= ranking.minWeight && man.height < ranking.minHeight || man.weight < ranking.minWeight && man.height <= ranking.minHeight)
            //        {
            //            if (ranking == rankings.Last())
            //            {
            //                rankings.AddAfter(rankings.Find(ranking), new Ranking(ranking.rank + ranking.count, 1, man.weight, man.height));
            //                man.rank = ranking.rank + ranking.count;
            //                break;
            //            }
            //        }
            //        else
            //        {
            //            man.rank = ranking.rank;
            //            ranking.count++;
            //            if (man.weight > ranking.maxWeight) ranking.maxWeight = man.weight;
            //            if (man.weight < ranking.minWeight) ranking.minWeight = man.weight;
            //            if (man.height > ranking.maxHeight) ranking.maxHeight = man.height;
            //            if (man.height < ranking.minHeight) ranking.minHeight = man.height;
            //
            //            isCheck = true;
            //        }
            //    }
            //}

            foreach (Man man in mans)
            {
                Console.Write(man.rank);
            }
        }
    }

    public class Man
    {
        public int weight;
        public int height;
        public int rank = 0;
        public Ranking ranking; // Ranking을 참조할 변수 추가

        public Man(int w, int h)
        {
            weight = w;
            height = h;
        }
    }

    public class Ranking
    {
        public int rank;
        public int count;
        public int maxWeight;
        public int minWeight;
        public int maxHeight;
        public int minHeight;

        public Ranking(int r, int c, int w, int h)
        {
            rank = r;
            count = c;
            maxWeight = w;
            minWeight = w;
            maxHeight = h;
            minHeight = h;
        }
    }
}