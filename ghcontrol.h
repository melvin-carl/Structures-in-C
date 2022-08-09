/** @brief Gh control constants, structures, function prototypes
 *  @file ghcontrol.h
 */
#ifndef GHCONTROL_H
#define GHCONTROL_H


//Includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//Structures
struct readings
{
    time_t rtime;
    float temperature;
    float humidity;
    float pressure;
};

struct setpoints
{
    float temperature;
    float humidity;
};

struct controls
{
    int heater;
    int humidifier;
};


//Constants
#define SEARCHSTR "serial\t\t:"
#define SYSINFOBUFSZ 512
#define GHUPDATE 2000
#define SENSORS 3
#define TEMPERATURE 0
#define HUMIDITY 1
#define PRESSURE 2
#define SIMULATE 1
#define LSTEMP -10
#define USTEMP 50
#define LSHUMID 0
#define USHUMID 100
#define LSPRESS 975
#define USPRESS 1016
#define STEMP 25.0
#define SHUMID 55.0
#define ON 1
#define OFF 0
#define SIMTEMPERATURE 1
#define SIMHUMIDITY 1
#define SIMPRESSURE 1
///Function Prototypes
///@cond INTERNAL
void GhDisplayHeader(const char * sname);
u_int64_t GhGetSerial(void);
int GhGetRandom(int range);
void GhDelay(int milliseconds);
void GhControllerInit(void);
void GhDisplayControls(struct controls ctrl);
void GhDisplayReadings(struct readings rdata);
void GhDisplayTargets(void);
struct controls GhSetControls(struct setpoints target, struct readings rdata);
struct setpoints GhSetTargets(void);
float GhGetHumidity(void);
float GhGetPressure(void);
float GhGetTemperature(void);
struct readings GhGetReadings(void);
int GhGetRandomRange(int lower, int upper);
///@endcond
#endif

