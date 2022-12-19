#include "MainWindow.h"

#include <QClipboard>

void MainWindow::setupWindow(){
	this->resize(800, 600);
	this->setCentralWidget(clipList);

	this->setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
	this->setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
	this->setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
	this->setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

	this->previewWidget->setWidget(this->preview);
	this->previewWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	this->previewWidget->setFeatures(QDockWidget::DockWidgetMovable);
	this->connect(this->previewWidget, &QDockWidget::visibilityChanged, [this](bool visible){
		this->showPreviewWindowAction->setChecked(visible);
	});

	this->addDockWidget(Qt::RightDockWidgetArea, this->previewWidget);

	this->setWindowTitle("");
}

void MainWindow::setupMenus(){
	QMenu *fileMenu = new QMenu(tr("&File"));{
		fileMenu->addAction(tr("&Open"), [this](){

		});

		fileMenu->addAction(tr("&Save"), [this](){

		});

		fileMenu->addAction(tr("&Exit"), [this](){
			qApp->exit();
		});

		this->menuBar()->addMenu(fileMenu);
	}

	QMenu *editMenu = new QMenu(tr("&Edit"));{
		this->underMonitoringAction->setCheckable(true);
		this->underMonitoringAction->setChecked(this->clipHelper->getEnable());
		this->connect(this->underMonitoringAction, &QAction::triggered, [this](bool checked){
			this->clipHelper->setEnable(checked);
			if(!checked){
				this->setWindowTitle(tr("Monitoring Stopped"));
			}else{
				this->setWindowTitle("");
			}
		});
		editMenu->addAction(this->underMonitoringAction);

		editMenu->addAction(tr("&Clear History"), [this](){
			if(this->clipHelper->getHistoryCount() <= 0){
				return;
			}
			int answer = QMessageBox::question(this, QApplication::applicationDisplayName(),
											   tr("This will clear all data, all history will be clean.\n"
													   "You can save the list before resize history data.\n"
													   "Proceed?"), QMessageBox::Yes, QMessageBox::Cancel);
			if(answer != QMessageBox::Yes){
				return;
			}
			this->clipHelper->clear();
			this->statusBar()->showMessage(tr("History cleared."));
		});

		editMenu->addAction(tr("&Set History size..."), [this](){
			bool ok = false;
			int historySize = this->clipHelper->getHistorySize();
			int newHistorySize = QInputDialog::getInt(this, QApplication::applicationDisplayName(),
													  tr("Please input max history size..."),
													  historySize,
													  1, 5000, 1, &ok);
			if (!ok){
				return;
			}
			if(newHistorySize < historySize){
				int answer = QMessageBox::question(this, QApplication::applicationDisplayName(),
												   tr("The size inputed is smaller than before, the extra oldest history data will be removed.\n"
														  "You can save the list before resize history data.\n"
														  "Proceed?"), QMessageBox::Yes, QMessageBox::Cancel);
				if(answer != QMessageBox::Yes){
					return;
				}
			}
			this->clipHelper->setHistorySize(newHistorySize);
			this->statusBar()->showMessage(tr("History size set to %1.").arg(newHistorySize));
		});

		this->menuBar()->addMenu(editMenu);
	}

	QMenu *viewMenu = new QMenu(tr("&View"));{
		this->showPreviewWindowAction->setCheckable(true);
		this->connect(this->showPreviewWindowAction, &QAction::triggered, [this](bool checked){
			this->previewWidget->setVisible(checked);
			this->statusBar()->showMessage(tr("Preview window %1.").arg(checked ? tr("open") : tr("closed")));
		});
		viewMenu->addAction(showPreviewWindowAction);

		this->closeAsExitAction->setCheckable(true);
		this->closeAsExitAction->setChecked(this->closeAsExit);
		this->connect(this->closeAsExitAction, &QAction::triggered, [this](bool checked){
			this->closeAsExit = checked;
			if(this->closeAsExit){
				this->statusBar()->showMessage(tr("Program will closed when window closed."));
			}else{
				this->statusBar()->showMessage(tr("Program run background when window closed."));
			}
		});
		viewMenu->addAction(closeAsExitAction);

		this->menuBar()->addMenu(viewMenu);
	}

	QMenu *aboutMenu = new QMenu(tr("&About"));{
		aboutMenu->addAction(tr("&About"), [this](){
			qDebug() << "about";
		});

		aboutMenu->addAction(tr("About &Qt..."), [](){
			qApp->aboutQt();
		});
		this->menuBar()->addMenu(aboutMenu);
	}
}

MainWindow::~MainWindow()
{
}

