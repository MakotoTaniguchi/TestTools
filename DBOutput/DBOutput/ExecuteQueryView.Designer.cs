namespace DBOutput
{
    partial class ExecuteQueryView
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.dataGridView = new System.Windows.Forms.DataGridView();
            this.TB_QUERY = new System.Windows.Forms.TextBox();
            this.BT_EXECUTE = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridView
            // 
            this.dataGridView.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.dataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView.Location = new System.Drawing.Point(12, 12);
            this.dataGridView.Name = "dataGridView";
            this.dataGridView.ReadOnly = true;
            this.dataGridView.RowTemplate.Height = 21;
            this.dataGridView.Size = new System.Drawing.Size(417, 304);
            this.dataGridView.TabIndex = 0;
            // 
            // TB_QUERY
            // 
            this.TB_QUERY.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.TB_QUERY.Location = new System.Drawing.Point(12, 336);
            this.TB_QUERY.Multiline = true;
            this.TB_QUERY.Name = "TB_QUERY";
            this.TB_QUERY.Size = new System.Drawing.Size(417, 82);
            this.TB_QUERY.TabIndex = 1;
            // 
            // BT_EXECUTE
            // 
            this.BT_EXECUTE.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.BT_EXECUTE.Location = new System.Drawing.Point(354, 426);
            this.BT_EXECUTE.Name = "BT_EXECUTE";
            this.BT_EXECUTE.Size = new System.Drawing.Size(75, 23);
            this.BT_EXECUTE.TabIndex = 2;
            this.BT_EXECUTE.Text = "実行";
            this.BT_EXECUTE.UseVisualStyleBackColor = true;
            this.BT_EXECUTE.Click += new System.EventHandler(this.BT_EXECUTE_Click);
            // 
            // ExecuteQueryView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(441, 461);
            this.Controls.Add(this.BT_EXECUTE);
            this.Controls.Add(this.TB_QUERY);
            this.Controls.Add(this.dataGridView);
            this.Name = "ExecuteQueryView";
            this.Text = "ExecuteQueryView";
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridView;
        private System.Windows.Forms.TextBox TB_QUERY;
        private System.Windows.Forms.Button BT_EXECUTE;
    }
}