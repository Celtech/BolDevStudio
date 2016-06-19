using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using NLua;
using KRBTabControl;
using FastColoredTextBoxNS;
using Aga.Controls.Tree;
using Aga.Controls.Tree.NodeControls;
using Aga.Controls;
using System.IO;
using System.Text.RegularExpressions;

namespace BoL_Dev_Studio
{
    public partial class Form1 : Form
    {
        string path;
        Lua lua = new Lua();

        struct Files
        {
            public string path;
            public string name;
            public string baseClass;
        }


        public static void nullFunction(string hello)
        {

        }

        public Form1()
        {
            InitializeComponent();
        }


        private void fastColoredTextBox1_TextChanged(object sender, FastColoredTextBoxNS.TextChangedEventArgs e)
        {
            e.ChangedRange.SetFoldingMarkers("{", "}");
            e.ChangedRange.SetFoldingMarkers("function", "end");
            e.ChangedRange.SetFoldingMarkers("if", "end");

            var s = (FastColoredTextBox)sender;
            toolStripStatusLabel3.Text = "Lines: " + s.LineInfos.Count.ToString() + "    Char Count: " + s.Text.Length.ToString();
        }

        private void newPage()
        {
            TabPageEx tp = new TabPageEx();
            tp.Text = "new file";

            tp.ImageIndex = 0;
            krbTabControl1.TabPages.Add(tp);
            FastColoredTextBox tb = new FastColoredTextBox();
            tb.Language = FastColoredTextBoxNS.Language.Lua;
            tb.AutoIndentChars = false;
            tb.Parent = tp;
            tb.ShowFoldingLines = true;
            tb.ContextMenuStrip = contextMenuStrip1;
            this.autocompleteMenu1.SetAutocompleteMenu(tb, this.autocompleteMenu1);
            tb.TextChanged += new System.EventHandler<TextChangedEventArgs>(this.fastColoredTextBox1_TextChanged);
            tb.SelectionChanged += new System.EventHandler(this.fastColoredTextBox1_SelectionChanged);
            tb.Dock = DockStyle.Fill;
            tb.CurrentLineColor = Color.FromArgb(199, 220, 83);

            tb.ReadOnly = false;

            krbTabControl1.SelectedTab = tp;
        }

        #region treeView

        private TreeModel _model;
        Node home;
        private Node AddRoot(string name, Image img)
        {
            Node node = new MyNode(name, img);
            _model.Nodes.Add(node);
            return node;
        }

        private Node AddChild(Node parent, string text , Image img)
        {
            Node node = new MyNode(text, img);
            parent.Nodes.Add(node);
            return node;
        }

        private void getFiles()
        {
            foreach(string f in Directory.GetFiles(path))
            {
                if (Path.GetFileName(f).Contains(".lua") || Path.GetFileName(f).Contains(".txt"))
                {
                    Node child = AddChild(home, Path.GetFileName(f), imageList2.Images[0]);
                }
            }
        }

        private void getFolders()
        {
            foreach (string f in Directory.GetDirectories(path))
            { 
                Node child = AddChild(home, Path.GetFileName(f), imageList2.Images[3]);
                foreach (string s in Directory.GetFiles(path))
                {
                    Node temp = AddChild(child, Path.GetFileName(s), imageList2.Images[0]);
                }
            }
        }

        private void treeInit()
        {
            _model = new TreeModel();
            treeViewAdv1.Model = _model;
            treeViewAdv1.BeginUpdate();
             
            home = AddRoot("Home", imageList2.Images[1]);

            getFolders();
            getFiles();
            
            treeViewAdv1.EndUpdate();
        }
        #endregion


        #region MenuStrip
        bool map, workSpace = true;
        private void toggleWorkSpaceToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (workSpace)
            {
                panel1.Hide();
                workSpace = false;
            }
            else
            {
                panel1.Show();
                workSpace = true;
            }
        }

        private void toggleDocumentMapToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (map)
            {
                panel2.Hide();
                map = false;
            }
            else
            {
                panel2.Show();
                map = true;
            }
        }

        private void newFileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Files f = new Files();


            using (NewProject form2 = new NewProject())
            {
                form2.StartPosition = FormStartPosition.CenterParent;
                form2.ShowDialog();
                f.name = form2.textbox1value;
                f.baseClass = form2.textbox2value;
                f.path = form2.textbox3value;

            }

            TabPageEx tp = new TabPageEx();
            tp.Text = f.name;

            tp.ImageIndex = 0;
            krbTabControl1.TabPages.Add(tp);
            FastColoredTextBox tb = new FastColoredTextBox();
            tb.Language = FastColoredTextBoxNS.Language.Lua;
            tb.AutoIndentChars = false;
            tb.Parent = tp;
            tb.ShowFoldingLines = true;
            tb.ContextMenuStrip = contextMenuStrip1;
            this.autocompleteMenu1.SetAutocompleteMenu(tb, this.autocompleteMenu1);
            tb.TextChanged += new System.EventHandler<TextChangedEventArgs>(this.fastColoredTextBox1_TextChanged);
            tb.SelectionChanged += new System.EventHandler(this.fastColoredTextBox1_SelectionChanged);
            tb.Dock = DockStyle.Fill;
            tb.CurrentLineColor = Color.FromArgb(199,220,83);
            
            tb.ReadOnly = false;
            tb.Text =
@"function OnLoad()
    " + f.baseClass + @"()
end

class """ + f.baseClass + @"""
function " + f.baseClass + @":__init()
    AddDrawCallback(function() self:OnDraw() end)
    AddTickCallback(function() self:OnTick() end)
end

function " + f.baseClass + @":OnDraw()
    
end

function " + f.baseClass + @":OnTick()
    
end";

            krbTabControl1.SelectedTab = tp;
        }
        #endregion


        #region ToolStrip
        private void toolStripButton9_Click(object sender, EventArgs e)
        {
            try
            {
                FastColoredTextBoxNS.FastColoredTextBox myTB = krbTabControl1.SelectedTab.Controls[0] as FastColoredTextBoxNS.FastColoredTextBox;
                bool error = false;
                lua.RegisterFunction("class", this, this.GetType().GetMethod("nullFunction"));
                try
                {
                    lua.DoString(Properties.Resources._class + myTB.Text);
                }
                catch (Exception ex)
                {
                    error = true;
                    toolStripStatusLabel1.Image = Properties.Resources._1;
                    toolStripStatusLabel1.Text = ex.Message;
                }
                finally
                {
                    if (!error)
                    {
                        toolStripStatusLabel1.Text = "Successfully Compiled";
                        toolStripStatusLabel1.Image = Properties.Resources._2;
                    }
                }
            }
            catch
            {

            }
        }

        private void toolStripButton16_Click(object sender, EventArgs e)
        {
            FastColoredTextBoxNS.FastColoredTextBox myTB = krbTabControl1.SelectedTab.Controls[0] as FastColoredTextBoxNS.FastColoredTextBox;
            if (myTB.Bookmarks.Contains(myTB.Selection.Start.iLine))
                myTB.Bookmarks.Remove(myTB.Selection.Start.iLine);
            else
                myTB.Bookmarks.Add(myTB.Selection.Start.iLine);

        }

        private void toolStripButton15_Click(object sender, EventArgs e)
        {
            FastColoredTextBoxNS.FastColoredTextBox myTB = krbTabControl1.SelectedTab.Controls[0] as FastColoredTextBoxNS.FastColoredTextBox;
            myTB.GotoPrevBookmark(myTB.Selection.Start.iLine);
        }

        private void toolStripButton17_Click(object sender, EventArgs e)
        {
            FastColoredTextBoxNS.FastColoredTextBox myTB = krbTabControl1.SelectedTab.Controls[0] as FastColoredTextBoxNS.FastColoredTextBox;
            myTB.GotoNextBookmark(myTB.Selection.Start.iLine);
        }
        #endregion


        private void AutoCompleteInit()
        {
            List<AutocompleteMenuNS.AutocompleteItem> items = new List<AutocompleteMenuNS.AutocompleteItem>();


            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("GetMyHero()") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("GetEnemyHeros()") { ImageIndex = 0 });

            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("OnLoad()") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("OnDraw()") { ImageIndex = 0 });

            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("OnTick()") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("OnUnload()") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("OnCreateObj(object)") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("OnDeleteObj(object)") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("OnWndMsg(msg,wParam)") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("OnProcessSpell(object,spellProc)") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("OnSendChat(text)") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("OnReset()") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("IsKeyPressed(wParam)") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("IsKeyDown(wParam)") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("CastSpell(iSpell)") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("CastSpell(iSpell,x,z)") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("CastSpell(iSpell,target)") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("LevelSpell(iSpell)") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("PrintChat(text)") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("SendChat(text)") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("BlockChat()") { ImageIndex = 0 });

            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("DrawText(text,size,x,y,ARGB)") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("DrawLine(x1, y1, x2, y2, size, ARGB)") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("DrawRectangle(x, y, width, height, ARGB)") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("DrawCircle(x,y,z,size,RGB)") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("PrintFloatText(target,iMode,text)") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("PingSignal(iMode,x,y,z,bPing)") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("GetTarget()") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("GetTickCount()") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("GetLatency()") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("GetCursorPos()") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("WorldToScreen(unit)") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("SetTarget(unit)") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("createSprite(szFile)") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("CLoLPacket(header)") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("SendPacket(LoLPacket)") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("BuyItem(itemID)") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("SellItem(iSlot)") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("IsItemPurchasable(itemID)") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("IsRecipePurchasable(recipeID)") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("DrawArrow(pos,arrowDir,fIdk1,fWidth,fIdk2,dwColor)") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("IsWallOfGrass(pos)") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("UpdateWindow()") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("GetKey(hotkey)") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("RGBA(r,g,b,a)") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("RGB(r,g,b )") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("test") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("test") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("test") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("test") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("test") { ImageIndex = 0 });
            items.Add(new AutocompleteMenuNS.SnippetAutocompleteItem("test") { ImageIndex = 0 });

            autocompleteMenu1.SetAutocompleteItems(items);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Working_Directory wd = new Working_Directory();
            wd.ShowDialog();
            path = wd.path;
            treeInit();
            AutoCompleteInit();
        }

        private void krbTabControl1_TabIndexChanged(object sender, EventArgs e)
        {
            var s = (TabPageEx)sender;
            MessageBox.Show(s.Name);
        }

        private void krbTabControl1_SelectedIndexChanged(object sender, EventArgs e)
        {
            FastColoredTextBoxNS.FastColoredTextBox myTB = krbTabControl1.SelectedTab.Controls[0] as FastColoredTextBoxNS.FastColoredTextBox;
            documentMap1.Target = myTB;
            saveToolStripMenuItem.Text = "Save " + myTB.Parent.Text;
            saveAsToolStripMenuItem.Text = "Save " + myTB.Parent.Text + "As...";
        }

        private void fastColoredTextBox1_SelectionChanged(object sender, EventArgs e)
        {
            var s = (FastColoredTextBox)sender;
            toolStripStatusLabel4.Text = "Current Line: " + (s.Selection.Start.iLine + 1) + "   Current Col: " + (s.Selection.Start.iChar);
        }

        

        private void lagFreeCirclesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FastColoredTextBoxNS.FastColoredTextBox myTB = krbTabControl1.SelectedTab.Controls[0] as FastColoredTextBoxNS.FastColoredTextBox;
            myTB.InsertText(Properties.Resources.LagFreeCircles);
            Range r = myTB.Range.Clone();
            r.End = new Place(myTB[myTB.LinesCount - 1].Count, myTB.LinesCount - 1);
            var pattern = Regex.Escape("function OnLoad()");
            foreach (var found in r.GetRanges(pattern))
            {
                myTB.Selection = found;
                myTB.Text.Insert(found.Start.iChar + 1, "test");
            }
        }

        private void toolStripButton18_Click(object sender, EventArgs e)
        {
            FastColoredTextBoxNS.FastColoredTextBox myTB = krbTabControl1.SelectedTab.Controls[0] as FastColoredTextBoxNS.FastColoredTextBox;
            myTB.ShowFindDialog();
        }

        private void toolStripButton3_Click(object sender, EventArgs e)
        {
            FastColoredTextBoxNS.FastColoredTextBox myTB = krbTabControl1.SelectedTab.Controls[0] as FastColoredTextBoxNS.FastColoredTextBox;
            myTB.SaveToFile("test.lua", Encoding.UTF8);
        }

        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            newPage();
        }

        private void toolStripButton19_Click(object sender, EventArgs e)
        {
            FastColoredTextBoxNS.FastColoredTextBox myTB = krbTabControl1.SelectedTab.Controls[0] as FastColoredTextBoxNS.FastColoredTextBox;
            myTB.ShowReplaceDialog();
        }

        
    }
}
