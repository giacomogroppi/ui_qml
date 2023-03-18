#ifndef COMMON_H
#define COMMON_H

#import <Foundation/Foundation.h>
#import <Foundation/NSString.h>

@class NSObject;

@interface FileManagerIOS : NSObject

+ (NSString *)getWritablePosition;

@end


#endif // COMMON_H
