#ifndef SPACE_OBJECT_H
#define SPACE_OBJECT_H

#include "buttons.h"
#include <QInputDialog>
#include <string>
#include <QPainter>
#include <QtGui>
#include <QMessageBox>
#include <QWidget>

class Space_Object
{
public:
    Space_Object(int widID);
    int getVelocity();
    int getDirection();
    int getMass();
    int getRad();
    bool getUse();
    bool getSatellite();

    int isClicked(QMouseEvent *e);

    void setVelocity(int vel);
    void setDir(int dir);
    void setUse(bool u);
    void setRad(int radi);

    void drawObjWidget(QPainter &p);

private:


    int velocity;
    int direction;
    int mass;
    bool satellite;
    bool use;
    int radius;
    int widgetY;
    int widgID;

    Buttons Vel;
    Buttons Dir;
    Buttons Rad;
    Buttons Mass;
    Buttons Display;
    Buttons Remove;

};

#endif // SPACE_OBJECT_H
