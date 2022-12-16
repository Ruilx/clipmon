#ifndef OTHERITEM_H
#define OTHERITEM_H

#include <src/ItemBase.h>

#include <src/Utils.h>

class OtherItem : public ItemBase
{
	qint64 size = 0;

	QRectF boundingRect() const override{
		return QRectF(0, 0, this->maxWidth, this->height);
	}

public:
	OtherItem(qint64 size, const QString &mimeString, QGraphicsItem *parent = nullptr): ItemBase{
		QObject::tr("[Binary] %1 Size: %2").arg(mimeString, Utils::formatNumber(size)), parent}, size{size}{
	}
};

#endif // OTHERITEM_H
