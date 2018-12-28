using System;
using System.Diagnostics;
using System.Windows.Forms;

using FbxWrapper;
using CommonLib;

using MyVector3 = CommonLib.Maths.Vector3;
using MyPolygon = CommonLib.Wavefront.Polygon;

using System.Collections.Generic;

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
            int index;
            string path = MyFileDialog.GetSaveFileName(DialogFileFormat.FBX_binary | DialogFileFormat.FBX_text, out index);
            if (string.IsNullOrEmpty(path)) return;

            try
            {
                //FileFormat.Null = -1 for autodetect by exporter
                FileFormat format = index == 1 ? FileFormat.Null : FileFormat.FbxAscii;
                Scene.Export(scene, path, format);
            }
            catch (Exception exc)
            {
                Debug.WriteLine(exc.ToString());
            }
        }

        private void openfbxToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string path = MyFileDialog.GetOpenFileName(DialogFileFormat.FBX_binary);
            if (string.IsNullOrEmpty(path)) return;

            try
            {
                scene = Scene.Import(path);
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

        private void convertobjTofbxToolStripMenuItem_Click(object sender, EventArgs e)
        {

            string path = MyFileDialog.GetOpenFileName(DialogFileFormat.OBJ);
            if (string.IsNullOrEmpty(path)) return;

            CommonLib.Wavefront.WavefrontObj obj = new CommonLib.Wavefront.WavefrontObj();
            if (!obj.Load(path)) return;

            //
            // https://download.autodesk.com/us/fbx/20112/fbx_sdk_help/index.html?url=WS73099cc142f487551fea285e1221e4f9ff8-7f5b.htm,topicNumber=d0e4543
            //
            scene = new Scene();
            Node rootnode = scene.RootNode;

            Node meshnode = new Node(AttributeType.eMesh, "Wavefront_obj_mesh");
            rootnode.AddChild(meshnode);

            Mesh mesh = meshnode.Mesh;
            mesh.ControlPointsCount = obj.vertices.Count;

            for (int i=0;i< obj.vertices.Count;i++)
            {
                MyVector3 v = obj.vertices[i];
                mesh.SetControlPointAt(v.x, v.y, v.z, 0, i);
            }

            var polygons = obj.groups[0].Polygons;

            for (int i=0;i< polygons.Count;i++)
            {
                MyPolygon p = polygons[i];
                mesh.AddPolygon(p.GetVerticesArray());
            }

            Debug.WriteLine("OK");

            savefbxToolStripMenuItem.Enabled = true;
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
