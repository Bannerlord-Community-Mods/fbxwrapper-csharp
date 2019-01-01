using System;
using System.Diagnostics;
using System.Windows.Forms;
using System.Collections.Generic;

using FbxWrapper;
using Polygon = CommonLib.Wavefront.Polygon;
using Vector3 = CommonLib.Maths.Vector3;
using FbxVector3 = FbxWrapper.Vector3;

namespace FbxWrapperTest
{
    public partial class Form1 : Form
    {
        Scene scene;
        List<FileFormat> writers;
        List<FileFormat> readers;

        public Form1()
        {
            InitializeComponent();
            ExportStripMenuItem.Enabled = false;
            scene = null;

            writers = new List<FileFormat>(Manager.GetSupportedWriters());
            readers = new List<FileFormat>(Manager.GetSupportedReaders());

            ReaderBox.Items.Add("Supported Readers :");
            ReaderBox.Items.Add("");
            WriterBox.Items.Add("Supported Writers :");
            WriterBox.Items.Add("");
            foreach (FileFormat info in readers)
            {
                string str = string.Format("{0}|*.{1}", info.Description, info.Extension);
                ReaderBox.Items.Add(str);
            }
            foreach (FileFormat info in writers)
            {
                string str = string.Format("{0}|*.{1}", info.Description, info.Extension);
                WriterBox.Items.Add(str);
            }
        }

        private void ExportStripMenuItem_Click(object sender, EventArgs e)
        {
            if (scene == null) return;

            string filter = "";

            for (int i = 0; i < writers.Count; i++)
            {
                if (i > 0) filter += "|";
                filter += string.Format("{0}|*.{1}", writers[i].Description, writers[i].Extension);
            }

            // fileID is the file format index that match with writers plugin list, can be different for each Sdk version
            int fileID;
            string path = MyFileDialog.GetSaveFileName(filter, out fileID);
            if (string.IsNullOrEmpty(path)) return;

            try
            {
                Scene.Export(scene, path, fileID - 1);
                Debug.WriteLine("OK");
            }
            catch (Exception exc)
            {
                Debug.WriteLine(exc.ToString());
            }
        }

        private void OpenStripMenuItem_Click(object sender, EventArgs e)
        {
            // fileID is the file format index that match with readers plugin list can be different for each Sdk version
            int fileID;
            string filter = "";
            for (int i = 0; i < readers.Count; i++)
            {
                if (i > 0) filter += "|";
                filter += string.Format("{0}|*.{1}", readers[i].Description, readers[i].Extension);
            }

            string path = MyFileDialog.GetOpenFileName(filter, out fileID);
            if (string.IsNullOrEmpty(path)) return;

            try
            {
                scene = Scene.Import(path, -1);
                Version version = scene.FileVersion;
                Debug.WriteLine(scene.FileVersion);
                Node root = scene.RootNode;
                treeView1.Nodes.Clear();
                treeView1.Nodes.Add(GetTreeNodeRecursive(root));
                treeView1.ExpandAll();
                ExportStripMenuItem.Enabled = true;
                Debug.WriteLine("OK");
            }
            catch (Exception exc)
            {
                Debug.WriteLine(exc.ToString());
            }

        }

        private void BuildCustomFbx()
        {
            scene = new Scene(null);
            Node rootnode = scene.RootNode;

            Node meshnode = new Node(AttributeType.Mesh, "");
            rootnode.AddChild(meshnode);

            Mesh mesh = meshnode.Mesh;
            //mesh.SetMappingMode(LayerElementType.Normal, MappingMode.ByControlPoint);

            mesh.ControlPointsCount = 4;

            FbxVector3[] vertices = new FbxVector3[]
            {
                new FbxVector3(0,0,0),
                new FbxVector3(1,0,0),
                new FbxVector3(0,1,0),
                new FbxVector3(1,1,0)
            };
            mesh.ControlPoints = vertices;

            // one square
            //mesh.AddPolygon(new int[] { 0, 1, 3, 2 });
            // triangulated
            mesh.AddPolygon(new int[] { 0, 1, 2 });
            mesh.AddPolygon(new int[] { 2, 1, 3 });


            // i'm using my library
            Vector3 n1 = new Vector3(-1, -1, 0);
            Vector3 n2 = new Vector3(1, -1, 0);
            Vector3 n3 = new Vector3(-1, 1, 0);
            Vector3 n4 = new Vector3(1, 1, 0);
            n1.Normalize();
            n2.Normalize();
            n3.Normalize();
            n4.Normalize();

            // byControlPoint
            //FbxVector3[] normals = new FbxVector3[] { Convert(n1), Convert(n2), Convert(n3), Convert(n4) };
            
            // byPolygon
            FbxVector3[] normals = new FbxVector3[] { Convert(n1), Convert(n4) };

            mesh.SetNormals(normals, MappingMode.ByPolygon, ReferenceMode.Direct);


    
            Manager.SetIOProperty(IOProperty.Exp_FBX_ANIMATION, false);
            Manager.SetIOProperty(IOProperty.Exp_FBX_EMBEDDED, false);
            Manager.SetIOProperty(IOProperty.Exp_FBX_MATERIAL, false);
        }



        public TreeNode GetTreeNodeRecursive(Node node)
        {
            if (node == null) return null;

            NodeAttribute attribute = node.Attribute;

            TreeNode viewNode;

            if (attribute!=null)
            {
                viewNode = new TreeNode(string.Format("{0} {1}", node.Name, attribute.Type.ToString())) ;

                if (attribute.Type == AttributeType.Mesh)
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

            // Write vertices
            TreeNode vertexnode = new TreeNode("vertices");
            int vcount = staticmesh.ControlPointsCount;
            for (int i=0;i<vcount;i++)
            {
                FbxWrapper.Vector3 v = staticmesh.GetControlPointAt(i);
                vertexnode.Nodes.Add(v.ToString());
            }
            header.Nodes.Add(vertexnode);

            // Write normals
            TreeNode normalnode = new TreeNode("normals " + staticmesh.GetMappingMode(LayerElementType.Normal).ToString());
            FbxVector3[] normals = staticmesh.GetNormals();
            foreach (FbxVector3 v in normals) normalnode.Nodes.Add(v.ToString());

            // Write indices
            TreeNode polygonode = new TreeNode("indices");
            var polygons = staticmesh.Polygons;
            foreach (FbxWrapper.Polygon p in polygons) polygonode.Nodes.Add(arraytostring(p.Indices));


            TreeNode textcoordnode = new TreeNode("textcoord");
            header.Nodes.Add(normalnode);
            header.Nodes.Add(polygonode);
            header.Nodes.Add(textcoordnode);
        }

        public string PolygonToString(FbxWrapper.Polygon polygon)
        {
            int[] index = polygon.Indices;
            string str = string.Join(",", index);
            return str;
        }

        private void makeCustomSceneToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BuildCustomFbx();
            treeView1.Nodes.Clear();
            treeView1.Nodes.Add(GetTreeNodeRecursive(scene.RootNode));
            treeView1.ExpandAll();
            ExportStripMenuItem.Enabled = true;
        }

        FbxVector3 Convert(Vector3 v) { return new FbxVector3(v.x, v.y, v.z); }

        string arraytostring(int[] a)
        {
            string str = "";
            foreach (int i in a) str += i + " ";
            return str;
        }
    }
}
