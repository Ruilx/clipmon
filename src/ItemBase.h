#ifndef ITEMBASE_H
#define ITEMBASE_H

#include <QApplication>

#include <QGraphicsItem>
#include <QGraphicsSimpleTextItem>

#include <QFont>

class ItemBase : public QGraphicsItem
{
	QGraphicsSimpleTextItem *title = new QGraphicsSimpleTextItem(this);

protected:
	int height = 25;
	int padding = 5;

	const int maxWidth = 640;

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

protected:
	virtual void renderDesc() = 0;

};

#endif // ITEMBASE_H
