using Mqtt;
using Mqtt.Messages;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace MqttApp
{
    class Program
    {
        const string MqttBrokerAddress = "127.0.0.1";
        const int MqttBrokerPort = 1883;

        static void Main(string[] args)
        {
            using (var countdown = new CountdownEvent(1))
            {
                var subscriber = new Subscriber(MqttBrokerAddress, MqttBrokerPort);
                subscriber.SubscribeHello((msg, topic) =>
                {
                    Console.WriteLine("Topic: " + topic);
                    Console.WriteLine("Message: " + msg);
                    countdown.Signal();
                });

                var publisher = new Publisher(MqttBrokerAddress, MqttBrokerPort);
                var hello = new MsgHello() { Name = "John", Date = DateTime.Now };
                publisher.PublishHello(hello);
                countdown.Wait();
            }
            Environment.Exit(0);
        }
    }
}
