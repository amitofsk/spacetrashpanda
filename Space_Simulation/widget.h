#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <iostream>
#include <QMouseEvent>
#include <vector>
#include <QTabWidget>
#include <QTime>
#include <QMessageBox>
#include "buttons.h"
#include "space_object.h"

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
    void drawButton(QPainter &painter, Buttons button);
    void timerEvent(QTimerEvent *e);

    int width = 1000;
    int height = 800;

    //tab 1 = sim
    //tab 2 = ISS
    //tab 3 = settings
    int currentTab = 1;

    int space_obj_count = 2;

    ~Widget();
private:
    QWidget* simulation_widget;
    QTabWidget* settings_widget;

    QImage earth;

    Buttons play;
    Buttons skip_forw;
    Buttons skip_back;
    Buttons display;
    Buttons remove;
    Buttons add;

    Buttons Simu;
    Buttons Setti;
    Buttons ISS;

    Buttons Simul[3];
    std::vector<Buttons> settin;

    std::vector<Space_Object> debris;

    int timerId;
    const int DELAY = 100;


};
#endif // WIDGET_H
