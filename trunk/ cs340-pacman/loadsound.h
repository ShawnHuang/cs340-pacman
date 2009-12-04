#ifndef LOADSOUND_H
#define LOADSOUND_H

#include <QSound>

// PACMAN SOUNDS
static QSound *eatSound = new QSound("../sounds/chomp.wav");
static QSound *eatFruit = new QSound("../sounds/eatfruit.wav");
static QSound *eatGhost = new QSound("../sounds/eatghost.wav");
static QSound *dying = new QSound("../sounds/pacmandying.wav");

// GAME SOUNDS
static QSound *extraLife = new QSound("../sounds/extrapac.wav");
static QSound *gameOverSound = new QSound("../sounds/gameover.wav");
static QSound *intro = new QSound("../sounds/intro.wav");
static QSound *start = new QSound("../sounds/start.wav");

//ENEMY SOUNDS

static QSound moveSound("../sounds/sirensoft.wav");
static QSound blueSound("../sounds/ghostblue.wav");
static QSound whiteSound("../sounds/returnghost.wav");
static QSound deadSound("../sounds/eatghost.wav");


#endif // LOADSOUND_H
