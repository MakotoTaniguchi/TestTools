using System;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.Windows;
using System.Runtime.InteropServices.ComTypes;

using System.Threading;

namespace SiteCaptureSharp
{
    //*************************************************************************
    /// <summary> Webサイトの画像イメージキャプチャ処理を管理します
    /// </summary>
    //*************************************************************************
    public class CaptureManager
    {
        [DllImport("ole32.dll")]
        private static extern int OleDraw(IntPtr pUnk, int dwAspect, IntPtr hdcDraw, ref Rectangle lprcBounds);

        public CaptureManager( string strURL , int x, int y )
        {
            m_browser = null;
            m_bitmap = null;
            m_URL = strURL;
            m_bCaptured = false;
            m_dXSize = x;
            m_dYSize = y;
        }

        private WebBrowser m_browser;
        private Bitmap m_bitmap;
        private string m_URL;
        private bool m_bCaptured;
        private int m_dXSize;
        private int m_dYSize;

        //*********************************************************************
        /// <summary>　指定されたWebサイトに移動した時のイベントハンドラ
        /// </summary>
        /// <param name="url"></param>
        /// <returns></returns>
        //*********************************************************************
        private void MyDocumentCompleted(object sender, WebBrowserDocumentCompletedEventArgs e)
        {
            if (e.Url.Equals("about:blank"))
            {
                m_bCaptured = true;
                return;
            }

            try
            {
                // キャプチャサイズを指定
                if (m_dXSize == 0 && m_dYSize == 0)
                {
                    m_browser.Width = m_browser.Document.Body.ScrollRectangle.Width;
                    m_browser.Height = m_browser.Document.Body.ScrollRectangle.Height;
                }
                else
                {
                    m_browser.Width = (int)m_dXSize;
                    m_browser.Height = (int)m_dYSize;
                }            

                // キャプチャの保存先m_bitmapを生成
                m_bitmap = new Bitmap(m_browser.Width, m_browser.Height);

                // 生成したm_bitmapにWebページの画像を保存
                Graphics graphic = null;
                IntPtr ptrObj = IntPtr.Zero;
                IntPtr ptrHdc = IntPtr.Zero;
                try
                {
                    graphic = Graphics.FromImage(m_bitmap);
                    ptrHdc = graphic.GetHdc();
                    ptrObj = Marshal.GetIUnknownForObject(m_browser.ActiveXInstance);
                    Rectangle rect = new Rectangle(0, 0, m_browser.Width, m_browser.Height);

                    // ptrObj画像内のrectで指定した領域を,HDCのエリアに貼付
                    OleDraw(ptrObj, (int)DVASPECT.DVASPECT_CONTENT, ptrHdc, ref rect);
                }
                finally
                {
                    if (ptrObj != IntPtr.Zero)
                    {
                        Marshal.Release(ptrObj);
                    }
                    if (ptrHdc != IntPtr.Zero)
                    {
                        graphic.ReleaseHdc(ptrHdc);
                    }
                    if (graphic != null)
                    {
                        graphic.Dispose();
                    }
                }
            }
            finally
            {
                m_bCaptured = true;
            }
        }


        //*********************************************************************
        /// <summary>　指定されたWebサイトに遷移する
        /// </summary>
        /// <param name="url">キャプチャ対象のサイトURL</param>
        /// <returns>         ページの画像</returns>
        //*********************************************************************
        public void CaptureBitmap()
        {
            m_bCaptured = false;

            //------------------------------------------------
            // Webサイト情報取得用のブラウザコントロールを作成
            //------------------------------------------------

            m_browser = new WebBrowser();
            m_browser.ScrollBarsEnabled = false;
            m_browser.ScriptErrorsSuppressed = true;

            //---------------------------------------------
            // 指定URLへNavigate()完了時のハンドラを登録
            //---------------------------------------------
            m_browser.DocumentCompleted += new WebBrowserDocumentCompletedEventHandler(MyDocumentCompleted);

            //------------------------------------------------
            // 指定されたページへ遷移       
            //------------------------------------------------
            m_browser.Navigate(m_URL, false);

            while (!m_bCaptured)
            {
                Application.DoEvents();
            }

        }

        //*********************************************************************
        /// <summary>　指定されたWebサイトをbitmap画像として取得する
        /// </summary>
        /// <param name="url">キャプチャ対象のサイトURL</param>
        /// <returns>         ページの画像</returns>
        //*********************************************************************
        public Bitmap GetBitmap()
        {
            Thread thread = new Thread(new ThreadStart(CaptureBitmap));
            thread.IsBackground = true;
            thread.SetApartmentState(ApartmentState.STA);
            thread.Start();

            thread.Join();

            return m_bitmap;
        }
    }
}