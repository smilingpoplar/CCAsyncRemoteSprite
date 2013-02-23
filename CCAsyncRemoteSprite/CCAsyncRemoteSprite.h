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
    bool init(const char *url);
    static CCAsyncRemoteSprite* create(const char *url);
    void onSuccess(std::function<void ()> success);
private:
    std::function<void ()> _success = nullptr;
};

#endif /* defined(__CCAsyncRemoteSprite__) */
