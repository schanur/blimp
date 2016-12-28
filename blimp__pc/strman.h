/* Autor: Bjoern Griebenow
 *
 */

#ifndef __STRMAN_H__
#define __STRMAN_H__

#include <sstream>
#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <algorithm>

using namespace std;

class strman
{
public:
    strman();
public:
    ~strman();

public: int countWords(string sWholeString, string sSeparator);
public: string getWord(string sWholeString, string sSeparator, int nWordNo);
public: string addWord(string sCollStr, string sStrToAdd, string sSeparator);
public: string swapWords(string sWholeString, string sSeparator, int nWordNo1, int nWordNo2);
public: string replaceWord(string sWholeString, string sNewWord, string sSeparator, int nWordToReplace);
public: string sortNumberListAsc(string sNumberList, string sSeparator);
public: string sortNumberListDesc(string sNumberList, string sSeparator);
public: string intToString(int nIntValue);
public: int stringToInt(string sStrValue);
};
#endif
