//
//  RecourseStringSearcher.h
//  YEImagesKit
//
//

#import <Foundation/Foundation.h>

extern NSString * const kNotificationResourceStringQueryDone;


@interface ResourceStringSearcher : NSObject

@property (strong, nonatomic, readonly) NSMutableSet *resStringSet;

+ (instancetype)sharedObject;

- (void)startWithProjectPath:(NSString *)projectPath excludeFolders:(NSArray *)excludeFolders resourceSuffixs:(NSArray *)resourceSuffixs fileSuffixs:(NSArray *)fileSuffixs;
- (void)reset;

- (BOOL)containsResourceName:(NSString *)name;

/**
 *  If resource name is: "icon_tag_1.png", and using in code by "icon_tag_%d", this resource is used with a similar name.
 *
 *  @param name resource name
 *
 *  @return BOOL
 */
- (BOOL)containsSimilarResourceName:(NSString *)name regExps:(NSArray *)regExps;

@end
