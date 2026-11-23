/**
 * @file     font_awesome.cpp
 * @brief    Font Awesome 6.5.2 免费图标字体组件实现 — C++ class
 *
 * 功能：维护图标名 -> UTF-8 编码符号表，提供按名查询
 * 修改：2026-11-21 由 font_awesome.c 重构为 FontAwesome 静态类
 */
#include "font_awesome.h"

#include <string.h>

/* Font Awesome 6.5.2 免费图标 UTF-8 编码表（与 font_awesome.h 常量一一对应） */
const FontAwesomeSymbol FontAwesome::SYMBOLS[] = {
    {"neutral", "\xEF\x98\x90"},              /* face-meh */
    {"home", "\xEF\x80\x95"},
    {"gear", "\xEF\x80\x93"},
    {"cog", "\xEF\x80\x93"},
    {"user", "\xEF\x80\x87"},
    {"search", "\xEF\x80\x82"},
    {"play", "\xEF\x81\x8B"},
    {"pause", "\xEF\x81\x8C"},
    {"stop", "\xEF\x81\x8D"},
    {"forward", "\xEF\x81\x8E"},
    {"backward", "\xEF\x81\x8A"},
    {"step-forward", "\xEF\x81\x91"},
    {"step-backward", "\xEF\x81\x88"},
    {"fast-forward", "\xEF\x81\x90"},
    {"fast-backward", "\xEF\x81\x89"},
    {"volume-up", "\xEF\x80\xA8"},
    {"volume-down", "\xEF\x80\xA7"},
    {"volume-off", "\xEF\x80\xA6"},
    {"volume-mute", "\xEF\x9A\xA9"},
    {"music", "\xEF\x80\x81"},
    {"heart", "\xEF\x80\x84"},
    {"star", "\xEF\x80\x85"},
    {"check", "\xEF\x80\x8C"},
    {"xmark", "\xEF\x80\x8D"},
    {"plus", "\x2B"},
    {"minus", "\xEF\x81\xA8"},
    {"arrow-up", "\xEF\x81\xB6"},
    {"arrow-down", "\xEF\x81\xB8"},
    {"arrow-left", "\xEF\x81\xA0"},
    {"arrow-right", "\xEF\x81\xA1"},
    {"chevron-up", "\xEF\x81\xB7"},
    {"chevron-down", "\xEF\x81\xB8"},
    {"chevron-left", "\xEF\x81\x93"},
    {"chevron-right", "\xEF\x81\x94"},
    {"angle-up", "\xEF\x84\x86"},
    {"angle-down", "\xEF\x84\x87"},
    {"angle-left", "\xEF\x84\x84"},
    {"angle-right", "\xEF\x84\x85"},
    {"circle-up", "\xEF\x8D\x9B"},
    {"circle-down", "\xEF\x8D\x98"},
    {"circle-left", "\xEF\x8D\x99"},
    {"circle-right", "\xEF\x8D\x9A"},
    {"square-up", "\xEF\x8C\x93"},
    {"square-down", "\xEF\x8C\x90"},
    {"square-left", "\xEF\x8C\x91"},
    {"square-right", "\xEF\x8C\x92"},
    {"up-long", "\xEF\x8C\x8C"},
    {"down-long", "\xEF\x8C\x89"},
    {"left-long", "\xEF\x8C\x8A"},
    {"right-long", "\xEF\x8C\x8B"},
    {"rotate-left", "\xEF\x8B\xAA"},
    {"rotate-right", "\xEF\x8B\xB1"},
    {"maximize", "\xEF\x8C\x9E"},
    {"minimize", "\xEF\x9E\x8C"},
    {"clock", "\xEF\x80\x97"},
    {"calendar", "\xEF\x84\xB3"},
    {"camera", "\xEF\x80\xB0"},
    {"video", "\xEF\x80\xBD"},
    {"image", "\xEF\x80\xBE"},
    {"folder", "\xEF\x81\xBB"},
    {"folder-open", "\xEF\x81\xBC"},
    {"file", "\xEF\x85\x9B"},
    {"file-lines", "\xEF\x85\x9C"},
    {"trash-can", "\xEF\x8B\xAD"},
    {"pen", "\xEF\x8C\x84"},
    {"pencil", "\xEF\x8C\x83"},
    {"save", "\xEF\x83\x87"},
    {"download", "\xEF\x80\x99"},
    {"upload", "\xEF\x82\x93"},
    {"cloud-arrow-up", "\xEF\x83\xAE"},
    {"cloud-arrow-down", "\xEF\x83\xAD"},
    {"wifi", "\xEF\x87\xAB"},
    {"bluetooth", "\xEF\x8A\x93"},
    {"bluetooth-b", "\xEF\x8A\x94"},
    {"battery-full", "\xEF\x89\x80"},
    {"battery-half", "\xEF\x89\x82"},
    {"battery-quarter", "\xEF\x89\x83"},
    {"battery-empty", "\xEF\x89\x84"},
    {"power-off", "\xEF\x80\x91"},
    {"signal", "\xEF\x80\x92"},
    {"bell", "\xEF\x83\xB3"},
    {"envelope", "\xEF\x83\xA0"},
    {"phone", "\xEF\x82\x95"},
    {"location-dot", "\xEF\x8F\x85"},
    {"map", "\xEF\x89\xB9"},
    {"cart-shopping", "\xEF\x81\xBA"},
    {"credit-card", "\xEF\x82\x9D"},
    {"money-bill", "\xEF\x83\x96"},
    {"chart-simple", "\xEF\x91\x87"},
    {"chart-line", "\xEF\x88\x81"},
    {"chart-bar", "\xEF\x82\x80"},
    {"chart-pie", "\xEF\x88\x80"},
    {"table", "\xEF\x83\x8E"},
    {"list", "\xEF\x80\xBA"},
    {"bars", "\xEF\x83\x89"},
    {"ellipsis", "\xEF\x85\x81"},
    {"sliders", "\xEF\x87\x9E"},
    {"lock", "\xEF\x80\xA3"},
    {"lock-open", "\xEF\x8F\x81"},
    {"key", "\xEF\x82\x84"},
    {"shield", "\xEF\x84\xB2"},
    {"eye", "\xEF\x81\xAE"},
    {"eye-slash", "\xEF\x81\xB0"},
};

const size_t FontAwesome::SYMBOL_COUNT = sizeof(FontAwesome::SYMBOLS) / sizeof(FontAwesome::SYMBOLS[0]);

const char *FontAwesome::getUtf8(const char *name)
{
    if (name == NULL) {
        return "";
    }
    for (size_t i = 0; i < SYMBOL_COUNT; i++) {
        if (strcmp(SYMBOLS[i].name, name) == 0) {
            return SYMBOLS[i].utf8;
        }
    }
    return "";
}
