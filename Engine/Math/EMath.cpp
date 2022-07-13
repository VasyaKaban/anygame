#include "EMath.h"

float DEGtoRAD(float DEGangle)
{
	return (PI / 180.0f * DEGangle);
}

float RADtoDEG(float RADangle)
{
	return (180.0f * RADangle / PI);
}