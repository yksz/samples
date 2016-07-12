using QuickGraph;
using QuickGraph.Algorithms.Observers;
using QuickGraph.Algorithms.ShortestPath;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GraphApp
{
    public partial class GraphForm : Form
    {
        const int NodeDiameter = 30;
        const int NodeRadius = NodeDiameter / 2;
        private static Brush NodeBrush = Brushes.Blue;
        private static Brush SelectedNodeBrush = Brushes.Red;
        private static Pen EdgePen = new Pen(Color.Black, 1);
        private static Pen ShortestPathPen = new Pen(Color.Red, 2);

        private AdjacencyGraph<Node, Edge<Node>> _graph = new AdjacencyGraph<Node, Edge<Node>>();
        private Node _selectedNode;
        private IEnumerable<Edge<Node>> _shortestPath;

        public GraphForm()
        {
            InitializeComponent();
        }

        private Node GetNode(Point p)
        {
            return _graph.Vertices.SingleOrDefault(v => IsPointWithinCircle(p, v.ToPoint(), NodeRadius));
        }

        private static bool IsPointWithinCircle(Point p, Point o, int radius)
        {
            return o.X - radius < p.X && p.X < o.X + radius
                && o.Y - radius < p.Y && p.Y < o.Y + radius;
        }

        private void pictureBox_MouseClick(object sender, MouseEventArgs e)
        {
            switch (e.Button)
            {
                case MouseButtons.Left:
                    MouseLeftClick(sender, e);
                    break;

                case MouseButtons.Right:
                    MouseRightClick(sender, e);
                    break;

                case MouseButtons.Middle:
                    MouseMiddleClick(sender, e);
                    break;
            }
        }

        private void MouseLeftClick(object sender, MouseEventArgs e)
        {
            var node = GetNode(e.Location);
            if (node == null)
            {
                _graph.AddVertex(new Node(e.Location));
                _selectedNode = null;
            }
            else
            {
                _shortestPath = null;
            }
            pictureBox.Refresh();
        }

        private void MouseRightClick(object sender, MouseEventArgs e)
        {
        }

        private void MouseMiddleClick(object sender, MouseEventArgs e)
        {
            _graph.Clear();
            _selectedNode = null;
            _shortestPath = null;
            pictureBox.Refresh();
        }

        private void pictureBox_MouseDown(object sender, MouseEventArgs e)
        {
            switch (e.Button)
            {
                case MouseButtons.Left:
                    MouseLeftDown(sender, e);
                    break;

                case MouseButtons.Right:
                    MouseRightDown(sender, e);
                    break;
            }
        }

        private void MouseLeftDown(object sender, MouseEventArgs e)
        {
            var node = GetNode(e.Location);
            if (node == null)
            {
                return;
            }
            _selectedNode = node;
            pictureBox.Refresh();
        }

        private void MouseRightDown(object sender, MouseEventArgs e)
        {
        }

        private void pictureBox_MouseUp(object sender, MouseEventArgs e)
        {
            switch (e.Button)
            {
                case MouseButtons.Left:
                    MouseLeftUp(sender, e);
                    break;

                case MouseButtons.Right:
                    MouseRightUp(sender, e);
                    break;
            }
        }

        private void MouseLeftUp(object sender, MouseEventArgs e)
        {
            if (_selectedNode == null)
            {
                return;
            }
            var node = GetNode(e.Location);
            if (node == null || node == _selectedNode)
            {
                return;
            }
            var edge = new Edge<Node>(_selectedNode, node);
            _graph.AddEdge(edge);
            _selectedNode = null;
            pictureBox.Refresh();
        }

        private void MouseRightUp(object sender, MouseEventArgs e)
        {
            if (_selectedNode == null)
            {
                return;
            }
            var node = GetNode(e.Location);
            if (node == null)
            {
                return;
            }
            var path = FindShortestPath(_selectedNode, node);
            if (path == null)
            {
                return;
            }
            _shortestPath = path;
            pictureBox.Refresh();
        }

        private IEnumerable<Edge<Node>> FindShortestPath(Node source, Node target)
        {
            Func<Edge<Node>, double> edgeCost = (e) => GetDistance(e.Source, e.Target);
            var dijkstra = new DijkstraShortestPathAlgorithm<Node, Edge<Node>>(_graph, edgeCost);
            var predecessors = new VertexPredecessorRecorderObserver<Node, Edge<Node>>();
            using (predecessors.Attach(dijkstra))
            {
                dijkstra.Compute(source);
            }
            IEnumerable<Edge<Node>> path;
            predecessors.TryGetPath(target, out path);
            return path;
        }

        private static double GetDistance(Node n1, Node n2)
        {
            return Math.Sqrt(Math.Pow(n1.X - n2.X, 2) + Math.Pow(n1.Y - n2.Y, 2));
        }

        private void pictureBox_Paint(object sender, PaintEventArgs e)
        {
            DrawGraph(e.Graphics);
        }

        private void DrawGraph(Graphics g)
        {
            foreach (var v in _graph.Vertices)
            {
                g.FillEllipse(NodeBrush,
                        new Rectangle(v.X - NodeRadius, v.Y - NodeRadius, NodeDiameter, NodeDiameter));
            }
            if (_selectedNode != null)
            {
                g.FillEllipse(SelectedNodeBrush,
                        new Rectangle(_selectedNode.X - NodeRadius, _selectedNode.Y - NodeRadius, NodeDiameter, NodeDiameter));
            }
            foreach (var e in _graph.Edges)
            {
                g.DrawLine(EdgePen, e.Source.ToPoint(), e.Target.ToPoint());
            }
            if (_shortestPath != null)
            {
                foreach (var e in _shortestPath)
                {
                    g.DrawLine(ShortestPathPen, e.Source.ToPoint(), e.Target.ToPoint());
                }
            }
        }
    }
}
