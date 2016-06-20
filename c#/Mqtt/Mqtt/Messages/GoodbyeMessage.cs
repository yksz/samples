using System;
using System.Text;

namespace Mqtt.Messages
{
    public class GoodbyeMessage : IMqttMessage
    {
        public string Name { get; set; }
        public DateTime Date { get; set; }

        public override string ToString()
        {
            var builder = new StringBuilder();
            builder.Append("GoodbyeMessage{");
            builder.Append("Name=").Append(Name);
            builder.Append(", Date=").Append(Date);
            builder.Append("}");
            return builder.ToString();
        }
    }
}
