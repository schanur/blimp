#ifndef __STRING_DUMP_H
#define __STRING_DUMP_H


#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <iostream>

using namespace std;
	
class StringDump
{
	private: unsigned int i;
	private: string sName;
	private: void printChar (char charToPrint);

	public: StringDump(string sOutputName);
	public: void dumpString (string strToDump);
	public: void dumpString (char *cpToDump, uint8_t uiLength);

};
#endif
