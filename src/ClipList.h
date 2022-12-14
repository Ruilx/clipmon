#ifndef CLIPLIST_H
#define CLIPLIST_H

#include <QApplication>
#include <QListWidget>
#include <QContextMenuEvent>
#include <QMessageBox>
#include <QMenu>

#include <QPixmap>
#include <QIcon>

#include <QDebug>

#include <src/ClipListItem.h>
#include <src/Utils.h>
#include <src/Global.h>

class ClipList : public QListWidget
{
	Q_OBJECT

	QMenu *menu = new QMenu("context", this);

	void setupPopupMenu(){
		this->menu->addAction(tr("&Copy to clipboard"), [this](){
			qDebug() << "Popup Menu: Copy to clipboard";
			QListWidgetItem *item = this->currentItem();
			if(item == nullptr){
				QWidget *parentOrSelf = this->parentWidget() == nullptr ? this : this->parentWidget();
				QMessageBox::critical(parentOrSelf, QApplication::applicationDisplayName(), tr("Not selected yet."), QMessageBox::Ok);
				return;
			}
			emit this->copyToClipboard(this->currentItem());
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
		this->setIconSize(IconSize);

		this->setupPopupMenu();

		this->connect(this, &ClipList::currentItemChanged, [this](QListWidgetItem *item, QListWidgetItem *old){
			qDebug() << "ClipList: CurrentItemChanged";
		});
	}

signals:
	void itemSelected(const ClipListItem *item);
	void copyToClipboard(const ClipListItem *item);
	void remove(const ClipListItem *item);

};

#endif // CLIPLIST_H
