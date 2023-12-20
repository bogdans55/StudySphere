#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>

enum Language
{
	SERBIAN,
	ENGLISH
};

enum Theme
{
	DARK,
	LIGHT
};

class Settings
{
  private:
	Language m_language;
	Theme m_theme;
	double m_volume;
	bool m_sound;

  public:
	Settings();
	~Settings();

	void setLanguage(const Language &newLanguage);
	void setTheme(const Theme &newTheme);
	void setVolume(const double &newVolume);
	void setSound(const bool &newSound);
};

#endif // SETTINGS_H
