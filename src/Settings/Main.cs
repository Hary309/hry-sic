using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Windows.Forms;

using Newtonsoft.Json;
using System.Diagnostics;

namespace Settings
{
	public partial class Main : Form
	{
		string currentSettingsFile = "sic_settings.txt";

		bool firstTime = true;

		SettingsData newSettings;

		public Main()
		{
			InitializeComponent();
		}

		private void SpeedTrackBar_ValueChanged(object sender, EventArgs e)
		{
			speedNumeric.Value = speedTrackBar.Value;
			newSettings.speed = speedTrackBar.Value;
		}

		private void SpeedNumeric_ValueChanged(object sender, EventArgs e)
		{
			speedTrackBar.Value = Convert.ToInt32(speedNumeric.Value);
			newSettings.speed = Convert.ToInt32(speedNumeric.Value);
		}

		void SaveSettings()
		{
			try
			{
				var currSettings = JsonConvert.DeserializeObject<SettingsData>(File.ReadAllText(currentSettingsFile));

				currSettings.active = newSettings.active;
				currSettings.disable_shortcuts = newSettings.disable_shortcuts;
				currSettings.speed = newSettings.speed;
				currSettings.rotation_style = newSettings.rotation_style;

				File.WriteAllText(currentSettingsFile, JsonConvert.SerializeObject(currSettings));

				if (firstTime)
				{
					Process[] process = Process.GetProcessesByName("eurotrucks2");

					if (process.Length != 0)
						MessageBox.Show("Saved! Press Home button in game to see the changes, if it isn't working, restart game.", "Info", MessageBoxButtons.OK, MessageBoxIcon.Information);

					firstTime = false;
				}
			}
			catch (Exception ex)
			{
				MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
				this.Close();
			}
		}

		bool LoadSettings()
		{
			try
			{
				if (!File.Exists(currentSettingsFile))
				{
					MessageBox.Show("Settings file not found!\nSettings file is creating while running game. So first run game then run this.", "Info", MessageBoxButtons.OK, MessageBoxIcon.Information);
					return false;
				}

				var settings = JsonConvert.DeserializeObject<SettingsData>(File.ReadAllText(currentSettingsFile));
				newSettings = settings;

				activeCheckBox.Checked = settings.active;
				disableScCheckBox.Checked = settings.disable_shortcuts;

				switch (settings.rotation_style)
				{
					case 0:
						rotStyleBox.Text = "Linear";
						break;
					case 1:
						rotStyleBox.Text = "Smooth";
						break;
				}

				if (settings.speed > speedTrackBar.Maximum)
				{
					MessageBox.Show("Speed value is too high!", "Error!", MessageBoxButtons.OK, MessageBoxIcon.Error);
					this.Close();
				}
				speedTrackBar.Value = settings.speed;
				speedNumeric.Value = settings.speed;
			}
			catch (Exception ex)
			{
				MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
				this.Close();
			}

			return true;
		}

		private void Main_Shown(object sender, EventArgs e)
		{
			if (!LoadSettings())
				this.Close();
		}

		private void LoadButton_Click(object sender, EventArgs e) => LoadSettings();

		private void SaveButton_Click(object sender, EventArgs e) => SaveSettings();

		private void ActiveCheckBox_CheckedChanged(object sender, EventArgs e) => newSettings.active = activeCheckBox.Checked;

		private void DisableScCheckBox_CheckedChanged(object sender, EventArgs e) => newSettings.disable_shortcuts = disableScCheckBox.Checked;

		private void RotStyleBox_SelectedIndexChanged(object sender, EventArgs e) => newSettings.rotation_style = rotStyleBox.SelectedIndex;
	}
}
