//
//  HttpCache.h
//  CCAsyncRemoteSprite
//
//  Created by smilingpoplar on 13-2-23.
//
//

#import <Foundation/Foundation.h>

@interface HttpCache : NSObject
@property (nonatomic) int cacheAge;

+ (id)sharedInstance;
- (void)cacheUrl:(NSString *)url success:(void (^)(NSString *path))success failure:(void (^)())failure;
- (void)clearUrl:(NSString *)url;
- (void)clearAll;
@end
