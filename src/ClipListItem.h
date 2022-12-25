#ifndef CLIPLISTITEM_H
#define CLIPLISTITEM_H

#include <QListWidgetItem>

#include <QPainter>
#include <QUrl>

#include <src/Global.h>
#include <src/ClipMimeData.h>

#include <src/Utils.h>

class ClipListItem : public QListWidgetItem
{
	ClipMimeData data;
public:
	ClipListItem(int type = Type): QListWidgetItem(nullptr, type){
		this->setDefaultIcon();
	}
	ClipListItem(const ClipMimeData &data, int type = Type): QListWidgetItem(nullptr, type){
		this->setClipMimeData(data);
	}

	void setDefaultIcon();
	void setToIcon(const QImage &image);
	void setToIcon(const QString &text);
	void setToIcon(const QList<QUrl> &urls);

	void setToText(){
		this->setText(Utils::mimeValue(this->data));
	}

	void setClipMimeData(const ClipMimeData &data){
		this->data = data;
		if(this->data.hasImage()){
			QImage image = qvariant_cast<QImage>(this->data.imageData());
			this->setToIcon(image);
		}else if(this->data.hasUrls()){
			this->setToIcon(this->data.urls());
		}else if(this->data.hasText()){
			this->setToIcon(this->data.text());
		}else if(this->data.hasHtml()){
			this->setToIcon(this->data.html());
		}else{
			this->setDefaultIcon();
		}
		this->setToText();
	}

	ClipMimeData* getClipMimeData(){
		return &(this->data);
	}
};

#endif // CLIPLISTITEM_H
