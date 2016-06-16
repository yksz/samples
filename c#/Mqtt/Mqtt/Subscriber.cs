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
    public class Subscriber
    {
        private readonly MqttClient Client;
        private readonly string ClientId;

        public Subscriber(string hostName, int port)
        {
            Client = new MqttClient(hostName, port, false, null, null, MqttSslProtocols.None);
            ClientId = Guid.NewGuid().ToString();
            Client.Connect(ClientId);
        }

        ~Subscriber()
        {
            Client.Disconnect();
        }

        public delegate void OnMessage<T>(T message, string topic) where T : class;

        private MqttClient.MqttMsgPublishEventHandler CreateHandler<T>(OnMessage<T> onMessage) where T : class
        {
            return (sender, e) =>
            {
                var jsonStr = Encoding.UTF8.GetString(e.Message);
                var msg = JsonConvert.DeserializeObject<T>(jsonStr);
                onMessage(msg, e.Topic);
            };
        }

        public void SubscribeHello(OnMessage<MsgHello> onMessage)
        {
            Client.MqttMsgPublishReceived += CreateHandler<MsgHello>(onMessage);
            Client.Subscribe(new string[] { Topic.Hello }, new byte[] { QoS.Get(Topic.Hello) });
        }
    }
}
