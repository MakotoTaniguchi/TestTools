<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="ProxyBrowser._Default" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head>
    <title>画像取得</title>
    <script language="javascript" type="text/javascript">
        function Checkbox_Visible_onclick()
        {        
            var CheckBox = document.getElementById("Checkbox_Visible");
            var Text_X = document.getElementById("TextBox_X_Size");
            var Text_Y = document.getElementById("TextBox_Y_Size");
                        
            if (CheckBox.checked)
            {
                Text_X.style.visibility = "visible";
                Text_Y.style.visibility = "visible";
            }
            else 
            {
                Text_X.style.visibility = "hidden";
                Text_Y.style.visibility = "hidden";
            }
        }
    </script>
</head>
<body>
    <form id="form" runat="server">
        <div align="center">
            <asp:Label ID="Label_URL" runat="server" Font-Size="Medium" Text="URLを入力" 
                valign="top" BorderStyle="Ridge"></asp:Label>
            <asp:TextBox ID="URL" runat="server" Width="500px" Wrap="False" 
                ToolTip="BitMap画像にしたいURLを入力して下さい"></asp:TextBox>
            <br />
            <asp:Label ID="Label_FileName" runat="server" BorderStyle="Ridge" Text="ファイル名"></asp:Label>
            <asp:TextBox ID="TextBox_FileName" runat="server" Width="500px" 
                ToolTip="BitMapのファイル名を入力して下さい。"></asp:TextBox>
            <br />
         </div>
         <div align="center">
            <input id="TextBox_X_Size" type="text" style="visibility: hidden" 
                 name="PageWidth" />
            <input id="TextBox_Y_Size" type="text" style="visibility: hidden" 
                 name="PageHight" />
             <br/>
            サイズ変更<input id="Checkbox_Visible" type="checkbox" 
                 onclick="Checkbox_Visible_onclick()" name="SizeCheck" />
            <br />
         </div>
         <div align="center" runat="server">
            <asp:Button ID="SendButton" runat="server" Text="取得" onclick="SendButton_Click"/>
            <br />
            <asp:Label ID="Label_Response" runat="server" align="center"></asp:Label>
         </div>
    </form>
    </body>
</html>
