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
