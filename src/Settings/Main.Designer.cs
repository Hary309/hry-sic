namespace Settings
{
    partial class Main
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.titleLabel = new System.Windows.Forms.Label();
            this.speedTrackBar = new System.Windows.Forms.TrackBar();
            this.speedLabel = new System.Windows.Forms.Label();
            this.speedNumeric = new System.Windows.Forms.NumericUpDown();
            this.activeCheckBox = new System.Windows.Forms.CheckBox();
            this.disableScCheckBox = new System.Windows.Forms.CheckBox();
            this.loadButton = new System.Windows.Forms.Button();
            this.saveButton = new System.Windows.Forms.Button();
            this.rotStyleBox = new System.Windows.Forms.ComboBox();
            this.rStyleLabel = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.speedTrackBar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.speedNumeric)).BeginInit();
            this.SuspendLayout();
            // 
            // titleLabel
            // 
            this.titleLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 36F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.titleLabel.Location = new System.Drawing.Point(12, 9);
            this.titleLabel.Name = "titleLabel";
            this.titleLabel.Size = new System.Drawing.Size(329, 55);
            this.titleLabel.TabIndex = 0;
            this.titleLabel.Text = "SIC - Settings";
            this.titleLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // speedTrackBar
            // 
            this.speedTrackBar.AutoSize = false;
            this.speedTrackBar.Location = new System.Drawing.Point(66, 130);
            this.speedTrackBar.Maximum = 100;
            this.speedTrackBar.Minimum = 1;
            this.speedTrackBar.Name = "speedTrackBar";
            this.speedTrackBar.Size = new System.Drawing.Size(193, 32);
            this.speedTrackBar.TabIndex = 1;
            this.speedTrackBar.TickFrequency = 10;
            this.speedTrackBar.TickStyle = System.Windows.Forms.TickStyle.None;
            this.speedTrackBar.Value = 75;
            this.speedTrackBar.ValueChanged += new System.EventHandler(this.SpeedTrackBar_ValueChanged);
            // 
            // speedLabel
            // 
            this.speedLabel.AutoSize = true;
            this.speedLabel.Location = new System.Drawing.Point(19, 130);
            this.speedLabel.Name = "speedLabel";
            this.speedLabel.Size = new System.Drawing.Size(41, 13);
            this.speedLabel.TabIndex = 3;
            this.speedLabel.Text = "Speed:";
            this.speedLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // speedNumeric
            // 
            this.speedNumeric.Increment = new decimal(new int[] {
            5,
            0,
            0,
            0});
            this.speedNumeric.Location = new System.Drawing.Point(266, 130);
            this.speedNumeric.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.speedNumeric.Name = "speedNumeric";
            this.speedNumeric.Size = new System.Drawing.Size(57, 20);
            this.speedNumeric.TabIndex = 4;
            this.speedNumeric.Value = new decimal(new int[] {
            75,
            0,
            0,
            0});
            this.speedNumeric.ValueChanged += new System.EventHandler(this.SpeedNumeric_ValueChanged);
            // 
            // activeCheckBox
            // 
            this.activeCheckBox.AutoSize = true;
            this.activeCheckBox.Checked = true;
            this.activeCheckBox.CheckState = System.Windows.Forms.CheckState.Checked;
            this.activeCheckBox.Location = new System.Drawing.Point(22, 81);
            this.activeCheckBox.Name = "activeCheckBox";
            this.activeCheckBox.Size = new System.Drawing.Size(71, 17);
            this.activeCheckBox.TabIndex = 6;
            this.activeCheckBox.Text = "Activated";
            this.activeCheckBox.UseVisualStyleBackColor = true;
            this.activeCheckBox.CheckedChanged += new System.EventHandler(this.ActiveCheckBox_CheckedChanged);
            // 
            // disableScCheckBox
            // 
            this.disableScCheckBox.AutoSize = true;
            this.disableScCheckBox.Location = new System.Drawing.Point(100, 80);
            this.disableScCheckBox.Name = "disableScCheckBox";
            this.disableScCheckBox.Size = new System.Drawing.Size(101, 17);
            this.disableScCheckBox.TabIndex = 7;
            this.disableScCheckBox.Text = "Disable hotkeys";
            this.disableScCheckBox.UseVisualStyleBackColor = true;
            this.disableScCheckBox.CheckedChanged += new System.EventHandler(this.DisableScCheckBox_CheckedChanged);
            // 
            // loadButton
            // 
            this.loadButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.loadButton.Location = new System.Drawing.Point(185, 189);
            this.loadButton.Name = "loadButton";
            this.loadButton.Size = new System.Drawing.Size(75, 23);
            this.loadButton.TabIndex = 8;
            this.loadButton.Text = "Load";
            this.loadButton.UseVisualStyleBackColor = true;
            this.loadButton.Click += new System.EventHandler(this.LoadButton_Click);
            // 
            // saveButton
            // 
            this.saveButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.saveButton.Location = new System.Drawing.Point(266, 189);
            this.saveButton.Name = "saveButton";
            this.saveButton.Size = new System.Drawing.Size(75, 23);
            this.saveButton.TabIndex = 9;
            this.saveButton.Text = "Save";
            this.saveButton.UseVisualStyleBackColor = true;
            this.saveButton.Click += new System.EventHandler(this.SaveButton_Click);
            // 
            // rotStyleBox
            // 
            this.rotStyleBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.rotStyleBox.FormattingEnabled = true;
            this.rotStyleBox.Items.AddRange(new object[] {
            "Linear",
            "EaseInOut",
            "EaseOut"});
            this.rotStyleBox.Location = new System.Drawing.Point(100, 103);
            this.rotStyleBox.Name = "rotStyleBox";
            this.rotStyleBox.Size = new System.Drawing.Size(121, 21);
            this.rotStyleBox.TabIndex = 10;
            this.rotStyleBox.SelectedIndexChanged += new System.EventHandler(this.RotStyleBox_SelectedIndexChanged);
            // 
            // rStyleLabel
            // 
            this.rStyleLabel.AutoSize = true;
            this.rStyleLabel.Location = new System.Drawing.Point(19, 106);
            this.rStyleLabel.Name = "rStyleLabel";
            this.rStyleLabel.Size = new System.Drawing.Size(74, 13);
            this.rStyleLabel.TabIndex = 11;
            this.rStyleLabel.Text = "Rotation style:";
            // 
            // Main
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(353, 224);
            this.Controls.Add(this.rStyleLabel);
            this.Controls.Add(this.rotStyleBox);
            this.Controls.Add(this.saveButton);
            this.Controls.Add(this.loadButton);
            this.Controls.Add(this.disableScCheckBox);
            this.Controls.Add(this.activeCheckBox);
            this.Controls.Add(this.speedLabel);
            this.Controls.Add(this.speedTrackBar);
            this.Controls.Add(this.titleLabel);
            this.Controls.Add(this.speedNumeric);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "Main";
            this.Text = "SIC - Settings";
            this.Shown += new System.EventHandler(this.Main_Shown);
            ((System.ComponentModel.ISupportInitialize)(this.speedTrackBar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.speedNumeric)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label titleLabel;
        private System.Windows.Forms.TrackBar speedTrackBar;
        private System.Windows.Forms.Label speedLabel;
        private System.Windows.Forms.NumericUpDown speedNumeric;
        private System.Windows.Forms.CheckBox activeCheckBox;
        private System.Windows.Forms.CheckBox disableScCheckBox;
        private System.Windows.Forms.Button loadButton;
        private System.Windows.Forms.Button saveButton;
		private System.Windows.Forms.ComboBox rotStyleBox;
		private System.Windows.Forms.Label rStyleLabel;
	}
}

