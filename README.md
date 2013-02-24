# CCAsyncRemoteSprite

async create sprite from remote image, with disk cache

for cocos2dx-2.x ios, using AFNetwork

[MIT Licence](http://opensource.org/licenses/mit-license.php)

### Usage

    auto sprite = CCAsyncRemoteSprite::create("http://smilingpoplar.github.com/CCAsyncRemoteSprite/avatar.png");
    auto item = CCMenuItemSprite::create(sprite, NULL, this, menu_selector(HelloWorld::itemCallback));
    sprite->onSuccess([=]() {
        item->setContentSize(sprite->getContentSize());
    });
    auto menu = CCMenu::create(item, NULL);
    auto size = CCDirector::sharedDirector()->getWinSize();
    menu->setPosition({size.width/2, size.height/2});
    addChild(menu);
    