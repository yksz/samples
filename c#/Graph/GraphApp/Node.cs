using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GraphApp
{
    class Node : IComparable<Node>
    {
        public int X { get; set; }
        public int Y { get; set; }

        public Node(System.Drawing.Point p)
        {
            X = p.X;
            Y = p.Y;
        }

        public System.Drawing.Point ToPoint()
        {
            return new System.Drawing.Point(X, Y);
        }

        public double GetDistance(Node other)
        {
            return Math.Sqrt(Math.Pow(this.X - other.X, 2) + Math.Pow(this.Y - other.Y, 2));
        }

        public int CompareTo(Node other)
        {
            if (this.X < other.X)
            {
                return -1;
            }
            else if (this.X == other.X)
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }

        public override int GetHashCode()
        {
            long bits = X;
            bits ^= Y * 31;
            return (((int)bits) ^ ((int)(bits >> 32)));
        }

        public override bool Equals(Object obj)
        {
            if (obj is Node)
            {
                var other = (Node)obj;
                return (this.X == other.X) && (this.Y == other.Y);
            }
            return false;
        }
    }
}
