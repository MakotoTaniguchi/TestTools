using System;
using System.IO;
using System.Collections.Generic;
using System.Windows.Forms;

using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Drawing;
using System.Drawing.Imaging;

using SiteCaptureSharp;

namespace ProxyBrowser
{
    public partial class _Default : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
        }

        protected void SendButton_Click(object sender, EventArgs e)
        {
            Label_Response.Text = "";

            int nWidth = 0;
            int nHight = 0;

            //-----------------------------------------------------------------------------------------
            // RequestされたHTTPを画像にコンバートする処理
            //-----------------------------------------------------------------------------------------
            // ファイルパスの作成
            string strFilePath = @"C:\Image\";
            if (!Directory.Exists(strFilePath))
            {
                Directory.CreateDirectory(strFilePath);
            }

            string FileName = System.IO.Path.GetFileNameWithoutExtension(TextBox_FileName.Text);
            strFilePath += FileName + ".png";

            string strCheck = Request.Form["SizeCheck"];
            if ("on" == strCheck)
            {
                string strWidth = Request.Form["PageWidth"];
                string strHight = Request.Form["PageHight"];

                int.TryParse(strWidth, out nWidth);
                int.TryParse(strHight, out nHight);
            }

            CaptureManager CaptureFunction = new CaptureManager(URL.Text, nWidth, nHight);
            Bitmap Png = CaptureFunction.GetBitmap();

            if (null == Png)
            {
                Label_Response.Text = "画像作成に失敗";
                return;
            }

            Png.Save(strFilePath.ToString(), ImageFormat.Png);

            string sFilePath;           // ファイルパス
            string sDownloadFileName;   // ダウンロードファイル名
            string sFileName = TextBox_FileName.Text + ".png";
            
            //-----------------------------------------------------------------------------------------
            // 物理ファイルパス取得
            //-----------------------------------------------------------------------------------------
            sFilePath = MapPath(string.Format(@"./File/{0}", sFileName));

            //-----------------------------------------------------------------------------------------
            // 日本語ファイル名を考慮したダウンロードファイル名作成
            //-----------------------------------------------------------------------------------------
            if (Request.Browser.Browser == "IE")
            {
                // IEの場合、ファイル名をURLエンコード
                sDownloadFileName = HttpUtility.UrlEncode(sFileName);
            }
            else
            {
                // IE以外はファイル名は無加工
                sDownloadFileName = sFileName;
            }

            Label_Response.Text = "画像作成に成功";

            //-----------------------------------------------------------------------------------------
            // ダウンロード処理
            //-----------------------------------------------------------------------------------------
            // Response情報クリア
            Response.ClearContent();
            // バッファリング
            Response.Buffer = true;
            // HTTPヘッダー情報設定
            Response.AddHeader("Content-Disposition", string.Format("attachment;filename={0}", sDownloadFileName));
            Response.ContentType = "image/png";
            // ファイル書込
            Response.WriteFile(strFilePath);
            // フラッシュ
            Response.Flush();
            // レスポンス終了
            Response.End();

            File.Delete(strFilePath);
        }
    }
}
