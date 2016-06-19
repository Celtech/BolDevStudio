using System;
using Aga.Controls.Tree;
using System.Drawing;

namespace BoL_Dev_Studio
{
    public class MyNode : Node
    {
        private Image _icon;
        public Image Icon
        {
            get { return _icon; }
            set { _icon = value; }
        }

        public override string Text
        {
            get
            {
                return base.Text;
            }
            set
            {
                if (string.IsNullOrEmpty(value))
                    throw new ArgumentNullException();

                base.Text = value;
            }
        }

        private bool _checked;
        /// <summary>
        /// Whether the box is checked or not.
        /// </summary>
		public bool Checked
        {
            get { return _checked; }
            set { _checked = value; }
        }

        /// <summary>
        /// Initializes a new MyNode class with a given Text property.
        /// </summary>
        /// <param name="text">String to set the text property with.</param>
		public MyNode(string text, Image icon)
            : base(text)
        {
            _icon = icon;
        }
    }
}
