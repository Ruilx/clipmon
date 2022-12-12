#ifndef CLIPLISTITEM_H
#define CLIPLISTITEM_H

#include <QListWidgetItem>
#include <src/ClipMimeData.h>

class QListWidget;
class ClipListItem : public QListWidgetItem
{
	const ClipMimeData *data;
public:
	ClipListItem(QListWidget *parent = nullptr, int type = QListWidgetItem::Type): QListWidgetItem(parent, type){}
//	ClipListItem(const QString &text, QListWidget *parent = nullptr, int type = QListWidgetItem::Type): QListWidgetItem(text, parent, type){}
//	ClipListItem(const QIcon &icon, const QString &text, QListWidget *parent = nullptr, int type = QListWidgetItem::Type): QListWidgetItem(icon, text, parent, type){}
	ClipListItem(const ClipMimeData *data, QListWidget *parent = nullptr, int type = QListWidgetItem::Type): QListWidgetItem(parent, type){
		if(data == nullptr){
			return;
		}
		this->setIcon(QIcon());
		this->setClipMimeData(data);

	}

	void setClipMimeData(const ClipMimeData *data){
		this->data = data;
	}
};

#endif // CLIPLISTITEM_H
