using System;
using System.Diagnostics;
using System.Windows.Forms;

using FbxWrapper;

namespace FbxWrapperTest
{
    public partial class Form1 : Form
    {
        Scene scene;

        public Form1()
        {
            InitializeComponent();
            savefbxToolStripMenuItem.Enabled = false;
            scene = null;
        }

        private void savefbxToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (scene == null) return;

            using (SaveFileDialog savedialog = new SaveFileDialog())
            {
                savedialog.DefaultExt = "fbx";
                savedialog.Filter = "Autodesk Fbx (*.fbx)|*.fbx| ASCII Fbx (*.fbx)|*.fbx";
                savedialog.RestoreDirectory = true;
                savedialog.Title = "Save fbx file";

                if (savedialog.ShowDialog()== DialogResult.OK)
                {
                    Debug.WriteLine("Save file : " + savedialog.FileName);

                    try
                    {
                        //FileFormat.Null = -1 for autodetect by exporter
                        FileFormat format = savedialog.FilterIndex == 1 ? FileFormat.Null : FileFormat.FbxAscii;
                        Scene.Export(scene, savedialog.FileName, format);
                    }
                    catch(Exception exc)
                    {
                        Debug.WriteLine(exc.ToString());
                    }
                }
            }
        }

        private void openfbxToolStripMenuItem_Click(object sender, EventArgs e)
        {
            using (OpenFileDialog opendialog = new OpenFileDialog())
            {
                opendialog.DefaultExt = "fbx";
                opendialog.Filter = "Autodesk Fbx (*.fbx)|*.fbx";
                opendialog.RestoreDirectory = true;
                opendialog.Title = "Open fbx file";

                if (opendialog.ShowDialog() == DialogResult.OK)
                {
                    Debug.WriteLine("Open file : " + opendialog.FileName);

                    try
                    {
                        scene = Scene.Import(opendialog.FileName);

                        Version version = scene.FileVersion;

                        Debug.WriteLine(scene.FileVersion);

                        Node root = scene.RootNode;
                        treeView1.Nodes.Clear();
                        treeView1.Nodes.Add(GetTreeNodeRecursive(root));
                        treeView1.ExpandAll();
                        savefbxToolStripMenuItem.Enabled = true;
                    }
                    catch (Exception exc)
                    {
                        Debug.WriteLine(exc.ToString());
                    }
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
                    UnpackMesh(viewNode, node);
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

        public void UnpackMesh(TreeNode header, Node node)
        {
            Mesh staticmesh = node.Mesh;

            Debug.WriteLine("triangulated : " + staticmesh.Triangulated);

            header.Nodes.Add(string.Format("Pos : {0}", node.Position.ToString()));
            header.Nodes.Add(string.Format("Scale : {0}", node.Scale.ToString()));
            header.Nodes.Add(string.Format("Rot : {0}", node.Rotation.ToString()));


            TreeNode vertexnode = new TreeNode("vertices");
            TreeNode normalnode = new TreeNode("normals");
            TreeNode polygonode = new TreeNode("indices");
            TreeNode textcoordnode = new TreeNode("textcoord");

            Vector3[] vertices = staticmesh.Vertices;
            foreach (Vector3 v in vertices) vertexnode.Nodes.Add(v.ToString());

            Vector2[] textcoord = staticmesh.TextureCoords;
            foreach (Vector2 v in textcoord) textcoordnode.Nodes.Add(v.ToString());

            Vector3[] normals = staticmesh.Normals;
            foreach (Vector3 v in normals) normalnode.Nodes.Add(v.ToString());

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
