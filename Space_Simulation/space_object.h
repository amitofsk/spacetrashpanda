#ifndef SPACE_OBJECT_H
#define SPACE_OBJECT_H


class Space_Object
{
public:
    Space_Object();
    int getVelocity();
    int getSize();
    int getDirection();
    int getMass();
    int getX();
    int getY();
    bool getUse();
    bool getSatellite();

    void setVelocity(int vel);
    void setDir(int dir);
    void setSize(int si);
    void setSatellite(bool sat);
    void setUse(bool u);
    void setX(int X);
    void setY(int Y);
private:


    int velocity;
    int direction;
    int size;
    int mass;
    bool satellite;
    bool use;
    int x;
    int y;

};

#endif // SPACE_OBJECT_H
