#ifndef __STRMAN_CPP__
#define __STRMAN_CPP__
#include "strman.h"

using namespace std;

strman :: strman()
{}
;

strman :: ~strman()
{}
;

int strman :: countWords(string sWholeString, string sSeperator)
{
    int nSeparatorPos;
    int nWordCount = 0;

    nSeparatorPos = sWholeString.find(sSeperator);
    while (nSeparatorPos != -1)
    {
        nWordCount++;
        sWholeString.erase(0, nSeparatorPos + 1);
        nSeparatorPos = sWholeString.find(sSeperator);
    }

    nWordCount++;
    return nWordCount;
};

string strman :: getWord(string sWholeString, string sSeparator, int nWordNo)
{
    int nSeparatorPos;
    string sWord;

    int i;
    for (i = 1; i < nWordNo; i++)
    {
        sWholeString.erase(0, sWholeString.find(sSeparator) + 1);
    }
    nSeparatorPos = sWholeString.find(sSeparator);
    if (nSeparatorPos != -1)
    {
        sWord = sWholeString.erase(nSeparatorPos);
    }
    else
    {
        sWord = sWholeString;
    }
    return sWord;
};

string strman :: addWord(string sCollStr, string sStrToAdd, string sSeparator)
{
    if (sCollStr == "")
    {
        sCollStr = sStrToAdd;
    }
    else
    {
        sCollStr = sCollStr + sSeparator + sStrToAdd;
    }
    return sCollStr;
};

string strman :: swapWords(string sWholeString, string sSeparator, int nWordNo1, int nWordNo2)
{
    string sSwappedString;
    int nWordCount = countWords(sWholeString, sSeparator);
    int nNextWord;
    
    int i;
    for (i = 1; i <= nWordCount; i++)
    {
	nNextWord = i;
	if (i == nWordNo1)
	{
	    nNextWord = nWordNo2;
	}
	if (i == nWordNo2)
	{
	    nNextWord = nWordNo1;
	}
	sSwappedString = addWord(sSwappedString, sSeparator, 
		getWord(sWholeString, sSeparator, nNextWord));
    }
    return sSwappedString;
};

string strman :: replaceWord(string sWholeString, string sNewWord, string sSeparator, int nWordToReplace)
{
    string sNewString;
    int nWordCount = countWords(sWholeString, sSeparator);
    int i;
    for (i = 1; i <= nWordCount; i++) {
	if (i == nWordToReplace) {
	    sNewString = addWord(sNewString, sNewWord, sSeparator);
	} else {
	    sNewString = addWord(sNewString, getWord(sWholeString, sSeparator, i), sSeparator);
	}
    }
    return (sNewString);
}

string strman :: sortNumberListAsc(string sNumberList, string sSeparator)
{
    return "";
}

string strman :: sortNumberListDesc(string sNumberList, string sSeparator)
{
    string sNewNumberList;
    //int nSmall;
    //int nSmallLast = -200000000;
    int i;
    //int j;
    
    int nWordCount = countWords(sNumberList, sSeparator);
    int naNumbers[nWordCount];
    for (i = 1; i <= nWordCount; i++) {
	naNumbers[i - 1] = stringToInt(getWord(sNumberList, sSeparator, i));
    }
    
    sort(naNumbers, naNumbers + nWordCount);
    
    for (i = 0; i < nWordCount; i++) {
	sNewNumberList = addWord(sNewNumberList, intToString(naNumbers[i]), sSeparator);
    }
    
    /*for (i = 0; i < nWordCount; i++) {
	//nSmallLast = 200000000;
	for (j = 0; j < nWordCount; j++) {
	    if ((naNumbers[j][1] == 0) &
		    (naNumbers[j][0] >= nSmallLast)) {
		    nSmall = j;
	    }
	}
	sNewNumberList = AddWord(sNewNumberList, IntToString(naNumbers[nSmall][0]), sSeparator);
	naNumbers[nSmall][1] = 1;
	nSmallLast = naNumbers[nSmall][0];
    }*/
    return (sNewNumberList);
}

string strman :: intToString(int nIntValue)
{
    ostringstream oStrStream;
    oStrStream << nIntValue;
    return oStrStream.str();
}

int strman :: stringToInt(string sStrValue)
{
    int nIntValue;
    istringstream iStrStream(sStrValue);
    iStrStream >> nIntValue;
    return nIntValue;
}

#endif
