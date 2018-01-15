//
//  StringUtils.h
//  YEImagesKit
//
//

#import <Foundation/Foundation.h>

@interface StringUtils : NSObject

+ (NSString *)stringByRemoveResourceSuffix:(NSString *)str;
+ (NSString *)stringByRemoveResourceSuffix:(NSString *)str suffix:(NSString *)suffix;
+ (BOOL)isImageTypeWithName:(NSString *)name;
+ (NSString *)getRelativePathFromFullPath:(NSString *)fullPath withProjectPath:(NSString *)projectPath;

@end
