#ifndef SPOINT_H
#define SPOINT_H

class sPoint
{
    private:
    /*const */int _x;
    /*const */int _y;

    public:

    sPoint();
    sPoint(int x, int y);
    sPoint(const sPoint& toCopied);

    int getX() const;

    int getY() const;
    
    void setX(int new_x);

    void setY(int new_y);

    int x() const;
    
    int y() const;
};

#endif // SPOINT_H
