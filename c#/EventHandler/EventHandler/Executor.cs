using System.Threading.Tasks;

namespace EventHandler
{
    public class Executor : IExecutor
    {
        public event TaskCompletedEventHandler TaskCompleted = delegate { };

        public void ExecuteAsync(int taskID)
        {
            Task.Run(() =>
            {
                TaskCompleted(taskID);
            });
        }
    }
}
