#ifndef CLIPLIST_H
#define CLIPLIST_H

#include <QListWidget>
#include <QContextMenuEvent>


#include <QPixmap>
#include <QBrush>
#include <QIcon>

#include <QMenu>

#include <QDebug>

#include <src/Utils.h>

class ClipList : public QListWidget
{
	Q_OBJECT

	QMenu *menu = new QMenu("context", this);

	void setupPopupMenu(){
		this->menu->addAction(tr("&Copy to clipboard"), [this](){
			qDebug() << "Popup Menu: Copy to clipboard";
		});

		this->menu->addAction(tr("&Show descriptions"), [this](){
			qDebug() << "Popup Menu: Show descriptions";
		});

		this->menu->addSeparator();

		this->menu->addAction(tr("&Delete"), [this](){
			qDebug() << "Popup Menu: Delete";
		});
	}

	void contextMenuEvent(QContextMenuEvent *event){
		QListWidgetItem *item = this->itemAt(event->pos());
		if(item == nullptr){
			// Empty area
			return;
		}else{
			this->menu->exec(event->globalPos());
		}
	}
public:
	ClipList(QWidget *parent = nullptr): QListWidget(parent){
		this->setMinimumWidth(250);
		this->setMovement(QListWidget::Static);
		this->setSpacing(2);

		this->setIconSize(QSize(64, 64));

		this->setupPopupMenu();


		QPixmap pixmap(100, 100);
		pixmap.fill(Qt::gray);
		Utils::drawIconPlaceholder(&pixmap);
		QListWidgetItem *item = new QListWidgetItem(tr("MIAO"), this, 0);
		item->setIcon(QIcon(pixmap));

		item = new QListWidgetItem(tr("MIAO2"), this, 0);
		item->setIcon(QIcon(pixmap));

		this->connect(this, &ClipList::currentRowChanged, [this](int currentRow){
			qDebug() << "CurrentRowChanged";
		});
	}
};

#endif // CLIPLIST_H
