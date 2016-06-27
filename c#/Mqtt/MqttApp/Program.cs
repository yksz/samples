using Mqtt;
using Mqtt.Messages;
using Newtonsoft.Json;
using NLog;
using System;
using System.Threading;

namespace MqttApp
{
    public class Program
    {
        const string MqttBrokerAddress = "127.0.0.1";
        const int MqttBrokerPort = 1883;

        private static Logger _log = LogManager.GetCurrentClassLogger();

        private static void Run()
        {
            using (var countdown = new CountdownEvent(2))
            {
                var subscriber = new Subscriber(MqttBrokerAddress, MqttBrokerPort);
                subscriber.Subscribe(Topic.Hello, Topic.Goodbye);
                subscriber.OnMessage += (topic, payload) =>
                {
                    if (topic == Topic.Hello)
                    {
                        var msg = JsonConvert.DeserializeObject<HelloMessage>(payload);
                        _log.Info("Topic: " + topic);
                        _log.Info("Message: " + msg);
                        countdown.Signal();
                    }
                    else if (topic == Topic.Goodbye)
                    {
                        var msg = JsonConvert.DeserializeObject<GoodbyeMessage>(payload);
                        _log.Info("Topic: " + topic);
                        _log.Info("Message: " + msg);
                        countdown.Signal();
                    }
                };

                var publisher = new Publisher(MqttBrokerAddress, MqttBrokerPort);
                publisher.Publish(Topic.Hello, new HelloMessage() { Name = "John Smith", Date = DateTime.Now });
                publisher.Publish(Topic.Goodbye, new GoodbyeMessage() { Name = "Jane Smith", Date = DateTime.Now });
                countdown.Wait();
            }
        }

        public static void Main(string[] args)
        {
            try
            {
                Run();
                Environment.Exit(0);
            }
            catch (Exception e)
            {
                _log.Error(e);
                Environment.Exit(1);
            }
        }
    }
}
