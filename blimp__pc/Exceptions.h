#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include <string>
#include <inttypes.h>

class GeneralException
{
    private: uint32_t uiExceptionType;
    private: std::string sErrorMessage;
    
    public: uint32_t exceptionType ();
    public: void exceptionType (uint32_t uiExceptionTypeToSet);
    
    public: std::string errorMessage ();
    public: void errorMessage (std::string sErrorMessageToSet);
};

#endif
