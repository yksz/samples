using System;
using System.Collections.Generic;
using System.Text;
using uPLibrary.Networking.M2Mqtt;

namespace Mqtt
{
    public class Subscriber
    {
        private readonly MqttClient Client;
        private readonly string ClientId;
        private readonly Dictionary<string, OnMessage> Handlers = new Dictionary<string, OnMessage>();

        public Subscriber(string hostName, int port)
        {
            Client = new MqttClient(hostName, port, false, null, null, MqttSslProtocols.None);
            ClientId = Guid.NewGuid().ToString();
            Client.Connect(ClientId);
            Client.MqttMsgPublishReceived += (sender, e) =>
            {
                if (Handlers.ContainsKey(e.Topic))
                {
                    var handler = Handlers[e.Topic];
                    var jsonStr = Encoding.UTF8.GetString(e.Message);
                    handler(e.Topic, jsonStr);
                } 
            };
        }

        ~Subscriber()
        {
            Client.Disconnect();
        }

        public delegate void OnMessage(string topic, string message);

        public void Subscribe(string topic, OnMessage onMessage)
        {
            Handlers.Add(topic, onMessage);
            Client.Subscribe(new string[] { topic }, new byte[] { QoS.Get(topic) });
        }
    }
}
