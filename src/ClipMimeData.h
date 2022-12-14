#ifndef CLIPMIMEDATA_H
#define CLIPMIMEDATA_H

#include <QMimeData>

class ClipMimeData : public QMimeData
{
	bool valid = false;
public:
	ClipMimeData(): QMimeData(){}

	ClipMimeData(const QMimeData &other): QMimeData(){
		this->setMimeData(other);
	}

	ClipMimeData(const ClipMimeData &other): QMimeData(){
		this->setMimeData(other);
	}

	void setMimeData(const QMimeData &mimeData){
		for(const QString &format: mimeData.formats()){
			if(mimeData.hasFormat(format)){
				this->setData(format, mimeData.data(format));
			}
		}
		if(!formats.isEmpty()){
			this->valid = true;
		}
	}

	ClipMimeData &operator = (const ClipMimeData &other){
		this->clear();
		this->setMimeData(other);
		return *this;
	}

	inline bool isValid() const{ return this->valid; }

	QString toString() const;
};

#endif // CLIPMIMEDATA_H
