#ifndef __EXCEPTIONS_CPP__
#define __EXCEPTIONS_CPP__

#include "Exceptions.h"

uint32_t GeneralException :: exceptionType ()
{
    return uiExceptionType;
}

void GeneralException :: exceptionType (uint32_t uiExceptionTypeToSet)
{
    uiExceptionType = uiExceptionTypeToSet;
}

std::string GeneralException :: errorMessage ()
{
    return sErrorMessage;
}

void GeneralException :: errorMessage (std::string sErrorMessageToSet)
{
    sErrorMessage = sErrorMessageToSet;
}

#endif
