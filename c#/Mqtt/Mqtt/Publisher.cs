using Mqtt.Messages;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using uPLibrary.Networking.M2Mqtt;

namespace Mqtt
{
    public class Publisher
    {
        private readonly MqttClient Client;
        private readonly string ClientId;

        public Publisher(string hostName, int port)
        {
            Client = new MqttClient(hostName, port, false, null, null, MqttSslProtocols.None);
            ClientId = Guid.NewGuid().ToString();
            Client.Connect(ClientId);
        }

        ~Publisher()
        {
            Client.Disconnect();
        }

        public void PublishHello(MsgHello msg)
        {
            var jsonStr = JsonConvert.SerializeObject(msg);
            Client.Publish(Topic.Hello, Encoding.UTF8.GetBytes(jsonStr));
        }
    }
}
