//
//  HttpCache.m
//  CCAsyncRemoteSprite
//
//  Created by smilingpoplar on 13-2-23.
//
//

#import "HttpCache.h"
#import "AFHTTPRequestOperation.h"

#if !__has_feature(objc_arc)
#error AFNetworking must be built with ARC.
// You can turn on ARC for only AFNetworking files by adding -fobjc-arc to the build phase for each of its files.
#endif

static const int kDefaultCacheAge = 60 * 60 * 24 * 7; // 1 week

@interface HttpCache ()
@property (nonatomic) NSString *cacheDir;
@end

@implementation HttpCache

+ (id)sharedInstance {
    static dispatch_once_t once;
    static id _sharedInstance;
    dispatch_once(&once, ^{ _sharedInstance = [[self alloc] init]; });
    return _sharedInstance;
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (id)init {
    self = [super init];
    if (self) {
        NSArray *paths = NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES);
        _cacheDir = [paths[0] stringByAppendingPathComponent:@"com.yangle.HttpCache"];
        if (![[NSFileManager defaultManager] fileExistsAtPath:_cacheDir]) {
            [[NSFileManager defaultManager] createDirectoryAtPath:_cacheDir
                                      withIntermediateDirectories:YES
                                                       attributes:nil
                                                            error:nil];
        }
        _cacheAge = kDefaultCacheAge;

        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(clearExpired)
                                                     name:UIApplicationWillTerminateNotification
                                                   object:nil];
    }
    return self;
}

- (NSString *)cachePathForUrl:(NSString *)url {
    return [self.cacheDir stringByAppendingPathComponent:[url lastPathComponent]];
}

- (void)cacheUrl:(NSString *)url success:(void (^)(NSString *path))success failure:(void (^)())failure {
    NSString *path = [self cachePathForUrl:url];
    if ([[NSFileManager defaultManager] fileExistsAtPath:path]) {
        if (success) success(path);
        return;
    }
    NSURLRequest *request = [NSURLRequest requestWithURL:[NSURL URLWithString:url]];
    AFHTTPRequestOperation *operation = [[AFHTTPRequestOperation alloc] initWithRequest:request];
    [operation setCompletionBlockWithSuccess:^(AFHTTPRequestOperation *operation, id responseObject) {
        [responseObject writeToFile:path atomically:YES];
        if (success) success(path);
    } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
        if (failure) failure();
    }];
    [operation start];
}

- (void)clearExpired {
    NSDate *expirationDate = [NSDate dateWithTimeIntervalSinceNow:-self.cacheAge];
    // convert NSString path to NSURL path
    NSURL *cacheURL = [NSURL fileURLWithPath:self.cacheDir isDirectory:YES];
    // build an enumerator by also prefetching file properties we want to read
    NSDirectoryEnumerator *fileEnumerator = [[NSFileManager defaultManager] enumeratorAtURL:cacheURL
                                                                 includingPropertiesForKeys:@[ NSURLIsDirectoryKey, NSURLContentModificationDateKey ]
                                                                                    options:NSDirectoryEnumerationSkipsHiddenFiles
                                                                               errorHandler:nil];
    for (NSURL *fileURL in fileEnumerator) {
        // skip folder
        NSNumber *isDirectory;
        [fileURL getResourceValue:&isDirectory forKey:NSURLIsDirectoryKey error:nil];
        if ([isDirectory boolValue]) continue;
        // compare file date with the max age
        NSDate *fileModificationDate;
        [fileURL getResourceValue:&fileModificationDate forKey:NSURLContentModificationDateKey error:nil];
        if ([[fileModificationDate laterDate:expirationDate] isEqualToDate:expirationDate]) {
            [[NSFileManager defaultManager] removeItemAtURL:fileURL error:nil];
        }
    }
}

- (void)clearUrl:(NSString *)url {
    [[NSFileManager defaultManager] removeItemAtPath:[self cachePathForUrl:url] error:nil];
}

- (void)clearAll {
    [[NSFileManager defaultManager] removeItemAtPath:self.cacheDir error:nil];
    [[NSFileManager defaultManager] createDirectoryAtPath:self.cacheDir
                              withIntermediateDirectories:YES
                                               attributes:nil
                                                    error:nil];
}

@end
