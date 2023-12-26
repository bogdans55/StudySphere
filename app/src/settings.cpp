#include <QApplication>
#include <QFile>

#include "lib/settings.h"

Settings::Settings() : m_language(SERBIAN), m_theme(DARK), m_volume(1.0), m_sound(true) {}

void Settings::setTheme(const Theme &newTheme)
{
	m_theme = newTheme;
}

void Settings::setVolume(const double &newVolume)
{
	m_volume = newVolume;
}

void Settings::setSound(const bool &newSound)
{
	m_sound = newSound;
}

void Settings::setLanguage(const Language &newLanguage)
{
	m_language = newLanguage;
}
