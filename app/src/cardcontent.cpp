#include "lib/cardcontent.h"

#include <QImage>

CardContent::CardContent(std::string &text)
    :m_text(text)
{}

CardContent::~CardContent()
{}

void show() {
}

// Setter
void CardContent::setImage(const QImage &image) {
    m_image = image;
}
