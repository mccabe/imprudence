
// A stub/incomplete spherical and polar coordinate classes


#include "spherical.h"

polar::polar(F64 x,F64 y)
{
	mRadius=sqrt(y*y+x*x);

	//Quadrant detction
	if(x==0 && y==0)
	{
		mTheta=0;
	}
	else if(x>=0)
	{
		mTheta=asin(y/mRadius);
	}
	else
	{
		mTheta=-1.0*asin(y/mRadius)+F_PI;
	}
}


void spherical::shift_axis(F64 sideRealTime,F64 dec)
{
		//Spherical axis shift
		//Shift one spherical axis to another, eg celestial to geographic

		F64 hourAngle=sideRealTime-mAzimuth;

		F64 R1=sin(dec)*sin(mAltitude)+cos(dec)*cos(mAltitude)*cos(hourAngle);
		F64 RX=cos(dec)*sin(mAltitude)-sin(dec)*cos(mAltitude)*cos(hourAngle);
		F64 RY=-1.0*cos(mAltitude)*sin(hourAngle);

		polar rp(RX,RY);

		mAzimuth=rp.mTheta;

		polar rp2(rp.mRadius,R1);

		mAltitude=rp2.mTheta;
}

LLVector3d spherical::asVector()
{
	//Asumes a decline vector for altitude
	LLVector3d result;
	result.mdV[VX]=mRadius * cos (mAltitude) * cos(mAzimuth);
	result.mdV[VY]=mRadius * cos (mAltitude) * sin(mAzimuth);
	result.mdV[VZ]=mRadius * sin (mAltitude);

	return result;
}
