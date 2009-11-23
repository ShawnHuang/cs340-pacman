#ifndef ANIMATEDSPRITES_H
#define ANIMATEDSPRITES_H

#include <QPixmap>

class AnimatedSprites {
    private:
        QList<QPixmap> spriteanim;
    public:
    AnimatedSprites() {}
    AnimatedSprites(QString path);
    QList<QPixmap> getSpriteList();
};

#endif // ANIMATEDSPRITES_H
