#ifndef CLIPHELPER_H
#define CLIPHELPER_H

#include <QObject>
#include <QList>

#include <src/Clipboard.h>
#include <src/ClipList.h>
#include <src/ClipListItem.h>
#include <src/ClipMimeData.h>

class ClipHelper : public QObject
{
	Q_OBJECT

	bool enable = true;

	int historySize = 55;
	QList<ClipListItem *> clipDataList;

	ClipList *list = nullptr;

	Clipboard *clipboard = new Clipboard(this);
public:
	explicit ClipHelper(const ClipList *list, QObject *parent = nullptr) : QObject(parent){
		Q_ASSERT_X(list != nullptr, __FUNCTION__, "Cliplist is nullptr");
		this->list = list;
		this->connect(this->clipboard, &Clipboard::copied, [this](const ClipMimeData &data){
			if(this->enable){
				qDebug() << "Helper catch copied!";
				ClipListItem *item = new ClipListItem(new ClipMimeData(data), this);
				this->clipDataList.prepend(item);
				this->list->addItem(item);
				if(this->clipDataList.length() >= this->historySize){
					ClipListItem *i = this->clipDataList.takeLast();
					this->list->removeItemWidget(i);
				}
				qDebug() << this->clipDataList.length();
			}
		});

		this->connect(this->list, &ClipList)

		this->connect(this->clipboard, &Clipboard::modeChanged, [this](QClipboard::Mode mode){
			emit clipboardModeChanged(mode);
		});
	}

	int getHistorySize() const{
		return this->historySize;
	}

	void setHistorySize(int size){
		if(size <= 0){
			return;
		}
		if(this->clipDataList.length() > this->historySize){
			this->clipDataList = this->clipDataList.mid(0, size);
		}
		this->historySize = size;
	}

	int getHistoryCount() const{
		return this->clipDataList.length();
	}

	void clear(){
		this->clipDataList.clear();
	}

	void setEnable(bool enable){
		this->enable = enable;
	}

	bool getEnable() const{
		return this->enable;
	}

signals:
	void clipboardModeChanged(QClipboard::Mode mode);
};

#endif // CLIPHELPER_H
