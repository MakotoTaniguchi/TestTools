using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using System.Diagnostics;
using System.IO;
using SQLServerHelper;

using System.Threading;

namespace DBOutput
{
    public partial class DBOUTPUT : Form
    {
        /*******************************
         * SQLサーバーのヘルパークラス
         ******************************/
        CDataBaseCtrl m_DataBaseCtrl = new CDataBaseCtrl();

        /**************************
         * 選択したインスタンス名
         *************************/
        string m_strInstanceName = "";

        /**************************
         * 選択したデータベース名
         *************************/
        string m_strDataBaseName = "";

        /**************************
         * 選択したテーブルの情報
         **************************/
        DataTable m_dataTable = null;

        /******************************
         * ローカルPCのインスタンス名
         ******************************/
        List<string> m_ListLocalInstances = null;

        /***************************************
         * ローカルネットワークのインスタンス名
         ***************************************/
        List<string> m_ListLocalNetInstances = null;

        /****************
         * データビュー
         ****************/
        TableDataView m_tableDataView = null;

        /*********************
         * プランデータビュー
         *********************/
        QueryPlanView m_QueryPlannView = null;

        /****************
         * プランデータ
         ****************/
        DataTable m_dtQueryPlanData = null;

        /******************
         * コンストラクタ
         ******************/
        public DBOUTPUT()
        {
            InitializeComponent();
        }

        /***********************************
         * ローカルネットインスタンス名取得
         ***********************************/
        private void LocalNetInstanceCollect()
        {
            // ローカルネットワークのインスタンス名を取得
            m_ListLocalNetInstances = CDataBaseCtrl.GetLocalNetInstance(false);
        }

        /***********************************
         * ローカルネットインスタンス名取得
         ***********************************/
        private void LocalInstanceCollect()
        {
            // ローカルPCのインスタンス名取得
            m_ListLocalInstances = CDataBaseCtrl.GetLocalInstance();
        }

        /*********************************
         * フォームの初期化(OnInitDialog)
         ********************************/
        void DBOUTPUT_Load(object sender, System.EventArgs e)
        {
            try 
            {
                // データ表示のフォームを作成
                m_tableDataView = new TableDataView();
                m_tableDataView.DataGridViewBind(m_dataTable);

                m_QueryPlannView = new QueryPlanView();
                m_QueryPlannView.DataGridViewBind(m_dtQueryPlanData);
                

                // データコレクトスレッド
                Thread LocalNetInstanceCollectThread = new Thread(LocalNetInstanceCollect);
                LocalNetInstanceCollectThread.Start();

                // インスタンス名の取得
                Thread LocalInstanceCollectThread = new Thread(LocalInstanceCollect);
                LocalInstanceCollectThread.Start();

                while (LocalNetInstanceCollectThread.IsAlive && LocalInstanceCollectThread.IsAlive)
                {
                    Thread.Sleep(1000);
                }

                // インスタンス名の設定
                List<string> ListInstanceName = m_ListLocalInstances;
                if (null != m_ListLocalNetInstances)
                {
                    ListInstanceName = m_ListLocalNetInstances;
                }

                // インスタンス名が取得出来たか
                if (null == ListInstanceName)
                {
                    return;
                }

                // インスタンス名のリスト作成
                foreach (string strInstanceName in ListInstanceName)
                {
                    CB_INSTANCE.Items.Add(strInstanceName);
                }
            }
            catch(Exception ex)
            {
                throw new System.NotImplementedException();
            }
        }

        /*********************************
         * インスタンス名を選択されました
         ********************************/
        private void CB_INSTANCE_SelectedValueChanged(object sender, EventArgs e)
        {
            // アイテムが存在していない場合
            if (0 >= CB_INSTANCE.Items.Count)
            {
                return;
            }

            // DB名のリストを全削除
            CB_DATABASE.Items.Clear();

            // インデックス確認
            if ( 0 > CB_INSTANCE.SelectedIndex)
            {
                return;
            }

            // 対象インスタンス名の指定
            m_strInstanceName = CB_INSTANCE.Items[CB_INSTANCE.SelectedIndex].ToString();

            // クエリの実行
            m_DataBaseCtrl.Connect(m_strInstanceName);
            DataTable dtDataBase = m_DataBaseCtrl.ExecuteQuery(DBOutput.Properties.Resources.rcDataBaseName);

            // DB名のリスト作成
            for (int i = 0; i < dtDataBase.Rows.Count; i++)
            {
                CB_DATABASE.Items.Add(dtDataBase.Rows[i][0].ToString());
            }

            // DBと切断
            m_DataBaseCtrl.DisConnect();
        }

        /**********************************
         * データベース名が選択されました
         *********************************/
        private void CB_DATABASE_SelectedValueChanged(object sender, EventArgs e)
        {
            // アイテムが存在していない場合
            if (0 >= CB_DATABASE.Items.Count)
            {
                return;
            }

            // テーブルリストを全削除
            CLB_TABLE.Items.Clear();

            // 対象DB指定
            m_strDataBaseName = CB_DATABASE.Items[CB_DATABASE.SelectedIndex].ToString();

            // クエリの実行
            m_DataBaseCtrl.Connect(m_strInstanceName, m_strDataBaseName);

            // sys.sysobjectsテーブルからテーブル情報を取得
            DataTable dtTable = m_DataBaseCtrl.ExecuteQuery(DBOutput.Properties.Resources.rcTableInfo);

            // sys.Schemasテーブルからスキーマを取得
            DataTable dtSchema = m_DataBaseCtrl.ExecuteQuery(DBOutput.Properties.Resources.rcSchemaInfo);

            // スキーマ名とテーブル名を関連付ける
            for (int i = 0; i < dtTable.Rows.Count; i++ )
            {
                for (int j = 0; j < dtSchema.Rows.Count; j++)
                {
                    if (dtTable.Rows[i][0].ToString() == dtSchema.Rows[j][0].ToString())
                    {
                        string strTableName = dtSchema.Rows[j][1].ToString() + "." + dtTable.Rows[i][1].ToString();
                        CLB_TABLE.Items.Add(strTableName);
                    }
                }
            }

            CLB_TABLE.Sorted = true;

            // DBと切断
            m_DataBaseCtrl.DisConnect();
        }

        /******************
         * 出力ボタン押下
         ******************/
        private void BT_OUTPUT_Click(object sender, EventArgs e)
        {
            // リストが空の場合
            if (0 >= CLB_TABLE.Items.Count)
            {
                return;
            }

            Thread TableDatasOutputThread = new Thread(TableDatasOutput);
            TableDatasOutputThread.Start();
        }

        /******************
         * 参照ボタン押下
         *******************/
        private void BTN_PATH_Click(object sender, EventArgs e)
        {
            //FolderBrowserDialogクラスのインスタンスを作成
            FolderBrowserDialog fbd = new FolderBrowserDialog();

            //上部に表示する説明テキストを指定する
            fbd.Description = "フォルダを指定してください。";

            //ルートフォルダを指定する
            //デフォルトでDesktop
            fbd.RootFolder = Environment.SpecialFolder.Desktop;

            //最初に選択するフォルダを指定する
            //RootFolder以下にあるフォルダである必要がある
            fbd.SelectedPath = System.Environment.CurrentDirectory;

            //ユーザーが新しいフォルダを作成できるようにする
            //デフォルトでTrue
            fbd.ShowNewFolderButton = true;

            //ダイアログを表示する
            if (fbd.ShowDialog(this) == DialogResult.OK)
            {
                //選択されたフォルダを表示する
                TB_OUTPUT_DIRECTORY.Text = fbd.SelectedPath;
            }

            return;
        }

        /*************************************
         * データ表示チェックボックス押下時
         *************************************/
        private void checkBox_CheckedChanged(object sender, EventArgs e)
        {
            // チェックされているか確認
            if (!checkBox.Checked)
            {
                // データグリッドを隠す
                m_tableDataView.Hide();
                return;
            }
            else 
            {
                // データグリッド表示
                m_tableDataView.Show();
            }

            // リストボックスが選択されているか確認
            int nSelectIndex = CLB_TABLE.SelectedIndex;
            if (0 > nSelectIndex)
            {
                // 未選択状態
                return;
            }

            // 接続
            bool bCon = m_DataBaseCtrl.Connect(m_strInstanceName, m_strDataBaseName);
            if(bCon)
            {
            	// クエリの実行
	            string strTable = CLB_TABLE.SelectedItem.ToString();
	            string strQuery = "Select * From " + strTable;
	            m_dataTable = m_DataBaseCtrl.ExecuteQuery(strQuery);

	            // 切断
	            m_DataBaseCtrl.DisConnect();
            }

            m_tableDataView.DataGridViewBind(m_dataTable);
        }

        /************************
         * リストボックスを選択
         ************************/
        private void CLB_TABLE_SelectedIndexChanged(object sender, EventArgs e)
        {
            // データ表示チェックボックスがチェックされていない場合
            if (!checkBox.Checked)
            {
                return;
            }

            // 接続
            bool bCon = m_DataBaseCtrl.Connect(m_strInstanceName, m_strDataBaseName);
            if(bCon)
            {
            	// クエリの実行
	            string strTable = CLB_TABLE.SelectedItem.ToString();
	            string strQuery = "Select * From " + strTable;
	            m_dataTable = m_DataBaseCtrl.ExecuteQuery(strQuery);

	            // 切断
	            m_DataBaseCtrl.DisConnect();
            }

            m_tableDataView.DataGridViewBind(m_dataTable);

        }

        /**********************************************
         * インスタンス取得方式チェックボックス押下時
         ***********************************************/
        private void checkBox_LocalNet_CheckedChanged(object sender, EventArgs e)
        {
            // インスタンス名のリストボックスを初期化
            CB_INSTANCE.Items.Clear();

            // インスタンス名を取得
            List<string> ListInstanceName = null;
            if (!checkBox_LocalNet.Checked)
            {
                // ローカルPCのインスタンス名取得
                ListInstanceName = m_ListLocalInstances;
            }
            else
            {
                // ローカルネットワークのインスタンス名を取得
                ListInstanceName = m_ListLocalNetInstances;
            }

            // インスタンス名が取得出来たか
            if (null == ListInstanceName)
            {
                CB_INSTANCE.Items.Clear();
                return;
            }

            // インスタンス名のリスト作成
            foreach (string strInstanceName in ListInstanceName)
            {
                CB_INSTANCE.Items.Add(strInstanceName);
            }
        }

        /****************************************
         * 選択されているテーブルのデータを出力
         ****************************************/
        private void TableDatasOutput()
        {
            // テーブル数
            int nTableCount = CLB_TABLE.CheckedItems.Count;

            // 出力数
            int nOutputCount = 0;

            // プログレスバーを表示する。
            Progress progress = new Progress();
            progress.InitializeValue(0, nTableCount);
            progress.Show();

            // ProcessStartInfo の新しいインスタンスを生成する
            ProcessStartInfo hPsInfo = new ProcessStartInfo();

            // ファイル出力
            List<string> ListTableName = new List<string>();
            foreach (object items in CLB_TABLE.CheckedItems)
            {
                // キャンセルが押下されたか確認
                if (progress.m_bIsCancel)
                {
                    // キャンセルが押下されたので中断
                    break;
                }

                // コマンドオプションの作成
                string strFileName = items.ToString() + ".csv";
                string strFilePath = System.IO.Path.Combine(TB_OUTPUT_DIRECTORY.Text, strFileName);
                string strCommandLine = m_strDataBaseName + "." + items.ToString() + " out " + strFilePath +
                                        " -w -t\",\" -T -S " + m_strInstanceName;

                // 起動するアプリケーションを設定する
                hPsInfo.FileName = "bcp";

                // コマンドライン引数を設定する
                hPsInfo.Arguments = strCommandLine;

                // 新しいウィンドウを作成するかどうかを設定する (初期値 false)
                //hPsInfo.CreateNoWindow = true;

                // シェルを使用するかどうか設定する (初期値 true)
                //hPsInfo.UseShellExecute = false;

                // 起動できなかった時にエラーダイアログを表示するかどうかを設定する (初期値 false)
                hPsInfo.ErrorDialog = true;

                // エラーダイアログを表示するのに必要な親ハンドルを設定する
                hPsInfo.ErrorDialogParentHandle = this.Handle;

                // アプリケーションを起動する時の動詞を設定する
                //hPsInfo.Verb = "Open";

                // 起動ディレクトリを設定する
                //hPsInfo.WorkingDirectory = @"C:\Hoge\";

                // 起動時のウィンドウの状態を設定する
                //hPsInfo.WindowStyle = System.Diagnostics.ProcessWindowStyle.Normal;     //通常
                hPsInfo.WindowStyle = ProcessWindowStyle.Hidden;     //非表示
                //hPsInfo.WindowStyle = System.Diagnostics.ProcessWindowStyle.Minimized;  //最小化
                //hPsInfo.WindowStyle = System.Diagnostics.ProcessWindowStyle.Maximized;  //最大化

                // ProcessStartInfo を指定して起動する
                Process ProcessRet = ProcessRet = Process.Start(hPsInfo);

                ProcessRet.WaitForExit();

                nOutputCount++;
                progress.SetCurrentPosiTion(nOutputCount);
                progress.Update();
            }

            if (progress.m_bIsCancel)
            {
                MessageBox.Show("中断されました");
            }
            else
            {
                MessageBox.Show("コマンド出力完了");
            }

            progress.Hide();
        }

        /***********************
         * プランボタン押下時
         ***********************/
        private void BT_PLAN_Click(object sender, EventArgs e)
        {
            // 接続
            bool bCon = m_DataBaseCtrl.Connect(m_strInstanceName);
            if (bCon)
            {
                // クエリの実行
                string strQuery = DBOutput.Properties.Resources.rcQueryPlan;
                m_dtQueryPlanData = m_DataBaseCtrl.ExecuteQuery(strQuery);

                // 切断
                m_DataBaseCtrl.DisConnect();
            }

            m_QueryPlannView.DataGridViewBind(m_dtQueryPlanData);

            m_QueryPlannView.Show();
        }

        private void BT_EXECUTEQUERY_Click(object sender, EventArgs e)
        {
            ExecuteQueryView Window = new ExecuteQueryView();
            Window.InitializeWindow(m_strInstanceName, m_strDataBaseName);
            Window.Show();
        }
    }
}
