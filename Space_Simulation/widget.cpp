#include "widget.h"

Widget::Widget(QWidget *parent): QWidget(parent) {
    load_Images();
    timerId = startTimer(DELAY);
    setFixedSize(width, height);
    for(int i =0; i<3; i++) {
        Buttons buttoner(width-90, 300+i*150, 80, 80);
        if(i==0) {
            Simul[i].setString("Frame Forward");
        } else if(i==1) {
            Simul[i].setString("play");
        } else if(i==2) {
            Simul[i].setString("Frame Back");
        }
    }

    debris.push_back(Space_Object(0));
    debris.push_back(Space_Object(1));

    Buttons button(0, 0, 100, 50, "Sim");
    Simu = button;
    Simu.setColor(QColor(205, 205, 205));
    Buttons buttone(210, 0, 100, 50, "Settings");
    Setti = buttone;
    Setti.setColor(QColor(50, 50, 50));
    Buttons buttonee(105, 0, 100, 50, "ISS View");
    ISS = buttonee;
    ISS.setColor(QColor(50, 50, 50));
    Buttons buttoneee(300, 200, 80, 200, "Add Object");
    add = buttoneee;
}

void Widget::load_Images() {
    earth.load("../earth2");
}

void Widget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter p(this);
    drawTabs(p);
    if(currentTab==1) {
        drawSim(p);
    } else if(currentTab==3) {
        drawSettings(p);
    } else if(currentTab==2) {
        drawISSView(p);
    }
}

void Widget::drawTabs(QPainter &p) {
    Simu.drawButton(p, Simu);
    ISS.drawButton(p, ISS);
    Setti.drawButton(p, Setti);
}

void Widget::drawSettings(QPainter &p){
 p.setBrush(QBrush(Qt::gray));
 p.drawRect(0, 50, width, height);
 for(int i = 0; i<space_obj_count; i++) {
     debris[i].drawObjWidget(p);
 }
 add.drawButton(p, add);
}

void Widget::drawSim(QPainter &p){
    QBrush brush(Qt::black);
    p.setBrush(brush);
    p.drawRect(0, 50, width-100, height);
    p.drawImage(((width-100)/2)-earth.width()/2, (((height-50)/2)-earth.height()/2)+50, earth);
}

void Widget::drawISSView(QPainter &p) {
    QBrush brush(Qt::red);
    p.setBrush(brush);
    p.drawRect(0, 50, width-100, height);
}

Widget::~Widget()
{
}



void Widget::timerEvent(QTimerEvent *e){
    Q_UNUSED(e);

    repaint();
}

void Widget::mousePressEvent(QMouseEvent *e) {


    if((currentTab==1 || currentTab==2) && Setti.isClicked(e)) {
        currentTab = 3;
        Simu.setColor(QColor(50, 50, 50));
        ISS.setColor(QColor(50, 50, 50));
        Setti.setColor(QColor(205, 205, 205));
    } else if((currentTab==2 || currentTab==3) && Simu.isClicked(e)) {
        currentTab =1;
        Setti.setColor(QColor(50, 50, 50));
        ISS.setColor(QColor(50, 50, 50));
        Simu.setColor(QColor(205, 205, 205));
    } else if((currentTab==1 || currentTab==3) && ISS.isClicked(e)) {
        currentTab =2;
        Setti.setColor(QColor(50, 50, 50));
        Simu.setColor(QColor(50, 50, 50));
        ISS.setColor(QColor(205, 205, 205));
    }
    if(currentTab==3) {
        for(int i = 0; i<space_obj_count; i++) {
            int val = debris[i].isClicked(e);
            QString str;
            if(val == 0) {
                str = "velocity.";
            } else if(val == 1) {
                str = "direction.";
            } else if(val == 2) {
                str = "radius.";
            } else if(val == 3) {
                str = "mass.";
            } else if(val==-1) {
                std::vector<Space_Object>::iterator death = debris.begin();
                for(int j = 0; j<i; j++, death++) {

                }
                debris.erase(death);
                space_obj_count--;
            }
        }
        if(add.isClicked(e)) {
            debris.push_back(Space_Object(space_obj_count));
            space_obj_count++;
        }
    }
    repaint();
}

void Widget::MouseMoveEvent(QMouseEvent *e) {

}
