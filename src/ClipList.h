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
			ClipListItem *item = static_cast<ClipListItem*>(this->currentItem());
			if(item == nullptr){
				QWidget *parentOrSelf = this->parentWidget() == nullptr ? this : this->parentWidget();
				QMessageBox::critical(parentOrSelf, QApplication::applicationDisplayName(), tr("Not selected yet."), QMessageBox::Ok);
				return;
			}
			emit this->copyToClipboard(item);
		});

		this->menu->addAction(tr("&Show descriptions"), [this](){
			qDebug() << "Popup Menu: Show descriptions";
			QListWidgetItem *item = this->currentItem();
			if(item == nullptr){
				return;
			}
			emit this->itemSelected(static_cast<ClipListItem *>(item));
		});

		this->menu->addSeparator();

		this->menu->addAction(tr("&Delete"), [this](){
			qDebug() << "Popup Menu: Delete";
			QListWidgetItem *item = this->currentItem();
			if(item == nullptr){
				return;
			}
			emit this->remove(static_cast<ClipListItem *>(item));
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
			Q_UNUSED(old);
			qDebug() << "ClipList: CurrentItemChanged";
			emit this->itemSelected(static_cast<ClipListItem *>(item));
		});
	}

signals:
	void itemSelected(ClipListItem *item);
	void copyToClipboard(ClipListItem *item);
	void remove(ClipListItem *item);

};

#endif // CLIPLIST_H
