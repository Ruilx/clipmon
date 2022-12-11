#ifndef CLIPMIMEDATA_H
#define CLIPMIMEDATA_H

#include <QMimeData>

#include <QDebug>

#include <src/Utils.h>

class ClipMimeData : public QMimeData
{
	Q_OBJECT
public:
	ClipMimeData(): QMimeData(){}

	ClipMimeData(const QMimeData &other): QMimeData(){
		this->setMimeData(other);
	}

	ClipMimeData(const ClipMimeData &other): QMimeData(){
		this->setMimeData(other);
	}

	void setMimeData(const QMimeData &mimeData){
		QStringList formats = mimeData.formats();
		for(const QString &format: formats){
			if(mimeData.hasFormat(format)){
				this->setData(format, mimeData.data(format));
			}
		}
	}

	ClipMimeData &operator =(const ClipMimeData &other){
		this->clear();
		this->setMimeData(other);
		return *this;
	}
};

#endif // CLIPMIMEDATA_H
