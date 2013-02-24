//
//  CCAsyncRemoteSprite.h
//  CCAsyncRemoteSprite
//
//  Created by smilingpoplar on 13-2-23.
//
//

#ifndef __CCAsyncRemoteSprite__
#define __CCAsyncRemoteSprite__

#include "cocos2d.h"

class CCAsyncRemoteSprite : public cocos2d::CCSprite {
public:
    bool init(const char *url,
              std::function<void (CCAsyncRemoteSprite *asyncRemoteSprite)> success,
              std::function<void ()> failure);
    static CCAsyncRemoteSprite* create(const char *url,
                                       std::function<void (CCAsyncRemoteSprite *asyncRemoteSprite)> success = nullptr,
                                       std::function<void ()> failure = nullptr);
};

#endif /* defined(__CCAsyncRemoteSprite__) */
