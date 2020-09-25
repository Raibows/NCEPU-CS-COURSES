using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Form3 : Form
    {
        public Form3()
        {
            InitializeComponent();
        }

        private void Form3_Load(object sender, EventArgs e)
        {

        }

      
        private void button2_Click(object sender, EventArgs e)
        {
            Form4 a = new Form4();
            a.Show(this);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Form5 a = new Form5();
            a.Show(this);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Form6 a = new Form6();
            a.Show(this);
        }


    }
}
