//#include "shapes.h"

#include <qapplication.h>
#include <qcanvas.h>

int main( int argc, char **argv )
{
  QApplication a( argc, argv );

  QCanvas *c = new QCanvas( 210, 75 );
  QCanvasView *cv = new QCanvasView( c );

  QCanvasRectangle *rect = new QCanvasRectangle( 10, 10, 40, 40, c );
  rect->setPen( Qt::black );
  rect->setBrush( Qt::red );
  rect->show();

  QCanvasText *t = new QCanvasText( "Rect", c );
  t->setX( 30 );
  t->setY( 55 );
  t->setTextFlags( Qt::AlignHCenter );
  t->show();

  QPointArray points( 3 );
  points.setPoint( 0, 20, 0 );
  points.setPoint( 1, 0, 40 );
  points.setPoint( 2, 40, 40 );

  QCanvasPolygon *poly = new QCanvasPolygon( c );
  poly->setPoints( points );
  poly->setX( 60 );
  poly->setY( 10 );
  poly->setBrush( Qt::blue );
  poly->show();

  t = new QCanvasText( "Poly", c );
  t->setX( 80 );
  t->setY( 55 );
  t->setTextFlags( Qt::AlignHCenter );
  t->show();

  QCanvasLine *line = new QCanvasLine( c );
  line->setPoints( 110, 10, 150, 50 );
  line->setPen( QPen( Qt::green, 4 ) );
  line->show();

  t = new QCanvasText( "Line", c );
  t->setX( 130 );
  t->setY( 55 );
  t->setTextFlags( Qt::AlignHCenter );
  t->show();

  QCanvasEllipse *elli = new QCanvasEllipse( 40, 40, 45*16, 225*16, c );
  elli->setX( 180 );
  elli->setY( 30 );
  elli->setBrush( Qt::cyan );
  elli->show();

  t = new QCanvasText( "Elli", c );
  t->setX( 180 );
  t->setY( 55 );
  t->setTextFlags( Qt::AlignHCenter );
  t->show();

  c->update();

  a.setMainWidget( cv );
  cv->show();

  return a.exec();
}
