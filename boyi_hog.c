#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include "boyi_hog.h"

short lut64[] = { 0, 0, 1, 2, 3, 4, 5, 6, 7, 8,
8, 9, 10, 11, 12, 13, 14, 14, 15, 16,
17, 18, 18, 19, 20, 21, 22, 22, 23, 24,
25, 25, 26, 27, 27, 28, 29, 30, 30, 31,
32, 32, 33, 33, 34 };
short lut32[] = { 35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
45, 46, 47, 47, 48, 49, 50, 50, 51, 52,
53, 53, 54, 54, 55, 56, 56, 57, 57, 58,
58, 59, 59, 59 };
short lut16[] = { 60, 60, 61, 62, 63, 63, 64, 65, 65, 66,
67, 67, 68, 68, 69, 69, 69 };
short lut8[] = { 70, 71, 71, 72, 73, 73, 74, 74 };
short lut4[] = { 75, 75, 76, 76, 77, 78, 78, 79, 79 };
short lut1[] = { 80, 81, 82, 83, 84, 84, 85, 85, 85, 86,
86, 86, 86, 86, 87, 87, 87 };


short GetMagnitude(short dy, short dx) 
{
        short mag;
        mag = (short)( abs(dy) + abs(dx) );
        //mag = (short)Math.Sqrt(dy * dy + dx * dx);
        return mag;
}


void BoMagnitude_32f(const float* x, const float* y, float* mag, int len)
{
    int i = 0;
    for( ; i < len; i++ )
    {
        float x0 = x[i], y0 = y[i];
        //mag[i] = sqrt(x0*x0 + y0*y0);
        mag[i] = GetMagnitude(y0,x0);
    }
};


int  BinByAngle(short angle, short mag, short center_angle ) {
        int sum=0;
        short a[8];

        a[0] = (short)(center_angle - 14);
        a[1] = (short)(center_angle - 11);
        a[2] = (short)(center_angle - 8);
        a[3] = (short)(center_angle - 5);
        a[4] = (short)(center_angle + 5);
        a[5] = (short)(center_angle + 8);
        a[6] = (short)(center_angle + 11);
        a[7] = (short)(center_angle + 14);
        if (a[3] < 10) a[3] = 0;    // edge case
        if (a[4] > 170) a[4] = 180; // edge case

        if ((angle >= a[3]) && (angle <= a[4])) {
                sum = sum + mag;
        } else if ((angle > a[4]) && (angle <= a[5])) {
                sum = sum + ((3 * mag) / 4);
        } else if ((angle > a[5]) && (angle <= a[6])) {
                sum = sum + (mag / 2);
        } else if ((angle > a[6]) && (angle <= a[7])) {
                sum = sum + (mag / 4);
        } else if ((angle >= a[2]) && (angle < a[3])) {
                sum = sum + ((3 * mag) / 4);
        } else if ((angle >= a[1]) && (angle < a[2])) {
                sum = sum + (mag / 2);
        } else if ((angle >= a[0]) && (angle < a[1])) {
                sum = sum + (mag / 4);
        }

        return sum;
}

short  GetAngle(short dy, short dx) 
{
        int slope=0;
        int angle=0;
        bool neg=0;
        int index=0;

        if (dx == 0) {  // prevent division-by-zero
                if (dy > 0) angle = 90;
                else if (dy < 0) angle = -90;
                else angle = 0;
        } else {
                slope = (64 * dy) / dx;
                if (slope < 0) {
                        neg = true;
                        slope = -slope;
                } else neg = false;
                if (slope > 362) {
                        index = (slope / 64) - 5;
                        if (index > 16) index = 16; // prevent too large angle
                        angle = lut1[index];
                } else if (slope > 238) {
                        index = (slope / 16) - 14;
                        angle = lut4[index];
                } else if (slope > 175) {
                        index = (slope / 8) - 22;
                        angle = lut8[index];
                } else if (slope > 110) {
                        index = (slope / 4) - 27;
                        angle = lut16[index];
                } else if (slope > 44) {
                        index = (slope / 2) - 22;
                        angle = lut32[index];
                } else {
                        index = slope;
                        angle = lut64[index];
                }
                if (neg) {
                        angle = -angle;
                }
        }
        angle = angle + 90;
        printf("angle:%d \n\r",angle);

        return (short)angle;
}


void BoFastAtan2_32f(const float *Y, const float *X, float *angle, int len, bool angleInDegrees)
{
    int i = 0;
    for( ; i < len; i++ )
    {
        float x = X[i], y = Y[i];
        printf("x:%f y:%f \n\r",x,y);
        printf("x:%d y:%d \n\r",x,y);

        angle[i] = GetAngle(y,x);
        //printf("index:%d angle:%d \n\r",i,angle[i]);

    }
};

#if 0
void boyi_myFastAtan2_32f(const float *Y, const float *X, float *angle, int len, bool angleInDegrees)
{
	int slope = 0;
	int neg = 0;
	int index = 0;
	int i = 0;
	short ang = 0;
	float scale = angleInDegrees ? 1 : (float)(myCV_PI / 180);

	for (i = 0; i< len; i++)
	{
		float ax = X[i] * 1000;
		float ay = Y[i] * 1000;
		short dx = 0, dy = 0;
		dx = (short)(ax);
		dy = (short)(ay);

		if (dx == 0)
		{
			// prevent division-by-zero
			if (dy > 0)
				ang = 90;
			else if (dy < 0)
				ang = 90;
			else ang = 0;//ang = 0;
		}
		else
		{
			slope = (64 * dy) / dx;
			if (slope < 0)
			{
				slope = -slope;
			}
			if (slope > 362)
			{
				index = (slope / 64) - 5;
				if (index > 16)
					index = 16; // prevent too large angle
				ang = lut1[index];
			}
			else if (slope > 238)
			{
				index = (slope / 16) - 14;
				ang = lut4[index];
			}
			else if (slope > 175)
			{
				index = (slope / 8) - 22;
				ang = lut8[index];
			}
			else if (slope > 110)
			{
				index = (slope / 4) - 27;
				ang = lut16[index];
			}
			else if (slope > 44)
			{
				index = (slope / 2) - 22;
				ang = lut32[index];
			}
			else
			{
				index = slope;
				ang = lut64[index];
			}
		}
		if (dx < 0)
			ang = 180 - ang;
		if (dy < 0)
			ang = 360 - ang;
		angle[i] = (float)(ang*scale);
	}

};
#endif

