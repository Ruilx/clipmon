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
public:
	MainWindow(QWidget *parent = nullptr): QMainWindow(parent){
		this->setupMenus();
		this->setupWindow();

		// Signal to signal
		this->connect(this->helper, &ClipHelper::showTrayMessage, [this](const QString &title, const QString &message, QSystemTrayIcon::MessageIcon icon, int timeout){
			emit this->showTrayMessage(title, message, icon, timeout);
		});

		this->statusBar()->showMessage(tr("Ready."));
	}
	~MainWindow();

signals:
	void showTrayMessage(const QString &title, const QString &message, QSystemTrayIcon::MessageIcon icon, int timeout);

};
#endif // MAINWINDOW_H
