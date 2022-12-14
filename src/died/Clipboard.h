#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include <QObject>
#include <QApplication>
#include <QClipboard>
#include <src/ClipMimeData.h>

#include <QDebug>

class Clipboard: public QObject
{
	Q_OBJECT
	// #ifndef QT_NO_CLIPBOARD
	QClipboard *clipboard = QApplication::clipboard();
	QClipboard::Mode mode = QClipboard::Clipboard;
public:
	Clipboard(QObject *parent = nullptr): QObject(parent){
		this->connect(this->clipboard, &QClipboard::changed, [this](QClipboard::Mode mode){
			this->mode = mode;
			emit this->modeChanged(mode);
		});

		this->connect(this->clipboard, &QClipboard::dataChanged, [this](){
			qDebug() << "Copied!";
			emit this->copied(this->getClipData());
		});

		ClipMimeData data = this->getClipData();
		if(data.isValid()){
			emit this->copied(data);
		}
	}

	ClipMimeData getClipData(){
		const QMimeData *data = this->clipboard->mimeData(this->mode);
		if(data == nullptr){
			return ClipMimeData();
		}
		return ClipMimeData(*data);
	}

signals:
	void copied(const ClipMimeData &data);
	void modeChanged(QClipboard::Mode mode);

public slots:
	void setData(const ClipMimeData &data){
		this->clipboard->setMimeData(new ClipMimeData(data), this->mode);
	}
};

#endif // CLIPBOARD_H
