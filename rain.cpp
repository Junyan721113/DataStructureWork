#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const Vec2d _Gravity = {0.0, 980};      /* cm / s^2 */
const Size _Size = {500, 500};          /* px */
const Size2f _RippleSize = {1, 0.3};    /* px */
const int _LightningTime = 20;
int _RainTime = 1;                /* frames */
int _RainAmount = 1;
int _RippleSpeed = 100;       /* cm / px */
int _RippleMax = 100;
int _Brightness = 0;
Vec2i _WindSpeed = {0, 0};
const Vec2d _InitVelocity = {20, 500};  /* cm / s */
int _Scale = 1;              /* cm / px */

RNG rng;
class _tpRainDrop {
public:
    Vec2d Velocity;
    Vec2d Position;
    Scalar Color;
    _tpRainDrop& operator>>=(double delta) {
        Vec2d diff = (Vec2d)(_WindSpeed) - Velocity;
        Velocity += _Gravity * delta + diff * 0.05;
        Position += Velocity * delta;
        return *this;
    }
    _tpRainDrop() {
        Velocity = Vec2d(rng.uniform(-_InitVelocity[0], _InitVelocity[0]), rng.uniform(0.0, _InitVelocity[1]));
        Position = Vec2d(rng.uniform((-100 - _WindSpeed[0] / 2.1828) * _Scale, (_Size.width + 100 - _WindSpeed[0] / 2.1828) * _Scale), -100);
        Color = Color.randu(_Brightness, 255);
    }
};

class _tpRipple {
public:
    Vec2d Position;
    float Radius;
    Scalar Color;
    _tpRipple& operator>>=(double delta) {
        Radius += _RippleSpeed * delta;
        return *this;
    }
    _tpRipple(Vec2d Pos, Scalar Col) {
        Position = Pos;
        Radius = 0.0;
        Color = Col;
    }
};

int main() {
    list<_tpRainDrop> RainDrops;
    list<_tpRipple> Ripples;
    Mat3b Canvas(_Size, CV_8UC3);
    int cnt;
    int lightning = 0;
    namedWindow("Rain");
    createTrackbar("RainDrop Time", "Rain", &_RainTime, 100);
    createTrackbar("Rain Amount", "Rain", &_RainAmount, 100);
    createTrackbar("Ripple Speed", "Rain", &_RippleSpeed, 200);
    createTrackbar("Ripple Max", "Rain", &_RippleMax, 200);
    createTrackbar("Wind Speed", "Rain", &_WindSpeed[0], 2000, [](int, void *){_WindSpeed[0] -= 1000;});
    createTrackbar("Brightness", "Rain", &_Brightness, 255);
    createTrackbar("Scale", "Rain", &_Scale, 5, [](int, void *){if(_Scale == 0) _Scale = 1;});
    while(waitKey(20) != 'q') {
        if(_RainTime != 0 && cnt % _RainTime == 0) for(int i = 1; i <= _RainAmount; i++) RainDrops.push_back(_tpRainDrop());
        if(rng.uniform(-490, 10) >= 0) lightning = _LightningTime;
        rectangle(Canvas, Rect(Point(0, 0), _Size), Scalar(255, 255, 255) * lightning-- / _LightningTime, -1);
        for(list<_tpRipple>::iterator i = Ripples.begin(); i != Ripples.end(); i++) {
            *i >>= 0.05;
            ellipse(Canvas, RotatedRect((Point)(i->Position) / _Scale, _RippleSize * i->Radius / (float)(_Scale), 0.0), i->Color * (_RippleMax - (i->Radius)) / _RippleMax);
            if(i->Radius > _RippleMax) Ripples.erase(i--);
        }
        for(list<_tpRainDrop>::iterator i = RainDrops.begin(); i != RainDrops.end(); i++) {
            *i >>= 0.05;
            line(Canvas, (Point)(i->Position) / _Scale, ((Point)(i->Position) - (Point)(i->Velocity * 0.05)) / _Scale, i->Color, 1);
            if(i->Position[1] + rng.uniform(50, 200) > _Size.height * _Scale) {
                Ripples.push_back(_tpRipple(i->Position, i->Color));
                RainDrops.erase(i--);
            }
        }
        cnt++;
        imshow("Rain", Canvas);
    }
    return 0;
}
