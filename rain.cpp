#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const Vec2d _Gravity = {0.0, 980};      /* cm / s^2 */
const Size _Size = {500, 500};          /* px */
const Size2f _RippleSize = {1, 0.3};    /* px */
const int _RainTime = 1;                /* frames */
const double _RippleSpeed = 30.0;       /* cm / px */
const Vec2d _InitVelocity = {20, 100};  /* cm / s */
const double _Scale = 1.0;              /* cm / px */

RNG rng;
class _tpRainDrop {
public:
    Vec2d Velocity;
    Vec2d Position;
    _tpRainDrop& operator>>=(double delta) {
        Velocity += _Gravity * delta;
        Position += Velocity * delta;
        return *this;
    }
    _tpRainDrop() {
        Velocity = Vec2d(rng.uniform(-_InitVelocity[0], _InitVelocity[0]), rng.uniform(0.0, _InitVelocity[1]));
        Position = Vec2d(rng.uniform(0, _Size.width), -100);
    }
};

class _tpRipple {
public:
    Vec2d Position;
    float Radius;
    _tpRipple& operator>>=(double delta) {
        Radius += _RippleSpeed * delta;
        return *this;
    }
    _tpRipple(Vec2d Pos) {
        Position = Pos;
        Radius = 0.0;
    }
};

int main() {
    list<_tpRainDrop> RainDrops;
    list<_tpRipple> Ripples;
    Mat3b Canvas;
    int cnt;
    while(waitKey(20) != 'q') {
        if(cnt % _RainTime == 0) RainDrops.push_back(_tpRainDrop());
        Canvas = Mat3b::zeros(_Size);
        for(list<_tpRainDrop>::iterator i = RainDrops.begin(); i != RainDrops.end(); i++) {
            *i >>= 0.05;
            line(Canvas, (Point)(i->Position) / _Scale, ((Point)(i->Position) - (Point)(i->Velocity * 0.05)) /_Scale, Scalar(255, 255, 255), 2);
            if(i->Position[1] + rng.uniform(50, 200) > _Size.height * _Scale) {
                Ripples.push_back(_tpRipple(i->Position));
                RainDrops.erase(i--);
            }
        }
        for(list<_tpRipple>::iterator i = Ripples.begin(); i != Ripples.end(); i++) {
            *i >>= 0.05;
            ellipse(Canvas, RotatedRect((Point)(i->Position), _RippleSize * i->Radius, 0.0), Scalar(255, 255, 255) / (i->Radius / 10));
            if(i->Radius > 255 * 10) Ripples.erase(i--);
        }
        cnt++;
        imshow("Rain", Canvas);
    }
    return 0;
}
