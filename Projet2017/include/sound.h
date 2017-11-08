
#ifndef SOUND_IS_DEF
#define SOUND_IS_DEF


void sound_init (int enable, int music_ok);
void sound_clean ();

int sound_start_music ();
void sound_keep_music ();
void sound_stop_music ();
void sound_pause_music ();
void sound_resume_music ();
void sound_fade_channel (int channel, int ms);
void sound_stop_channel (int channel);
int sound_channel_playing (int channel);

enum {
  SOUND_CLOC,
  SOUND_JUMP,
  SOUND_BING,
  SOUND_SHOT,
  SOUND_BOUM,
  SOUND_YEEHA,
  SOUND_PSCHH,
  SOUND_BEEP,
  SOUND_REBOURS,
  SOUND_QUESTION,
  SOUND_TANK,
  SOUND_PLOP,
  SOUND_PLOUF,
  SOUND_BUBBLES,
  SOUND_TORPEDO,
  SOUND_DEFECT,
  NB_SOUNDS
};

int play_sound (unsigned sound);


#endif
