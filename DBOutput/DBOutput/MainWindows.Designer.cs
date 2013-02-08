namespace DBOutput
{
    partial class DBOUTPUT
    {
        /// <summary>
        /// 必要なデザイナ変数です。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        /// <param name="disposing">マネージ リソースが破棄される場合 true、破棄されない場合は false です。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows フォーム デザイナで生成されたコード

        /// <summary>
        /// デザイナ サポートに必要なメソッドです。このメソッドの内容を
        /// コード エディタで変更しないでください。
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(DBOUTPUT));
            this.CB_INSTANCE = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.CB_DATABASE = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.CLB_TABLE = new System.Windows.Forms.CheckedListBox();
            this.BT_OUTPUT = new System.Windows.Forms.Button();
            this.TB_OUTPUT_DIRECTORY = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.BTN_PATH = new System.Windows.Forms.Button();
            this.checkBox = new System.Windows.Forms.CheckBox();
            this.checkBox_LocalNet = new System.Windows.Forms.CheckBox();
            this.BT_PLAN = new System.Windows.Forms.Button();
            this.BT_EXECUTEQUERY = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // CB_INSTANCE
            // 
            this.CB_INSTANCE.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.CB_INSTANCE.FormattingEnabled = true;
            this.CB_INSTANCE.Location = new System.Drawing.Point(102, 12);
            this.CB_INSTANCE.Name = "CB_INSTANCE";
            this.CB_INSTANCE.Size = new System.Drawing.Size(303, 20);
            this.CB_INSTANCE.TabIndex = 0;
            this.CB_INSTANCE.SelectedValueChanged += new System.EventHandler(this.CB_INSTANCE_SelectedValueChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(18, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(70, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "インスタンス名";
            // 
            // CB_DATABASE
            // 
            this.CB_DATABASE.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.CB_DATABASE.FormattingEnabled = true;
            this.CB_DATABASE.Location = new System.Drawing.Point(102, 45);
            this.CB_DATABASE.Name = "CB_DATABASE";
            this.CB_DATABASE.Size = new System.Drawing.Size(303, 20);
            this.CB_DATABASE.TabIndex = 1;
            this.CB_DATABASE.SelectedValueChanged += new System.EventHandler(this.CB_DATABASE_SelectedValueChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(18, 48);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(74, 12);
            this.label2.TabIndex = 1;
            this.label2.Text = "データベース名";
            // 
            // CLB_TABLE
            // 
            this.CLB_TABLE.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.CLB_TABLE.FormattingEnabled = true;
            this.CLB_TABLE.Location = new System.Drawing.Point(20, 78);
            this.CLB_TABLE.Name = "CLB_TABLE";
            this.CLB_TABLE.Size = new System.Drawing.Size(385, 172);
            this.CLB_TABLE.Sorted = true;
            this.CLB_TABLE.TabIndex = 2;
            this.CLB_TABLE.SelectedIndexChanged += new System.EventHandler(this.CLB_TABLE_SelectedIndexChanged);
            // 
            // BT_OUTPUT
            // 
            this.BT_OUTPUT.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.BT_OUTPUT.Location = new System.Drawing.Point(330, 278);
            this.BT_OUTPUT.Name = "BT_OUTPUT";
            this.BT_OUTPUT.Size = new System.Drawing.Size(75, 23);
            this.BT_OUTPUT.TabIndex = 3;
            this.BT_OUTPUT.Text = "出力";
            this.BT_OUTPUT.UseVisualStyleBackColor = true;
            this.BT_OUTPUT.Click += new System.EventHandler(this.BT_OUTPUT_Click);
            // 
            // TB_OUTPUT_DIRECTORY
            // 
            this.TB_OUTPUT_DIRECTORY.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.TB_OUTPUT_DIRECTORY.Location = new System.Drawing.Point(91, 280);
            this.TB_OUTPUT_DIRECTORY.Name = "TB_OUTPUT_DIRECTORY";
            this.TB_OUTPUT_DIRECTORY.Size = new System.Drawing.Size(132, 19);
            this.TB_OUTPUT_DIRECTORY.TabIndex = 3;
            // 
            // label3
            // 
            this.label3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(18, 283);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 12);
            this.label3.TabIndex = 1;
            this.label3.Text = "出力先";
            // 
            // BTN_PATH
            // 
            this.BTN_PATH.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.BTN_PATH.Location = new System.Drawing.Point(238, 278);
            this.BTN_PATH.Name = "BTN_PATH";
            this.BTN_PATH.Size = new System.Drawing.Size(75, 23);
            this.BTN_PATH.TabIndex = 4;
            this.BTN_PATH.Text = "参照";
            this.BTN_PATH.UseVisualStyleBackColor = true;
            this.BTN_PATH.Click += new System.EventHandler(this.BTN_PATH_Click);
            // 
            // checkBox
            // 
            this.checkBox.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.checkBox.AutoSize = true;
            this.checkBox.Location = new System.Drawing.Point(20, 318);
            this.checkBox.Name = "checkBox";
            this.checkBox.Size = new System.Drawing.Size(76, 16);
            this.checkBox.TabIndex = 5;
            this.checkBox.Text = "データ表示";
            this.checkBox.UseVisualStyleBackColor = true;
            this.checkBox.CheckedChanged += new System.EventHandler(this.checkBox_CheckedChanged);
            // 
            // checkBox_LocalNet
            // 
            this.checkBox_LocalNet.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.checkBox_LocalNet.AutoSize = true;
            this.checkBox_LocalNet.Location = new System.Drawing.Point(102, 318);
            this.checkBox_LocalNet.Name = "checkBox_LocalNet";
            this.checkBox_LocalNet.Size = new System.Drawing.Size(114, 16);
            this.checkBox_LocalNet.TabIndex = 6;
            this.checkBox_LocalNet.Text = "ローカルネットワーク";
            this.checkBox_LocalNet.UseVisualStyleBackColor = true;
            this.checkBox_LocalNet.CheckedChanged += new System.EventHandler(this.checkBox_LocalNet_CheckedChanged);
            // 
            // BT_PLAN
            // 
            this.BT_PLAN.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.BT_PLAN.Location = new System.Drawing.Point(238, 315);
            this.BT_PLAN.Name = "BT_PLAN";
            this.BT_PLAN.Size = new System.Drawing.Size(75, 23);
            this.BT_PLAN.TabIndex = 7;
            this.BT_PLAN.Text = "プラン";
            this.BT_PLAN.UseVisualStyleBackColor = true;
            this.BT_PLAN.Click += new System.EventHandler(this.BT_PLAN_Click);
            // 
            // BT_EXECUTEQUERY
            // 
            this.BT_EXECUTEQUERY.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.BT_EXECUTEQUERY.Location = new System.Drawing.Point(330, 315);
            this.BT_EXECUTEQUERY.Name = "BT_EXECUTEQUERY";
            this.BT_EXECUTEQUERY.Size = new System.Drawing.Size(75, 23);
            this.BT_EXECUTEQUERY.TabIndex = 8;
            this.BT_EXECUTEQUERY.Text = "クエリ";
            this.BT_EXECUTEQUERY.UseVisualStyleBackColor = true;
            this.BT_EXECUTEQUERY.Click += new System.EventHandler(this.BT_EXECUTEQUERY_Click);
            // 
            // DBOUTPUT
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.ClientSize = new System.Drawing.Size(424, 352);
            this.Controls.Add(this.BT_EXECUTEQUERY);
            this.Controls.Add(this.BT_PLAN);
            this.Controls.Add(this.checkBox_LocalNet);
            this.Controls.Add(this.checkBox);
            this.Controls.Add(this.TB_OUTPUT_DIRECTORY);
            this.Controls.Add(this.BTN_PATH);
            this.Controls.Add(this.BT_OUTPUT);
            this.Controls.Add(this.CLB_TABLE);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.CB_DATABASE);
            this.Controls.Add(this.CB_INSTANCE);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimumSize = new System.Drawing.Size(440, 390);
            this.Name = "DBOUTPUT";
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Show;
            this.Text = "データ抽出";
            this.Load += new System.EventHandler(this.DBOUTPUT_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox CB_INSTANCE;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox CB_DATABASE;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.CheckedListBox CLB_TABLE;
        private System.Windows.Forms.Button BT_OUTPUT;
        private System.Windows.Forms.TextBox TB_OUTPUT_DIRECTORY;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button BTN_PATH;
        private System.Windows.Forms.CheckBox checkBox;
        private System.Windows.Forms.CheckBox checkBox_LocalNet;
        private System.Windows.Forms.Button BT_PLAN;
        private System.Windows.Forms.Button BT_EXECUTEQUERY;
    }
}

