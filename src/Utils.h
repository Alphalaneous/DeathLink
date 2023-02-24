#pragma once

#ifndef __UTILS_HPP
#define __UTILS_HPP

template<typename Base, typename T>
inline bool instanceof(const T* ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

class Utils {
    public:
        static int randomBetween(int min, int max) {
            static bool first = true;
            if (first)
            {
                srand(time(NULL)); 
                first = false;
            }
            return min + rand() % ((max + 1) - min);
        };

        static gd::CCMenuItemSpriteExtra* getSpriteAtPos(CCArray* children, double x, double y) {
            CCObject* object;
            CCARRAYDATA_FOREACH(children->data, object) {
                if (instanceof<gd::CCMenuItemSpriteExtra>(object)) {
                    gd::CCMenuItemSpriteExtra* menu = reinterpret_cast<gd::CCMenuItemSpriteExtra*>(object);
                    if (menu->getPositionX() == x && menu->getPositionY() == y) {
                        
                        return menu;
                    }
                }
            }
            return nullptr;
        }
        static CCMenu* getMenuAtPos(CCArray* children, double x, double y) {
            CCObject* object;
            CCARRAYDATA_FOREACH(children->data, object) {
                if (instanceof<CCMenu>(object)) {
                    CCMenu* menu = reinterpret_cast<CCMenu*>(object);
                    if (menu->getPositionX() == x && menu->getPositionY() == y) {

                        return menu;
                    }
                }
            }
            return nullptr;
        }
        template<class Type = cocos2d::CCNode*>
        static Type getChildOfType(cocos2d::CCNode* node, size_t index) {
            auto indexCounter = static_cast<size_t>(0);

            for (size_t i = 0; i < node->getChildrenCount(); ++i) {
                Type obj = reinterpret_cast<Type>(
                    node->getChildren()->objectAtIndex(i)
                    );
                if (obj != nullptr) {
                    if (indexCounter == index) {
                        return obj;
                    }
                    ++indexCounter;
                }
            }

            return nullptr;
        }

};

#endif