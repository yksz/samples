using System;
using System.Windows.Forms;

namespace DigitalClock
{
    public partial class DigitalClock : Form
    {
        const int Interval = 1000;
        System.Windows.Forms.Timer _timer;

        public DigitalClock()
        {
            InitializeComponent();

            UpdateTimeLabel();

            _timer = new System.Windows.Forms.Timer();
            _timer.Interval = Interval;
            _timer.Tick += (sender, e) =>
            {
                UpdateTimeLabel();
            };
            _timer.Start();
        }

        void UpdateTimeLabel()
        {
            DateTime time = DateTime.Now;
            timeLabel.Text = time.ToString("HH:mm.ss");
        }
    }
}
