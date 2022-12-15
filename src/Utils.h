#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QPainter>
#include <QMimeDatabase>

#include <QImage>
#include <QHash>

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

	static void drawIconPlaceholder(QPixmap *pixmap, const QPen &pen = QPen(Qt::white)){
		QRect rect = QRect(QPoint(0, 0), pixmap->size() - QSize(1, 1));
		QPainter painter(pixmap);
		painter.setPen(pen);
		painter.drawRect(rect);
		painter.drawLine(rect.topLeft(), rect.bottomRight());
		painter.drawLine(rect.topRight(), rect.bottomLeft());
		painter.end();
	}

	static QString imageFormat(QImage::Format format){
		static const QHash<QImage::Format, QString> table = {
			{QImage::Format_Invalid,  QObject::tr("Invalid")},
			{QImage::Format_Mono,     QObject::tr("Mono")},
			{QImage::Format_MonoLSB,  QObject::tr("Mono LSB")},
			{QImage::Format_Indexed8, QObject::tr("Indexed 8-bit")},
			{QImage::Format_RGB32,    QObject::tr("RGB 32-bit")},
			{QImage::Format_ARGB32,   QObject::tr("ARGB 32-bit")},
			{QImage::Format_ARGB32_Premultiplied, QObject::tr("ARGB 32-bit Premultiplied")},
			{QImage::Format_RGB16,    QObject::tr("RGB 16-bit 565")},
			{QImage::Format_ARGB8565_Premultiplied, QObject::tr("ARGB 24-bit 8565 Premultiplied")},
			{QImage::Format_RGB666,   QObject::tr("RGB 24-bit 666")},
			{QImage::Format_ARGB6666_Premultiplied, QObject::tr("ARGB 24-bit 6666 Premultiplied")},
			{QImage::Format_RGB555,   QObject::tr("RGB 16-bit 555")},
			{QImage::Format_ARGB8555_Premultiplied, QObject::tr("ARGB 24-bit 8555 Premultiplied")},
			{QImage::Format_RGB888,   QObject::tr("RGB 24-bit 888")},
			{QImage::Format_RGB444,   QObject::tr("RGB 16-bit 444")},
			{QImage::Format_ARGB4444_Premultiplied, QObject::tr("ARGB 16-bit 4444 Premultiplied")},
			{QImage::Format_RGBX8888, QObject::tr("RGBX 32-bit 8888")},
			{QImage::Format_RGBA8888, QObject::tr("RGBA 32-bit 8888")},
			{QImage::Format_RGBA8888_Premultiplied, QObject::tr("RGBA 32-bit 8888 Premultiplied")},
			{QImage::Format_BGR30,    QObject::tr("BGR 32-bit 10-10-10")},
			{QImage::Format_A2BGR30_Premultiplied, QObject::tr("ABGR 32bit 2-10-10-10 Premultiplied")},
			{QImage::Format_RGB30,    QObject::tr("RGB 32-bit 10-10-10")},
			{QImage::Format_A2RGB30_Premultiplied, QObject::tr("ARGB 32bit 2-10-10-10 Premultiplied")},
			{QImage::Format_Alpha8,   QObject::tr("Alpha 8-bit")},
			{QImage::Format_Grayscale8, QObject::tr("Grayscale 8-bit")},
			{QImage::Format_RGBX64,   QObject::tr("RGBX 64-bit 16-16-16-16")},
			{QImage::Format_RGBA64,   QObject::tr("RGBA 64-bit 16-16-16-16")},
			{QImage::Format_RGBA64_Premultiplied, QObject::tr("RGBA 64-bit 16-16-16-16 Premultiplied")},
		};
		if(table.contains(format)){
			return table.value(format);
		}
		return "Unknown Format";
	}
};

#endif // UTILS_H
