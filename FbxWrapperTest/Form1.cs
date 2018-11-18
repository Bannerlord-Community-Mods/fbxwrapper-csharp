using System;
using System.Diagnostics;
using System.Windows.Forms;

using FbxWrapper;

namespace FbxWrapperTest
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void openfbxToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Manager manager = new Manager();

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                Debug.WriteLine("Open file : " + openFileDialog.FileName);

                
            }
        }
    }
}
