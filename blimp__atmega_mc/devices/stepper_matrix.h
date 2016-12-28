#ifndef __STEPPER_MATRIX_H__
#define __STEPPER_MATRIX_H__

#include <inttypes.h>

/*struct stepper_matrix {
	
}*/

/// Initialisierung der Schrittmotoren-Matrix
void initStepperMatrix (uint8_t uiMatrixSize);

/// Schaltet die D-Flip-Flops fuer den
/// zu verwendenden Schrittmotor um
/// Die jewils anderen Schrittmotoren
/// sind dadurch bis zum nächsten umschalten
/// nicht ansprechbar.
void changeStepperMatrixPosition (uint8_t uiMatrixPosition);

/// 

#endif
