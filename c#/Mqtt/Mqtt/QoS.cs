using System.Collections.Generic;
using uPLibrary.Networking.M2Mqtt.Messages;

namespace Mqtt
{
    static class QoS
    {
        private static readonly Dictionary<string, byte> _qosLevels = new Dictionary<string, byte>();

        static QoS()
        {
            _qosLevels.Add(Topic.Hello, MqttMsgBase.QOS_LEVEL_EXACTLY_ONCE);
            _qosLevels.Add(Topic.Goodbye, MqttMsgBase.QOS_LEVEL_EXACTLY_ONCE);
        }

        public static byte Get(string topic)
        {
            return _qosLevels[topic];
        }
    }
}
