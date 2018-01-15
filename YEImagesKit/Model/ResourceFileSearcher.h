//
//  ResourceFileSearcher.h
//  YEImagesKit
//
//

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

extern NSString * const kNotificationResourceFileQueryDone;


@interface ResourceFileInfo : NSObject

@property (strong, nonatomic) NSString *name;
@property (strong, nonatomic) NSString *fullPath;//fullPath
@property (strong, nonatomic) NSString *relativePath;//relativePath, relative to the project path
@property (assign, nonatomic) BOOL isDir;
@property (assign, nonatomic) uint64_t fileSize;

- (NSImage *)image;

@end


@interface ResourceFileSearcher : NSObject

@property (strong, nonatomic, readonly) NSMutableDictionary *resNameInfoDict;/**< dict<NSString name, ResourceFileInfo *info> */

+ (instancetype)sharedObject;

- (void)startWithProjectPath:(NSString *)projectPath excludeFolders:(NSArray *)excludeFolders resourceSuffixs:(NSArray *)resourceSuffixs;
- (void)reset;

@end
