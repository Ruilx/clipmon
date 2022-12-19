#ifndef OTHERITEM_H
#define OTHERITEM_H

#include <src/ItemBase.h>

#include <src/ClipMimeData.h>
#include <src/Utils.h>

class OtherItem : public ItemBase
{
	QByteArray data;

	QRectF boundingRect() const override{
		return QRectF(0, 0, this->maxWidth, this->height);
	}

	const ClipMimeData toClipMimeData() override{
		ClipMimeData mimeData;
		mimeData.setData(this->mimeString, this->data);
		return mimeData;
	}

public:
	OtherItem(const QByteArray &data, const QString &mimeString, QGraphicsItem *parent = nullptr): ItemBase{
		QObject::tr("[Binary] %1 Size: %2").arg(mimeString, Utils::formatNumber(data.length())), parent}, data{data}{
	}
};

#endif // OTHERITEM_H
