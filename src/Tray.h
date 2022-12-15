#ifndef TRAY_H
#define TRAY_H

#include <QApplication>
#include <QSystemTrayIcon>
#include <QMainWindow>
#include <QPixmap>
#include <QTimer>
#include <QIcon>
#include <QMenu>

#include <QDebug>

#include <src/Utils.h>

class Tray : public QObject
{
	Q_OBJECT

	QMainWindow *mainWindow = nullptr;

	QMenu *menu = new QMenu(this->mainWindow);
	QSystemTrayIcon *tray = new QSystemTrayIcon(this);

	void setupPopupMenu(){
		this->menu->addAction(tr("&Open Main Window..."), [this](){
			qDebug() << "Open Main Menu...";
			if(!this->mainWindow->isVisible()){
				this->mainWindow->show();
			}
		});

		this->menu->addSeparator();

		this->menu->addAction(tr("&Exit"), [](){
			qApp->exit();
		});
	}

	void setupTray(){
		QPixmap pixmap = QPixmap(16, 16);
		pixmap.fill(Qt::transparent);
		Utils::drawIconPlaceholder(&pixmap);
		this->tray->setIcon(QIcon(pixmap));
		this->tray->setContextMenu(this->menu);
	}
public:
	Tray(QMainWindow *mainWindow, QObject *parent = nullptr): QObject(parent){
		this->mainWindow = mainWindow;
		this->setupTray();
		this->setupPopupMenu();

		this->connect(this->tray, &QSystemTrayIcon::activated, [this](QSystemTrayIcon::ActivationReason reason){
			qDebug() << "Tray," << reason;
			if(reason == QSystemTrayIcon::DoubleClick){
				qDebug() << "Tray, Double click";
				if(!this->mainWindow->isVisible()){
					this->mainWindow->show();
				}
			}
		});

		this->connect(this->tray, &QSystemTrayIcon::messageClicked, [this](){
			qDebug() << "Tray: message click";
		});

		QTimer::singleShot(1000, [this](){
			this->tray->showMessage(tr("Start Monitoring..."), tr("Clipboard is now under monitoring."), QSystemTrayIcon::Information, 5000);
		});
	}

	void setVisible(bool enable){
		this->tray->setVisible(enable);
	}

	void show(){
		this->tray->show();
	}

	void hide(){
		this->tray->hide();
	}

public slots:
	void showMessage(const QString &title, const QString &message, QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::Information, int timeout = 5000){
		this->tray->showMessage(title, message, icon, timeout);
	}
};

#endif // TRAY_H
