#ifndef CARDCONTENT_H
#define CARDCONTENT_H

#include <QImage>

class CardContent
{
public:
    CardContent(std::string &text);
    ~CardContent();

    void show();

    // Getters
    inline std::string getText() const {return m_text;}
    inline QImage getImage() const {return m_image;}

    // Setter
    void setImage(const QImage &image);

private:
    std::string m_text;
    QImage m_image;
};


#endif // CARDCONTENT_H
