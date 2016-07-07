using System;
using System.Configuration.Install;
using System.Linq;
using System.Reflection;
using System.ServiceProcess;
using System.Text;

namespace WinService
{
    public class HelloService : ServiceBase
    {
        public HelloService()
        {
            this.ServiceName = Config.ServiceName;
            this.CanShutdown = true;
            this.CanStop = true;
            this.AutoLog = true;
        }

        protected override void OnStart(string[] args)
        {
            this.EventLog.WriteEntry(String.Format("Start service: {0}", Config.ServiceName));
        }

        protected override void OnStop()
        {
            this.EventLog.WriteEntry(String.Format("Stop service: {0}", Config.ServiceName));
            this.ExitCode = 0;
        }

        protected override void OnShutdown()
        {
            this.EventLog.WriteEntry(String.Format("Shutdown service: {0}", Config.ServiceName));
        }

        public static void Main(string[] args)
        {
            if (args.Length < 1)
            {
                ServiceBase.Run(new HelloService());
                return;
            }

            switch (args[0])
            {
                case "--help":
                    PrintHelpMessage();
                    break;

                case "--install":
                    if (IsServiceInstalled(Config.ServiceName))
                    {
                        Console.WriteLine("This service is already installed");
                    }
                    else
                    {
                        ManagedInstallerClass.InstallHelper(new string[] { Assembly.GetExecutingAssembly().Location });
                        StartService(Config.ServiceName);
                    }
                    break;

                case "--uninstall":
                    if (IsServiceInstalled(Config.ServiceName))
                    {
                        StopService(Config.ServiceName);
                        ManagedInstallerClass.InstallHelper(new string[] { "/u", Assembly.GetExecutingAssembly().Location });
                    }
                    else
                    {
                        Console.WriteLine("This service is NOT installed");
                    }
                    break;

                default:
                    PrintHelpMessage();
                    break;
            }
        }

        static void PrintHelpMessage()
        {
            var builder = new StringBuilder();
            builder.Append(Assembly.GetExecutingAssembly().GetName().Name);
            builder.AppendLine(" [option]");
            builder.AppendLine("");
            builder.AppendLine("OPTION");
            builder.AppendLine("--help");
            builder.AppendLine("    Print this message");
            builder.AppendLine("--install");
            builder.AppendLine("    Install this service");
            builder.AppendLine("--uninstall");
            builder.AppendLine("    Uninstall this service");
            Console.WriteLine(builder);
        }

        static bool IsServiceInstalled(string name)
        {
            var services = ServiceController.GetServices();
            return services.Any(service => service.ServiceName == name);
        }

        static void StartService(string name)
        {
            using (var service = new ServiceController(name))
            {
                service.Start();
            }
        }

        static void StopService(string name)
        {
            using (var service = new ServiceController(name))
            {
                service.Stop();
            }
        }
    }
}
