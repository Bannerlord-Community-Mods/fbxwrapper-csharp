namespace FbxWrapperTest
{
    partial class Form1
    {
        /// <summary>
        /// Variabile di progettazione necessaria.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Pulire le risorse in uso.
        /// </summary>
        /// <param name="disposing">ha valore true se le risorse gestite devono essere eliminate, false in caso contrario.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Codice generato da Progettazione Windows Form

        /// <summary>
        /// Metodo necessario per il supporto della finestra di progettazione. Non modificare
        /// il contenuto del metodo con l'editor di codice.
        /// </summary>
        private void InitializeComponent()
        {
            this.treeView1 = new System.Windows.Forms.TreeView();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.openfbxToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.savefbxToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.convertobjTofbxToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // treeView1
            // 
            this.treeView1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.treeView1.Location = new System.Drawing.Point(0, 24);
            this.treeView1.Name = "treeView1";
            this.treeView1.Size = new System.Drawing.Size(706, 322);
            this.treeView1.TabIndex = 2;
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openfbxToolStripMenuItem,
            this.convertobjTofbxToolStripMenuItem,
            this.savefbxToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(706, 24);
            this.menuStrip1.TabIndex = 3;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // openfbxToolStripMenuItem
            // 
            this.openfbxToolStripMenuItem.Name = "openfbxToolStripMenuItem";
            this.openfbxToolStripMenuItem.Size = new System.Drawing.Size(75, 20);
            this.openfbxToolStripMenuItem.Text = "Open *.fbx";
            this.openfbxToolStripMenuItem.Click += new System.EventHandler(this.openfbxToolStripMenuItem_Click);
            // 
            // savefbxToolStripMenuItem
            // 
            this.savefbxToolStripMenuItem.Name = "savefbxToolStripMenuItem";
            this.savefbxToolStripMenuItem.Size = new System.Drawing.Size(70, 20);
            this.savefbxToolStripMenuItem.Text = "Save *.fbx";
            this.savefbxToolStripMenuItem.Click += new System.EventHandler(this.savefbxToolStripMenuItem_Click);
            // 
            // convertobjTofbxToolStripMenuItem
            // 
            this.convertobjTofbxToolStripMenuItem.Name = "convertobjTofbxToolStripMenuItem";
            this.convertobjTofbxToolStripMenuItem.Size = new System.Drawing.Size(76, 20);
            this.convertobjTofbxToolStripMenuItem.Text = "Open *.obj";
            this.convertobjTofbxToolStripMenuItem.Click += new System.EventHandler(this.convertobjTofbxToolStripMenuItem_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(706, 346);
            this.Controls.Add(this.treeView1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Form1";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TreeView treeView1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem openfbxToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem savefbxToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem convertobjTofbxToolStripMenuItem;
    }
}

