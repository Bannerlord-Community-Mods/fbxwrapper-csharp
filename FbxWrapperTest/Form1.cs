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

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                Debug.WriteLine("Open file : " + openFileDialog.FileName);

                try
                {
                    Scene scene = Scene.Import(openFileDialog.FileName);
                    Node root = scene.RootNode;

                    treeView1.Nodes.Clear();
                    treeView1.Nodes.Add(GetTreeNodeRecursive(root));
                    treeView1.ExpandAll();
                }
                catch (Exception exc)
                {
                    Debug.WriteLine(exc.ToString());
                }
            }
        }

        public TreeNode GetTreeNodeRecursive(Node node)
        {
            if (node == null) return null;
            TreeNode viewNode = new TreeNode(node.Name);

            for (int i=0;i<node.GetChildCount();i++)
            {
                Node child = node.GetChild(i);
                TreeNode viewChild = GetTreeNodeRecursive(child);
                if (viewChild!=null) viewNode.Nodes.Add(viewChild);
            }

            return viewNode;
        }
    }
}
