//
//  CCAsyncRemoteMenuItem.cpp
//  CCAsyncRemoteSprite
//
//  Created by smilingpoplar on 13-2-24.
//
//

#include "CCAsyncRemoteMenuItem.h"
#include "CCAsyncRemoteSprite.h"

USING_NS_CC;

bool CCAsyncRemoteMenuItem::init(const char *url, CCObject* target, cocos2d::SEL_MenuHandler selector) {
    retain();
    CCAsyncRemoteSprite *sprite = CCAsyncRemoteSprite::create(url, [=](CCAsyncRemoteSprite *thisAsyncRemoteSprite) {
        setContentSize(thisAsyncRemoteSprite->getContentSize());
        release();
    }, [=]() {
        release();
    });
    if (!CCMenuItemSprite::initWithNormalSprite(sprite, NULL, NULL, target, selector)) return false;
    return true;
}

CCAsyncRemoteMenuItem* CCAsyncRemoteMenuItem::create(const char *url, CCObject* target, cocos2d::SEL_MenuHandler selector) {
    auto sprite = new CCAsyncRemoteMenuItem();
    if (sprite && sprite->init(url, target, selector)) {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}