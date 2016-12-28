#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

using namespace std;

class GeneralException
{
    private: uint32_t uiExceptionType;
    private: string sErrorMessage;
    
    public: uint32_t exceptionType ();
    public: void exceptionType (uint32_t uiExceptionTypeToSet);
    
    public: string errorMessage ();
    public: void errorMessage (string sErrorMessageToSet);
};

#endif
