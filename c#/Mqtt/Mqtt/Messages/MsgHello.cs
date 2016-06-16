using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Mqtt.Messages
{
    public class MsgHello
    {
        public string Name { get; set; }
        public DateTime Date { get; set; }

        public override string ToString()
        {
            var builder = new StringBuilder();
            builder.Append("MsgHello{");
            builder.Append("Name=").Append(Name);
            builder.Append(", Date=").Append(Date);
            builder.Append("}");
            return builder.ToString();
        }
    }
}
