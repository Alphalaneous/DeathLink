#pragma once

#ifndef __INPUT_PROMPT_H
#define __INPUT_PROMPT_H

#include "BrownAlertDelegate.hpp"
#include "InputNode.hpp"

class InputPrompt : public BrownAlertDelegate {
    public:
        using InputResult = std::function<void(const char*)>;
    protected:
        InputNode* m_pInput;
        InputResult m_pResultFunc;
        gd::CCMenuItemSpriteExtra* m_pTrashBtn;
        bool m_bApplyOnEsc = false;

        inline void setup() override {};
        void onApply(cocos2d::CCObject*) {
            this->m_pResultFunc(this->m_pInput->getString());

            this->onClose(nullptr);
        }
        void onTrash(cocos2d::CCObject*) {
            this->m_pInput->setString("");

            if (!this->m_bApplyOnEsc)
                this->m_pResultFunc("");

            this->onClose(nullptr);
        }
        void onClose(cocos2d::CCObject*) override
        {
            if (this->m_bApplyOnEsc)
                this->m_pResultFunc(this->m_pInput->getString());

            BrownAlertDelegate::onClose(nullptr);
        }
        bool init(const char* title, const char* inputText, InputResult resFunc, const char* applyText) {
            if (!BrownAlertDelegate::init(250.0f, 140.0f, "GJ_square05.png", title))
                return false;

            auto winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();

            this->m_pInput = InputNode::create(160.0f, inputText, "bigFont.fnt");
            this->m_pInput->setPosition(winSize / 2);
            this->m_pLayer->addChild(this->m_pInput);
            this->m_pResultFunc = resFunc;

            auto button = gd::CCMenuItemSpriteExtra::create(
                gd::ButtonSprite::create(
                    applyText, 0, 0, "goldFont.fnt", "GJ_button_01.png", 0, .8f
                ),
                this,
                (cocos2d::SEL_MenuHandler)&InputPrompt::onApply
            );
            button->setPosition(0.0f, -this->m_pLrSize.height / 2 + 25.0f);

            this->m_pButtonMenu->addChild(button);

            this->m_pTrashBtn = gd::CCMenuItemSpriteExtra::create(
                cocos2d::CCSprite::createWithSpriteFrameName("GJ_resetBtn_001.png"),
                this,
                (cocos2d::SEL_MenuHandler)&InputPrompt::onTrash
            );
            this->m_pTrashBtn->setPosition(
                cocos2d::CCPoint{ 0, 0 } - this->m_pLrSize / 2 + cocos2d::CCPoint{ 25.0f, 25.0f }
            );
            this->m_pTrashBtn->setVisible(false);

            this->m_pButtonMenu->addChild(this->m_pTrashBtn);

            return true;
        }

    public:
        inline static InputPrompt* create(
            const char* title,
            const char* inputText,
            InputResult resFunc,
            const char* applyText = "Apply"
        ) {
            auto pRet = new InputPrompt();

            if (pRet && pRet->init(title, inputText, resFunc, applyText)) {
                pRet->autorelease();
                return pRet;
            }

            CC_SAFE_DELETE(pRet);
            return nullptr;
        }

        inline InputPrompt* setApplyOnEsc(bool on) {
            this->m_bApplyOnEsc = on; return this;
        }

        inline InputPrompt* setTrashButton(bool on) {
            this->m_pTrashBtn->setVisible(on); return this;
        }

        inline InputPrompt* setCallback(InputResult resFunc) {
            this->m_pResultFunc = resFunc; return this;
        }

        inline InputPrompt* setFilter(std::string const& filter) {
            this->m_pInput->getInputNode()->setAllowedChars(filter);
            return this;
        }

        inline InputNode* getInputNode() {
            return m_pInput;
        }
};
#endif