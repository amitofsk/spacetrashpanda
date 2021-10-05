//Written by: Nikolas Pensyl
#include "space_object.h"
#include <QObject>

Space_Object::Space_Object(int widID, int off)
{
    offset = off;
    widgID = widID;
    velocity = 5+widID;
    mass = 10;
    direction = 0+widID*10;
    if(widID==0) {
        direction = 180;
    }

    radius = 30+widID*10;
    widgetY = widID*120+60;
    Buttons a(235, widgetY+35-offset, 80, 50, QString::number(velocity));
    Buttons b(360, widgetY+35-offset, 80, 50, QString::number(direction));
    Buttons c(485, widgetY+35-offset, 80, 50, QString::number(radius));
    Buttons e(610, widgetY+35-offset, 80, 50, QString::number(mass));
    Buttons f(735, widgetY+35-offset, 80, 50, "Yes");
    Buttons g(860, widgetY+20-offset, 80, 60, "remove");
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
int Space_Object::getWidgetY() {
    return widgetY;
}
int Space_Object::getwidID() {
    return widgID;
}

int Space_Object::getRisk() {
    return risk;
}

void Space_Object::drawObjWidget(QPainter &p) {
    p.setBrush(QBrush(Qt::NoBrush));
    p.drawRect(10, widgetY-offset, 960, 100);
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

    p.drawText(10+textWidth/2, widgetY+40-offset, name);
    name = "Velocity";
    textWidth = fm.horizontalAdvance(name);
    p.drawText(280-textWidth/2, widgetY+20-offset, "Velocity");
    name = "Direction";
    textWidth = fm.horizontalAdvance(name);
    p.drawText(405-textWidth/2, widgetY+20-offset, "Direction");
    name = "Radius";
    textWidth = fm.horizontalAdvance(name);
    p.drawText(525-textWidth/2, widgetY+20-offset, "Radius");
    name = "Mass";
    textWidth = fm.horizontalAdvance(name);
    p.drawText(650-textWidth/2, widgetY+20-offset, "Mass");
    if(widgID!=0) {
        name = "Display";
    textWidth = fm.horizontalAdvance(name);
    p.drawText(772-textWidth/2, widgetY+20-offset, "Display?");
    }
    Vel.drawButton(p, Vel);
    Dir.drawButton(p, Dir);
    Rad.drawButton(p, Rad);
    Mass.drawButton(p, Mass);
    if(widgID!=0) {
        Display.drawButton(p, Display);
        Remove.drawButton(p, Remove);
    }

}

void Space_Object::setWidgetY(int widy) {
    widgetY = widy;
    Vel.setY(widgetY+35-offset);
    Dir.setY(widgetY+35-offset);
    Rad.setY(widgetY+35-offset);
    Mass.setY(widgetY+35-offset);
    Display.setY(widgetY+35-offset);
    Remove.setY(widgetY+20-offset);
}
void Space_Object::setwidID(int widID) {
    widgID = widID;
    setWidgetY(widgID*120+60);
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

void Space_Object::setMass(int mas) {
    mass = mas;
}

void Space_Object::setOff(int off) {
    offset = off;
    Vel.setY(widgetY+35-offset);
    Dir.setY(widgetY+35-offset);
    Rad.setY(widgetY+35-offset);
    Mass.setY(widgetY+35-offset);
    Display.setY(widgetY+35-offset);
    Remove.setY(widgetY+20-offset);
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
    } else if(Remove.isClicked(e) && widgID!=0) {
        return -1;
    }

    return 5;
}

void Space_Object::setNew(int val, int k) {
    if(val==0) {
        Vel.setString(QString::number(k));
        velocity = k;
    } else if(val==1) {
        Dir.setString(QString::number(k));
        setDir(k);
    } else if(val==2) {
        Rad.setString(QString::number(k));
        setRad(k);
    } else {
        Mass.setString(QString::number(k));
        setMass(k);
    }
}

void Space_Object::setRisk(int ri) {
    risk = ri;
}


