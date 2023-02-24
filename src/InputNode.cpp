#include "InputNode.hpp"
#include "includes.h"

gd::CCTextInputNode* InputNode::getInputNode() {
    return this->m_pInput;
}

cocos2d::extension::CCScale9Sprite* InputNode::getBG() {
    return this->m_pBG;
}

void InputNode::setEnabled(bool enabled) {
    this->m_pInput->setMouseEnabled(enabled);
    this->m_pInput->setTouchEnabled(enabled);
}

InputNode* InputNode::createMulti(float _w, float _h, const char* _phtxt, const char* _fnt, int _cc) {
    auto pRet = new InputNode();

    if (pRet && pRet->initMulti(_w, _h, _phtxt, _fnt, "", _cc)) {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return nullptr;
}

InputNode* InputNode::createMulti(float _w, float _h, const char* _phtxt, const char* _fnt, const std::string & _awc, int _cc) {
    auto pRet = new InputNode();

    if (pRet && pRet->initMulti(_w, _h, _phtxt, _fnt, _awc, _cc)) {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return nullptr;
}
