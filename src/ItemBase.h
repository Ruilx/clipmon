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

	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:
	ItemBase(const QString &title, QGraphicsItem *parent = nullptr): QGraphicsItem(parent){
		QFont font = QApplication::font();
		font.setPointSize(12);
		font.setWeight(QFont::Bold);
		this->title->setFont(font);
		this->setTitle(title);
		this->title->setPos(0, 0);

		this->setFlag(QGraphicsItem::ItemIsSelectable, true);
		this->setFlag(QGraphicsItem::ItemIsMovable, true);
	}

	void setTitle(const QString &title){
		QString t;
		if(title.length() > 512){
			t = title.left(512) + "...";
		}else{
			t = title;
		}
		this->title->setText(t);
		this->height = this->title->boundingRect().height();
	}

	QString getTitle() const{
		return this->title->text();
	}

	const ClipMimeData getClipMimeData();
};

#endif // ITEMBASE_H
