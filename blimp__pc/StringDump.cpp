#ifndef __STRING_DUMP_CPP
#define __STRING_DUMP_CPP

#include "StringDump.h"

StringDump::StringDump(string sOutputName)
{
	i = 0;
	sName = sOutputName;
}


void StringDump::printChar (char charToPrint)
{
	cerr << sName << ":\t" << "No: " << i 
			<< "\thex: " << (int*) charToPrint
			<< "\tint: " << (int16_t) charToPrint 
			<< "  \tchar: ";
	if ((charToPrint < 32) && (charToPrint >= 0)) {
		cerr << "cc" << endl;
	} else {
		cerr << "\"" << charToPrint << "\"\t" << endl;
	}
}

void StringDump::dumpString (string strToDump)
{
	int j = 0, k = 0;
	unsigned int iStrPos = 0;
	char lastchar = 0x00; 
	while (iStrPos < strToDump.length ()) { 
		if (lastchar == strToDump[iStrPos]) {
			j++;	
			if (j >= 10) {
				k++;
				if (k == 1000) {
					cout << "*" << flush;
					k = 0;
				}
			} else {
				printChar(strToDump[iStrPos]);
			}
		} else {
			if (j >= 10) {
				cout << endl;
			}
			j = 0;
			k = 0;
			lastchar = strToDump[iStrPos];
			printChar(strToDump[iStrPos]);
		}
		i++;
		iStrPos++;
	}
}

void StringDump::dumpString (char *cpToDump, uint8_t uiLength)
{
	string strToDump (cpToDump, uiLength);
	dumpString (strToDump);

}

#endif
