#ifndef __PROTOCOL_PACKET_HANDLER_C__
#define __PROTOCOL_PACKET_HANDLER_C__

#include "protocol_packet_handler.h"
//#include "engine_speed.h"

uint8_t uartProtocolHandleRemoteRequest (struct strUartProtocol *strpProtocolLink)
{
	switch (strpProtocolLink->receive.commandData[0]) {
		
		/* Antwort mit einem Paket um der
		 * Gegenstelle zu signalisieren,
		 * dass die Verbindung noch besteht
		 * und sich der Microcontroller in
		 * einem einsatzbereiten Zustand
		 * befindet.
		 */
		case __UART_PROTOCOL_ECHO: {
			uartProtocolSendResponse (strpProtocolLink, NULL, 0);
			printDebugMsg ("packet received: echo");
			break;
		}
		
		/* Uebertragung des Kompasswerts
		 * mit 8 Bit Aufloesung.
		 */
		case __UART_PROTOCOL_SENSOR_COMPASS_8_BIT_RES: {
			struct packetSensorCompass8Bit cCompass;
			cCompass.uiDirection = readFromI2C (192, 1);
			uartProtocolSendResponse (strpProtocolLink, (char*) &cCompass, 1);
			break;
		}
		
		/* Uebertragung des Kompasswerts
		 * mit 16 Bit Aufloesung.
		 */
		case __UART_PROTOCOL_SENSOR_COMPASS_16_BIT_RES: {
			struct packetSensorCompass16Bit cCompass;
			cCompass.uiDirection = readFromI2C (192, 2);
			cCompass.uiDirection |= (readFromI2C (192, 3)) << 8;
			uartProtocolSendResponse (strpProtocolLink, (char*) &cCompass, 2);
			break;
		}
		
		/* Initialisiert den Messvorgang
		 * des Ultraschalldistanzsensors.
		 */
		case __UART_PROTOCOL_SENSOR_ULTRASONIC_START: {
			/*writeToI2C(224, 0, 81);*/
			uartProtocolSendResponse (strpProtocolLink, NULL, 0);
			printDebugMsg ("packet received: ultrasonic start");
			break;
		}

		/* Uebertragung der zuvor gemessenen
		 * Distanz des Ultraschalldistanzsensors.
		 */
		case __UART_PROTOCOL_SENSOR_ULTRASONIC_READ: {
			struct packetSensorUltrasonicRead cUltrasonic;
			/*cUltrasonic.uiDistance = 14000;*/
			cUltrasonic.uiDistance = 1;
			/*//char buf[16];
			//U32IntToString (&buf, cUltrasonic.uiDistance);
			//printDebugMsg (&buf);
			//uartPutBinX ((char *) &cUltrasonic.uiDistance, 2);*/
			toNetworkByteOrder ((char*) &cUltrasonic.uiDistance, 2);
			/*//uartPutU32Int (cUltrasonic.uiDistance);
			//cUltrasonic.uiDistance = readFromI2C (224, 3);
			//cUltrasonic.uiDistance |= (readFromI2C (224, 2)) << 8;*/
			uartProtocolSendResponse (strpProtocolLink, (char*) &cUltrasonic, 2);
			printDebugMsg ("packet received: ultrasonic read");
			break;
		}
		
		/* Setzen der Werte fuer beide Antriebsmotoren. */
		case __UART_PROTOCOL_ENGINE_BOTH: {
			printDebugMsg ("packet received: engine both");
			struct packetSetEngineBoth cEngineBoth;
			int16_t *ipNewEngineSpeed, iNewEngineSpeed;
			ipNewEngineSpeed = (int16_t*) &strpProtocolLink->receive.commandData[__HEADER_SIZE];
			iNewEngineSpeed = *ipNewEngineSpeed;
			toPlatformByteOrder ((char*) &iNewEngineSpeed, 2);
			iEngineLeft = iNewEngineSpeed;
			ipNewEngineSpeed = (int16_t*) &strpProtocolLink->receive.commandData[__HEADER_SIZE + sizeof (int16_t)];
			iNewEngineSpeed = *ipNewEngineSpeed;
			toPlatformByteOrder ((char*) &iNewEngineSpeed, 2);
			iEngineRight = iNewEngineSpeed;
			uartProtocolSendResponse (strpProtocolLink, (char*) &cEngineBoth, 2);
			break;
		}

		/* Setzen des wertes fuer den rechten
		 * Antriebsmotor.
		 */
		case __UART_PROTOCOL_ENGINE_RIGHT: {
			printDebugMsg ("packet received: engine right");
			/*struct packetSetEngineRight cEngineRight;*/
			int16_t *ipNewEngineSpeed, iNewEngineSpeed;
			ipNewEngineSpeed = (int16_t*) &strpProtocolLink->receive.commandData[__HEADER_SIZE];
			iNewEngineSpeed = *ipNewEngineSpeed;
			toPlatformByteOrder ((char*) &iNewEngineSpeed, 2);
			iEngineRight = iNewEngineSpeed;
			break;
		}		
		
		/* Setzen des Wertes fuer den linken
		 * Antriebsmotor.
		 */
		case __UART_PROTOCOL_ENGINE_LEFT: {
			printDebugMsg ("packet received: engine left");
			/*struct packetSetEngineLeft cEngineLeft;*/
			int16_t *ipNewEngineSpeed, iNewEngineSpeed;
			ipNewEngineSpeed = (int16_t*) &strpProtocolLink->receive.commandData[__HEADER_SIZE];
			iNewEngineSpeed = *ipNewEngineSpeed;
			toPlatformByteOrder ((char*) &iNewEngineSpeed, 2);
			iEngineLeft = iNewEngineSpeed;
			break;
		}

		/* Aendern des Winkels der Welle
		 * der Antriebsmotoren.
		 */
		case __UART_PROTOCOL_STEPPER_ENGINE: {
			struct packetSetStepperEngine cStepperEngine;
			int16_t *ipNewAngle, iNewAngle;
			ipNewAngle = (int16_t*) &strpProtocolLink->receive.commandData[__HEADER_SIZE];
			iNewAngle = *ipNewAngle;
			toPlatformByteOrder ((char*) &iNewAngle, 2);
			/*setStepperOffsetAngle (&caStepper[__STEPPER_ENGINE], iNewAngle);*/
			uartProtocolSendResponse (strpProtocolLink, (char*) &cStepperEngine, 2);
			printDebugMsg ("packet received: stepper horizontal");
			printDebugMsg ("value: ");
			/*uartPutS32Int (iNewAngle);*/
			break;
		}

		/* Aendern der vertikalen Position
		 * der Sensorplattform.
		 */
		case __UART_PROTOCOL_STEPPER_VERTICAL: {
			struct packetSetStepperVertical cStepperVertical;
			int16_t* ipNewAngle, iNewAngle;
			ipNewAngle = (int16_t*) &strpProtocolLink->receive.commandData[__HEADER_SIZE];
			iNewAngle = *ipNewAngle;
			toPlatformByteOrder ((char*) &iNewAngle, 2);
			//setStepperOffsetAngle (&caStepper[__STEPPER_SENSOR_VERTICAL], iNewAngle);
			uartProtocolSendResponse (strpProtocolLink, (char*) &cStepperVertical, 2);
			printDebugMsg ("packet received: stepper vertical");
			printDebugMsg ("value: ");
			//uartPutS32Int (iNewAngle);
			break;
		}

		/* Aendern der horizontalen Position
		 * der Sensorplatform.
		 */
		case __UART_PROTOCOL_STEPPER_HORIZONTAL: {
			struct packetSetStepperHorizontal cStepperHorizontal;
			int16_t *ipNewAngle, iNewAngle;
			ipNewAngle = (int16_t*) &strpProtocolLink->receive.commandData[__HEADER_SIZE];
			iNewAngle = *ipNewAngle;
			toPlatformByteOrder ((char*) &iNewAngle, 2);
			/*//setStepperOffsetAngle (&caStepper[__STEPPER_SENSOR_HORIZONTAL], iNewAngle);
			//setStepperAbsoluteAngle (&caStepper[__STEPPER_SENSOR_HORIZONTAL], iNewAngle, __STEPPER_DIRECTION_LEFT);*/
			uartProtocolSendResponse (strpProtocolLink, (char*) &cStepperHorizontal, 2);
			printDebugMsg ("packet received: stepper horizontal");
			printDebugMsg ("value: ");
			/*uartPutS32Int (iNewAngle);*/
			break;
		}

		/* Aendert den Status einer LED
		 * DEBUG
		 */
		case __UART_PROTOCOL_COMMAND_LED_1: {
			break;
		}
		
		/* Ein unbekannter Pakettyp wurde empfangen.
		 * Das Paket wird verworfen und eine
		 * Fehlermeldung an die Gegenstelle 
		 * zurueck gesendet.
		 */
		default: {
			strpProtocolLink->uiOccuredErrorCode = __ERROR_PROTOCOL_UNKNOWN_REQUEST;
			printDebugMsg("\nunknown protocol request\n");
			/*return (__ERROR);*/
			break;
		}
	}
	
	return (__SUCCESS);
}

uint8_t uartProtocolHandlePacket (struct strUartProtocol *strpProtocolLink)
{
	uint8_t uiPacketType = uartProtocolGetPacketType (strpProtocolLink);
	if (uiPacketType == __UART_REMOTE_REQUEST) {
		return (uartProtocolHandleRemoteRequest (strpProtocolLink));
	} else if (uiPacketType == __UART_REMOTE_RESPONSE) {
		uartProtocolIncSequenceNo(strpProtocolLink,
				&strpProtocolLink->uiSequenceNoReceivePos,
				strpProtocolLink->uiSequenceNoSendPos);
		return (__SUCCESS);
	} else {
		printDebugMsg("\nunknown packet source\n");
		/* FIXME: anderer return wert */
		return (__SUCCESS);
	}
}


#endif
