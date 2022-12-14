#include "ClipMimeData.h"

#include <src/Utils.h>

QString ClipMimeData::toString() const{
	return Utils::toString(*this);
}
