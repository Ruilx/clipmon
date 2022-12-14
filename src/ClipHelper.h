#ifndef CLIPHELPER_H
#define CLIPHELPER_H

#include <QObject>

#include <src/Clipboard.h>
#include <src/ClipList.h>
#include <src/ClipListItem.h>
#include <src/ClipMimeData.h>

class ClipHelper : public QObject
{
	Q_OBJECT

	// 启用剪切板记录
	bool enable = true;

	int historySize = 55;

	Clipboard *clipboard = new Clipboard(this);

	ClipList *clipList = nullptr;

public:
	explicit ClipHelper(ClipList *clipList, QObject *parent = nullptr): QObject(parent){
		Q_ASSERT_X(list != nullptr, __FUNCTION__, "Cliplist is nullptr");
		this->list = list;

		this->connect(this->clipboard, &Clipboard::copied, [this](const ClipMimeData &data, bool owns){
			if(this->enable){
				qDebug() << "Enable! Get clipboard data";
				if(!owns){
					ClipListItem *item = new ClipListItem(data);
					this->clipList->insertItem(0, item);
					if(this->clipList->count() >= this->historySize){
						this->clipList->takeItem(this->clipList->count() -1);
					}
					qDebug() << "Count:" << this->clipList->count();
				}
			}
		});

		this->connect(this->clipList, &ClipList::copyToClipboard, [this](const QListWidgetItem *item){

		});
	}

signals:

};

#endif // CLIPHELPER_H
