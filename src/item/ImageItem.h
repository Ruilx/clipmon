#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include <src/ItemBase.h>

#include <QGraphicsPixmapItem>

#include <QTextDocument>

#include <QPainter>
#include <QPixmap>
#include <QImage>

#include <src/Utils.h>

class ImageItem : public ItemBase
{
	QGraphicsPixmapItem *item = new QGraphicsPixmapItem(this);
	QImage image;

	QRectF boundingRect() const override{
		return QRectF(0, 0, this->maxWidth, this->height + this->padding + this->item->boundingRect().height());
	}

public:
	ImageItem(const QImage &image, const QString &mimeString = QString(), QGraphicsItem *parent = nullptr)
		: ItemBase(QObject::tr("[Image] %1 Size: (%2, %3) Format: %4").arg(mimeString).arg(image.width()).arg(image.height()).arg(Utils::imageFormat(image.format())), parent){

		this->image = image;
		this->mimeString = mimeString;
		QPixmap transformed;
		if(pixmap.width() > this->maxWidth){
			transformed = QPixmap::fromImage(image.scaledToWidth(this->maxWidth));
		}else{
			transformed = QPixmap::fromImage(pixmap);
		}
		if(transformed.height() > this->maxWidth * 2.25){
			transformed = transformed.copy(0, 0, transformed.width(), this->maxWidth * 2.25);
			int height = QFontMetrics(this->title->font()).height();

			QPainter p(&transformed);
			p.setPen(Qt::white);
			p.drawText(QRectF(0, transformed.height() - height, transformed.width(), height), QObject::tr("<CLIPPED>"));
			p.end();
		}
		this->item->setPixmap(transformed);
	}
};

#endif // IMAGEITEM_H
