/** @brief Serial: f398eb12
 * @file ghc.c
 */

#include "ghcontrol.h"


//Function Prototypes

int main (void)

{
	GhDisplayHeader("Melvin Carl Pote");
	time_t now;
	struct controls ctrl = {0};
	srand((unsigned) time(NULL));
	GhControllerInit();
	struct readings creadings ={0};
	struct setpoints sets = {0};
	sets = GhSetTargets();
        while (1)
	{
		now = time(NULL);
		creadings = GhGetReadings();
		ctrl = GhSetControls(sets,creadings);
		GhDisplayReadings(creadings);
		GhDisplayTargets();
		GhDisplayControls(ctrl);
		GhDelay(GHUPDATE);
	}

	fprintf(stdout, "Press ENTER to continue....");
	fgetc(stdin);

	return EXIT_FAILURE;

}



