//
//  CCAsyncRemoteMenuItem.h
//  CCAsyncRemoteSprite
//
//  Created by smilingpoplar on 13-2-24.
//
//

#ifndef __CCAsyncRemoteMenuItem__
#define __CCAsyncRemoteMenuItem__

#include "cocos2d.h"

class CCAsyncRemoteMenuItem : public cocos2d::CCMenuItemSprite {
public:
    bool init(const char *url, CCObject* target, cocos2d::SEL_MenuHandler selector);
    static CCAsyncRemoteMenuItem* create(const char *url, CCObject* target, cocos2d::SEL_MenuHandler selector);
};

#endif /* defined(__CCAsyncRemoteMenuItem__) */
