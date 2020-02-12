
using System;
using System.Diagnostics;
using System.Windows.Forms;

namespace FbxWrapperTest
{

    public static class MyFileDialog
    {
        public static string GetOpenFileName(string filter)
        {
            int selected;
            return GetOpenFileName(filter, out selected);
        }

        public static string GetOpenFileName(string filter, out int selected)
        {
            selected = 0;
            using (OpenFileDialog opendialog = new OpenFileDialog())
            {
                opendialog.Filter = filter;
                opendialog.RestoreDirectory = true;
                opendialog.Title = "Open 3d file format";

                if (opendialog.ShowDialog() == DialogResult.OK)
                {
                    Debug.WriteLine("Open file : " + opendialog.FileName);
                    selected = opendialog.FilterIndex;
                    return opendialog.FileName;
                }
                return null;
            }
        }
        public static string GetSaveFileName(string filter, out int selected)
        {
            selected = 0;
            using (SaveFileDialog savedialog = new SaveFileDialog())
            {
                savedialog.Filter = filter;
                savedialog.RestoreDirectory = true;
                savedialog.Title = "Save 3d file format";

                if (savedialog.ShowDialog() == DialogResult.OK)
                {
                    Debug.WriteLine("Save file : " + savedialog.FileName);
                    selected = savedialog.FilterIndex;
                    return savedialog.FileName;
                }
                return null;
            }
        }
    }
}
