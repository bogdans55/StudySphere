#ifndef WHITEBOARDWINDOW_H
#define WHITEBOARDWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

namespace Ui
{
class WhiteboardWindow;
}

class WhiteboardWindow : public QWidget
{
	Q_OBJECT

  public:
	explicit WhiteboardWindow(QWidget *parent = nullptr);
	~WhiteboardWindow() override;

  protected:
	void paintEvent(QPaintEvent *event) override;

	void mousePressEvent(QMouseEvent *event) override;

	void mouseMoveEvent(QMouseEvent *event) override;

	void mouseReleaseEvent(QMouseEvent *event) override;

	void resizeEvent(QResizeEvent *event) override;

  private:
	Ui::WhiteboardWindow *ui;

	void drawLineTo(const QPoint &endPoint);

	QImage image;
	QPoint lastPoint;
	bool drawing;
	QColor penColor;
	int penWidth;

	void resizeImage(QImage *image, const QSize &newSize);
};

#endif // WHITEBOARDWINDOW_H
