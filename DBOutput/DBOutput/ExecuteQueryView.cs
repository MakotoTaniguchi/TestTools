using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using SQLServerHelper;

namespace DBOutput
{
    public partial class ExecuteQueryView : Form
    {
        /*****************
         * コンストラクタ
         *****************/
        public ExecuteQueryView()
        {
            InitializeComponent();
        }

        /*****************
         * デストラクタ
         *****************/
        ~ExecuteQueryView()
        {
            m_DataBaseCtrl.DisConnect();
        }

        /**************
         * 初期化処理
         **************/
        public void InitializeWindow(string strInstanceName, string strDBName)
        {
            m_strInstanceName = strInstanceName;
            m_strDBName = strDBName;
        }

        /*******************
         * データバインド
         *******************/
        private void DataGridViewBind(DataTable dataTable)
        {
            if (null == dataTable)
            {
                return;
            }

            dataGridView.DataMember = dataTable.TableName;
            dataGridView.DataSource = dataTable;

            dataGridView.Visible = true;
        }

        /*******************
         * 実行ボタン押下時
         *******************/
        private void BT_EXECUTE_Click(object sender, EventArgs e)
        {

            bool bRet = m_DataBaseCtrl.Connect(m_strInstanceName, m_strDBName);
            if (!bRet)
            {
                MessageBox.Show("接続に失敗しました");
                return;
            }

            m_dtResultQuery = m_DataBaseCtrl.ExecuteQuery(TB_QUERY.Text);
            DataGridViewBind(m_dtResultQuery);

            m_DataBaseCtrl.DisConnect();
        }

        /**************
         * メンバ変数
         **************/
        private CDataBaseCtrl m_DataBaseCtrl = new CDataBaseCtrl();     // SQLServerの操作変数
        private DataTable m_dtResultQuery = null;                       // クエリの実行結果
        private string m_strInstanceName = "";
        private string m_strDBName = "";
    }
}
