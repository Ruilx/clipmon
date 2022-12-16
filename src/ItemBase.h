#ifndef ITEMBASE_H
#define ITEMBASE_H

#include <QApplication>

#include <QGraphicsItem>
#include <QGraphicsSimpleTextItem>

#include <QFont>

class ClipMimeData;
class ItemBase : public QGraphicsItem
{
protected:
	QGraphicsSimpleTextItem *title = new QGraphicsSimpleTextItem(this);

	QString mimeString;

	int height = 25;
	int padding = 5;

	const int maxWidth = 640;

	virtual const ClipMimeData toClipMimeData() = 0;

public:
	ItemBase(const QString &title, QGraphicsItem *parent = nullptr): QGraphicsItem(parent){
		QFont font = QApplication::font();
		font.setPointSize(12);
		this->title->setFont(font);
		this->setTitle(title);
		this->title->setPos(0, 0);
	}

	void setTitle(const QString &title){
		QString t;
		if(title.length() > 100){
			t = title.left(100) + "...";
		}else{
			t = title;
		}
		this->title->setText(t);
		this->height = this->title->boundingRect().height();
	}

	QString getTitle() const{
		return this->title->text();
	}
};

#endif // ITEMBASE_H
