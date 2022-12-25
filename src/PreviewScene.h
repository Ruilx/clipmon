#ifndef PREVIEWSCENE_H
#define PREVIEWSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <QHash>
#include <QUuid>

#include <QDebug>

#include <src/ClipMimeData.h>

#include <src/item/TextItem.h>
#include <src/item/HtmlItem.h>
#include <src/item/ImageItem.h>
#include <src/item/OtherItem.h>

class PreviewScene : public QObject
{
	Q_OBJECT

	QHash<QString, QGraphicsScene*> scenes;
public:
	explicit PreviewScene(QObject *parent = nullptr) : QObject{parent}{}

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

	QGraphicsScene *getScene(ClipMimeData *mimeData){
		if(mimeData == nullptr){
			qDebug() << "PreviewScene::getScene(): mimeData is nullptr.";
			return nullptr;
		}
		QString id = mimeData->getId();
		if(id.isEmpty() || !this->scenes.contains(id)){
			QString uuid = QUuid::createUuid().toString(QUuid::WithoutBraces);
			this->scenes.insert(uuid, this->genScene(mimeData));
			mimeData->setId(uuid);
			id = uuid;
		}
		return this->scenes.value(id, nullptr);
	}

	void removeScene(const QString &id){
		if(id.isEmpty()){
			return;
		}
		if(this->scenes.contains(id)){
			QGraphicsScene *scene = this->scenes.take(id);
			if(scene == nullptr){
				qDebug() << "Scene:" << id << "not found in scenes.";
				return;
			}
			QList<QGraphicsView *> views = scene->views();
			qDebug() << "Scene:" << id << "has attached" << views.length() << "views.";
			for(QGraphicsView *view: views){
				if(view != nullptr){
					view->setScene(nullptr);
				}
			}
			// scene will take its all items ownership.
			// @see void QGraphicsScene::addItem(QGraphicsItem *item)
			delete scene;
			qDebug() << "Scene:" << id << "has deleted.";
		}
	}

	void clear(){
		for(const QString &key: this->scenes.keys()){
			this->removeScene(key);
		}
	}

protected:
	QGraphicsScene *genScene(const ClipMimeData *mimeData){
		static const QStringList mimeTypes = {"text/plain", "text/html"};
		static const QStringList mimeTypesPrefix = {"image"};
		int startY = 0;
		QGraphicsScene *scene = new QGraphicsScene(this);
		if(mimeData->hasText()){
			TextItem *textItem = new TextItem(mimeData->text(), "text/plain");
			startY = PreviewScene::addToScene(textItem, scene, startY);
		}
		if(mimeData->hasHtml()){
			HtmlItem *htmlItem = new HtmlItem(mimeData->html(), "text/html");
			startY = PreviewScene::addToScene(htmlItem, scene, startY);
		}
		if(mimeData->hasImage()){
			QString imageMimeType = PreviewScene::findPrefix(mimeData, "image/");
			ImageItem *imageItem = new ImageItem(qvariant_cast<QImage>(mimeData->imageData()), imageMimeType.isEmpty() ? "image/*" : imageMimeType);
			startY = PreviewScene::addToScene(imageItem, scene, startY);
		}

		for(const QString &format: mimeData->formats()){
			if(mimeTypes.contains(format)){
				continue;
			}
			int splitLeft = format.indexOf('/');
			QString prefix = format;
			if(splitLeft >= 0){
				prefix = format.left(splitLeft);
			}
			if(mimeTypesPrefix.contains(prefix)){
				continue;
			}
			OtherItem *otherItem = new OtherItem(mimeData->data(format), format);
			startY = PreviewScene::addToScene(otherItem, scene, startY);
		}
		return scene;
	}

private:
	static int addToScene(ItemBase *item, QGraphicsScene *scene, int startY = 0){
		item->setPos(0, startY);
		scene->addItem(item);
		return startY + item->boundingRect().height();
	}

	static QString findPrefix(const QMimeData *mimeData, const QString &prefix){
		for(const QString &format: mimeData->formats()){
			if(format.startsWith(prefix)){
				return format;
			}
		}
		return "";
	}

signals:

};

#endif // PREVIEWSCENE_H
