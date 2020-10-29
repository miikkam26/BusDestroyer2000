#include "basicprojectile.h"


#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QDebug>
#include <QGraphicsItem>

basicProjectile::basicProjectile(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){

    setPixmap(QPixmap(":/images/fireball_16x16.png"));
    setTransformOriginPoint(5, 10);
    setRotation(-90);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &basicProjectile::move);
    timer->start(50);

    this->setDimensions();
    qDebug() << "projectile height:"<<this->_projectileHeight;
    qDebug() << "proejctile width:"<<this->_projectileWidth;

}

basicProjectile::~basicProjectile()
{

}

void basicProjectile::setDimensions()
{
    QImage *fireball= new QImage(":/images/fireball_16x16.png");
    _projectileHeight = fireball->height();
    _projectileWidth = fireball->width();
    //qDebug() << "fireball height: "<<bulletHeight_;
    //qDebug() << "fireball width: "<<bulletWidth_;
    delete fireball;
}

void basicProjectile::move()
{
    setPos(x(), y() - _projectileVelocity);

    if(pos().y() + _projectileHeight < 0){
        scene()->removeItem(this);
        delete this;
    }
}


