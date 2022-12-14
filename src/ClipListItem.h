#ifndef CLIPLISTITEM_H
#define CLIPLISTITEM_H

#include <QListWidgetItem>

#include <QPainter>

#include <src/Global.h>
#include <src/ClipMimeData.h>

#include <src/Utils.h>

class ClipListItem : public QListWidgetItem
{
	Q_OBJECT

	const ClipMimeData *data;
public:
	ClipListItem(int type = Type): QListWidgetItem(nullptr, type){}
	ClipListItem(const ClipMimeData *data, int type = Type): QListWidgetItem(nullptr, type){
		if(data == nullptr){
			this->setDefaultIcon();
			return;
		}
	}

	void setDefaultIcon(){
		QPixmap pixmap(IconSize);
		pixmap.fill(Qt::white);
		Utils::drawIconPlaceholder(&pixmap, QPen(Qt::black));
		this->setIcon(QIcon(pixmap));
	}

	void setToIcon(const QImage &image){
		QImage scaled = image.scaled(IconSize, Qt::KeepAspectRatioByExpanding);
		scaled = scaled.copy(qAbs(image.width() - IconSize.width()) / 2, qAbs(image.height() - IconSize.height()) / 2, IconSize.width(), IconSize.height());
		this->setIcon(QPixmap::fromImage(scaled));
	}

	void setToIcon(const QString &text){
		QPixmap pixmap(IconSize);
		QPainter p(&pixmap);
		p.drawText(QRect(QPoint(0, 0), IconSize), Qt::AlignLeft, text);
		p.end();
		this->setIcon(pixmap);
	}

	void setClipMimeData(const ClipMimeData *data){
		if(data == nullptr){
			return;
		}
		this->data = data;
		QPixmap pixmap(IconSize);
		pixmap.fill(Qt::white);
		if(this->data->hasImage()){

		}

	}
};

#endif // CLIPLISTITEM_H
