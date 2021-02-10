#ifndef ONE_H
#define ONE_H

#include <windows.h>

/*  To use this exported function of dll, include this header
 *  in your project.
 */

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif

class one
{
    public:
        one();
        virtual ~one();
        void tttt();

    protected:

    private:
};

#ifdef __cplusplus
}
#endif




#endif // ONE_H
