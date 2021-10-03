#include "space_object.h"
#include <QObject>

Space_Object::Space_Object(int widID)
{
    widgID = widID;
    velocity = 5+widID;
    mass = 10;
    direction = 0+widID*10;
    radius = 20;
    widgetY = widID*100;
    Buttons a(235, widgetY+25, 80, 50, QString::number(velocity));
    Buttons b(360, widgetY+25, 80, 50, QString::number(direction));
    Buttons c(485, widgetY+25, 80, 50, QString::number(radius));
    Buttons e(610, widgetY+25, 80, 50, QString::number(mass));
    Buttons f(735, widgetY+25, 80, 50, "Yes");
    Buttons g(860, widgetY+10, 80, 60, "remove");
    Vel = a;
    Dir = b;
    Rad = c;
    Mass = e;
    Display = f;
    Remove = g;
}

int Space_Object::getVelocity() {
    return velocity;
}

int Space_Object::getDirection() {
    return direction;
}
int Space_Object::getMass() {
    return mass;
}
int Space_Object::getRad() {
    return radius;
}
bool Space_Object::getUse() {
    return use;
}
bool Space_Object::getSatellite() {
    return satellite;
}
void Space_Object::drawObjWidget(QPainter &p) {

    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    p.setFont(font);
    p.setPen(QColor(Qt::black));
    QString name;
    if(widgID==0) {
        name = "Space Station";
    } else {
        name = "Debris: " + QString::number(widgID);
    }
    int textWidth = fm.horizontalAdvance(name);
    p.drawRect(10, widgetY, 960, 80);
    p.drawText(10+textWidth/2, widgetY+40, name);
    p.drawText(287+textWidth/2, widgetY+10, "Velocity");
    p.drawText(437+textWidth/2, widgetY+10, "Direction");
    p.drawText(562+textWidth/2, widgetY+10, "Radius");
    p.drawText(687+textWidth/2, widgetY+10, "Mass");
    p.drawText(817+textWidth/2, widgetY+10, "Display?");
    Vel.drawButton(p, Vel);
    Dir.drawButton(p, Dir);
    Rad.drawButton(p, Rad);
    Mass.drawButton(p, Mass);
    if(widgID!=0) {
        Display.drawButton(p, Display);
        Remove.drawButton(p, Remove);
    }

}
void Space_Object::setRad(int radi) {
    radius = radi;
}
void Space_Object::setVelocity(int vel) {
    velocity = vel;
}
void Space_Object::setDir(int dir) {
    direction = dir;
}

void Space_Object::setUse(bool u) {
    use = u;
}

int Space_Object::isClicked(QMouseEvent *e) {
    QString str;
    if(Vel.isClicked(e)) {
        return 0;
    } else if(Dir.isClicked(e)) {
        return 1;
    } else if(Rad.isClicked(e)) {
        return 2;
    } else if(Mass.isClicked(e)) {
        return 3;
    } else if(Display.isClicked(e)) {
        if(use) {
            Display.setString("No");
        } else {
            Display.setString("Yes");
        }
        use = !use;
        return 4;
    } else if(Remove.isClicked(e)) {
        return -1;
    }

    return 5;
}
