#include "ClipListItem.h"



void ClipListItem::setDefaultIcon(){
	QPixmap pixmap(IconSize);
	pixmap.fill(Qt::white);
	Utils::drawIconPlaceholder(&pixmap, QPen(Qt::black));
	this->setIcon(QIcon(pixmap));
}

void ClipListItem::setToIcon(const QImage &image){
	QImage scaled = image.scaled(IconSize, Qt::KeepAspectRatioByExpanding);
	scaled = scaled.copy(qAbs(image.width() - IconSize.width()) / 2, qAbs(image.height() - IconSize.height()) / 2, IconSize.width(), IconSize.height());
	this->setIcon(QPixmap::fromImage(scaled));
}

void ClipListItem::setToIcon(const QString &text){
	QPixmap pixmap(IconSize);
	pixmap.fill(Qt::white);
	QPainter p(&pixmap);
	p.drawText(QRect(QPoint(0, 0), IconSize), Qt::AlignLeft, text);
	p.end();
	this->setIcon(pixmap);
}

void ClipListItem::setToIcon(const QList<QUrl> &urls){
	QPixmap pixmap(IconSize);
	pixmap.fill(Qt::white);
	QStringList list;
	for(const QUrl &url: urls){
		list.append(url.toString());
	}
	QPainter p(&pixmap);
	p.drawText(QPoint(0, 0), list.join('\n'));
	p.end();
	this->setIcon(pixmap);
}
