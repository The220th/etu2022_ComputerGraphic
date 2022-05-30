
#include <cmath>
#include <string>

#include "./include/Point.h"
#include "./include/Camera.h"

Camera::Camera() : O(0.0, 0.0, 0.0), F(0.0, 1.0, 0.0), U(0.0, 0.0, 1.0), R(1.0, 0.0, 0.0)
{
    
}

Point Camera::o() const
{
    return O;
}

Point Camera::f() const
{
    return F;
}

Point Camera::u() const
{
    return U;
}

Point Camera::r() const
{
    return R;
}

Point Camera::vf() const
{
    Point res(F);
    res.sub(O);
    return res;
}

Point Camera::vu() const
{
    Point res(U);
    res.sub(O);
    return res;
}

Point Camera::vr() const
{
    Point res(R);
    res.sub(O);
    return res;
}

void Camera::move(double x, double y, double z)
{
    O.setX(O.x() + x);
    O.setY(O.y() + y);
    O.setZ(O.z() + z);

    F.setX(F.x() + x);
    F.setY(F.y() + y);
    F.setZ(F.z() + z);

    U.setX(U.x() + x);
    U.setY(U.y() + y);
    U.setZ(U.z() + z);

    R.setX(R.x() + x);
    R.setY(R.y() + y);
    R.setZ(R.z() + z);
}

void Camera::rotateOX(double a)
{
    rotate(a, 1);
}

void Camera::rotateOY(double a)
{
    rotate(a, 2);
}

void Camera::rotateOZ(double a)
{
    rotate(a, 3);
}

/*mode: 1-OX, 2-OY, 3-OZ*/
void Camera::rotate(double alpha, int mode)
{
    //https://i.imgur.com/WQtfkPW.png

    double o_x_buff, o_y_buff, o_z_buff;

    if(mode == 1)
    {
        o_x_buff = R.x();
        o_y_buff = R.y();
        o_z_buff = R.z();
    }
    else if(mode == 2)
    {
        o_x_buff = F.x();
        o_y_buff = F.y();
        o_z_buff = F.z();
    }
    else /*if(mode == 3)*/
    {
        o_x_buff = U.x();
        o_y_buff = U.y();
        o_z_buff = U.z();
    }

    const double o_x = o_x_buff-O.x();
    const double o_y = o_y_buff-O.y();
    const double o_z = o_z_buff-O.z();

    double x, y, z;
    double x_, y_, z_;

    // F

    x_ = F.x()-O.x(); y_ = F.y()-O.y(), z_ = F.z()-O.z();

    x = x_ * ( o_x*o_x*c1(alpha) + c(alpha) );
    x += y_ * ( o_x*o_y*c1(alpha) - o_z*s(alpha) );
    x += z_ * ( o_x*o_z*c1(alpha) + o_y*s(alpha) );

    y = x_ * ( o_x*o_y*c1(alpha) + o_z*s(alpha) );
    y += y_ * ( o_y*o_y*c1(alpha)  + c(alpha) );
    y += z_ * ( o_y*o_z*c1(alpha) - o_x*s(alpha) );

    z = x_ * ( o_x*o_z*c1(alpha) - o_y*s(alpha) );
    //z += y_ * ( o_x*o_z*c1(alpha)  + o_x*s(alpha) );
    z += y_ * ( o_y*o_z*c1(alpha)  + o_x*s(alpha) );
    z += z_ * ( o_z*o_z*c1(alpha) + c(alpha) );

    F.setX(x+O.x()); F.setY(y+O.y()); F.setZ(z+O.z());

    // U

    x_ = U.x()-O.x(); y_ = U.y()-O.y(), z_ = U.z()-O.z();

    x = x_ * ( o_x*o_x*c1(alpha) + c(alpha) );
    x += y_ * ( o_x*o_y*c1(alpha) - o_z*s(alpha) );
    x += z_ * ( o_x*o_z*c1(alpha) + o_y*s(alpha) );

    y = x_ * ( o_x*o_y*c1(alpha) + o_z*s(alpha) );
    y += y_ * ( o_y*o_y*c1(alpha)  + c(alpha) );
    y += z_ * ( o_y*o_z*c1(alpha) - o_x*s(alpha) );

    z = x_ * ( o_x*o_z*c1(alpha) - o_y*s(alpha) );
    //z += y_ * ( o_x*o_z*c1(alpha)  + o_x*s(alpha) );
    z += y_ * ( o_y*o_z*c1(alpha)  + o_x*s(alpha) );
    z += z_ * ( o_z*o_z*c1(alpha) + c(alpha) );

    U.setX(x+O.x()); U.setY(y+O.y()); U.setZ(z+O.z());
    
    // R

    x_ = R.x()-O.x(); y_ = R.y()-O.y(), z_ = R.z()-O.z();

    x = x_ * ( o_x*o_x*c1(alpha) + c(alpha) );
    x += y_ * ( o_x*o_y*c1(alpha) - o_z*s(alpha) );
    x += z_ * ( o_x*o_z*c1(alpha) + o_y*s(alpha) );

    y = x_ * ( o_x*o_y*c1(alpha) + o_z*s(alpha) );
    y += y_ * ( o_y*o_y*c1(alpha)  + c(alpha) );
    y += z_ * ( o_y*o_z*c1(alpha) - o_x*s(alpha) );

    z = x_ * ( o_x*o_z*c1(alpha) - o_y*s(alpha) );
    //z += y_ * ( o_x*o_z*c1(alpha)  + o_x*s(alpha) );
    z += y_ * ( o_y*o_z*c1(alpha)  + o_x*s(alpha) );
    z += z_ * ( o_z*o_z*c1(alpha) + c(alpha) );

    R.setX(x+O.x()); R.setY(y+O.y()); R.setZ(z+O.z());
}

double Camera::c(double a)
{
	double a_rad = (M_PI*a) / 180.0;
	double res = cos(a_rad);
	return res;
}

double Camera::s(double a)
{
	double a_rad = (M_PI*a) / 180.0;
	double res = sin(a_rad);
	return res;
}

double Camera::c1(double a)
{
	double a_rad = (M_PI*a) / 180.0;
	double res = cos(a_rad);
	return 1.0 - res;
}

std::string Camera::print() const
{
    Point vf(F); vf.sub(O);
    Point vu(U); vu.sub(O);
    Point vr(R); vr.sub(O);
    std::string res = O.print("O: ") + "   " + vf.print("F: ") + "=" + std::to_string(vf.vector_len()) + "   " + vu.print("U: ") + "=" + std::to_string(vu.vector_len()) + "   " + vr.print("R: ") + "=" + std::to_string(vr.vector_len());
    return res;
}

void Camera::moveForward(double s)
{
    Point v = vf();
    v.mul(s);
    move(v.x(), v.y(), v.z());
}

void Camera::moveBack(double s)
{
    moveForward(-s);
}

void Camera::moveRight(double s)
{
    Point v = vr();
    v.mul(s);
    move(v.x(), v.y(), v.z());
}

void Camera::moveLeft(double s)
{
    moveRight(-s);
}

void Camera::moveUp(double s)
{
    Point v = vu();
    v.mul(s);
    move(v.x(), v.y(), v.z());
}

void Camera::moveDown(double s)
{
    moveUp(-s);
}
