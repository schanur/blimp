#include <iostream>

#include <sys/types.h>

//#include <libgpsmm.h>
//#include "gpsd_config.h"
#include <gps.h>

using namespace std;

void bla (struct gps_data_t *gpsdata, char *message, size_t len, int level)
{
	//cerr << "2: " << message << endl;
	cerr << "lat: " << (double)gpsdata->fix.latitude << " lon: " << gpsdata->fix.longitude << endl;
}



int main (void)
{
	cerr.precision (15);

	gps_data_t *test = gps_open("127.0.0.1", DEFAULT_GPSD_PORT);
	if (!test) {
		cerr << "moeoeepp" << endl;
	}
	cerr << "a" << endl;
	gps_set_raw_hook(test, &bla);
	//(void) gps_poll (test);
	while (1) {
		(void)gps_query(test, "w+x\n");
		(void) gps_poll (test);
		cerr << "1";
		usleep (100);
	}
	cerr << test->fix.latitude << endl;
	return 0;
}