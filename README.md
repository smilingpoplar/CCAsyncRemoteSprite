# CCAsyncRemoteSprite

async create sprite from remote image, with disk cache

for cocos2dx-2.x ios, using AFNetwork

[MIT Licence](http://opensource.org/licenses/mit-license.php)

### Usage

    const char *url = "http://smilingpoplar.github.com/CCAsyncRemoteSprite/avatar.png";
    auto size = CCDirector::sharedDirector()->getWinSize();
    // 1. sprite
    auto sprite = CCAsyncRemoteSprite::create(url);
    addChild(sprite);
    sprite->setPosition({size.width/2, size.height/2});
    // 2. menu item
    auto item = CCAsyncRemoteMenuItem::create(url, this, menu_selector(HelloWorld::itemCallback));
    auto menu = CCMenu::create(item, NULL);
    addChild(menu);
    menu->setPosition({size.width/2, size.height/2});
    