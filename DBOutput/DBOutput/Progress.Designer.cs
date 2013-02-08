namespace DBOutput
{
    partial class Progress
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
            this.progressBar = new System.Windows.Forms.ProgressBar();
            this.LB_PROGRESS = new System.Windows.Forms.Label();
            this.BT_CANCEL = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // progressBar
            // 
            this.progressBar.Location = new System.Drawing.Point(34, 40);
            this.progressBar.Name = "progressBar";
            this.progressBar.Size = new System.Drawing.Size(205, 23);
            this.progressBar.TabIndex = 0;
            // 
            // LB_PROGRESS
            // 
            this.LB_PROGRESS.AutoEllipsis = true;
            this.LB_PROGRESS.AutoSize = true;
            this.LB_PROGRESS.Location = new System.Drawing.Point(105, 17);
            this.LB_PROGRESS.Name = "LB_PROGRESS";
            this.LB_PROGRESS.Size = new System.Drawing.Size(45, 12);
            this.LB_PROGRESS.TabIndex = 1;
            this.LB_PROGRESS.Text = "?/?完了";
            this.LB_PROGRESS.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // BT_CANCEL
            // 
            this.BT_CANCEL.Location = new System.Drawing.Point(93, 80);
            this.BT_CANCEL.Name = "BT_CANCEL";
            this.BT_CANCEL.Size = new System.Drawing.Size(75, 23);
            this.BT_CANCEL.TabIndex = 2;
            this.BT_CANCEL.Text = "キャンセル";
            this.BT_CANCEL.UseVisualStyleBackColor = true;
            this.BT_CANCEL.Click += new System.EventHandler(this.BT_CANCEL_Click);
            // 
            // Progress
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.ClientSize = new System.Drawing.Size(265, 122);
            this.Controls.Add(this.BT_CANCEL);
            this.Controls.Add(this.LB_PROGRESS);
            this.Controls.Add(this.progressBar);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Progress";
            this.ShowInTaskbar = false;
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.Text = "進捗";
            this.TopMost = true;
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ProgressBar progressBar;
        private System.Windows.Forms.Label LB_PROGRESS;
        private System.Windows.Forms.Button BT_CANCEL;
    }
}