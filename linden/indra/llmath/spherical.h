#include "stdtypes.h"
#include "v3dmath.h"

// Very basic stub class for polar coordinates
// Accept a constructor containing cartesian co-ordinates
// provide theta and R as public variables

class polar
{
	public:
		inline polar();
		polar(F64 x,F64 y);

		// Helper function to convert Degrees to Radians
		static inline F64 radFromDegrees(F64 degrees) { return ((degrees/360.0)*F_TWO_PI); };

		// Helper function to convert Hours to Radians (24 Hours = 2 PI rads = 1 rev)
		static inline F64 radFromHours(F64 hours) { return ((hours/24.0)*F_TWO_PI); };

		// Helper function to convert Hours:Mins:Secs to radians
		static inline F64 radFromHMS(F64 hours,F64 mins, F64 secs){return ((F_PI/12.0)*hours) +((F_PI/720.0)*(double)mins) + ((F_PI/43200.0)*(double)secs);};

		// Helper function to convert Degrees:Mins:Secs to radians
		static inline F64 radFromDMS(F64 degrees,F64 mins,F64 secs){return ((degrees+(mins/60.0)+(secs/(60.0*60.0)))/180)*F_PI;};

		F64 mTheta;
		F64 mRadius;
};

// Very Basic stub class for spherical coordinates
// Accept constructor that contains the 3 spherical co-ordinates
// and provides a rotate axis function and a to cartesian function

class spherical
{
	public:

	inline spherical();
	inline spherical(F64 azimuth, F64 altitude, F64 radius){ mAzimuth=azimuth; mAltitude=altitude; mRadius=radius;};

	F64 mAzimuth; //Also known as RA
	F64 mAltitude; //Also declination
	F64 mRadius;

	// Shift the spherical co-ordinates by the spherical rotation
	// described by hourangle and dec
	// these may also be described as longitude and latitude
	// but on the earth longitude wrt a fixed point in the sky depends on the time of day
	// so hour angle is a more common term
	void shift_axis(F64 hourangle,F64 dec);

	// Convert to cartesian
	LLVector3d asVector();

};
