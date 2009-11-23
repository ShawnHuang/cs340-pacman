#ifndef LOADSOUND_H
#define LOADSOUND_H

#include <QSound>

// PACMAN SOUNDS
QSound eatSound("./sounds/chomp.wav");
QSound eatFruit("./sounds/eatfruit.wav");
QSound eatGhost("./sounds/eatghost.wav");
QSound dying("./sounds/pacmandying.wav");

// GAME SOUNDS
QSound extraLife("./sounds/extrapac.wav");
QSound gameOver("./sounds/gameover.wav");
QSound intro("./sounds/intro.wav");
QSound start("./sounds/start.wav");

#endif // LOADSOUND_H
