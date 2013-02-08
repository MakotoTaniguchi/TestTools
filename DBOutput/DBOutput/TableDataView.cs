using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
//using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace DBOutput
{
    public partial class TableDataView : Form
    {
        /*******************
         * コンストラクタ
         *******************/
        public TableDataView()
        {
            InitializeComponent();
        }

        /*******************************
         * フォームを閉じる間のイベント
         *******************************/
        void TableDataView_FormClosing(object sender, System.Windows.Forms.FormClosingEventArgs e)
        {
            try 
            {
                e.Cancel = true;
                this.Hide();
            }
            catch(Exception ex)
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
