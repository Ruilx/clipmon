#include "Utils.h"

#include <src/ClipMimeData.h>


QString Utils::toString(const ClipMimeData &d){
	return Utils::mimeDesc(d);
}

QString Utils::mimeDesc(const ClipMimeData &d){
	QStringList images;
	QStringList texts;
	QStringList videos;
	QStringList audios;
	QStringList others;
	QStringList formats = d.formats();
	for(const QString &format: formats){
		if(Utils::isTextMimetype(format)){
			texts.append(format);
			continue;
		}
		if(Utils::isImageMimetype(format)){
			images.append(format);
			continue;
		}
		if(Utils::isVideoMimetype(format)){
			videos.append(format);
			continue;
		}
		if(Utils::isAudioMimeType(format)){
			audios.append(format);
			continue;
		}
		others.append(format);
	}
	QString result;
	if(!texts.isEmpty()){
		result.append(QObject::tr("[Text]"));
		result.append(QString(" (%1)").arg(texts.join(", ")));
	}
	if(!images.isEmpty()){
		if(!result.isEmpty()){
			result.append(" ");
		}
		result.append(QObject::tr("[Image]"));
		result.append(QString(" (%1)").arg(images.join(", ")));
	}
	if(!videos.isEmpty()){
		if(!result.isEmpty()){
			result.append(" ");
		}
		result.append(QObject::tr("[Video]"));
		result.append(QString(" (%1)").arg(videos.join(", ")));
	}
	if(!audios.isEmpty()){
		if(!result.isEmpty()){
			result.append(" ");
		}
		result.append(QObject::tr("[Audio]"));
		result.append(QString(" (%1)").arg(audios.join(", ")));
	}
	if(!others.isEmpty()){
		if(!result.isEmpty()){
			result.append(" ");
		}
		result.append(others.join(", "));
	}
	return result;
}

QString Utils::mimeValue(const ClipMimeData &d){
	int line = 0;
	static const int maxline = 4;
	QStringList results;
	QStringList formats = d.formats();
	for(const QString &format: formats){
		if(line >= maxline){
			break;
		}
		if(Utils::isTextMimetype(format)){
			QString text = QString::fromUtf8(d.data(format));
			if(text.length() > 100){
				text = text.left(100).append("...");
			}
			results.append(QObject::tr("[Text (%1)] ").arg(format) % text.replace('\n', "\\n"));
			line++;
			continue;
		}
		if(Utils::isImageMimetype(format)){
			QString text;
			if(d.hasImage()){
				QImage image = qvariant_cast<QImage>(d.imageData());
				text.append(QObject::tr("Size: %1x%2 Format: %3").arg(image.width()).arg(image.height()).arg(Utils::imageFormat(image.format())));
			}else{
				text.append(QObject::tr("Size: %1").arg(Utils::formatNumber(d.data(format).length())));
			}
			results.append(QObject::tr("[Image (%1)] ").arg(format) % text);
			line++;
			continue;
		}

		// others
		results.append(QObject::tr("[%1] ").arg(format) % QObject::tr("Size: %1").arg(Utils::formatNumber(d.data(format).length())));
		line++;
	}
	if(results.isEmpty()){
		return QObject::tr("[Empty]");
	}else{
		return results.join('\n');
	}
}
