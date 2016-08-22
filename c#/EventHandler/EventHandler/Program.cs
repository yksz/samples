using System;
using System.Linq;
using System.Threading;

namespace EventHandler
{
    class Program
    {
        private const int NumTasks = 10;
        private static readonly CountdownEvent _countdown = new CountdownEvent(NumTasks);

        public static void Main(string[] args)
        {
            IExecutor executor = new Executor();
            executor.TaskCompleted += Completed;
            foreach (int i in Enumerable.Range(1, NumTasks))
            {
                executor.ExecuteAsync(i);
            }
            _countdown.Wait();
            Environment.Exit(0);
        }

        private static void Completed(int id)
        {
            Console.WriteLine("Completed: id=" + id);
            _countdown.Signal();
        }
    }
}
