using System;
using System.Collections;
using System.Collections.Generic;

using System.Data;
using System.Data.Sql;
using System.Data.SqlClient;

using System.Diagnostics;
using System.Windows.Forms;

namespace SQLServerHelper
{
    class CDataBaseCtrl : IDisposable
    {
        /******************
         * コンストラクタ
         *******************/
        public CDataBaseCtrl()
        {
            m_cSqlConnection = null;
            m_cReader = null;
            sw = new Stopwatch();
        }

        /*****************
         * デストラクタ
         ****************/
        ~CDataBaseCtrl()
        {
            DisConnect();
        }

        /******************************
         * IDisposableインターフェース
         ******************************/
        public void Dispose()
        {
            DisConnect();
        }

        /*****************
         * 64bitOSか判定
         *****************/
        static private bool Is64BitOs()
        {
            bool bRet = false;

            //Windows NT系OSか調べる
            if (System.Environment.OSVersion.Platform == System.PlatformID.Win32NT)
            {
                //ローカルコンピュータの環境変数"PROCESSOR_ARCHITECTURE"の値を取得
                string procArch = System.Environment.GetEnvironmentVariable(
                    "PROCESSOR_ARCHITECTURE", System.EnvironmentVariableTarget.Machine);
                if ( !(procArch == null || procArch == "x86") )
                {
                    // 64BitOS
                    bRet = true;
                }
            }

            return bRet;
        }

        /***************************
         * LocalInstanceを取得する
         ***************************/
        public static List<string> GetLocalInstance()
        {
            // OSによってオープンするレジストリが違う
            string strRegKey="";
            if (CDataBaseCtrl.Is64BitOs())
            {
                strRegKey = @"SOFTWARE\Wow6432Node\Microsoft\Microsoft SQL Server\Instance Names\SQL";
            }
            else 
            {
                strRegKey = @"SOFTWARE\Microsoft\Microsoft SQL Server\Instance Names\SQL";
            }

            // キーを読み取り専用で開く
            Microsoft.Win32.RegistryKey regkey = Microsoft.Win32.Registry.LocalMachine.OpenSubKey(strRegKey, false);

            // キーが存在しないときは null が返される
            if (regkey == null)
            {
                MessageBox.Show("ローカルインスタンス名の取得に失敗しました。");
                return null;
            }

            // 複数あるキーの名前を取得
            string[] strKeyNames = regkey.GetValueNames();
            regkey.Close();

            // Listにインスタンス名を格納
            List<string> ListInstances = new List<string>();
            foreach (string strKeyName in strKeyNames)
            {
                string strInstanceName = "localhost\\" + strKeyName;
                ListInstances.Add(strInstanceName);
            }

            return ListInstances;
        }

        /***************************************
         * ローカルネットのインスタンスを取得
         ****************************************/
        public static List<string> GetLocalNetInstance(bool bLocalHost)
        {
            List<string> ListInstanceName = new List<string>();
            string strInstanceName = "";

            try 
            {
                // ローカルネットワークのインスタンスを取得
                SqlDataSourceEnumerator instance = SqlDataSourceEnumerator.Instance;
                DataTable dataTable = instance.GetDataSources();

                foreach (DataRow row in dataTable.Rows)
                {
                	if(bLocalHost)
                	{
                		// ローカルホストか調べる
                        if (row["ServerName"].ToString() != System.Environment.MachineName)
	                    {
	                        continue;
	                    }
                	}

                    // インスタンス名
                    strInstanceName = row["ServerName"].ToString() + "\\";

                    // 既定のインスタンス名の場合
                    if (row["InstanceName"].ToString() == "")
                    {
                        // 既定のインスタンスではインスタンス名が空文字が返ってくる。
                        strInstanceName += "SQLEXPRESS";
                    }
                    else
                    {
                        // 名前付きインスタンス名の場合はそのまま
                        strInstanceName += row["InstanceName"].ToString();
                    }

                    ListInstanceName.Add(strInstanceName);
                }

                ListInstanceName.Sort();
            }
            catch(Exception e)
            {
                Debug.WriteLine(e.Message);
            }

            return ListInstanceName;
        }

        /************************************
         * Windows認証でインスタンスに接続
         ************************************/
        public bool Connect(string strInstanceName)
        {
            bool bRet = true;

            if (0 >= strInstanceName.Length)
            {
            	Debug.WriteLine("インスタンス名が選択されていません");
                return false;
            }

			// Windows認証
            string strConnect = string.Empty;
            strConnect = "Data Source=" + strInstanceName + ";";
            strConnect += "Integrated Security=true;";
            
            m_cSqlConnection = new SqlConnection(strConnect);

            try 
            {
                // データベース接続を開く
                m_cSqlConnection.Open();
            }
            catch (InvalidOperationException e)
            {
                MessageBox.Show(e.Message);
                Debug.WriteLine( e.Message );
                bRet = false;
            }
            catch (SqlException e)
            {
                MessageBox.Show(e.Message);
                Debug.WriteLine(e.Message);
                bRet = false;
            }

            return bRet;
        }

        /************************************
         * Windows認証でデータベースに接続
         ************************************/
        public bool Connect(string strInstanceName, string strDataBaseName)
        {
            bool bRet = true;
            
            if (0 >= strInstanceName.Length || 0 >= strDataBaseName.Length)
            {
            	Debug.WriteLine("インスタンス名とDB名が選択されていません");
                return false;
            }

			// Windows認証
            string strConnect = string.Empty;
            strConnect = "Data Source=" + strInstanceName + ";";
            strConnect += " Database=" + strDataBaseName + ";";
            strConnect += "Integrated Security=true;";
            m_cSqlConnection = new SqlConnection(strConnect);

            try
            {
                // データベース接続を開く
                m_cSqlConnection.Open();
            }
            catch (InvalidOperationException e)
            {
                Debug.WriteLine(e.Message);
                bRet = false;
            }
            catch (SqlException e)
            {
                Debug.WriteLine(e.Message);
                bRet = false;
            }

            return bRet;
        }

        /*******************
         * 接続を切断する。
         ******************/
        public void DisConnect() 
        {
            if (null == m_cSqlConnection)
            {
                Debug.WriteLine("接続されていません");
                return;
            }

            m_cSqlConnection.Close();
            m_cSqlConnection.Dispose();
        }

        /**************************
         * Update系のクエリを実行
         *************************/
        public int ExecuteUpdate(string strQuery)
        {
            if (null == m_cSqlConnection)
            {
                Debug.WriteLine("接続されていません");
                return 0;
            }

            int nResult = 0;

			try
			{
				SqlCommand hCommand = m_cSqlConnection.CreateCommand();
	            hCommand.CommandText = strQuery;

                sw.Start();
	            nResult = hCommand.ExecuteNonQuery();
                sw.Stop();

                long lTime = sw.ElapsedMilliseconds;
                Debug.WriteLine(lTime);
			}
			catch(ArgumentException ex)
			{
				Debug.WriteLine(ex.Message);
			}
			catch(Exception ex)
			{
				Debug.WriteLine(ex.Message);
			}

            return nResult;
        }

        /**************************
         * クエリの実行(DataTable)
         **************************/
        public DataTable ExecuteQuery(string strQuery)
        {
            if (null == m_cSqlConnection)
            {
                Debug.WriteLine("接続されていません");
                return null;
            }
			
			DataTable QueryData = null;
			
			try
			{
				SqlCommand hCommand = m_cSqlConnection.CreateCommand();
	            hCommand.CommandText = strQuery;

	            QueryData = new DataTable();

                sw.Start();
	            QueryData.Load(hCommand.ExecuteReader());
                sw.Stop();

                long lTime = sw.ElapsedMilliseconds;
                Debug.WriteLine(lTime);
			}
			catch(ArgumentException ex)
			{
				Debug.WriteLine(ex.Message);
			}
			catch(SqlException ex)
			{
				Debug.WriteLine(ex.Message);
			}
			catch(Exception ex)
			{
				Debug.WriteLine(ex.Message);
			}

            return QueryData;
        }

        /******************************************************
         * SqlDataReaderを実行した後のデータ取り出し（string）
         ******************************************************/
        public bool GetDataReader( string strField, List<string> ListData )
        {
            bool bRet = true;

            if (null == m_cReader)
            {
                return false;
            }
            
            try
            {
            	while (m_cReader.Read())
	            {
	                string strData = (string)m_cReader[strField];
	                ListData.Add(strData);
	            }
            }
            catch(SqlException ex)
			{
				bRet = false;
				Debug.WriteLine(ex.Message);
			}
			catch(Exception ex)
			{
				bRet = false;
				Debug.WriteLine(ex.Message);
			}

            return bRet;
        }

        /**************************************************
         * SqlDataReaderを実行した後のデータ取り出し(int)
         *************************************************/
        public bool GetDataReader(string strField, List<int> ListData)
        {
            bool bRet = true;

            if (null == m_cReader)
            {
                return false;
            }
            
            try
            {
            	while (m_cReader.Read())
	            {
	                int nData = (int)m_cReader[strField];
	                ListData.Add(nData);
	            }
            }
            catch(SqlException ex)
			{
				bRet = false;
				Debug.WriteLine(ex.Message);
			}
			catch(Exception ex)
			{
				bRet = false;
				Debug.WriteLine(ex.Message);
			}

            return bRet;
        }

		/************
		 * 接続確認
		 ************/
        public bool isConnect()
        {
            bool bConnect = false;
            if (null != m_cSqlConnection)
            {
                bConnect = true;
            }
            return bConnect;
        }

        /**************
         * メンバ変数
         **************/
        private SqlConnection m_cSqlConnection = null;  // コネクションクラス
        private SqlDataReader m_cReader = null;         // データ取得領域
        private Stopwatch sw = null;                    // 計測
    }
}