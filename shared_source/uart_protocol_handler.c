#ifndef __UART_PROTOCOL_HANDLER_C__
#define __UART_PROTOCOL_HANDLER_C__


#include "uart_protocol_handler.h"

uint8_t uartProtocolInitProtocolHandler (const uint8_t uiSequenceNoBegin, const uint8_t uiSequenceNoEnd)
{
	protocol.uiSequenceNoBegin = uiSequenceNoBegin;
	protocol.uiSequenceNoEnd = uiSequenceNoEnd;
	protocol.uiSequenceNoReceivePos = protocol.uiSequenceNoBegin;
	protocol.uiSequenceNoSendPos = protocol.uiSequenceNoBegin;
	protocol.receive.dataPos = 0;
	protocol.send.dataPos = 0;
	protocol.uiSendResetCharCount = 0;
	protocol.uiReceiveResetCharCount = 0;
	protocol.uiUARTWatchdog = 0;
	protocol.uiConnectionState = __PROTOCOL_STATE_CONNECTION_RESET;
	return (__SUCCESS);
}

void uartProtocolIncSequenceNo (uint8_t *uiSequenceNoToInc, uint8_t uiSequenceBarrier)
{
	//cerr << "vor inc " << (int)protocol.uiSequenceNoSendPos << " Begin " << (int)protocol.uiSequenceNoBegin << " End " << (int)protocol.uiSequenceNoEnd << endl;
	if (++(*uiSequenceNoToInc) > protocol.uiSequenceNoEnd) {
		*uiSequenceNoToInc = protocol.uiSequenceNoBegin;
	}
	if (*uiSequenceNoToInc == uiSequenceBarrier) {
		//panic();
	}
	//cerr << "nach inc " << (int)protocol.uiSequenceNoSendPos << endl;
}

uint8_t uartProtocolNewCommandReceived ()
{
	/// TODO
	/// und ebendfalls Timeout falls der PC z.B. nach
	/// N-1 Zeichen mit dem Senden aufhoert.

	char uiCharFromBuffer;
	if (UART_RECEIVE_NONBLOCK(&uiCharFromBuffer) == __ERROR) {
	//if (uartGetChar(&uiCharFromBuffer) == __ERROR) {
		return (0);
	} //else {
		//cerr << uiCharFromBuffer;
	//}
	//FIXME
	protocol.receive.commandData[protocol.receive.dataPos] = uiCharFromBuffer;
	
	/// Prüfung ob die Gegenstelle ein Reset-Zeichen sendet
	if ( protocol.receive.commandData[protocol.receive.dataPos] == __UART_PROTOCOL_RESET_STATE_1_CHAR) {
		if (++protocol.uiReceiveResetCharCount >= __UART_PROTOCOL_RESET_STATE_1_LENGTH) {
			return (4);
		}
	} else {
		protocol.uiReceiveResetCharCount = 0;
	}
	
	if (protocol.receive.dataPos > 2) {
		/// TODO: 7 gegen define ersetzen
		if (protocol.receive.commandData[2] > 7) {
			return (2);
		}
		if (protocol.receive.dataPos == protocol.receive.commandData[2]) {
			/// Paket wurde komplett empfangen
			return (1);
		}
	}
	protocol.receive.dataPos++;
	return (0);
}

/*int8_t uartProtocolcalcXORChecksum ()
{
	char uiXORedValue = 0x00;
	uint8_t i;
	for (i = 0; i < protocol.receive.dataPos; i++) {
		uiXORedValue ^= protocol.receive.commandData[i];
	}
	if (uiXORedValue == protocol.receive.commandData[protocol.receive.dataPos]) {
		return (1);
	} 	
	return (0);
}*/

uint8_t uartProtocolNewCommandValid ()
{
	char uiXORedValue = 0x00;
	uint8_t i;
	for (i = 0; i < protocol.receive.dataPos; i++) {
		uiXORedValue ^= protocol.receive.commandData[i];
	}
	if (uiXORedValue == protocol.receive.commandData[protocol.receive.dataPos]) {
		return (1);
	} 	
	return (0);
}

uint8_t uartProtocolSendMessage (const char *uipResponse, const uint8_t uiPayloadLength, const uint8_t uiSeqenceNo, const uint8_t uiPacketTypeNo)
{
	//while (UART_SEND_NONBLOCK ('=') == __ERROR) {}
	char uiXORedValue = 0x00;
	uint8_t i;
	/// TODO:
	/// Header struct verwenden
	
	if (uiPayloadLength > __MAX_PAYLOAD_SIZE) {
		/// FIXME:
		//while (uartPutString ("payload too long (send).") == __ERROR) {}
		return (__ERROR);
	}

	protocol.send.commandData[__PACKET_TYPE_POS] = uiPacketTypeNo;
	protocol.send.commandData[__SEQUENCE_NO_POS] = uiSeqenceNo;
	protocol.send.commandData[__PACKET_LENGTH_POS] = uiPayloadLength + __HEADER_SIZE;
	//cerr << "Sequenznummer : " << (int)uiSeqenceNo << endl;
	for (i = 0; i < uiPayloadLength; i++) {
		protocol.send.commandData[i + __HEADER_SIZE] = *(uipResponse + i);
	}
	
	/// Berechnung der Pruefsumme des Pakets
	for (i = 0; i < uiPayloadLength + __HEADER_SIZE; i++) {
		uiXORedValue ^= protocol.send.commandData[i];
	}
	protocol.send.commandData[uiPayloadLength + __HEADER_SIZE] = uiXORedValue;
	
	for (i = 0; i <= uiPayloadLength + __HEADER_SIZE; i++) {
		while (UART_SEND_NONBLOCK (protocol.send.commandData[i]) == __ERROR) {}
	}
	return (__SUCCESS);
}

uint8_t uartProtocolSendResponse (const char *uipResponse, const uint8_t uiPayloadLength)
{
	return (uartProtocolSendMessage (uipResponse, 
			uiPayloadLength,
			protocol.receive.commandData[__SEQUENCE_NO_POS],
			protocol.receive.commandData[__PACKET_TYPE_POS]));
	
}

uint8_t uartProtocolSendRequest (const char *uipResponse, const uint8_t uiPayloadLength, const uint8_t uiPacketTypeNo)
{
	uartProtocolIncSequenceNo(&protocol.uiSequenceNoSendPos, protocol.uiSequenceNoReceivePos);
	return (uartProtocolSendMessage(uipResponse,
			uiPayloadLength,
			protocol.uiSequenceNoSendPos,
			uiPacketTypeNo));
}

uint8_t uartProtocolGetPacketType ()
{
	if ((protocol.receive.commandData[__SEQUENCE_NO_POS] >= __UART_SEQENCE_NO_BEGIN) &&
			(protocol.receive.commandData[__SEQUENCE_NO_POS] <= __UART_SEQENCE_NO_END)) {
		
		return (__UART_REMOTE_RESPONSE);
	}
	return (__UART_REMOTE_REQUEST);
}

void uartProtocolClearIncomingCommandBuffer ()
{
	protocol.receive.dataPos = 0;
}

void uartProtocolUndoResetProgress ()
{
	protocol.uiReceiveResetCharCount = 0;
	protocol.uiSendResetCharCount = 0;
}

uint8_t uartProtocolConnectionReset () {
	/// TODO: EinFehlerfall falls der PC beispielsweise
	/// aufhoert Resets zu senden. Also Timeout etc..
	/// Code komentieren	

	char cReceivedChar;
	if (UART_RECEIVE_NONBLOCK (&cReceivedChar) == __SUCCESS) {
		if (cReceivedChar == __UART_PROTOCOL_RESET_STATE_1_CHAR) {
			if (protocol.uiReceiveResetCharCount < __UART_PROTOCOL_RESET_STATE_1_LENGTH) {
				protocol.uiReceiveResetCharCount++;
			} else if (protocol.uiReceiveResetCharCount > __UART_PROTOCOL_RESET_STATE_1_LENGTH) {
				uartProtocolUndoResetProgress ();
			}
		} else if (cReceivedChar == __UART_PROTOCOL_RESET_STATE_2_CHAR) {
			if (protocol.uiReceiveResetCharCount <  __UART_PROTOCOL_RESET_STATE_1_LENGTH) {
				uartProtocolUndoResetProgress ();
			} else if (protocol.uiReceiveResetCharCount < __UART_PROTOCOL_RESET_STATE_2_LENGTH) {
				protocol.uiReceiveResetCharCount++;
			} else {
				uartProtocolUndoResetProgress ();
			}
		} else {
			uartProtocolUndoResetProgress ();
		}
	}
	if (protocol.uiReceiveResetCharCount < __UART_PROTOCOL_RESET_STATE_1_LENGTH) {
		if (UART_SEND_NONBLOCK (__UART_PROTOCOL_RESET_STATE_1_CHAR) == __SUCCESS) {
			if (protocol.uiSendResetCharCount < __UART_PROTOCOL_RESET_STATE_1_LENGTH) {
				protocol.uiSendResetCharCount++;
			}
		}
	} else if (protocol.uiSendResetCharCount < __UART_PROTOCOL_RESET_STATE_1_LENGTH) {
		if (UART_SEND_NONBLOCK (__UART_PROTOCOL_RESET_STATE_1_CHAR) == __SUCCESS) {
			if (protocol.uiSendResetCharCount < __UART_PROTOCOL_RESET_STATE_1_LENGTH) {
				protocol.uiSendResetCharCount++;
			}
		}
	} else if (protocol.uiSendResetCharCount < __UART_PROTOCOL_RESET_STATE_2_LENGTH) {
		if (UART_SEND_NONBLOCK (__UART_PROTOCOL_RESET_STATE_2_CHAR) == __SUCCESS) {
			protocol.uiSendResetCharCount++;
		}
	} else if (protocol.uiReceiveResetCharCount == __UART_PROTOCOL_RESET_STATE_2_LENGTH) {
		protocol.uiUARTWatchdog = 0;
		return (__COMPLETE);
	}
	return (__INCOMPLETE);
}


uint8_t uartProtocolDoHandlerStep ()
{
	//uartPutChar (49);
	switch (protocol.uiConnectionState) {
		case __PROTOCOL_STATE_COMMAND_INCOMLETE: {
			//while (uartPutString ("protocol state: incomplete\n") == __ERROR) {}
			switch (uartProtocolNewCommandReceived ()) {
			/// TODO: hart kodierte Zahlen durch defines ersetzen
			/// und die faelle alle noch etwas besser abhandeln
			
				case 0: {
					///es wurde kein Paket komplettiert
					//while (uartPutString ("case: 0 \n") == __ERROR) {}
					break;
				}
				case 1: {
					/// Paket wurde komplett empfangen
					//while (uartPutString ("case: aok \n") == __ERROR) {}
					protocol.uiConnectionState = __PROTOCOL_STATE_COMMAND_COMPLETE;
					break;
				}
				case 2: {
					/// laengen Fehler
					//while (uartPutString ("case: laengenfehler \n") == __ERROR) {}
					protocol.uiConnectionState =  __PROTOCOL_STATE_CONNECTION_RESET;
					break;
				}
				case 3: {
					/// Timeout
					//FIXME:
					//panic ();
					break;
				}
				case 4: {
					/// PC hat RESET gesendet
					protocol.uiConnectionState =  __PROTOCOL_STATE_CONNECTION_RESET;
					break;
				}
				default: {
					//FIXME:
					//panic ();
				}
			}
			/// TODO: Fehler zurueckgeben bei einem Timeout
			break;
		}

		case __PROTOCOL_STATE_COMMAND_COMPLETE: {
			//while (uartPutString ("protocol state: complete\n") == __ERROR) {}
			if (uartProtocolNewCommandValid () == 1) {
				protocol.uiConnectionState = __PROTOCOL_STATE_COMMAND_VALID;
			} else {
				protocol.uiConnectionState = __PROTOCOL_STATE_COMMAND_INVALID;
			}
			break;
		}

		case __PROTOCOL_STATE_COMMAND_INVALID: {
			//while (uartPutString ("protocol state: invalid\n") == __ERROR) {}
			/// TODO: Momentan wird nur nach BIT-Fehlern gesucht.
			/// Später noch den Fall der Logik-Fehler betrachten.
			//while (uartPutString ("\ncommand invalid.\n") == __ERROR) {}
			protocol.uiConnectionState = __PROTOCOL_STATE_CONNECTION_RESET;
			break;
		}

		case __PROTOCOL_STATE_COMMAND_VALID: {
			//while (uartPutString ("protocol state: valid\n") == __ERROR) {}
			//if (1) {
			//if (uartProtocolHandlePacket () == __SUCCESS) {
				/// Gehe wieder an den Anfang
				/// und warte auf ein neues
				/// Kommando.
			uartProtocolClearIncomingCommandBuffer ();
			protocol.uiConnectionState = __PROTOCOL_STATE_COMMAND_INCOMLETE;
			//} else {
				/// Die Anfrage vom PC macht keinen Sinn.
			//	protocol.uiConnectionState = __PROTOCOL_STATE_CONNECTION_RESET;
			//}
			break;
		}

		case __PROTOCOL_STATE_CONNECTION_RESET: {
			//while (uartPutString ("protocol state: reset\n") == __ERROR) {}
			/// TODO: Hier fehlt auch noch was...
			if (uartProtocolConnectionReset () == __COMPLETE) {
				//while (uartPutString ("reset sequence complete.\n") == __ERROR) {}				
				protocol.uiConnectionState = __PROTOCOL_STATE_COMMAND_INCOMLETE;
				uartProtocolUndoResetProgress ();
				uartProtocolClearIncomingCommandBuffer ();
				//while (uartPutString ("\nreset complete.\n") == __ERROR) {}
				//#ifdef __cplusplus
				protocol.uiSequenceNoReceivePos = protocol.uiSequenceNoBegin;
				protocol.uiSequenceNoSendPos = protocol.uiSequenceNoBegin;
				//#ifdef __DEBUG__
				//printDebugMsg ("Reset complete.\n");
				//#endif
				//#endif
			}
			break;
		}

		default: {
			//while (uartPutString ("protocol state: moeoeepp!!??\n") == __ERROR) {}
			/// moeoeepp???	
			//FIXME
			//panic ();
			break;
		}
	}
	return (protocol.uiConnectionState);
}

#endif
