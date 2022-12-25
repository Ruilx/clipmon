#include "ItemBase.h"

#include <src/ClipMimeData.h>

void ItemBase::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Q_UNUSED(painter);
	Q_UNUSED(option);
	Q_UNUSED(widget);
}

const ClipMimeData ItemBase::getClipMimeData(){
	return this->toClipMimeData();
}
