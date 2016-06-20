using Mqtt;
using Mqtt.Messages;
using Newtonsoft.Json;
using System;
using System.Threading;

namespace MqttApp
{
    class Program
    {
        const string MqttBrokerAddress = "127.0.0.1";
        const int MqttBrokerPort = 1883;

        static void Main(string[] args)
        {
            using (var countdown = new CountdownEvent(2))
            {
                var subscriber = new Subscriber(MqttBrokerAddress, MqttBrokerPort);
                subscriber.Subscribe(Topic.Hello, (topic, msgStr) =>
                {
                    var msg = JsonConvert.DeserializeObject<HelloMessage>(msgStr);
                    Console.WriteLine("Topic: " + topic);
                    Console.WriteLine("Message: " + msg);
                    countdown.Signal();
                });
                subscriber.Subscribe(Topic.Goodbye, (topic, msgStr) =>
                {
                    var msg = JsonConvert.DeserializeObject<GoodbyeMessage>(msgStr);
                    Console.WriteLine("Topic: " + topic);
                    Console.WriteLine("Message: " + msg);
                    countdown.Signal();
                });

                var publisher = new Publisher(MqttBrokerAddress, MqttBrokerPort);
                publisher.Publish(Topic.Hello, new HelloMessage() { Name = "John Smith", Date = DateTime.Now });
                publisher.Publish(Topic.Goodbye, new GoodbyeMessage() { Name = "Jane Smith", Date = DateTime.Now });
                countdown.Wait();
            }
            Environment.Exit(0);
        }
    }
}
