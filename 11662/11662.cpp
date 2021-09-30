#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double getDist(double ax, double ay, double bx, double by) {
    return sqrt(pow(ax - bx, 2) + pow(ay - by, 2));
}

int main() {
    double Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;
    cin >> Ax >> Ay >> Bx >> By >> Cx >> Cy >> Dx >> Dy;

    double mLeftX = Ax, mLeftY = Ay, mRightX = Bx, mRightY = By;
    double gLeftX = Cx, gLeftY = Cy, gRightX = Dx, gRightY = Dy;

    double mLeftPointX, mLeftPointY, mRightPointX, mRightPointY, gLeftPointX, gLeftPointY, gRightPointX, gRightPointY;
    for(int i = 0; i < 1000; ++i) {
        mLeftPointX = (2 * mLeftX + mRightX) / 3;
        mLeftPointY = (2 * mLeftY + mRightY) / 3;
        mRightPointX = (mLeftX + 2 * mRightX) / 3;
        mRightPointY = (mLeftY + 2 * mRightY) / 3;

        gLeftPointX = (2 * gLeftX + gRightX) / 3;
        gLeftPointY = (2 * gLeftY + gRightY) / 3;
        gRightPointX = (gLeftX + 2 * gRightX) / 3;
        gRightPointY = (gLeftY + 2 * gRightY) / 3;

        double distLeft = getDist(mLeftPointX, mLeftPointY, gLeftPointX, gLeftPointY);
        double distRight = getDist(mRightPointX, mRightPointY, gRightPointX, gRightPointY);

        if(distLeft > distRight) {
            mLeftX = mLeftPointX;
            mLeftY = mLeftPointY;
            gLeftX = gLeftPointX;
            gLeftY = gLeftPointY;
        }
        else {
            mRightX = mRightPointX;
            mRightY = mRightPointY;
            gRightX = gRightPointX;
            gRightY = gRightPointY;
        }

    }

    double mFinalX = (mLeftX + mRightX) / 2;
    double mFinalY = (mLeftY + mRightY) / 2;

    double gFinalX = (gLeftX + gRightX) / 2;
    double gFinalY = (gLeftY + gRightY) / 2;

    double ret = getDist(mFinalX, mFinalY, gFinalX, gFinalY);

    cout << fixed;
    cout.precision(10);
    cout << ret;

    return 0;
}