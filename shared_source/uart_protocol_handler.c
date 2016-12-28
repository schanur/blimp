#ifndef __UART_PROTOCOL_HANDLER_C__
#define __UART_PROTOCOL_HANDLER_C__


#include "uart_protocol_handler.h"

uint8_t uartProtocolInitProtocolHandler (struct strUartProtocol *strpProtocolLink,
		const uint8_t uiSequenceNoBegin,
		const uint8_t uiSequenceNoEnd)
{
	strpProtocolLink->uiSequenceNoBegin = uiSequenceNoBegin;
	strpProtocolLink->uiSequenceNoEnd = uiSequenceNoEnd;
	strpProtocolLink->uiSequenceNoReceivePos = strpProtocolLink->uiSequenceNoBegin;
	strpProtocolLink->uiSequenceNoSendPos = strpProtocolLink->uiSequenceNoBegin;
	strpProtocolLink->receive.dataPos = 0;
	strpProtocolLink->send.dataPos = 0;
	strpProtocolLink->uiSendResetCharCount = 0;
	strpProtocolLink->uiReceiveResetCharCount = 0;
	strpProtocolLink->uiUARTWatchdog = 0;
	strpProtocolLink->uiConnectionState = __PROTOCOL_STATE_CONNECTION_RESET;
	return (__SUCCESS);
}

void uartProtocolIncSequenceNo (struct strUartProtocol *strpProtocolLink,
		uint8_t *uiSequenceNoToInc,
		uint8_t uiSequenceBarrier)
{
	//cerr << "vor inc " << (int)protocol.uiSequenceNoSendPos << " Begin " << (int)protocol.uiSequenceNoBegin << " End " << (int)protocol.uiSequenceNoEnd << endl;
	if (++(*uiSequenceNoToInc) > strpProtocolLink->uiSequenceNoEnd) {
		*uiSequenceNoToInc = strpProtocolLink->uiSequenceNoBegin;
	}
	if (*uiSequenceNoToInc == uiSequenceBarrier) {
		//panic();
	}
	//cerr << "nach inc " << (int)protocol.uiSequenceNoSendPos << endl;
}

uint8_t uartProtocolNewCommandReceived (struct strUartProtocol *strpProtocolLink)
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
	strpProtocolLink->receive.commandData[strpProtocolLink->receive.dataPos] = uiCharFromBuffer;
	
	/// Prüfung ob die Gegenstelle ein Reset-Zeichen sendet
	if (strpProtocolLink->receive.commandData[strpProtocolLink->receive.dataPos] == __UART_PROTOCOL_RESET_STATE_1_CHAR) {
		if (++strpProtocolLink->uiReceiveResetCharCount >= __UART_PROTOCOL_RESET_STATE_1_LENGTH) {
			return (4);
		}
	} else {
		strpProtocolLink->uiReceiveResetCharCount = 0;
	}
	
	if (strpProtocolLink->receive.dataPos > 2) {
		/// TODO: 7 gegen define ersetzen
		if (strpProtocolLink->receive.commandData[2] > 7) {
			return (2);
		}
		if (strpProtocolLink->receive.dataPos == strpProtocolLink->receive.commandData[2]) {
			/// Paket wurde komplett empfangen
			return (1);
		}
	}
	strpProtocolLink->receive.dataPos++;
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

uint8_t uartProtocolNewCommandValid (struct strUartProtocol *strpProtocolLink)
{
	char uiXORedValue = 0x00;
	uint8_t i;
	for (i = 0; i < strpProtocolLink->receive.dataPos; i++) {
		uiXORedValue ^= strpProtocolLink->receive.commandData[i];
	}
	if (uiXORedValue == strpProtocolLink->receive.commandData[strpProtocolLink->receive.dataPos]) {
		return (1);
	} 	
	return (0);
}

uint8_t uartProtocolSendMessage (struct strUartProtocol *strpProtocolLink,
		const char *uipResponse,
		const uint8_t uiPayloadLength,
		const uint8_t uiSeqenceNo,
		const uint8_t uiPacketTypeNo)
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

	strpProtocolLink->send.commandData[__PACKET_TYPE_POS] = uiPacketTypeNo;
	strpProtocolLink->send.commandData[__SEQUENCE_NO_POS] = uiSeqenceNo;
	strpProtocolLink->send.commandData[__PACKET_LENGTH_POS] = uiPayloadLength + __HEADER_SIZE;
	//cerr << "Sequenznummer : " << (int)uiSeqenceNo << endl;
	for (i = 0; i < uiPayloadLength; i++) {
		strpProtocolLink->send.commandData[i + __HEADER_SIZE] = *(uipResponse + i);
	}
	
	/// Berechnung der Pruefsumme des Pakets
	for (i = 0; i < uiPayloadLength + __HEADER_SIZE; i++) {
		uiXORedValue ^= strpProtocolLink->send.commandData[i];
	}
	strpProtocolLink->send.commandData[uiPayloadLength + __HEADER_SIZE] = uiXORedValue;
	
	for (i = 0; i <= uiPayloadLength + __HEADER_SIZE; i++) {
		while (UART_SEND_NONBLOCK (strpProtocolLink->send.commandData[i]) == __ERROR) {}
	}
	return (__SUCCESS);
}

uint8_t uartProtocolSendResponse (struct strUartProtocol *strpProtocolLink,
		const char *uipResponse,
		const uint8_t uiPayloadLength)
{
	return (uartProtocolSendMessage (strpProtocolLink,
			uipResponse, 
			uiPayloadLength,
			strpProtocolLink->receive.commandData[__SEQUENCE_NO_POS],
			strpProtocolLink->receive.commandData[__PACKET_TYPE_POS]));
	
}

uint8_t uartProtocolSendRequest (struct strUartProtocol *strpProtocolLink,
		const char *uipResponse,
		const uint8_t uiPayloadLength,
		const uint8_t uiPacketTypeNo)
{
	uartProtocolIncSequenceNo(strpProtocolLink, &strpProtocolLink->uiSequenceNoSendPos, strpProtocolLink->uiSequenceNoReceivePos);
	return (uartProtocolSendMessage(strpProtocolLink,
			uipResponse,
			uiPayloadLength,
			strpProtocolLink->uiSequenceNoSendPos,
			uiPacketTypeNo));
}

uint8_t uartProtocolGetPacketType (struct strUartProtocol *strpProtocolLink)
{
	if ((strpProtocolLink->receive.commandData[__SEQUENCE_NO_POS] >= __UART_SEQENCE_NO_BEGIN) &&
			(strpProtocolLink->receive.commandData[__SEQUENCE_NO_POS] <= __UART_SEQENCE_NO_END)) {
		
		return (__UART_REMOTE_RESPONSE);
	}
	return (__UART_REMOTE_REQUEST);
}

void uartProtocolClearIncomingCommandBuffer (struct strUartProtocol *strpProtocolLink)
{
	strpProtocolLink->receive.dataPos = 0;
}

void uartProtocolUndoResetProgress (struct strUartProtocol *strpProtocolLink)
{
	strpProtocolLink->uiReceiveResetCharCount = 0;
	strpProtocolLink->uiSendResetCharCount = 0;
}

uint8_t uartProtocolConnectionReset (struct strUartProtocol *strpProtocolLink) {
	/// TODO: EinFehlerfall falls der PC beispielsweise
	/// aufhoert Resets zu senden. Also Timeout etc..
	/// Code komentieren	

	char cReceivedChar;
	if (UART_RECEIVE_NONBLOCK (&cReceivedChar) == __SUCCESS) {
		if (cReceivedChar == __UART_PROTOCOL_RESET_STATE_1_CHAR) {
			if (strpProtocolLink->uiReceiveResetCharCount < __UART_PROTOCOL_RESET_STATE_1_LENGTH) {
				strpProtocolLink->uiReceiveResetCharCount++;
			} else if (strpProtocolLink->uiReceiveResetCharCount > __UART_PROTOCOL_RESET_STATE_1_LENGTH) {
				uartProtocolUndoResetProgress (strpProtocolLink);
			}
		} else if (cReceivedChar == __UART_PROTOCOL_RESET_STATE_2_CHAR) {
			if (strpProtocolLink->uiReceiveResetCharCount <  __UART_PROTOCOL_RESET_STATE_1_LENGTH) {
				uartProtocolUndoResetProgress (strpProtocolLink);
			} else if (strpProtocolLink->uiReceiveResetCharCount < __UART_PROTOCOL_RESET_STATE_2_LENGTH) {
				strpProtocolLink->uiReceiveResetCharCount++;
			} else {
				uartProtocolUndoResetProgress (strpProtocolLink);
			}
		} else {
			uartProtocolUndoResetProgress (strpProtocolLink);
		}
	}
	if (strpProtocolLink->uiReceiveResetCharCount < __UART_PROTOCOL_RESET_STATE_1_LENGTH) {
		if (UART_SEND_NONBLOCK (__UART_PROTOCOL_RESET_STATE_1_CHAR) == __SUCCESS) {
			if (strpProtocolLink->uiSendResetCharCount < __UART_PROTOCOL_RESET_STATE_1_LENGTH) {
				strpProtocolLink->uiSendResetCharCount++;
			}
		}
	} else if (strpProtocolLink->uiSendResetCharCount < __UART_PROTOCOL_RESET_STATE_1_LENGTH) {
		if (UART_SEND_NONBLOCK (__UART_PROTOCOL_RESET_STATE_1_CHAR) == __SUCCESS) {
			if (strpProtocolLink->uiSendResetCharCount < __UART_PROTOCOL_RESET_STATE_1_LENGTH) {
				strpProtocolLink->uiSendResetCharCount++;
			}
		}
	} else if (strpProtocolLink->uiSendResetCharCount < __UART_PROTOCOL_RESET_STATE_2_LENGTH) {
		if (UART_SEND_NONBLOCK (__UART_PROTOCOL_RESET_STATE_2_CHAR) == __SUCCESS) {
			strpProtocolLink->uiSendResetCharCount++;
		}
	} else if (strpProtocolLink->uiReceiveResetCharCount == __UART_PROTOCOL_RESET_STATE_2_LENGTH) {
		strpProtocolLink->uiUARTWatchdog = 0;
		return (__COMPLETE);
	}
	return (__INCOMPLETE);
}


uint8_t uartProtocolDoHandlerStep (struct strUartProtocol *strpProtocolLink)
{
	//uartPutChar (49);
	switch (strpProtocolLink->uiConnectionState) {
		case __PROTOCOL_STATE_COMMAND_INCOMLETE: {
			//while (uartPutString ("protocol state: incomplete\n") == __ERROR) {}
			switch (uartProtocolNewCommandReceived (strpProtocolLink)) {
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
					strpProtocolLink->uiConnectionState = __PROTOCOL_STATE_COMMAND_COMPLETE;
					break;
				}
				case 2: {
					/// laengen Fehler
					//while (uartPutString ("case: laengenfehler \n") == __ERROR) {}
					strpProtocolLink->uiConnectionState =  __PROTOCOL_STATE_CONNECTION_RESET;
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
					strpProtocolLink->uiConnectionState =  __PROTOCOL_STATE_CONNECTION_RESET;
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
			if (uartProtocolNewCommandValid (strpProtocolLink) == 1) {
				strpProtocolLink->uiConnectionState = __PROTOCOL_STATE_COMMAND_VALID;
			} else {
				strpProtocolLink->uiConnectionState = __PROTOCOL_STATE_COMMAND_INVALID;
			}
			break;
		}

		case __PROTOCOL_STATE_COMMAND_INVALID: {
			//while (uartPutString ("protocol state: invalid\n") == __ERROR) {}
			/// TODO: Momentan wird nur nach BIT-Fehlern gesucht.
			/// Später noch den Fall der Logik-Fehler betrachten.
			//while (uartPutString ("\ncommand invalid.\n") == __ERROR) {}
			strpProtocolLink->uiConnectionState = __PROTOCOL_STATE_CONNECTION_RESET;
			break;
		}

		case __PROTOCOL_STATE_COMMAND_VALID: {
			//while (uartPutString ("protocol state: valid\n") == __ERROR) {}
			//if (1) {
			//if (uartProtocolHandlePacket () == __SUCCESS) {
				/// Gehe wieder an den Anfang
				/// und warte auf ein neues
				/// Kommando.
			uartProtocolClearIncomingCommandBuffer (strpProtocolLink);
			strpProtocolLink->uiConnectionState = __PROTOCOL_STATE_COMMAND_INCOMLETE;
			//} else {
				/// Die Anfrage vom PC macht keinen Sinn.
			//	protocol.uiConnectionState = __PROTOCOL_STATE_CONNECTION_RESET;
			//}
			break;
		}

		case __PROTOCOL_STATE_CONNECTION_RESET: {
			//while (uartPutString ("protocol state: reset\n") == __ERROR) {}
			/// TODO: Hier fehlt auch noch was...
			if (uartProtocolConnectionReset (strpProtocolLink) == __COMPLETE) {
				//while (uartPutString ("reset sequence complete.\n") == __ERROR) {}				
				strpProtocolLink->uiConnectionState = __PROTOCOL_STATE_COMMAND_INCOMLETE;
				uartProtocolUndoResetProgress (strpProtocolLink);
				uartProtocolClearIncomingCommandBuffer (strpProtocolLink);
				//while (uartPutString ("\nreset complete.\n") == __ERROR) {}
				//#ifdef __cplusplus
				strpProtocolLink->uiSequenceNoReceivePos = strpProtocolLink->uiSequenceNoBegin;
				strpProtocolLink->uiSequenceNoSendPos = strpProtocolLink->uiSequenceNoBegin;
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
	return (strpProtocolLink->uiConnectionState);
}

#endif
