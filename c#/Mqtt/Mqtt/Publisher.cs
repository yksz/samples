using Mqtt.Messages;
using Newtonsoft.Json;
using System;
using System.Text;
using uPLibrary.Networking.M2Mqtt;

namespace Mqtt
{
    public class Publisher
    {
        private readonly MqttClient _client;
        private readonly string _clientId;

        public Publisher(string hostName, int port)
        {
            _client = new MqttClient(hostName, port, false, null, null, MqttSslProtocols.None);
            _clientId = Guid.NewGuid().ToString();
            _client.Connect(_clientId);
        }

        ~Publisher()
        {
            if (_client.IsConnected)
            {
                _client.Disconnect();
            }
        }

        public void Publish<T>(string topic, T msg) where T : IMqttMessage
        {
            var jsonStr = JsonConvert.SerializeObject(msg);
            _client.Publish(topic, Encoding.UTF8.GetBytes(jsonStr));
        }
    }
}
