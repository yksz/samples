using System.ComponentModel;
using System.Configuration.Install;
using System.ServiceProcess;

namespace WinService
{
    [RunInstaller(true)]
    public class HelloServiceInstaller : Installer
    {
        public HelloServiceInstaller()
        {
            var processInstaller = new ServiceProcessInstaller
            {
                Account = ServiceAccount.LocalSystem,
            };
            var serviceInstaller = new ServiceInstaller
            {
                ServiceName = Config.ServiceName,
                StartType = ServiceStartMode.Automatic,
            };
            this.Installers.Add(processInstaller);
            this.Installers.Add(serviceInstaller);
        }
    }
}
