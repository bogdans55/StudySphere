#include <QApplication>
#include <QFile>

#include "lib/settings.h"

Settings::Settings()
    :m_language(SERBIAN), m_theme(LIGHT), m_volume(1.0), m_sound(true)
{
}

Settings::~Settings()
{
}

void Settings::setTheme(const Theme &newTheme)
{
    m_theme = newTheme;
    QString styleSheetPath;

    if (m_theme == DARK) {
        styleSheetPath = "../app/assets/Diffnes/Diffnes.qss";
    } else {
        styleSheetPath = "../app/assets/Medize/Medize.qss";
    }

    QFile styleSheetFile(styleSheetPath);
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    qApp->setStyleSheet(styleSheet);
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
