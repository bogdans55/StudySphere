#include "lib/settings.h"

#include<QTranslator>
#include<QFile>

Settings& Settings::instance(QApplication* app) {
    static Settings settingsInstance(app);  // Static local variable ensures a single instance
    return settingsInstance;
}

Settings::Settings(QApplication* app)
    : m_app(app), m_theme(DARK), m_volume(1.0), m_sound(true)
{
    m_translator = new QTranslator;
}

Settings::~Settings()
{
    delete m_translator;
}

void Settings::setTheme(const int index)
{
    QString styleSheetName;

    switch (index) {
    case DARK:
        styleSheetName = "Diffnes";
        m_theme = DARK;
        break;
    case LIGHT:
        styleSheetName = "Medize";
        m_theme = LIGHT;
        break;
        // Add more cases for other themes if needed

    default:
        qDebug() << "Unsupported theme index!";
        return;
    }

    if (!styleSheetName.isEmpty()) {
        QString styleSheetPath = QString("../app/res/themes/%1.qss").arg(styleSheetName);
        QFile styleSheetFile(styleSheetPath);
        styleSheetFile.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(styleSheetFile.readAll());
        qApp->setStyleSheet(styleSheet);
        qDebug() << "Theme changed!" << m_theme;
    }
}


void Settings::setVolume(const double &newVolume)
{
    m_volume = newVolume;
}

void Settings::setSound(const bool &newSound)
{
    m_sound = newSound;
}

void Settings::setLanguage(const int index)
{
    QString languageFileName;

    switch (index) {
        case ENGLISH:
            languageFileName = "english";
            m_language = ENGLISH;
            break;
        case SERBIAN:
            languageFileName = "serbian";
            m_language = SERBIAN;
            break;
        // Add more cases for other languages

        default:
            qDebug() << "Unsupported language index!";
            return;
    }

    if (!languageFileName.isEmpty()) {
        QString filePath = QString("../app/res/languages/%1.qm").arg(languageFileName);
        if (m_translator->load(filePath)) {
            m_app->installTranslator(m_translator);
            qDebug() << "Translation done!" << m_language;
        } else {
            qDebug() << "Failed to load translation file:" << filePath;
        }
    }
}
