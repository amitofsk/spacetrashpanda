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


    Buttons button(0, 0, 100, 50, "Sim");
    Simu = button;
    Simu.setColor(QColor(205, 205, 205));
    Buttons buttone(105, 0, 100, 50, "Settings");
    Setti = buttone;
    Setti.setColor(QColor(50, 50, 50));
    Buttons addObj(300, 200, 80, 400, "Add Object");

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
    } else if(currentTab==2) {
        drawSettings(p);
    }
}

void Widget::drawTabs(QPainter &p) {
    Simu.drawButton(p, Simu);
    Setti.drawButton(p, Setti);
}

void Widget::drawSettings(QPainter &p){
 p.setBrush(QBrush(Qt::gray));
 p.drawRect(0, 50, width, height);
}

void Widget::drawSim(QPainter &p){
    QBrush brush(Qt::black);
    p.setBrush(brush);
    p.drawRect(0, 50, width-100, height);
    p.drawImage(((width-100)/2)-earth.width()/2, (((height-50)/2)-earth.height()/2)+50, earth);
}

Widget::~Widget()
{
}

void Widget::timerEvent(QTimerEvent *e){
    Q_UNUSED(e);

    repaint();
}

void Widget::mousePressEvent(QMouseEvent *e) {


    if(currentTab==1 && Setti.isClicked(e)) {
        currentTab = 2;
        Simu.setColor(QColor(50, 50, 50));
        Setti.setColor(QColor(205, 205, 205));
    } else if(currentTab==2 && Simu.isClicked(e)) {
        currentTab =1;
        Setti.setColor(QColor(50, 50, 50));
        Simu.setColor(QColor(205, 205, 205));
    }
    repaint();
}

void Widget::MouseMoveEvent(QMouseEvent *e) {

}
