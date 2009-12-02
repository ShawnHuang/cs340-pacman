#ifndef LOADSOUND_H
#define LOADSOUND_H

#include <QSound>

// PACMAN SOUNDS

//static QSound eatSound("/Users/usha/Documents/workspace/pacman/ cs340-pacman/sounds/chomp.wav");
//static QSound eatFruit("/Users/usha/Documents/workspace/pacman/ cs340-pacman/sounds/eatfruit.wav");
//static QSound eatGhost("/Users/usha/Documents/workspace/pacman/ cs340-pacman/sounds/eatghost.wav");
//static QSound dying("/Users/usha/Documents/workspace/pacman/ cs340-pacman/sounds/pacmandying.wav");

static QSound *eatSound = new QSound("/Users/usha/Documents/workspace/pacman/ cs340-pacman/sounds/chomp.wav");
static QSound *eatFruit = new QSound("/Users/usha/Documents/workspace/pacman/ cs340-pacman/sounds/eatfruit.wav");
static QSound *eatGhost = new QSound("/Users/usha/Documents/workspace/pacman/ cs340-pacman/sounds/eatghost.wav");
static QSound *dying = new QSound("/Users/usha/Documents/workspace/pacman/ cs340-pacman/sounds/pacmandying.wav");

// GAME SOUNDS
//static QSound extraLife("/Users/usha/Documents/workspace/pacman/ cs340-pacman/sounds/sounds/extrapac.wav");
//static QSound gameOver("/Users/usha/Documents/workspace/pacman/ cs340-pacman/sounds/sounds/gameover.wav");
//static QSound intro("/Users/usha/Documents/workspace/pacman/ cs340-pacman/sounds/sounds/intro.wav");
//static QSound start("/Users/usha/Documents/workspace/pacman/ cs340-pacman/sounds/sounds/start.wav");

// GAME SOUNDS
static QSound *extraLife = new QSound("../sounds/extrapac.wav");
static QSound *gameOver = new QSound("../sounds/gameover.wav");
static QSound *intro = new QSound("../sounds/intro.wav");
static QSound *start = new QSound("../sounds/start.wav");

//ENEMY SOUNDS
static QSound moveSound("/Users/usha/Documents/workspace/pacman/ cs340-pacman/sounds/sirensoft.wav");
static QSound blueSound("/Users/usha/Documents/workspace/pacman/ cs340-pacman/sounds/ghostblue.wav");
static QSound returnSound("/Users/usha/Documents/workspace/pacman/ cs340-pacman/sounds/returnghost.wav");

#endif // LOADSOUND_H
