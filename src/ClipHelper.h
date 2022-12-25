#ifndef CLIPHELPER_H
#define CLIPHELPER_H

#include <QObject>
#include <QSystemTrayIcon>

#include <src/Clipboard.h>
#include <src/Preview.h>
#include <src/ClipList.h>
#include <src/ClipListItem.h>
#include <src/ClipMimeData.h>
#include <src/PreviewScene.h>

class ClipHelper : public QObject
{
	Q_OBJECT

	// 启用剪切板记录
	bool enable = true;

	int historySize = 55;

	Clipboard *clipboard = new Clipboard(this);

	ClipList *clipList = nullptr;
	Preview *preview = nullptr;

	// Can be singleton
	PreviewScene *scenes = new PreviewScene(this);
	QGraphicsScene *errorScene = new QGraphicsScene(this);

	void setupErrorScene(){
		QFont font = QApplication::font();
		font.setPointSize(32);
		this->errorScene->addText(tr("Cannot display description."), font);
	}

	void setupClipList(){
		// 列表中选择
		this->connect(this->clipList, &ClipList::itemSelected, [this](ClipListItem *item){
			if(this->preview->isVisible()){
				if(item == nullptr){
					qDebug() << "Cliplist::ItemSelected Slot:" << "ClipListItem *item is nullptr";
					return;
				}
				ClipMimeData *data = item->getClipMimeData();
				if(data == nullptr){
					qDebug() << "Cliplist::ItemSelected Slot:" << "ClipMimeData *data is nullptr";
					return;
				}
				QGraphicsScene *scene = this->scenes->getScene(data);
				if(scene == nullptr){
					qDebug() << "Cliplist::ItemSelected Slot:" << "PreviewScene::getScene() QGraphicsScene *scene is nullptr";
					scene = this->errorScene;
				}
				this->preview->setScene(scene);
			}
		});

		// 列表中复制
		this->connect(this->clipList, &ClipList::copyToClipboard, [this](ClipListItem *item){
			if(item == nullptr){
				qDebug() << "Cliplist::copyToClipboard Slot:" << "ClipListItem *item is nullptr";
				return;
			}
			ClipMimeData *data = item->getClipMimeData();
			if(data == nullptr){
				qDebug() << "Cliplist::copyToClipboard Slot:" << "ClipMimeData *data is nullptr";
				return;
			}
			this->copyToClipboard(data);
			emit this->showTrayMessage(tr("Copied"), tr("Select data has been copied."), QSystemTrayIcon::Information, 5000);
		});

		// 列表中删除
		this->connect(this->clipList, &ClipList::remove, [this](ClipListItem *item){
			if(item == nullptr){
				qDebug() << "Cliplist::remove Slot:" << "ClipListItem *item is nullptr";
				return;
			}
			ClipMimeData *data = item->getClipMimeData();
			if(data == nullptr){
				qDebug() << "Cliplist::remove Slot:" << "ClipMimeData *data is nullptr";
				return;
			}
			QString id = data->getId();
			if(!id.isEmpty()){
				this->scenes->removeScene(id);
			}
			QListWidgetItem *i = this->clipList->takeItem(this->clipList->row(item));
			if(i != nullptr){
				delete i;
				i = nullptr;
			}
		});
	}

public:
	explicit ClipHelper(ClipList *clipList, Preview *preview, QObject *parent = nullptr): QObject(parent){
		Q_ASSERT_X(clipList != nullptr, __FUNCTION__, "Cliplist is nullptr");
		this->clipList = clipList;

		Q_ASSERT_X(preview != nullptr, __FUNCTION__, "Preview is nullptr");
		this->preview = preview;

		this->setupErrorScene();
		this->setupClipList();

		// 剪切板有新消息
		this->connect(this->clipboard, &Clipboard::copied, [this](const ClipMimeData &data, bool owns){
			if(this->enable){
				qDebug() << "Enable! Get clipboard data";
				if(!owns){
					qDebug() << "Data:" << Utils::toString(data);
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
	}

	inline void setEnable(bool e){ this->enable = e; }
	inline bool getEnable() const{ return this->enable; }

	inline void setHistorySize(int size){ this->historySize = size; }
	inline int getHistorySize() const { return this->historySize; }
	inline int getHistoryCount() const { return this->clipList->count(); }

//	inline const PreviewScene *getPreviewScenes(){
//		return this->scenes;
//	}

	void clear(){
		this->clipList->clear();
		this->scenes->clear();
	}

 signals:
	void clipModeChanged(QClipboard::Mode mode);

	void showTrayMessage(const QString &title, const QString &message, QSystemTrayIcon::MessageIcon icon, int timeout);


public slots:
	void copyToClipboard(const ClipMimeData *data){
		this->clipboard->setData(*data);
	}
};

#endif // CLIPHELPER_H
