#pragma once

namespace Yelo
{
	namespace Enums
	{
		enum ui_audio_feedback_sound
		{
			_ui_audio_feedback_sound_cursor,
			_ui_audio_feedback_sound_forward,
			_ui_audio_feedback_sound_back,
			_ui_audio_feedback_sound_flag_failure,
		};
	};

	namespace UIWidgets
	{
		void PlayAudioFeedbackSound(Enums::ui_audio_feedback_sound type);

		s_ui_widget_instance* LoadByNameOrTag(datum_index ui_widget_definition_index, const char * name = nullptr,
			s_ui_widget_instance* parent = nullptr, 
			// don't set ctrl'er index unless you specify the last three params as well
			short controller_index = NONE,
			datum_index topmost_widget_definition_index = datum_index::null,
			datum_index parent_widget_definition_index = datum_index::null,
			short child_index_from_parent = NONE);

		bool DisplayScriptedWidget(const char * name);
	};
};
