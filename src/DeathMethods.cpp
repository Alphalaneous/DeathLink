#include "includes.h"
#include "ServerListener.h"
#include "DeathMethods.h"

void DeathMethods::link(CCObject* obj) {

    InputPrompt* p = InputPrompt::create("Link Deaths to Player", "Username", [this](const char* val) -> void {
        if (val && strlen(val)) {
            ServerListener::instance()->sendMessage("link: " + std::string(val));
        }
        }, "Link");

    
    p->show();

  
}

