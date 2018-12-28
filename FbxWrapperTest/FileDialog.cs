
using System;
using System.Diagnostics;
using System.Windows.Forms;

namespace FbxWrapperTest
{
    [Flags]
    public enum DialogFileFormat
    {
        Empty = 0,
        FBX_binary = 1,
        FBX_text = 2,
        OBJ = 4
    }

    public static class MyFileDialog
    {
        const string FbxBinString = "Autodesk Fbx(*.fbx)|*.fbx";
        const string FbxTxtString = "Autodesk ASCII Fbx(*.fbx)|*.fbx";
        const string ObjString = "Wavefront Obj(*.obj)| *.obj";

        static string GetFilterString(DialogFileFormat filterflag)
        {
            if (filterflag == DialogFileFormat.Empty) return null;
            string str = null;
            if (filterflag.HasFlag(DialogFileFormat.FBX_binary)) str += string.Format("{0}{1}", str != null ? "|" : "", FbxBinString);
            if (filterflag.HasFlag(DialogFileFormat.FBX_text)) str += string.Format("{0}{1}", str != null ? "|" : "", FbxTxtString);
            if (filterflag.HasFlag(DialogFileFormat.OBJ)) str += string.Format("{0}{1}", str != null ? "|" : "", ObjString);
            return str;
        }

        public static string GetOpenFileName(DialogFileFormat filterflag)
        {
            using (OpenFileDialog opendialog = new OpenFileDialog())
            {
                opendialog.Filter = GetFilterString(filterflag);
                opendialog.RestoreDirectory = true;
                opendialog.Title = "Open 3d file format";

                if (opendialog.ShowDialog() == DialogResult.OK)
                {
                    Debug.WriteLine("Open file : " + opendialog.FileName);
                    return opendialog.FileName;
                }
                return null;
            }
        }
        public static string GetSaveFileName(DialogFileFormat filterflag, out int filterIndex)
        {
            filterIndex = 0;
            using (SaveFileDialog savedialog = new SaveFileDialog())
            {
                string filter = GetFilterString(filterflag);
                savedialog.Filter = filter;
                savedialog.RestoreDirectory = true;
                savedialog.Title = "Save 3d file format";

                if (savedialog.ShowDialog() == DialogResult.OK)
                {
                    Debug.WriteLine("Save file : " + savedialog.FileName);
                    filterIndex = savedialog.FilterIndex;
                    return savedialog.FileName;
                }
                return null;
            }
        }
    }
}
