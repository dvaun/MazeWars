#include <ctime>
#include <string.h>

//-----------------------------------------------------------------------------
//Setup timers
const double physicsRate = 1.0 / 60.0;
const double oobillion = 1.0 / 1e9;
//unsigned int upause=0;
double timeDiff(struct timespec *start, struct timespec *end) 
{
	return (double)(end->tv_sec - start->tv_sec ) +
	(double)(end->tv_nsec - start->tv_nsec) * oobillion;
}
void timeCopy(struct timespec *dest, struct timespec *source) 
{
	memcpy(dest, source, sizeof(struct timespec));
}
//-----------------------------------------------------------------------------
