/** @brief Gh control functions
 *  @file ghcontrol.c
 */
#include "ghcontrol.h"
#include <cstring>

/*@brief prints out user's name, alongside the string
 *@version February72022
 *@author Melvin Carl Pote
 *@param sname string with operator's name
 *@return void
*/
void GhDisplayHeader(const char * sname)
{
	fprintf(stdout, "%s's CENG153 Greenhouse Controller\n", sname);
}

u_int64_t GhGetSerial(void)
{

	static u_int64_t serial = 0;
	FILE * fp;
	char buf[SYSINFOBUFSZ];
	char searchstring[] = SEARCHSTR;
	fp = fopen ("/proc/cpuinfo", "r");
	if (fp != NULL)
	{
	   while(fgets(buf, sizeof(buf), fp) != NULL)
	   {
	     if (!strncasecmp(searchstring, buf, strlen(searchstring)))
	     {
		sscanf(buf+strlen(searchstring), "%Lx", &serial);
	     }

	   }
	   fclose(fp);
	}

	if (serial == 0)
	{

	  system("uname -a");
	  system("ls --fu /usr/lib/codeblocks | grep -Po '\\.\\K[^ ]+'>stamp.txt");
	  fp = fopen("stamp.txt", "r");
	  if (fp != NULL)
	  {
	    while (fgets(buf, sizeof(buf), fp) != NULL)
	    {
		sscanf(buf, "%Lx", &serial);
	    }
	    fclose(fp);
	  }

	}
	return serial;

}



int GhGetRandom(int range)
{
	return rand() % range;
}

void GhDelay(int milliseconds)
{
	long wait;
	clock_t now, start;

	wait = milliseconds*(CLOCKS_PER_SEC/1000);
	start = clock();
	now = start;
	while( (now-start) < wait)
	{
		now = clock();
	}
}


void GhControllerInit(void)
{
	srand((unsigned) time(NULL));
}

/*@brief will print out if heater & humidifier is on or off
 *@version FEBRUARY72022
 *@author Melvin Carl Pote
 *@param boolean value of pointer
 *@return void
*/
void GhDisplayControls(struct controls ctrl)
{
	if (ctrl.heater == ON && ctrl.humidifier == ON){
		fprintf(stdout,"Heater is ON  Humidifier is ON \n\n");
	}

	else if (ctrl.heater == ON && ctrl.humidifier == OFF){
		fprintf(stdout, "Heater is ON  Humidifier is OFF \n\n");
	}


	else if (ctrl.heater == OFF && ctrl.humidifier == ON){
		fprintf(stdout, "Heater is OFF  Humidifier is ON \n \n");
	}

	else if (ctrl.heater == OFF && ctrl.humidifier == OFF){
		fprintf(stdout, "Heater is OFF  Humidifier is OFF \n \n");
	}

}

/*@brief prints out random values for humidity, temp, and pressure
 *@version FEB072022
 *@author Melvin Carl Pote
 *@param random values
 *@return void
*/

void GhDisplayReadings(struct readings rdata)
{
    printf("\n%sReadings\tT: %4.1fC\tH: %4.1f%%\tP: %6.1fmB\n", ctime(&rdata.rtime), rdata.temperature, rdata.humidity, rdata.pressure);
}

void GhDisplayTargets(void)
{
	fprintf(stdout,"Temperature target = %5.1fC  Humidity target = %5.1f% \n", STEMP, SHUMID);
}

/*@brief pointer values based on condition
 *@version FEB072022
 *@author Melvin Carl Pote
 *@param pointer values
 *@return void
*/
struct controls GhSetControls(struct setpoints target, struct readings rdata)
{
	struct controls cset;

	if(rdata.temperature<target.temperature){
        cset.heater = ON;
	}
	else {
        cset.heater = OFF;
	}

	if(rdata.humidity < target.humidity){
        cset.humidifier = ON;
	}

	else{
        cset.humidifier = OFF;
	}

	return cset;
}

struct setpoints GhSetTargets(void)
{
    struct setpoints cpoints;
    cpoints.temperature = STEMP;
    cpoints.humidity = SHUMID;
    return cpoints;
}

float GhGetHumidity(void)
{
#if SIMHUMIDITY

		return GhGetRandomRange(LSHUMID, USHUMID);

#else
		return 55.0;
#endif // SIMHUMIDITY
}

float GhGetPressure(void)
{
#if SIMPRESSURE

		return GhGetRandomRange(LSPRESS, USPRESS);


#else
		return 1013.0;
#endif // SIMPRESSURE

}

float GhGetTemperature(void)
{
#if SIMTEMPERATURE
		return GhGetRandomRange(LSTEMP, USTEMP);


#else
		return 25.0;
#endif // SIMTEMPERATURE
}

struct readings GhGetReadings(void)
{
    struct readings now = {0};

    now.rtime = time(NULL);
    now.temperature = GhGetTemperature();
    now.humidity = GhGetHumidity();
    now.pressure = GhGetPressure();
	return now;
}

int GhGetRandomRange(int lower, int upper)
{
	return rand() % (upper + 1 - lower) + lower;
}

