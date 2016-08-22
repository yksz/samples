namespace EventHandler
{
    public delegate void TaskCompletedEventHandler(int taskID);

    public interface IExecutor
    {
        event TaskCompletedEventHandler TaskCompleted;

        void ExecuteAsync(int taskID);
    }
}
