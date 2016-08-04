using QuickGraph;
using QuickGraph.Algorithms.Observers;
using QuickGraph.Algorithms.ShortestPath;
using QuickGraph.Serialization;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml;

namespace GraphApp
{
    public partial class GraphForm : Form
    {
        private const int NodeDiameter = 30;
        private const int NodeRadius = NodeDiameter / 2;
        private const int EdgeDiameter = 10;
        private const int EdgeRadius = EdgeDiameter / 2;
        private const int ArrowSize = 10;
        private const string GraphFileName = "graph.graphml";
        private static readonly Brush NodeBrush = Brushes.LightSkyBlue;
        private static readonly Brush SelectedNodeBrush = Brushes.Red;
        private static readonly Brush EdgeBrush = Brushes.Black;
        private static readonly Pen EdgePen = new Pen(Color.Black, 1);
        private static readonly Pen ShortestPathPen = new Pen(Color.Red, 2);

        private AdjacencyGraph<Node, Edge<Node>> _graph = new AdjacencyGraph<Node, Edge<Node>>();
        private Node _selectedNode;
        private IEnumerable<Edge<Node>> _shortestPath;

        public GraphForm()
        {
            InitializeComponent();
        }

        private void GraphForm_KeyDown(object sender, KeyEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.R: // read
                    _graph = ReadGraph(GraphFileName);
                    _selectedNode = null;
                    _shortestPath = null;
                    pictureBox.Refresh();
                    break;

                case Keys.W: // write
                    WriteGraph(GraphFileName, _graph);
                    break;
            }
        }

        private static AdjacencyGraph<Node, Edge<Node>> ReadGraph(string filename)
        {
            var graph = new AdjacencyGraph<Node, Edge<Node>>();
            using (var reader = XmlReader.Create(filename))
            {
                graph.DeserializeFromGraphML(reader,
                        id => new Node(),
                        (source, target, id) => new Edge<Node>(source, target));
            }
            return graph;
        }

        private void WriteGraph(string filename, AdjacencyGraph<Node, Edge<Node>> graph)
        {
            var settings = new XmlWriterSettings
            {
                Indent = true,
                IndentChars = "  ",
            };
            using (var writer = XmlWriter.Create(filename, settings))
            {
                graph.SerializeToGraphML<Node, Edge<Node>, AdjacencyGraph<Node, Edge<Node>>>(writer);
            }
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
        }

        private void MouseRightClick(object sender, MouseEventArgs e)
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
            _shortestPath = path;
            pictureBox.Refresh();
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

        private void pictureBox_MouseUp(object sender, MouseEventArgs e)
        {
            switch (e.Button)
            {
                case MouseButtons.Left:
                    MouseLeftUp(sender, e);
                    break;
            }
        }

        private void MouseLeftUp(object sender, MouseEventArgs e)
        {
            var node = GetNode(e.Location);
            if (node == null) // create node
            {
                var newNode = new Node(e.Location);
                if (_graph.Vertices.Any(v => v.GetDistance(newNode) <= NodeDiameter)) // overlap?
                {
                    return;
                }
                _graph.AddVertex(newNode);
            }
            else // click node
            {
                if (_selectedNode == null)
                {
                    return;
                }
                if (node == _selectedNode) // same node
                {
                    // nothing
                }
                else // other node
                {
                    var edge = new Edge<Node>(_selectedNode, node);
                    _graph.AddEdge(edge);
                }
            }
            _shortestPath = null;
            pictureBox.Refresh();
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

        private IEnumerable<Edge<Node>> FindShortestPath(Node source, Node target)
        {
            Func<Edge<Node>, double> edgeCost = e => e.Source.GetDistance(e.Target);
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
                var source = e.Source.ToPoint();
                var target = e.Target.ToPoint();
                g.DrawLine(EdgePen, source, target);
                DrawArrow(g, source, target);
            }
            if (_shortestPath != null)
            {
                foreach (var e in _shortestPath)
                {
                    g.DrawLine(ShortestPathPen, e.Source.ToPoint(), e.Target.ToPoint());
                }
            }
        }

        private void DrawArrow(Graphics g, Point source, Point target)
        {
            Matrix rotateMatrix = new Matrix();
            rotateMatrix.RotateAt((float)GetDegree(target, source), target);
            g.Transform = rotateMatrix;
            g.FillPolygon(EdgeBrush, new Point[] { target,
                    new Point(target.X + ArrowSize, target.Y + ArrowSize / 2),
                    new Point(target.X + ArrowSize, target.Y - ArrowSize / 2) });
            g.Transform = new Matrix();
        }

        private double GetDegree(Point o, Point p)
        {
            double radian = Math.Atan2(p.Y - o.Y, p.X - o.X);
            return ToDegree(radian);
        }

        private static double ToDegree(double radian)
        {
            return radian * 180 / Math.PI;
        }
    }
}
