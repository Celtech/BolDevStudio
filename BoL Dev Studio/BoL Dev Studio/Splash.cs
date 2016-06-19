using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BoL_Dev_Studio
{
    public partial class Splash : Form
    {
        public Splash()
        {
            InitializeComponent();
        }

        int count = 0;

        private void Splash_Load(object sender, EventArgs e)
        {
            
        }

        private void end()
        {
            Form1 frm = new Form1();
            frm.Show();
            this.Hide();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            count++;
            if(count >= 5)
            {
                timer1.Stop();
                end();
            }
        }
    }
}
