#ifndef CLIPLISTITEM_H
#define CLIPLISTITEM_H

#include <QListWidgetItem>
#include <src/ClipMimeData.h>

#include <QRect>
#include <QPixmap>
#include <QImage>
#include <QPainter>
#include <QTextItem>

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
		QPixmap pixmap(64, 64);
		pixmap.fill(Qt::white);
		Utils::drawIconPlaceholder(&pixmap, QPen(Qt::black));
		this->setIcon(QIcon(pixmap));
		this->setClipMimeData(data);

	}

	void setClipMimeData(const ClipMimeData *data){
		this->data = data;
		QPixmap pixmap(64, 64);
		pixmap.fill(Qt::white);
		if(this->data->hasImage()){
			QImage image = qvariant_cast<QImage>(this->data->imageData());
			image = image.scaled(QSize(64, 64), Qt::KeepAspectRatioByExpanding);
			image = image.copy(qAbs(image.width() - 64) / 2, qAbs(image.height() - 64) / 2, 64, 64);
			this->setIcon(QIcon(QPixmap::fromImage(image)));
		}else if(this->data->hasText()){
			QPainter p(&pixmap);
			p.drawText(QRect(0, 0, 64, 64), Qt::AlignLeft, this->data->text());
			p.end();
			this->setIcon(QIcon(pixmap));
		}else if(this->data->hasHtml()){
			QPainter p(&pixmap);
			p.drawText(QRect(0, 0, 64, 64), Qt::AlignLeft, this->data->html());
			p.end();
		}else if(this->data->hasUrls()){
			QPainter p(&pixmap);
			p.drawText(QRect(0, 0, 64, 64), Qt::AlignLeft, QString(this->data->urls().join('\n')));
			p.end();
		}else{
			int start = 0;
			int height = QFontMetrics(this->font()).height();
			QPainter p(&pixmap);
			for(const QString &format: data->formats()){
				if(start + height >= height){
					break;
				}
				p.drawText(QPoint(0, start), format);
				start += height;
			}
			p.end();
		}
	}
};

#endif // CLIPLISTITEM_H
