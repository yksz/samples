using Mqtt.Messages;
using Newtonsoft.Json;
using System;
using System.Text;
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

        public void Publish<T>(string topic, T msg) where T : IMqttMessage
        {
            var jsonStr = JsonConvert.SerializeObject(msg);
            Client.Publish(topic, Encoding.UTF8.GetBytes(jsonStr));
        }
    }
}
