using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Settings
{
	class SettingsData
	{
		public bool active { get; set; }
		public bool disable_shortcuts { get; set; }
		public double interior_look_forward { get; set; }
		public double interior_look_left { get; set; }
		public double interior_look_right { get; set; }
		public double interior_look_up_left { get; set; }
		public double interior_look_up_middle { get; set; }
		public double interior_look_up_right { get; set; }
		public int rotation_style { get; set; }
		public int speed { get; set; }
		public int version { get; set; }
	}
}
