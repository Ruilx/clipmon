#ifndef PREVIEWSCENE_H
#define PREVIEWSCENE_H

#include <QGraphicsScene>

class PreviewScene : public QGraphicsScene
{
	Q_OBJECT
public:
	PreviewScene(QObject *parent = nullptr): QGraphicsScene(parent){

	}
};

#endif // PREVIEWSCENE_H
