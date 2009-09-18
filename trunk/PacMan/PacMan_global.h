#ifndef PACMAN_GLOBAL_H
#define PACMAN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PACMAN_LIBRARY)
#  define PACMANSHARED_EXPORT Q_DECL_EXPORT
#else
#  define PACMANSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PACMAN_GLOBAL_H
