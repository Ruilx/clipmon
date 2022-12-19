#ifndef PREVIEW_H
#define PREVIEW_H

#include <QGraphicsView>

class Preview : public QGraphicsView
{
	Q_OBJECT

	QPointF lastPos;
	qreal currentScale = 1.0f;
	bool mouseMovePressed = false;

	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;

	void wheelEvent(QWheelEvent *event) override;

	void resizeEvent(QResizeEvent *event) override;

	QGraphicsScene *scene = new QGraphicsScene(this);
public:
	Preview(QWidget *parent = nullptr): QGraphicsView(parent){
		QPalette pal;{
			pal.setColor(QPalette::Base, Qt::lightGray);
			pal.setColor(QPalette::Background, Qt::lightGray);
		}
		this->setPalette(pal);
		this->setMinimumSize(500, 100);

		this->setRenderHint(QPainter::TextAntialiasing);

		this->setDragMode(QGraphicsView::RubberBandDrag);
		this->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
		this->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

		this->setInteractive(false);

		this->setScene(this->scene);
	}
};

#endif // PREVIEW_H
