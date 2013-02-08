using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace DBOutput
{
    public partial class QueryPlanView : Form
    {
        /******************
         * コンストラクタ
         ******************/
        public QueryPlanView()
        {
            InitializeComponent();
        }

        /*******************************
         * フォームを閉じる間のイベント
         *******************************/
        void QueryPlanView_FormClosing(object sender, System.Windows.Forms.FormClosingEventArgs e)
        {
            try
            {
                e.Cancel = true;
                this.Hide();
            }
            catch (Exception ex)
            {
                throw new System.NotImplementedException();
            }
        }

        /*************************
         * 再描画(画面が崩れる為)
         *************************/
        void dataGridView_Scroll(object sender, System.Windows.Forms.ScrollEventArgs e)
        {
            try
            {
                this.dataGridView.Invalidate();
            }
            catch (Exception ex)
            {
                throw new System.NotImplementedException();
            }
        }

        /*******************
         * データバインド
         *******************/
        public void DataGridViewBind(DataTable dataTable)
        {
            if (null == dataTable)
            {
                return;
            }

            dataGridView.DataMember = dataTable.TableName;
            dataGridView.DataSource = dataTable;

            dataGridView.Visible = true;
        }
    }
}
