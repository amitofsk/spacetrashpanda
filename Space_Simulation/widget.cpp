//Written by: Nikolas Pensyl
#include "widget.h"

Widget::Widget(QWidget *parent): QWidget(parent) {
    load_Images();
    scroll_offset= 0;
    Frame = 0;

    setFixedSize(width, height);

    debris.push_back(Space_Object(0, scroll_offset));
    debris.push_back(Space_Object(1, scroll_offset));

    Buttons button(105, 0, 100, 50, "Sim");
    Simu = button;
    Simu.setColor(QColor(205, 205, 205));
    Buttons buttone(420, 0, 100, 50, "Settings");
    Setti = buttone;
    Setti.setColor(QColor(50, 50, 50));
    Buttons butt(0, 0, 100, 50, "About");
    Info = butt;
    Info.setColor(QColor(205, 205, 205));
    Buttons buttonee(210, 0, 100, 50, "ISS View");
    ISS = buttonee;
    ISS.setColor(QColor(50, 50, 50));
    Buttons butto(315, 0, 100, 50, "Risk");
    Graphrisk = butto;
    Graphrisk.setColor(QColor(50, 50, 50));

    Buttons buttoneee(400, 300, 200, 80, "Add Object");
    add = buttoneee;

    //Simulation Buttons
    Buttons b(910, height-120, 75, 70, "Back 1");
    Buttons f(910, height-270, 75, 70, "Go 1");
    Buttons p(910, height-420, 75, 70, "Play");
    Buttons r(910, height-570, 75, 70, "Reset");

    skip_back = b;
    skip_forw = f;
    play = p;
    restart = r;
    dead = false;
    playing = false;

    timerId = startTimer(DELAY);
}

void Widget::load_Images() {
    earth.load("../earth2");
    earth_Hor.load("../Earth_Horizon");
    iss2.load("../iss2");
}

void Widget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter p(this);
    if(currentTab==1) {
        drawSim(p);
    } else if(currentTab==3) {
        drawSettings(p);
    } else if(currentTab==2) {
        drawISSView(p);
    } else if(currentTab==4) {
        drawGraph(p);
    } else if(currentTab==0) {
        drawInfo(p);
    }
    drawTabs(p);
}

void Widget::drawTabs(QPainter &p) {
    p.setBrush(QBrush(Qt::gray));
    p.setPen(QPen(Qt::gray));
    p.drawRect(0, 0, width, 50);
    Simu.drawButton(p, Simu);
    ISS.drawButton(p, ISS);
    Setti.drawButton(p, Setti);
    Graphrisk.drawButton(p, Graphrisk);
    Info.drawButton(p, Info);
}

void Widget::drawSettings(QPainter &p){

 p.setBrush(QBrush(Qt::gray));
 p.drawRect(0, 50, width, height);
 for(int i = 0; i<space_obj_count; i++) {
     debris[i].drawObjWidget(p);
 }
 add.drawButton(p, add);
}

void Widget::drawInfo(QPainter &p) {
    p.setPen(QPen(Qt::white));
    p.setBrush(QBrush(Qt::black));
    p.drawRect(0, 50, width, height);
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    p.setFont(font);
    QString str = "Welcome to the Space Debris Simulator";
    int textWidth = fm.horizontalAdvance(str);
    p.drawText(width/2-textWidth/2, 90, str);
    str = "This is not a real time simulator as it is in 2D.";
    p.drawText(10, 150, str);
    str = "This is because there are so many real-time space debris trackers.";
    p.drawText(10, 200, str);
    str = "We designed this with risk to space craft and human life in mind.";
    p.drawText(10, 250, str);
    str = "Which is why when you see the dots or \"debris\" changing color";
    p.drawText(10, 300, str);
    str = "within our Simulator you can see how the threat level increases as there is less time to manueaver.";
    p.drawText(10, 350, str);
    str = "We have also made a view to focus more on the satillite as it was our thinking";
    p.drawText(10, 400, str);
    str = "that nothing is more affected by space debris than working satillites and space stations";
    p.drawText(10, 450, str);
    str = "Also you will see a white bar in both simulation screens that is";
    p.drawText(10, 500, str);
    str = "a filter by threat level bar which maxes at 255 which is the max risk/threat.";
    p.drawText(10, 550, str);
    str = "So as you slide it up only the debris with the risk level or higher will be displayed";
    p.drawText(10, 600, str);
    str = "Lastly you will see a tab for a Graph which is something we thought would be";
    p.drawText(10, 650, str);
    str =  "nice to have as it would be much easier to see the risk to a craft by a certain object.";
    p.drawText(10, 700, str);
    str = "And of Course";
    p.drawText(10, 750, str);
    str = "Have fun with it :)";
    p.drawText(width/2-textWidth/2, 780, str);
}

void Widget::drawSim(QPainter &p){

    QBrush brush(Qt::black);
    p.setBrush(brush);
    p.drawRect(0, 50, width-100, height);
    p.drawImage(((width-100)/2)-earth.width()/2, (((height-50)/2)-earth.height()/2)+50, earth);
    skip_back.drawButton(p, skip_back);
    skip_forw.drawButton(p, skip_forw);
    play.drawButton(p, play);
    restart.drawButton(p, restart);
        if(playing) {
          Frame++;
        }
        for(int i = 0; i<space_obj_count; i++) {
            if(i==0) {
                p.drawImage(width/2-(debris[i].getRad()+earth.width())*cos(((debris[i].getDirection()+Frame*debris[i].getVelocity())%360)*PI/180), height/2-(debris[i].getRad()+earth.width())*sin(((debris[i].getDirection()+Frame*debris[i].getVelocity())%360)*PI/180), iss2);
            }
            if(i!=0 && debris[i].getUse()) {
                debris[i].setRisk(CalcRisk(i));
                if(debris[i].getRisk()>=dangerFilter) {
                    p.setBrush(QBrush(QColor(debris[i].getRisk(), 255-debris[i].getRisk(),0)));
                    p.setPen(QPen(QColor(debris[i].getRisk(), 255-debris[i].getRisk(),0)));
                    p.drawEllipse(width/2-(debris[i].getRad()+earth.width())*cos(((debris[i].getDirection()+Frame*debris[i].getVelocity())%360)*PI/180), height/2-(debris[i].getRad()+earth.width())*sin(((debris[i].getDirection()+Frame*debris[i].getVelocity())%360)*PI/180), debris[i].getMass(), debris[i].getMass());
                }
            }
        }
    drawFilter(p);
    p.setPen(QPen(Qt::white));
    QString str = "Frame num: " + QString::number(Frame);
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    p.setFont(font);
    p.drawText(30, 100, str);
}

void Widget::drawGraph(QPainter &p) {
    p.setBrush(QBrush(Qt::white));
    p.drawRect(0, 0, 1000, 800);
    p.setPen(QPen(Qt::black));
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    p.setFont(font);
    for(int i = 19; i>-1; i--) {
        p.drawLine(100, (19-i)*700/17, 900, (19-i)*700/17);
        p.drawText(40, (19-i)*700/17+5, QString::number((255/17) * i));
    }
    for(int i = 0; i<21; i++) {
        p.drawLine(i*800/20+100, 60, i*800/20+100, 760);
        p.drawText(i*800/20+95, 780, QString::number(5*i));
    }
        p.setBrush(QBrush(Qt::red));
        p.setPen(QPen(Qt::red,6));
        p.drawLine(100, 700, 900, 90);
}

int Widget::CalcRisk(int i) {
    int ri;
    if(abs((debris[0].getDirection()+Frame*debris[0].getVelocity())-(debris[i].getDirection()+debris[i].getVelocity()*Frame)-5)!=0) {
        ri = 255/sqrt(sqrt(abs((debris[0].getDirection()+Frame*debris[0].getVelocity())-(debris[i].getDirection()+debris[i].getVelocity()*Frame)-5)));
        ri += debris[i].getMass();
    } else {
        ri=255;
        dead = true;
        playing = false;
        play.setString("Play");
    }

    return ri;
}

void Widget::drawISSView(QPainter &p) {
    QBrush brush(Qt::black);
    p.setBrush(brush);
    p.drawRect(0, 50, width-100, height);
    p.drawImage(0, 600, earth_Hor);
    p.setBrush(QBrush(Qt::gray));
    p.drawRect(900, 0, width, height);
    p.drawImage(((width-100)/2)-iss2.width()/2-100, (((height-10)/2)-iss2.height()/2)+20, iss2);
    skip_back.drawButton(p, skip_back);
    skip_forw.drawButton(p, skip_forw);
    play.drawButton(p, play);
    restart.drawButton(p, restart);
    if(playing) {
      Frame++;
    }
    int Mdir = debris[0].getDirection() + Frame*debris[0].getVelocity();
    for(int i = 1; i<space_obj_count; i++) {
        if(debris[i].getUse()) {
            debris[i].setRisk(CalcRisk(i));
            if(debris[i].getRisk()>=dangerFilter) {
                p.setBrush(QBrush(QColor(debris[i].getRisk(), 255-debris[i].getRisk(),0)));
                p.setPen(QPen(QColor(debris[i].getRisk(), 255-debris[i].getRisk(),0)));
                p.drawEllipse(1000-(debris[i].getRad()+550  )*cos(((debris[i].getDirection()+Frame*debris[i].getVelocity()-Mdir+90)%360)*PI/180)-600, 1000-(debris[i].getRad()+550)*sin(((debris[i].getDirection()+Frame*debris[i].getVelocity()-Mdir+90)%360)*PI/180), debris[i].getMass(), debris[i].getMass());
            }
        }
    }
    p.setPen(QPen(Qt::white));
    drawFilter(p);
    QString str = "Frame num: " + QString::number(Frame);
    QFont font("Courier", 15, QFont::DemiBold);
    p.setFont(font);
    p.drawText(30, 100, str);
}

void Widget::Calculations(int i) {
    if(debris[i].getUse()) {
        debris[i].setDir(debris[i].getVelocity()+debris[i].getDirection());
        if(debris[i].getDirection()>=360) {
            debris[i].setDir(debris[i].getDirection()-360);
        } else if(debris[i].getDirection()<=0) {
            debris[i].setDir(debris[i].getDirection()+360);
        }

    }
}

void Widget::drawFilter(QPainter &p) {
    int y = 60;
    int yer = 120;
    if(currentTab==1) {
      y = 740;
      yer= 710;
    }
    p.setPen(QPen(Qt::white));
    p.setBrush(QBrush(Qt::white));
    p.drawText(228, y+15, "0");
    p.drawText(768, y+15, "255");
    p.drawText(493, yer, QString::number(dangerFilter));
    p.drawRect(245, y, 510, 20);
    p.drawRect(245+dangerFilter*2, y-15, 25, 50);
}

Widget::~Widget()
{
}



void Widget::timerEvent(QTimerEvent *e){
    Q_UNUSED(e);

    repaint();
}

void Widget::mousePressEvent(QMouseEvent *e) {


    if((currentTab==1 || currentTab==2|| currentTab==4 || currentTab==0) && Setti.isClicked(e)) {
        currentTab = 3;
        Simu.setColor(QColor(50, 50, 50));
        ISS.setColor(QColor(50, 50, 50));
        Setti.setColor(QColor(205, 205, 205));
        Graphrisk.setColor(QColor(50, 50, 50));
        Info.setColor(QColor(50, 50, 50));
        playing = false;
        play.setString("Play");
    } else if((currentTab==2 || currentTab==3 || currentTab==4|| currentTab==0) && Simu.isClicked(e)) {
        currentTab =1;
        Setti.setColor(QColor(50, 50, 50));
        ISS.setColor(QColor(50, 50, 50));
        Simu.setColor(QColor(205, 205, 205));
        Graphrisk.setColor(QColor(50, 50, 50));
        Info.setColor(QColor(50, 50, 50));
        playing = false;
        play.setString("Play");
    } else if((currentTab==1 || currentTab==3 || currentTab==4 || currentTab==0) && ISS.isClicked(e)) {
        currentTab =2;
        Setti.setColor(QColor(50, 50, 50));
        Simu.setColor(QColor(50, 50, 50));
        ISS.setColor(QColor(205, 205, 205));
        Graphrisk.setColor(QColor(50, 50, 50));
        Info.setColor(QColor(50, 50, 50));
        playing = false;
        play.setString("Play");
    } else if((currentTab==1 || currentTab==3 || currentTab==2 || currentTab==0) && Graphrisk.isClicked(e)) {
        currentTab = 4;
        Setti.setColor(QColor(50, 50, 50));
        ISS.setColor(QColor(50, 50, 50));
        Simu.setColor(QColor(50, 50, 50));
        Graphrisk.setColor(QColor(205, 205, 205));
        Info.setColor(QColor(50, 50, 50));
        playing = false;
        play.setString("Play");
    }
    else if((currentTab==1 || currentTab==3 || currentTab==2 || currentTab==4) && Info.isClicked(e)) {
            currentTab = 0;
            Setti.setColor(QColor(50, 50, 50));
            ISS.setColor(QColor(50, 50, 50));
            Simu.setColor(QColor(50, 50, 50));
            Info.setColor(QColor(205, 205, 205));
            Graphrisk.setColor(QColor(50, 50, 50));
            playing = false;
            play.setString("Play");
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
                add.setY(add.getY()-120);
                for(int j = 1; j<space_obj_count; j++) {
                    if(debris[j].getwidID()!=j) {
                        debris[j].setwidID(j);
                    }
                }
            }
            if(val<=3 && val!=-1) {
                bool ok = false;
                int k;
                int check;
                if(val==0 ||val==1) {
                    check = 0;
                } else {
                    check = 1;
                }
                while(!ok) {
                   k = QInputDialog::getInt(this, tr("QInputDialog::getInteger()"),
                                                tr("Input the new ") + str, 10, check, 360, 1, &ok);
                }
                debris[i].setNew(val, k);

            }
        }
        if(add.isClicked(e)) {
            space_obj_count++;
            debris.push_back(Space_Object(space_obj_count-1, scroll_offset));
            add.setY(add.getY()+120);
        }

    } else if(currentTab==2 || currentTab==1) {
        if(skip_forw.isClicked(e)) {
            if(playing) {
                playing = false;
                play.setString("Play");
            }
            if(!dead) {
                Frame +=1;
            }
        }
        if(skip_back.isClicked(e)) {
            if(playing) {
                playing = false;
                play.setString("Play");
                dead = false;
            }
            if(Frame>0) {
                Frame -=1;
            }
        }
        if(play.isClicked(e)) {
            play.setString("Pause");
            playing = !playing;
            if(!playing) {
                play.setString("Play");
            }
        }
        if(restart.isClicked(e)) {
            Frame= 0;
            playing = false;
            play.setString("Play");
        }
        int y = 60;
        if(currentTab==1) {
            y = 740;
        }
        if(e->button()==Qt::LeftButton && y-30<e->y() && y+30>e->y() && e->x()>245 && e->x()<755) {
            dangerFilter = (e->x()-245)/2;
        }
    }

    repaint();
    repaint();
}

void Widget::wheelEvent(QWheelEvent *e) {
    if(e->angleDelta().y()>0 &&  currentTab==3 && -scroll_offset+(space_obj_count*120+60)>height-100) {
        scroll_offset+=5;
        if(-scroll_offset+(space_obj_count*120+60)<height-100) {
            scroll_offset = (space_obj_count*120+60)-(height-100);
        } else {
            add.setY(add.getY()-5);
        }

    } else if(e->angleDelta().y()<0 &&  currentTab==3 && scroll_offset>0) {
        scroll_offset-=5;
        if(scroll_offset<0) {
            scroll_offset = 0;
        } else {
            add.setY(add.getY()+5);
        }
    }
    for(int i = 0; i<space_obj_count; i++) {
        debris[i].setOff(scroll_offset);

    }
    repaint();
}

void Widget::MouseMoveEvent(QMouseEvent *e) {
 if(currentTab==1) {
     ISS.isHovering(e);
     Setti.isHovering(e);
     skip_forw.isHovering(e);
     skip_back.isHovering(e);
     play.isHovering(e);
     restart.isHovering(e);
 } else if(currentTab==2) {
     Simu.isHovering(e);
     Setti.isHovering(e);
     skip_forw.isHovering(e);
     skip_back.isHovering(e);
     play.isHovering(e);
     restart.isHovering(e);
 } else if(currentTab==3) {
     Simu.isHovering(e);
     ISS.isHovering(e);
 } else if(currentTab==4) {
     ISS.isHovering(e);
     Setti.isHovering(e);
     Simu.isHovering(e);
 }
 repaint();
}
