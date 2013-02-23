#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "CCAsyncRemoteSprite.h"

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

    auto sprite = CCAsyncRemoteSprite::create("http://smilingpoplar.github.com/CCAsyncRemoteSprite/avatar.png");
    auto item = CCMenuItemSprite::create(sprite, NULL, this, menu_selector(HelloWorld::itemCallback));
    sprite->onSuccess([=]() {
        item->setContentSize(sprite->getContentSize());
    });
    auto menu = CCMenu::create(item, NULL);
    auto size = CCDirector::sharedDirector()->getWinSize();
    menu->setPosition({size.width/2, size.height/2});
    addChild(menu);
    
    auto author = CCLabelTTF::create("YangLe", "", 28);
    addChild(author);
    author->setPosition({size.width/2, size.height/2-70});
    
    return true;
}

void HelloWorld::itemCallback(CCObject* pSender) {
    CCLOG("button callback");
}
