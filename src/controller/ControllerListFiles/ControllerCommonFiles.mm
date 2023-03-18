#include "ControllerCommonFiles.h"
#include "src/ios/common.h"
#import <objc/runtime.h>

#ifdef Q_OS_IOS
extern "C" const char* callObjectiveCFunction();

const char* callObjectiveCFunction()
{
    // Ottiene il selettore del metodo getWritablePosition
    SEL selector = NSSelectorFromString(@"getWritablePosition");

    // Ottiene la classe FileManagerIOS
    Class myClass = objc_getClass("FileManagerIOS");

    // Chiama il metodo getWritablePosition sulla classe FileManagerIOS
    IMP imp = [myClass methodForSelector:selector];
    NSString *(*func)(id, SEL) = (NSString *(*)(id, SEL))imp;
    NSString *result = func(myClass, selector);

    // Converte il risultato in una stringa QByteArray di Qt
    QByteArray byteArray = result.UTF8String;

    // Restituisce la stringa QByteArray di Qt come un char array
    return byteArray;
}
#endif

namespace ControllerCommonFiles {

QByteArray getDocumentFolder()
{
    QByteArray ret {};

#ifdef Q_OS_IOS
    return QByteArray(callObjectiveCFunction());
#endif
}

}
