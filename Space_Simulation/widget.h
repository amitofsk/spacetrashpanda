#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <iostream>
#include <QMouseEvent>
#include <vector>
#include <QWheelEvent>
#include <QTime>
#include <QMessageBox>
#include <math.h>
#include "buttons.h"
#include "space_object.h"

#define PI 3.14159265

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    void load_Images();
    void drawTabs(QPainter &p);
    void drawSettings(QPainter &p);
    void drawSim(QPainter &p);
    void drawISSView(QPainter &p);
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void MouseMoveEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);
    void drawButton(QPainter &painter, Buttons button);
    void timerEvent(QTimerEvent *e);
    void Calculations(int i);
    void drawGraph(QPainter &p);
    void drawInfo(QPainter &p);
    int width = 1000;
    int height = 800;

    //tab 0 = Intro
    //tab 1 = sim
    //tab 2 = ISS
    //tab 3 = settings
    //tab 4 = graph of risk
    int currentTab = 0;

    int space_obj_count = 2;

    ~Widget();
private:
    QWidget* simulation_widget;

    QImage earth;
    QImage earth_Hor;
    QImage iss2;

    Buttons play;
    Buttons skip_forw;
    Buttons restart;
    Buttons skip_back;

    Buttons add;

    Buttons Simu;
    Buttons Setti;
    Buttons ISS;
    Buttons Graphrisk;
    Buttons Info;

    std::vector<Space_Object> debris;

    int timerId;
    const int DELAY = 100;

    int scroll_offset;

    bool playing = false;
    bool dead = false;

    int Frame;
    int dangerFilter = 0;
    int CalcRisk(int i);
    void drawFilter(QPainter &p);
};
#endif // WIDGET_H
