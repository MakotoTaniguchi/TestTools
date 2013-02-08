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
    public partial class Progress : Form
    {
        // コンストラクタ
        public Progress()
        {
            InitializeComponent();
            m_bIsCancel = false;
        }

        // 初期化
        public void InitializeValue(int nMin, int nMax)
        {
            // 最小値と最大値をセット
            progressBar.Minimum = nMin;
            SetMaxProgress(nMax);

            // 現在値セット
            SetCurrentPosiTion(0);
        }

        // プログレスバーの最大値を設定
        public void SetMaxProgress(int nMax)
        {
            progressBar.Maximum = nMax;
        }

        // プログレスバーの現在値を設定する。
        public void SetCurrentPosiTion(int nPosiTion)
        {
            progressBar.Value = nPosiTion;
            LB_PROGRESS.Text = nPosiTion.ToString() + "/" + progressBar.Maximum.ToString() + "完了";
        }

        // 中止ボタンの状態
        public bool m_bIsCancel;

        private void BT_CANCEL_Click(object sender, EventArgs e)
        {
            m_bIsCancel = true;
        }
    }
}
