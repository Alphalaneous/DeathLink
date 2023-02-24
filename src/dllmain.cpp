#include "includes.h"
#include "ServerListener.h"
#include "DeathMethods.h"
#include <thread>
#include "Utils.h"

bool (__thiscall* MenuLayer_init)(CCLayer* self);
bool __fastcall MenuLayer_init_H(CCLayer* self, void*) {

    if (!MenuLayer_init(self)) return false;

    auto buttonSprite = CCSprite::createWithSpriteFrameName("gj_linkBtn_001.png");

    auto button = gd::CCMenuItemSpriteExtra::create(buttonSprite, self,
        menu_selector(DeathMethods::link));

    auto winSize = CCDirector::sharedDirector()->getWinSize();

    button->setPosition({ 100, 105 });

    auto menu = CCMenu::create();
    menu->addChild(button);

    menu->setPosition({ 0,0 });

    self->addChild(menu);
    
    
}
void(__thiscall* PlayerObject_playerDestroyed)(gd::PlayerObject* self, bool);
void __fastcall PlayerObject_playerDestroyed_H(gd::PlayerObject* self, void*, bool param_1) {

    PlayerObject_playerDestroyed(self, param_1);
    ServerListener::instance()->sendMessage("dead");
}

void(__thiscall* PlayLayer_destroyPlayer)(CCLayer* self, bool);
void __fastcall PlayLayer_destroyPlayer_H(CCLayer* self, void*, bool param_1) {
    
    PlayLayer_destroyPlayer(self, param_1);
}

DWORD WINAPI thread_func(void* hModule) {
    MH_Initialize();
    auto base = reinterpret_cast<std::uintptr_t>(GetModuleHandle(0));
    
    MH_CreateHook(
        reinterpret_cast<void*>(base + 0x1907b0),
        reinterpret_cast<void*>(&MenuLayer_init_H),
        reinterpret_cast<void**>(&MenuLayer_init)
    );
    MH_CreateHook(
        reinterpret_cast<void*>(base + 0x1EFAA0),
        reinterpret_cast<void*>(&PlayerObject_playerDestroyed_H),
        reinterpret_cast<void**>(&PlayerObject_playerDestroyed)
    );
    MH_CreateHook(
        reinterpret_cast<void*>(base + 0x20A1A0),
        reinterpret_cast<void*>(&PlayLayer_destroyPlayer_H),
        reinterpret_cast<void**>(&PlayLayer_destroyPlayer)
    );
    MH_EnableHook(MH_ALL_HOOKS);

    ServerListener* listener = nullptr;
    listener->instance();

    return 0;
}

BOOL APIENTRY DllMain(HMODULE handle, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        auto h = CreateThread(0, 0, thread_func, handle, 0, 0);
        if (h)
            CloseHandle(h);
        else
            return FALSE;
    }
    return TRUE;
}