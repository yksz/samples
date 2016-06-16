using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using uPLibrary.Networking.M2Mqtt.Messages;

namespace Mqtt
{
    static class QoS
    {
        private static Dictionary<string, byte> QosLevels = new Dictionary<string, byte>();

        static QoS()
        {
            QosLevels.Add(Topic.Hello, MqttMsgBase.QOS_LEVEL_EXACTLY_ONCE);
        }

        public static byte Get(string topic)
        {
            return QosLevels[topic];
        }
    }
}
