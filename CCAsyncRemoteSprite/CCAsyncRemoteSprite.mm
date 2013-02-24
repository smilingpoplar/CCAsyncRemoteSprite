//
//  CCAsyncRemoteSprite.mm
//  CCAsyncRemoteSprite
//
//  Created by smilingpoplar on 13-2-23.
//
//

#include "CCAsyncRemoteSprite.h"
#include "HttpCache.h"

using namespace std;
USING_NS_CC;

bool CCAsyncRemoteSprite::init(const char *url) {
    if (!CCSprite::init()) {
        return false;
    }
    
    retain();
    [[HttpCache sharedInstance] cacheUrl:@(url) success:^(NSString *path) {
        auto texture = CCTextureCache::sharedTextureCache()->addImage([path UTF8String]);
        if (texture) {
            setTexture(texture);
            CCRect rect = CCRectZero;
            rect.size = texture->getContentSize();
            setTextureRect(rect);
            if (_success) _success();
        }
        release();
    } failure:^{
        release();
    }];
    return true;
}

CCAsyncRemoteSprite* CCAsyncRemoteSprite::create(const char *url) {
    auto sprite = new CCAsyncRemoteSprite();
    if (sprite && sprite->init(url)) {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

void CCAsyncRemoteSprite::onSuccess(function<void ()> success) {
    _success = success;
}
