//
//  YEFileUtils.h
//  YEImagesKit
//
//

#import <Foundation/Foundation.h>

@interface YEFileUtils : NSObject
/**
 *  get file size, contain directory
 *  @param path  path
 *  @param isDir
 *
 *  @return
 */
+ (uint64_t)fileSizeAtPath:(NSString *)path isDir:(BOOL *)isDir;

+ (uint64_t)folderSizeAtPath:(NSString *)path;

@end
