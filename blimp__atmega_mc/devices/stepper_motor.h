#ifndef __STEPPER_MOTOR_H__
#define __STEPPER_MOTOR_H__

/*#include <stdlib.h>*/
#include <avr/io.h>
#include <stdint.h>

/*#include "global_vars.h"*/
#include "../defines.h"
/*#include "../shared_source/debug.c"*/

#include "../io/ports.h"
#include "stepper_matrix.h"

#define __UNIPOLAR_FULLSTEP			0
#define __BIPOLAR_FULLSTEP			1
#define __BIPOLAR_HALFSTEP			2

#define __STEPPER_ENGINE_STEPS_PER_REDUCED_CYCLE		24
#define __STEPPER_SENSOR_HORIZONTAL_STEPS_PER_REDUCED_CYCLE	850
#define __STEPPER_SENSOR_VERTICAL_STEPS_PER_REDUCED_CYCLE	850

#define __STEPPER_ENGINE 			3
#define __STEPPER_SENSOR_HORIZONTAL		1
#define __STEPPER_SENSOR_VERTICAL		2

#define __STEPPER_DIRECTION_LEFT	0
#define __STEPPER_DIRECTION_RIGHT	1

#define __STEPPER_NOT_INITIALIZED		0xff

struct stepper {
	uint8_t uiStepperNo;
	uint8_t uiStepType;
	int16_t iStepCount;
	int16_t iStepsPerReducedCycle;  /* Schritte fuer 360 Grad hinter Uebersetzung */
	int16_t iStepsLeft;				/* Schritte bis SollGrad */
	uint8_t uiSpeed;
	uint8_t uiAccelleration;
	int8_t iStepNo;	
};
/*//int16_t iAbsoluteStepPos;	/// Anzahl der Schritte mod Schritte fuer 360Grad
//struct stepper caStepper[4];*/

/* Initialisierung eines Schrittmotors.*/
void initStepper (struct stepper* cStepperToInit, const uint8_t uiStepperNo, const uint8_t uiStepType);

/*//void setStepperAbsolutePos (struct stepper* cStepperToSet, int16_t, iStepPos);
//void setStepperOffsetPos (struct stepper* cStepperToSet, int16_t, iStepPos);*/

/* Wird aufgerufen um einen der Schrittmotoren zu setzen.
 * Der uebergebene Wert ist die Aenderung der aktuellen
 * Position in Grad und Drehrichtung. 
 * iAngle: neue Position
 */
void setStepperAbsoluteAngle (struct stepper* cStepperToSet, int16_t iAngle, const uint8_t uiDirection);

/* Wird aufgerufen um einen der Schrittmotoren zu setzen.
 * Der uebergebene Wert ist der Absolute Wert zwischen 0 und 360 Grad,
 * wobei die Funktion selbst die Drehrichtung bestimmt.
 * iAngle: neue Position
 */
void setStepperOffsetAngle (struct stepper* cStepperToSet, const int16_t iAngle);

/* Legt die Geschwindigkeit des Motors fest
 * Der Parameter uiSpeed ist die Anzahl an Zeitzyklen
 * die zwischen 2 Zyklen liegt.
 */
void setStepperSpeed (struct stepper* cStepperToSet, const uint8_t uiSpeed);

/* Legt fest ob eine Beschlaeunigungsphase beim Start der
 * Bewegung erfolgen soll.
 */
void setStepperAccelleration (struct stepper* cStepperToSet, const uint8_t uiAccelleration);

/* Schaltet alle Ports aus
 * void switchAllStepperPortsOff ();
 * Berechnet die Steps zur Zielpos.
 */
uint8_t stepperStatus (struct stepper* cStepper);

/* Die Routine wird vom Timer-Interrupt-Handler aufgerufen.
 * Beim Aufruf fuehrt der Motor einen Schritt aus.
 * Die Haufigkeit, mit der die Routine pro Schrittmotor
 * aufgerufen wird, haengt von den Parametern uiSpeed
 * und uiAcceleration ab.
 */
void doStepperStep (struct stepper *cStepper);

/*#################################################################################*/
/* Interne Routinen */


/* Wird intern aufgerufen wenn ein Signal ueber einen Port an den
 * betreffenden Motor gesendet werden soll
 */
void changeStepperPhase (struct stepper *cStepper);

/* Umrechnung des Winkels in die Anzahl der benötigten Schritte */
int16_t calculateSteps (struct stepper* cStepper, const int16_t iAngle);

/* Tabelle, die die Pinnummer eines Schrittmotors
 * auf einen Ausgangsport des Microcontrollers
 * umlegt
 */
void setStepperAddressPin (struct stepper* cStepper, const uint8_t uiPinNo, const uint8_t uiValue);

/* Abschalten des Schrittmotors */
void switchAllStepperPortsOff (struct stepper* cStepperToStop);

#endif
