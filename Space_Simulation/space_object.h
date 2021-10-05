#ifndef SPACE_OBJECT_H
#define SPACE_OBJECT_H
//Written by: Nikolas Pensyl
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
    Space_Object(int widID, int off);
    int getVelocity();
    int getDirection();
    int getMass();
    int getRad();
    int getWidgetY();
    int getwidID();
    bool getUse();
    bool getSatellite();
    int getRisk();

    int isClicked(QMouseEvent *e);

    void setVelocity(int vel);
    void setDir(int dir);
    void setUse(bool u);
    void setRad(int radi);
    void setMass(int mas);
    void setWidgetY(int widy);
    void setwidID(int widgID);
    void drawObjWidget(QPainter &p);
    void setNew(int val, int k);
    void setOff(int off);
    void setRisk(int ri);


private:


    int velocity;
    int direction;
    int mass;
    bool satellite;
    bool use = true;
    int radius;
    int widgetY;
    int widgID;

    int offset;
    int risk;


    Buttons Vel;
    Buttons Dir;
    Buttons Rad;
    Buttons Mass;
    Buttons Display;
    Buttons Remove;

};

#endif // SPACE_OBJECT_H
