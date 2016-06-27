using System;
using System.Text;
using uPLibrary.Networking.M2Mqtt;

namespace Mqtt
{
    public class Subscriber
    {
        public delegate void OnMessageEventHandler(string topic, string payload);

        public event OnMessageEventHandler OnMessage
        {
            add
            {
                _client.MqttMsgPublishReceived += (sender, e) =>
                {
                    var jsonStr = Encoding.UTF8.GetString(e.Message);
                    value(e.Topic, jsonStr);
                };
            }
            remove { }
        }

        private readonly MqttClient _client;
        private readonly string _clientId;

        public Subscriber(string hostName, int port)
        {
            _client = new MqttClient(hostName, port, false, null, null, MqttSslProtocols.None);
            _clientId = Guid.NewGuid().ToString();
            _client.Connect(_clientId);
        }

        ~Subscriber()
        {
            if (_client.IsConnected)
            {
                _client.Disconnect();
            }
        }

        public void Subscribe(params string[] topics)
        {
            foreach (var topic in topics)
            {
                Subscribe(topic, QoS.Get(topic));
            }
        }

        public void Subscribe(string topic, byte qos)
        {
            _client.Subscribe(new string[] { topic }, new byte[] { qos });
        }
    }
}
