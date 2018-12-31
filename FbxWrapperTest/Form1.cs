using System;
using System.Diagnostics;
using System.Windows.Forms;
using System.Collections.Generic;

using FbxWrapper;
using Polygon = CommonLib.Wavefront.Polygon;
using Vector3 = CommonLib.Maths.Vector3;


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
            }
            catch (Exception exc)
            {
                Debug.WriteLine(exc.ToString());
            }

        }

        private void convertobjTofbxToolStripMenuItem_Click(object sender, EventArgs e)
        {

            string path = MyFileDialog.GetOpenFileName("Wavefront Obj (*.obj)|*.obj");
            if (string.IsNullOrEmpty(path)) return;

            CommonLib.Wavefront.WavefrontObj obj = new CommonLib.Wavefront.WavefrontObj();
            if (!obj.Load(path)) return;

            //
            // https://download.autodesk.com/us/fbx/20112/fbx_sdk_help/index.html?url=WS73099cc142f487551fea285e1221e4f9ff8-7f5b.htm,topicNumber=d0e4543
            //
            scene = new Scene(null);
            Node rootnode = scene.RootNode;

            Node meshnode = new Node(AttributeType.eMesh, "Wavefront_obj_mesh");
            rootnode.AddChild(meshnode);

            Mesh mesh = meshnode.Mesh;
            mesh.ControlPointsCount = obj.vertices.Count;

            for (int i = 0; i < obj.vertices.Count; i++)
            {
                Vector3 v = obj.vertices[i];
                mesh.SetControlPointAt(i, v.x, v.y, v.z, 0);

                Vector3 V = new Vector3();
                float w = 0;
                mesh.GetControlPointAt(i, ref V.x, ref V.y, ref V.z, ref w);

            }

            var polygons = obj.groups[0].Polygons;

            for (int i=0;i< polygons.Count;i++)
            {
                Polygon p = polygons[i];
                mesh.AddPolygon(p.GetVerticesArray());
            }

            Debug.WriteLine("OK");

            ExportStripMenuItem.Enabled = true;
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

            int vcount = staticmesh.ControlPointsCount;
            for (int i=0;i<vcount;i++)
            {
                CommonLib.Maths.Vector4 v = new CommonLib.Maths.Vector4();
                staticmesh.GetControlPointAt(i, ref v.x, ref v.y, ref v.z, ref v.w);
                vertexnode.Nodes.Add(v.ToString());
            }
            header.Nodes.Add(vertexnode);

            /*
            Vector2[] textcoord = staticmesh.TextureCoords;
            foreach (Vector2 v in textcoord) textcoordnode.Nodes.Add(v.ToString());

            Vector3[] normals = staticmesh.Normals;
            foreach (Vector3 v in normals) normalnode.Nodes.Add(v.ToString());

            Polygon[] indices = staticmesh.Polygons;
            foreach (Polygon t in indices) polygonode.Nodes.Add(PolygonToString(t));
            */

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
    }
}
