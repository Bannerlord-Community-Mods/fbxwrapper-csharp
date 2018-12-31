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
            this.FileStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.OpenStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ExportStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ReaderBox = new System.Windows.Forms.ListBox();
            this.WriterBox = new System.Windows.Forms.ListBox();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // treeView1
            // 
            this.treeView1.Dock = System.Windows.Forms.DockStyle.Left;
            this.treeView1.Location = new System.Drawing.Point(0, 24);
            this.treeView1.Name = "treeView1";
            this.treeView1.Size = new System.Drawing.Size(411, 352);
            this.treeView1.TabIndex = 2;
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.FileStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(714, 24);
            this.menuStrip1.TabIndex = 3;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // FileStripMenuItem
            // 
            this.FileStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.OpenStripMenuItem,
            this.ExportStripMenuItem});
            this.FileStripMenuItem.Name = "FileStripMenuItem";
            this.FileStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.FileStripMenuItem.Text = "File";
            // 
            // OpenStripMenuItem
            // 
            this.OpenStripMenuItem.Name = "OpenStripMenuItem";
            this.OpenStripMenuItem.Size = new System.Drawing.Size(107, 22);
            this.OpenStripMenuItem.Text = "Open";
            this.OpenStripMenuItem.Click += new System.EventHandler(this.OpenStripMenuItem_Click);
            // 
            // ExportStripMenuItem
            // 
            this.ExportStripMenuItem.Name = "ExportStripMenuItem";
            this.ExportStripMenuItem.Size = new System.Drawing.Size(107, 22);
            this.ExportStripMenuItem.Text = "Export";
            this.ExportStripMenuItem.Click += new System.EventHandler(this.ExportStripMenuItem_Click);
            // 
            // ReaderBox
            // 
            this.ReaderBox.Dock = System.Windows.Forms.DockStyle.Left;
            this.ReaderBox.FormattingEnabled = true;
            this.ReaderBox.Location = new System.Drawing.Point(411, 24);
            this.ReaderBox.Name = "ReaderBox";
            this.ReaderBox.Size = new System.Drawing.Size(143, 352);
            this.ReaderBox.TabIndex = 4;
            // 
            // WriterBox
            // 
            this.WriterBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.WriterBox.FormattingEnabled = true;
            this.WriterBox.Location = new System.Drawing.Point(554, 24);
            this.WriterBox.Name = "WriterBox";
            this.WriterBox.Size = new System.Drawing.Size(160, 352);
            this.WriterBox.TabIndex = 5;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(714, 376);
            this.Controls.Add(this.WriterBox);
            this.Controls.Add(this.ReaderBox);
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
        private System.Windows.Forms.ToolStripMenuItem FileStripMenuItem;
        private System.Windows.Forms.ListBox ReaderBox;
        private System.Windows.Forms.ToolStripMenuItem OpenStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem ExportStripMenuItem;
        private System.Windows.Forms.ListBox WriterBox;
    }
}

