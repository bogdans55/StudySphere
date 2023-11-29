#ifndef CARDCONTENT_H
#define CARDCONTENT_H

#include <QImage>

class CardContent
{
public:
    CardContent();
    CardContent(QString &text);
    ~CardContent();

    void show();

    // Getters
    inline QString text() const {return m_text;}
    inline QImage image() const {return m_image;}

    // Setter
    void setImage(const QImage &image);
    void setText(const QString& text);

private:
    QString m_text;
    QImage m_image;
};


#endif // CARDCONTENT_H
