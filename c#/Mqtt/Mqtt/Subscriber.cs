using System;
using System.Collections.Generic;
using System.Text;
using uPLibrary.Networking.M2Mqtt;

namespace Mqtt
{
    public class Subscriber
    {
        private readonly MqttClient _client;
        private readonly string _clientId;
        private readonly Dictionary<string, OnMessage> _handlers = new Dictionary<string, OnMessage>();

        public Subscriber(string hostName, int port)
        {
            _client = new MqttClient(hostName, port, false, null, null, MqttSslProtocols.None);
            _clientId = Guid.NewGuid().ToString();
            _client.Connect(_clientId);
            _client.MqttMsgPublishReceived += (sender, e) =>
            {
                if (_handlers.ContainsKey(e.Topic))
                {
                    var handler = _handlers[e.Topic];
                    var jsonStr = Encoding.UTF8.GetString(e.Message);
                    handler(e.Topic, jsonStr);
                } 
            };
        }

        ~Subscriber()
        {
            _client.Disconnect();
        }

        public delegate void OnMessage(string topic, string message);

        public void Subscribe(string topic, OnMessage handler)
        {
            _handlers.Add(topic, handler);
            _client.Subscribe(new string[] { topic }, new byte[] { QoS.Get(topic) });
        }
    }
}
