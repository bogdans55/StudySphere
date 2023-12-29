#include "lib/whiteboardwindow.h"
#include "ui_whiteboardwindow.h"

#include "lib/studysessionwindow.h"

WhiteboardWindow::WhiteboardWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WhiteboardWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StaticContents);
    image = QImage(size(), QImage::Format_RGB32);
    image.fill(Qt::white);
    drawing = false;
    penColor = Qt::black;
    penWidth = 4;

//    connect(this, &WhiteboardWindow::destroyed, this, &StudySessionWindow::clearWhiteboard);
}

WhiteboardWindow::~WhiteboardWindow()
{
    delete ui;
}

void WhiteboardWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, image);
}

void WhiteboardWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton) {
        lastPoint = event->pos();
        drawing = true;
        if (event->button() == Qt::RightButton) {
            penColor = Qt::white;
        } else {
            penColor = Qt::black;
        }
    }
}

void WhiteboardWindow::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton || event->buttons() & Qt::RightButton) && drawing) {
        drawLineTo(event->pos());
    }
}

void WhiteboardWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if ((event->button() == Qt::LeftButton || event->button() == Qt::RightButton) && drawing) {
        drawLineTo(event->pos());
        drawing = false;
    }
}

void WhiteboardWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
}

void WhiteboardWindow::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&image);
    painter.setPen(QPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    lastPoint = endPoint;
    update();
}

void WhiteboardWindow::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(Qt::white);
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}
