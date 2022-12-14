#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include <QObject>
#include <QApplication>
#include <QClipboard>

#include <src/ClipMimeData.h>

#include <QDebug>

class Clipboard : public QObject
{
	Q_OBJECT

	QClipboard *clipboard = QApplication::clipboard();
	QClipboard::Mode mode = QClipboard::Clipboard;
public:
	explicit Clipboard(QObject *parent = nullptr): QObject(parent){
		this->connect(this->clipboard, &QClipboard::changed, [this](QClipboard::Mode mode){
			this->mode = mode;
			emit this->modeChanged(mode);
		});

		this->connect(this->clipboard, &QClipboard::dataChanged, [this](){
			qDebug() << "Get copied!";
			bool owns = false;
			switch(this->mode){
				case QClipboard::Clipboard:
					owns = this->clipboard->ownsClipboard();
					break;
				case QClipboard::Selection:
					owns = this->clipboard->ownsSelection();
					break;
				case QClipboard::FindBuffer:
					owns = this->clipboard->ownsFindBuffer();
					break;
				default:
					break;
			}
			const ClipMimeData data = this->getClip();
			if(data.isValid()){
				emit this->copied(data, owns);
			}else{
				qCritical() << "Clipboard data is invalid.";
			}
		});
	}

	const ClipMimeData getClip(){
		const QMimeData *data = this->clipboard->mimeData(this->mode);
		if(data == nullptr){
			return ClipMimeData();
		}
		return ClipMimeData(*data);
	}

signals:
	void copied(const ClipMimeData &data, bool owned);
	void modeChanged(QClipboard::Mode mode);

public slots:
	void setData(const ClipMimeData &data){
		this->clipboard->setMimeData(&data, this->mode);
	}

};

#endif // CLIPBOARD_H
