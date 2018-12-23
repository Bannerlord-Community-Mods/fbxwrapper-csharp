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

            NodeAttribute attribute = node.Attribute;

            TreeNode viewNode;

            if (attribute!=null)
            {
                viewNode = new TreeNode(string.Format("{0} {1}", node.Name, attribute.Type.ToString())) ;

                if (attribute.Type == AttributeType.eMesh)
                {
                    UnpackMesh(viewNode, node.Mesh);
                }
            }
            else
            {
                viewNode = new TreeNode(string.Format("{0} {1}", node.Name, "null"));
            }

            for (int i = 0; i < node.GetChildCount(); i++)
            {
                Node child = node.GetChild(i);
                TreeNode viewChild = GetTreeNodeRecursive(child);
                if (viewChild != null) viewNode.Nodes.Add(viewChild);
            }

            return viewNode;
        }

        public void UnpackMesh(TreeNode header, Mesh staticmesh)
        {
            TreeNode vertexnode = new TreeNode("vertices");
            TreeNode normalnode = new TreeNode("normals");
            TreeNode polygonode = new TreeNode("indices");
            TreeNode textcoordnode = new TreeNode("textcoord");


            Vector3[] vertices = staticmesh.Vertices;
            foreach (Vector3 v in vertices) vertexnode.Nodes.Add(v.ToString());

            Polygon[] indices = staticmesh.Polygons;
            foreach (Polygon t in indices) polygonode.Nodes.Add(PolygonToString(t));

            header.Nodes.Add(vertexnode);
            header.Nodes.Add(normalnode);
            header.Nodes.Add(polygonode);
            header.Nodes.Add(textcoordnode);
        }

        public string PolygonToString(Polygon polygon)
        {
            int[] index = polygon.Indices;
            string str = string.Join(",", index);
            return str;
        }
    }
}
