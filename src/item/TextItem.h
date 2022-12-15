#ifndef TEXTITEM_H
#define TEXTITEM_H

#include <src/ItemBase.h>

#include <QGraphicsTextItem>

#include <QTextDocument>

class TextItem : public ItemBase
{
	QGraphicsTextItem *item = new QGraphicsTextItem(this);

	void renderDesc() override{
		this->setPos(0, this->height + this->padding);
	}

	QRectF boundingRect() const override{
		return QRectF(0, 0, this->maxWidth, this->height + this->padding + this->item->boundingRect().height());
	}
public:
	TextItem(const QString &text, const QString &mimeString = QString(), QGraphicsItem *parent = nullptr): ItemBase(QObject::tr("[Text] %1").arg(mimeString), parent){
		QTextDocument *doc = this->item->document();
		doc->setTextWidth(this->maxWidth);
		doc->setPlainText(text);
		QFont font = QApplication::font();
		font.setPointSize(12);
		this->item->setFont(font);
	}


};

#endif // TEXTITEM_H
