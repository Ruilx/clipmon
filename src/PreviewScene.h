#ifndef PREVIEWSCENE_H
#define PREVIEWSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <QHash>
#include <QUuid>

#include <src/ClipMimeData.h>

class PreviewScene : public QObject
{
	Q_OBJECT

	QHash<QString, QGraphicsScene*> scenes;
public:
	explicit PreviewScene(QObject *parent = nullptr) : QObject{parent}{

	}

	~PreviewScene(){
		for(QHash<QString, QGraphicsScene*>::Iterator iterator = this->scenes.begin(); iterator != this->scenes.end(); iterator++){
			QGraphicsScene *scene = iterator.value();
			if(scene != nullptr){
				QList<QGraphicsView*> views = scene->views();
				for(QGraphicsView *view: views){
					if(view == nullptr){
						continue;
					}
					view->setScene(nullptr);
				}
				delete scene;
				scene = nullptr;
			}
		}
	}

	void addScene(const ClipMimeData *mimeData){
		if(mimeData == nullptr){
			return;
		}
		QString id = mimeData->getId();
		if(id.isEmpty()){
			QString uuid = QUuid::createUuid().toString();
			this->genScene(mimeData, uuid);
		}

	}

protected:
	void genScene(const ClipMimeData *mimeData, const QString &uuid){
		int startY = 0;
		QGraphicsScene *scene = new QGraphicsScene(this);

	}

signals:

};

#endif // PREVIEWSCENE_H
