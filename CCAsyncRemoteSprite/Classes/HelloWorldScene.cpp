#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "CCAsyncRemoteSprite.h"
#include "CCAsyncRemoteMenuItem.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
    if (!CCLayer::init()) return false;

    const char *url = "http://smilingpoplar.github.com/CCAsyncRemoteSprite/avatar.png";
    auto size = CCDirector::sharedDirector()->getWinSize();
    // 1. sprite
//    auto sprite = CCAsyncRemoteSprite::create(url);
//    addChild(sprite);
//    sprite->setPosition({size.width/2, size.height/2});
    // 2. menu item
    auto item = CCAsyncRemoteMenuItem::create(url, this, menu_selector(HelloWorld::itemCallback));
    auto menu = CCMenu::create(item, NULL);
    addChild(menu);
    menu->setPosition({size.width/2, size.height/2});
    
    auto author = CCLabelTTF::create("YangLe", "", 28);
    addChild(author);
    author->setPosition({size.width/2, size.height/2-70});
    
    return true;
}

void HelloWorld::itemCallback(CCObject* pSender) {
    CCLOG("button callback");
}
