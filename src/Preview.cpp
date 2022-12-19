#include "Preview.h"

#include <QMouseEvent>
#include <QWheelEvent>
#include <QResizeEvent>
#include <QScrollBar>

void Preview::mousePressEvent(QMouseEvent *event){
	if(event->buttons() & Qt::LeftButton){
		this->mouseMovePressed = true;
		this->lastPos = event->pos();
		return;
	}
}

void Preview::mouseReleaseEvent(QMouseEvent *event){
	Q_UNUSED(event);
	this->mouseMovePressed = false;
}

void Preview::mouseMoveEvent(QMouseEvent *event){
	if(this->mouseMovePressed){
		QPoint pos = event->pos();
		int dx = pos.x() - this->lastPos.x();
		int dy = pos.y() - this->lastPos.y();

		this->horizontalScrollBar()->setValue(this->horizontalScrollBar()->value() - dx);
		this->verticalScrollBar()->setValue(this->verticalScrollBar()->value() - dy);

		this->lastPos = pos;
	}
}

void Preview::wheelEvent(QWheelEvent *event){
	int angle = event->angleDelta().y();
	qreal factor = 1.1;
	if(angle < 0){
		factor = 1 / factor;
	}
	this->scale(factor, factor);
}

void Preview::resizeEvent(QResizeEvent *event){
	QGraphicsView::resizeEvent(event);
	this->fitInView(this->sceneRect(), Qt::KeepAspectRatio);
}








