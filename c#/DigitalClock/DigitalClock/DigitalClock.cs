using System;
using System.Windows.Forms;

namespace DigitalClock
{
    public partial class DigitalClock : Form
    {
        const int Interval = 1000;
        System.Windows.Forms.Timer timer;

        public DigitalClock()
        {
            InitializeComponent();

            UpdateTimeLabel();

            timer = new System.Windows.Forms.Timer();
            timer.Interval = Interval;
            timer.Tick += (sender, e) =>
            {
                UpdateTimeLabel();
            };
            timer.Start();
        }

        void UpdateTimeLabel()
        {
            DateTime time = DateTime.Now;
            timeLabel.Text = time.ToString("HH:mm.ss");
        }
    }
}
