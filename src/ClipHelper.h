#ifndef CLIPHELPER_H
#define CLIPHELPER_H

#include <QObject>

#include <src/Clipboard.h>
#include <src/Preview.h>
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
	Preview *preview = nullptr;

public:
	explicit ClipHelper(ClipList *clipList, Preview *preview, QObject *parent = nullptr): QObject(parent){
		Q_ASSERT_X(clipList != nullptr, __FUNCTION__, "Cliplist is nullptr");
		this->clipList = clipList;

		Q_ASSERT_X(preview != nullptr, __FUNCTION__, "Preview is nullptr");
		this->preview = preview;

		// 剪切板有新消息
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

		// 剪切板模式改变
		this->connect(this->clipboard, &Clipboard::modeChanged, [this](QClipboard::Mode mode){
			emit clipModeChanged(mode);
		});

		//列表要求复制内容至剪切板
		this->connect(this->clipList, &ClipList::copyToClipboard, [this](const ClipListItem *item){
			if(item == nullptr){
				qDebug() << "Ready to Copy nullptr to Clipboard";
				return;
			}
			const ClipMimeData *mimeData = item->getClipMimeData();
			this->clipboard->setData(*mimeData);
		});

		//列表内容点击
		this->connect(this->clipList, &ClipList::currentRowChanged, [this](int row){

		});
	}

signals:
	void clipModeChanged(QClipboard::Mode mode);
};

#endif // CLIPHELPER_H
