using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BoL_Dev_Studio
{
    public partial class NewProject : Form
    {
        public NewProject()
        {
            InitializeComponent();
        }


        public string textbox1value
        {
            get { return textBox1.Text; }
            set { textBox1.Text = value; }
        }

        public string textbox2value
        {
            get { return textBox2.Text; }
            set { textBox2.Text = value; }
        }

        public string textbox3value
        {
            get { return textBox3.Text; }
            set { textBox3.Text = value; }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
