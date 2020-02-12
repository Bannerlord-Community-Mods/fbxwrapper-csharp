using System;
using System.Windows.Forms;
using System.IO;

namespace FbxWrapperTest
{
    static class Program
    {
        /// <summary>
        /// Punto di ingresso principale dell'applicazione.
        /// </summary>
        [STAThread]
        static void Main()
        {
            string necessarydll = Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location);
            necessarydll = Path.Combine(necessarydll, "libfbxsdk.dll");

            System.Diagnostics.Debug.Assert(File.Exists(necessarydll), "Require libfbxsdk.dll in the same location");

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
    }
}
