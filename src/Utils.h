#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QPainter>
#include <QMimeDatabase>

class ClipMimeData;
class Utils
{
public:

	static QString toString(const ClipMimeData &d);

	static QString mimeDesc(const ClipMimeData &d);

	static bool isImageMimetype(const QString &format){
		if(format.startsWith("image/")){
			return true;
		}
		return false;
	}

	static bool isVideoMimetype(const QString &format){
		if(format.startsWith("video/")){
			return true;
		}
		return false;
	}

	static bool isTextMimetype(const QString &format){
		if(format.startsWith("text/")){
			return true;
		}
		return false;
	}

	static bool isAudioMimeType(const QString &format){
		if(format.startsWith("audio/")){
			return true;
		}
		return false;
	}

	static void drawIconPlaceholder(QPixmap *pixmap){
		QRect rect = QRect(QPoint(0, 0), pixmap->size() - QSize(1, 1));
		QPen pen(Qt::white);
		QPainter painter(pixmap);
		painter.setPen(pen);
		painter.drawRect(rect);
		painter.drawLine(rect.topLeft(), rect.bottomRight());
		painter.drawLine(rect.topRight(), rect.bottomLeft());
		painter.end();
	}
};

#endif // UTILS_H
