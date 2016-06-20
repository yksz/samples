using System.Collections.Generic;
using uPLibrary.Networking.M2Mqtt.Messages;

namespace Mqtt
{
    static class QoS
    {
        private static readonly Dictionary<string, byte> QosLevels = new Dictionary<string, byte>();

        static QoS()
        {
            QosLevels.Add(Topic.Hello, MqttMsgBase.QOS_LEVEL_EXACTLY_ONCE);
            QosLevels.Add(Topic.Goodbye, MqttMsgBase.QOS_LEVEL_EXACTLY_ONCE);
        }

        public static byte Get(string topic)
        {
            return QosLevels[topic];
        }
    }
}
