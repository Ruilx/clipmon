#ifndef HTMLITEM_H
#define HTMLITEM_H

#include <src/ItemBase.h>

#include <QGraphicsTextItem>

#include <QTextDocument>

class HtmlItem : public ItemBase
{
	QGraphicsTextItem *item = new QGraphicsTextItem(this);
	QString text;

	QRectF boundingRect() const override{
		return QRectF(0, 0, this->maxWidth, this->height + this->padding + this->item->boundingRect().height());
	}

public:
	HtmlItem(const QString &text, const QString &mimeString = QString(), QGraphicsItem *parent = nullptr): ItemBase{QObject::tr("[HTML] %1").arg(mimeString), parent}{
		this->text = text;
		this->mimeString = mimeString;
		QTextDocument *doc = this->item->document();
		doc->setTextWidth(this->maxWidth);
		QString displayText = this->text.left(1024);
		if(this->text.length() > 1024){
			displayText.append("...");
		}
		doc->setPlainText(displayText);
		QFont font = QApplication::font();
		font.setPointSize(12);
		this->item->setFont(font);
	}
};

#endif // HTMLITEM_H
