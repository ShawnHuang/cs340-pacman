#include <QDir>

#include "animatedsprites.h"

AnimatedSprites::AnimatedSprites(QString path)
{
    QFileInfo fi(path);
    QDir d = QDir(fi.path(), fi.fileName());
    foreach (QString entry, d.entryList())
            spriteanim << QPixmap(fi.path() + "/" + entry);
}

QList<QPixmap> AnimatedSprites::getSpriteList()
{
    return spriteanim;
}
