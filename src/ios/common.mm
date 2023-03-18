#include "common.h"
#import <Foundation/Foundation.h>
#import <Foundation/NSString.h>

@implementation FileManagerIOS

+ (NSString *)getWritablePosition {
    // Trova la directory Documenti dell'applicazione
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);

    // Se non è stata trovata alcuna directory Documenti, restituisci nil
    if (paths.count == 0) {
        return nil;
    }

    // Restituisci il percorso della prima directory Documenti trovata
    return paths[0];
}

@end
