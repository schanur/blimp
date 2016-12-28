#ifndef __STEPPER_MOTOR_C__
#define __STEPPER_MOTOR_C__

#include "stepper_motor.h"

void initStepper (struct stepper* cStepperToInit, const uint8_t uiStepperNo, const uint8_t uiStepType)
{
	cStepperToInit->uiStepperNo = uiStepperNo;
	cStepperToInit->uiStepType = uiStepType;

	cStepperToInit->iStepCount = 0;
	/*cStepperToInit->iTargetAngle;*/
	cStepperToInit->iStepsLeft = 0;
	switch (cStepperToInit->uiStepperNo)  {
		case __STEPPER_ENGINE : {
			cStepperToInit->iStepsPerReducedCycle = __STEPPER_ENGINE_STEPS_PER_REDUCED_CYCLE;
			break;
		}
		case __STEPPER_SENSOR_HORIZONTAL : {
			cStepperToInit->iStepsPerReducedCycle = __STEPPER_SENSOR_HORIZONTAL_STEPS_PER_REDUCED_CYCLE;
			break;
		}
		case __STEPPER_SENSOR_VERTICAL : {
			cStepperToInit->iStepsPerReducedCycle = __STEPPER_SENSOR_VERTICAL_STEPS_PER_REDUCED_CYCLE;
			break;
		}
	}
	
	/* FIXME: Das geht schief (letzten Wert auf eprom schreiben oder justieren) */
	/*//caStepper[uiStepperNo].uiSpeed = 5;

	//uiStepperWatch[uiStepperNo] = 0;
	//uiStepperWatch[uiStepperNo] = 10;*/
}

void setStepperAbsolutePos (struct stepper* cStepperToSet, int16_t iAngle)
{

}

void setStepperOffsetPos (struct stepper* cStepperToSet, int16_t iAngle)
{

}

void setStepperAbsoluteAngle (struct stepper* cStepperToSet, int16_t iAngle, const uint8_t uiDirection)
{
	if (stepperStatus (cStepperToSet) != __COMPLETE) {
		/*printDebugMsg("\nsetStepperAngle (): wasnt ready\n");*/
	} else if (((int16_t) ((int32_t) cStepperToSet->iStepCount * 360 / cStepperToSet->iStepsPerReducedCycle)) != iAngle) {
		iAngle = iAngle - (int16_t) ((int32_t) (cStepperToSet->iStepCount * 360 / cStepperToSet->iStepsPerReducedCycle));
		if (iAngle < 0) {
			iAngle += cStepperToSet->iStepsPerReducedCycle;
		}
		if (uiDirection == __STEPPER_DIRECTION_LEFT) {
			iAngle = iAngle * (-1);
		}
		cStepperToSet->iStepsLeft = calculateSteps (cStepperToSet, iAngle);
	}
}

void setStepperOffsetAngle (struct stepper* cStepperToSet, int16_t iAngle)
{
	if (stepperStatus (cStepperToSet) != __COMPLETE) {
		/*printDebugMsg("\nsetStepperAngle (): wasnt ready\n");*/
	} else {
		cStepperToSet->iStepsLeft = calculateSteps (cStepperToSet, iAngle);

		/*cStepperToSet->iTargetAngle = */
	}
}

void changeStepperPhase (struct stepper *cStepper)
{
	
	switchAllStepperPortsOff (cStepper);
	uint8_t ring0, ring1;
	ring0 = cStepper->iStepNo < 2;
	ring1 = ((cStepper->iStepNo == 1) || (cStepper->iStepNo == 2));
	if (ring0) {setStepperAddressPin (cStepper, 0, __ON);}
	if (!ring0) {setStepperAddressPin (cStepper, 1, __ON);}
	if (ring1) {setStepperAddressPin (cStepper, 2, __ON);}
	if (!ring1) {setStepperAddressPin (cStepper, 3, __ON);}
}

void doStepperStep (struct stepper *cStepper)
{
	if (cStepper->iStepsLeft > 0) {
		cStepper->iStepNo = (cStepper->iStepNo + 1) % 4;
		cStepper->iStepCount++;
		cStepper->iStepCount %= cStepper->iStepsPerReducedCycle;
		cStepper->iStepsLeft--;
	} else if (cStepper->iStepsLeft < 0) {
		cStepper->iStepNo--;
		if (cStepper->iStepNo == -1) {
			cStepper->iStepNo = 3;
		}
		cStepper->iStepCount--;
		if (cStepper->iStepCount < 0) {
			cStepper->iStepCount += cStepper->iStepsPerReducedCycle;
		}
		cStepper->iStepsLeft++;
	} else {
		/*//printDebugMsg("\ndoStepperStep (): undefined path\n");
		//panic ();*/
	}
	changeStepperPhase (cStepper);
}


int16_t calculateSteps (struct stepper* cStepper, const int16_t iAngle)
{
	int16_t iStepsLeft; /* iCalc; */

	/* Errechnen der zu drehenden Steps */
	iStepsLeft = (int16_t) (((int32_t) cStepper->iStepsPerReducedCycle * iAngle) / 360);
	/*iStepsLeft /= 360;*/
	return (iStepsLeft);
}

uint8_t stepperStatus (struct stepper* cStepper)
{
	if (cStepper->iStepsLeft == 0) {
		return (__COMPLETE);
	} else {
		return (__INCOMPLETE);
	}
}

void setStepperAddressPin (struct stepper* cStepper, const uint8_t uiPinNo, const uint8_t uiValue)
{
	switch (cStepper->uiStepperNo) {
		case (__STEPPER_SENSOR_HORIZONTAL): {
			switch (uiPinNo) {
				case (0): {
					setPort (__PORT_C, 0, uiValue);
					break;
				}
				case (1): {
					setPort (__PORT_C, 1, uiValue);
					break;
				}
				case (2): {
					setPort (__PORT_C, 2, uiValue);
					break;
				}
				case (3): {
					setPort (__PORT_C, 3, uiValue);
					break;
				}
				/*case (0): {
					setPort (__PORT_C, 2, uiValue);
					break;
				}
				case (1): {
					setPort (__PORT_C, 3, uiValue);
					break;
				}
				case (2): {
					setPort (__PORT_D, 3, uiValue);
					break;
				}
				case (3): {
					setPort (__PORT_B, 3, uiValue);
					break;
				}*/
			}
			break;
		}
		case (__STEPPER_SENSOR_VERTICAL): {
			switch (uiPinNo) {
				case (0): {
					setPort (__PORT_D, 2, uiValue);
					break;
				}
				case (1): {
					setPort (__PORT_B, 0, uiValue);
					break;
				}
				case (2): {
					setPort (__PORT_D, 6, uiValue);
					break;
				}
				case (3): {
					setPort (__PORT_D, 7, uiValue);
					break;
				}
			}
			break;
		}
		case (__STEPPER_ENGINE): {
			/*//printDebugMsg("\nsetStepperAddressPin (): wrong stepper");
			//panic ();*/
			break;
		}
		default: {
			/*//printDebugMsg("\nsetStepperAddressPin (): unknown stepper");
			//panic ();*/
			break;
		}
	}
}

void switchAllStepperPortsOff (struct stepper* cStepperToStop)
{
	uint8_t i;
	for (i = 0; i < 4; i++) {
		setStepperAddressPin (cStepperToStop, i, __OFF);
	}
}

#endif
