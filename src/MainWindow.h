#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <src/Global.h>
#include <QApplication>
#include <QMainWindow>
#include <QDockWidget>
#include <QMenuBar>
#include <QStatusBar>
#include <QMenu>
#include <QAction>
#include <QInputDialog>
#include <QMessageBox>
#include <QSystemTrayIcon>

#include <QDebug>

#include <src/ClipHelper.h>
#include <src/ClipList.h>
#include <src/Preview.h>
#include <src/PreviewScene.h>

class MainWindow : public QMainWindow
{
	Q_OBJECT

	ClipList *clipList = new ClipList(this);
	Preview *preview = new Preview(this);

	ClipHelper *helper = new ClipHelper(this->clipList, this->preview, this);

	// Can be singleton
	PreviewScene *scenes = new PreviewScene(this);
	QGraphicsScene *errorScene = new QGraphicsScene(this);

	QDockWidget *previewWidget = new QDockWidget(tr("Preview"), this);

	QAction *showPreviewWindowAction = new QAction(tr("Show &Preview Window"), this);
	QAction *underMonitoringAction = new QAction(tr("Under &Monitoring"), this);
	QAction *closeAsExitAction = new QAction(tr("&Close window to Exit"), this);

	bool closeAsExit = false;

	void closeEvent(QCloseEvent *event){
		if(this->closeAsExit){
			event->accept();
			return;
		}
		event->ignore();
		if(this->isVisible()){
			this->hide();
		}
	}

	void setupWindow();
	void setupMenus();

	void setupErrorScene(){
		QFont font = QApplication::font();
		font.setPointSize(32);
		this->errorScene->addText(tr("Cannot display description."), font);
	}

	void setupClipList(){
		// 列表中选择
		this->connect(this->clipList, &ClipList::itemSelected, [this](const ClipListItem *item){
			if(this->preview->isVisible()){
				if(item == nullptr){
					qDebug() << "Cliplist::ItemSelected Slot:" << "ClipListItem *item is nullptr";
					return;
				}
				const ClipMimeData *data = item->getClipMimeData();
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
		this->connect(this->clipList, &ClipList::copyToClipboard, [this](const ClipListItem *item){
			if(item == nullptr){
				qDebug() << "Cliplist::copyToClipboard Slot:" << "ClipListItem *item is nullptr";
				return;
			}
			const ClipMimeData *data = item->getClipMimeData();
			if(data == nullptr){
				qDebug() << "Cliplist::copyToClipboard Slot:" << "ClipMimeData *data is nullptr";
				return;
			}
			this->helper->copyToClipboard(data);
			emit this->showTrayMessage(tr("Copied"), tr("Select data has been copied."), QSystemTrayIcon::Information, 5000);
		});

		// 列表中删除
		this->connect(this->clipList, &ClipList::remove, [this](const ClipListItem *item){
			if(item == nullptr){
				qDebug() << "Cliplist::remove Slot:" << "ClipListItem *item is nullptr";
				return;
			}
			const ClipMimeData *data = item->getClipMimeData();
			if(data == nullptr){
				qDebug() << "Cliplist::remove Slot:" << "ClipMimeData *data is nullptr";
				return;
			}
			QString id = data->getId();
			if(!id.isEmpty()){
				this->scenes->removeScene(id);
			}
		});
	}
public:
	MainWindow(QWidget *parent = nullptr): QMainWindow(parent){
		this->setupMenus();
		this->setupWindow();
		this->setupErrorScene();
		this->setupClipList();

		this->statusBar()->showMessage(tr("Ready."));
	}
	~MainWindow();

signals:
	void showTrayMessage(const QString &title, const QString &message, QSystemTrayIcon::MessageIcon icon, int timeout);

};
#endif // MAINWINDOW_H
