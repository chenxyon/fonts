/**
 * @file     font_awesome.h
 * @brief    Font Awesome 6.5.2 免费图标字体组件 — C++ class
 *
 * 功能：提供 Font Awesome 6.5.2 免费图标字体的 UTF-8 编码查询，
 *       配合 lv_font_montserrat + Font Awesome 符号字体使用，
 *       可在 LVGL 标签中直接显示图标字符。
 * 修改：2026-11-21 由 C API（font_awesome_get_utf8 + FONT_AWESOME_* 宏）
 *       重构为 FontAwesome 静态类；图标宏改为类静态常量，符号表改为结构化数组
 *
 * 用法：
 *   const char *icon = FontAwesome::getUtf8("play");   // 按名查询
 *   const char *icon = FontAwesome::PLAY;              // 直接用常量
 *   lv_label_set_text(label, icon);
 *
 * 注意：需先生成包含所需符号的 Font Awesome 字体（14px 版本见
 *       font_awesome_14_1.c，导出符号 font_awesome_14_1）
 */
#ifndef FONT_AWESOME_H
#define FONT_AWESOME_H

#include <stddef.h>

/**
 * 图标符号表条目
 */
struct FontAwesomeSymbol {
    const char *name; /* 图标名，如 "play" */
    const char *utf8; /* UTF-8 编码，如 "\xEF\x81\x8B" */
};

/**
 * Font Awesome 图标查询类（纯静态工具类）
 */
class FontAwesome {
public:
    /* ---- 符号表 ---- */
    static const FontAwesomeSymbol SYMBOLS[]; /*!< 全部图标符号（见 font_awesome.cpp） */
    static const size_t SYMBOL_COUNT;         /*!< 符号数量（= 数组长度） */

    /**
     * @brief  按名称查询图标的 UTF-8 编码
     *
     * 功能：线性查找符号表，找到返回 UTF-8 字符串，找不到返回空串 ""
     */
    static const char *getUtf8(const char *name);

    /* ---- 常用图标常量（与符号表内容一致，免查表直接使用） ---- */
    static constexpr const char *NEUTRAL              = "\xEF\x98\x90"; /* face-meh */
    static constexpr const char *HOME                 = "\xEF\x80\x95";
    static constexpr const char *GEAR                 = "\xEF\x80\x93";
    static constexpr const char *COG                  = "\xEF\x80\x93";
    static constexpr const char *USER                 = "\xEF\x80\x87";
    static constexpr const char *SEARCH               = "\xEF\x80\x82";
    static constexpr const char *PLAY                 = "\xEF\x81\x8B";
    static constexpr const char *PAUSE                = "\xEF\x81\x8C";
    static constexpr const char *STOP                 = "\xEF\x81\x8D";
    static constexpr const char *FORWARD              = "\xEF\x81\x8E";
    static constexpr const char *BACKWARD             = "\xEF\x81\x8A";
    static constexpr const char *STEP_FORWARD         = "\xEF\x81\x91";
    static constexpr const char *STEP_BACKWARD        = "\xEF\x81\x88";
    static constexpr const char *FAST_FORWARD         = "\xEF\x81\x90";
    static constexpr const char *FAST_BACKWARD        = "\xEF\x81\x89";
    static constexpr const char *VOLUME_UP            = "\xEF\x80\xA8";
    static constexpr const char *VOLUME_DOWN          = "\xEF\x80\xA7";
    static constexpr const char *VOLUME_OFF           = "\xEF\x80\xA6";
    static constexpr const char *VOLUME_MUTE          = "\xEF\x9A\xA9";
    static constexpr const char *MUSIC                = "\xEF\x80\x81";
    static constexpr const char *HEART                = "\xEF\x80\x84";
    static constexpr const char *STAR                 = "\xEF\x80\x85";
    static constexpr const char *CHECK                = "\xEF\x80\x8C";
    static constexpr const char *XMARK                = "\xEF\x80\x8D";
    static constexpr const char *PLUS                 = "\x2B";
    static constexpr const char *MINUS                = "\xEF\x81\xA8";
    static constexpr const char *ARROW_UP             = "\xEF\x81\xB6";
    static constexpr const char *ARROW_DOWN           = "\xEF\x81\xB8";
    static constexpr const char *ARROW_LEFT           = "\xEF\x81\xA0";
    static constexpr const char *ARROW_RIGHT          = "\xEF\x81\xA1";
    static constexpr const char *CHEVRON_UP           = "\xEF\x81\xB7";
    static constexpr const char *CHEVRON_DOWN         = "\xEF\x81\xB8";
    static constexpr const char *CHEVRON_LEFT         = "\xEF\x81\x93";
    static constexpr const char *CHEVRON_RIGHT        = "\xEF\x81\x94";
    static constexpr const char *ANGLE_UP             = "\xEF\x84\x86";
    static constexpr const char *ANGLE_DOWN           = "\xEF\x84\x87";
    static constexpr const char *ANGLE_LEFT           = "\xEF\x84\x84";
    static constexpr const char *ANGLE_RIGHT          = "\xEF\x84\x85";
    static constexpr const char *CIRCLE_UP            = "\xEF\x8D\x9B";
    static constexpr const char *CIRCLE_DOWN          = "\xEF\x8D\x98";
    static constexpr const char *CIRCLE_LEFT          = "\xEF\x8D\x99";
    static constexpr const char *CIRCLE_RIGHT         = "\xEF\x8D\x9A";
    static constexpr const char *SQUARE_UP            = "\xEF\x8C\x93";
    static constexpr const char *SQUARE_DOWN          = "\xEF\x8C\x90";
    static constexpr const char *SQUARE_LEFT          = "\xEF\x8C\x91";
    static constexpr const char *SQUARE_RIGHT         = "\xEF\x8C\x92";
    static constexpr const char *UP_LONG              = "\xEF\x8C\x8C";
    static constexpr const char *DOWN_LONG            = "\xEF\x8C\x89";
    static constexpr const char *LEFT_LONG            = "\xEF\x8C\x8A";
    static constexpr const char *RIGHT_LONG           = "\xEF\x8C\x8B";
    static constexpr const char *ROTATE_LEFT          = "\xEF\x8B\xAA";
    static constexpr const char *ROTATE_RIGHT         = "\xEF\x8B\xB1";
    static constexpr const char *MAXIMIZE             = "\xEF\x8C\x9E";
    static constexpr const char *MINIMIZE             = "\xEF\x9E\x8C";
    static constexpr const char *CLOCK                = "\xEF\x80\x97";
    static constexpr const char *CALENDAR             = "\xEF\x84\xB3";
    static constexpr const char *CAMERA               = "\xEF\x80\xB0";
    static constexpr const char *VIDEO                = "\xEF\x80\xBD";
    static constexpr const char *IMAGE                = "\xEF\x80\xBE";
    static constexpr const char *FOLDER               = "\xEF\x81\xBB";
    static constexpr const char *FOLDER_OPEN          = "\xEF\x81\xBC";
    static constexpr const char *FILE                 = "\xEF\x85\x9B";
    static constexpr const char *FILE_LINES           = "\xEF\x85\x9C";
    static constexpr const char *TRASH_CAN            = "\xEF\x8B\xAD";
    static constexpr const char *PEN                  = "\xEF\x8C\x84";
    static constexpr const char *PENCIL               = "\xEF\x8C\x83";
    static constexpr const char *SAVE                 = "\xEF\x83\x87";
    static constexpr const char *DOWNLOAD             = "\xEF\x80\x99";
    static constexpr const char *UPLOAD               = "\xEF\x82\x93";
    static constexpr const char *CLOUD_ARROW_UP       = "\xEF\x83\xAE";
    static constexpr const char *CLOUD_ARROW_DOWN     = "\xEF\x83\xAD";
    static constexpr const char *WIFI                 = "\xEF\x87\xAB";
    static constexpr const char *BLUETOOTH            = "\xEF\x8A\x93";
    static constexpr const char *BLUETOOTH_B          = "\xEF\x8A\x94";
    static constexpr const char *BATTERY_FULL         = "\xEF\x89\x80";
    static constexpr const char *BATTERY_HALF         = "\xEF\x89\x82";
    static constexpr const char *BATTERY_QUARTER      = "\xEF\x89\x83";
    static constexpr const char *BATTERY_EMPTY        = "\xEF\x89\x84";
    static constexpr const char *POWER_OFF            = "\xEF\x80\x91";
    static constexpr const char *SIGNAL               = "\xEF\x80\x92";
    static constexpr const char *BELL                 = "\xEF\x83\xB3";
    static constexpr const char *ENVELOPE             = "\xEF\x83\xA0";
    static constexpr const char *PHONE                = "\xEF\x82\x95";
    static constexpr const char *LOCATION_DOT         = "\xEF\x8F\x85";
    static constexpr const char *MAP                  = "\xEF\x89\xB9";
    static constexpr const char *CART_SHOPPING        = "\xEF\x81\xBA";
    static constexpr const char *CREDIT_CARD          = "\xEF\x82\x9D";
    static constexpr const char *MONEY_BILL           = "\xEF\x83\x96";
    static constexpr const char *CHART_SIMPLE         = "\xEF\x91\x87";
    static constexpr const char *CHART_LINE           = "\xEF\x88\x81";
    static constexpr const char *CHART_BAR            = "\xEF\x82\x80";
    static constexpr const char *CHART_PIE            = "\xEF\x88\x80";
    static constexpr const char *TABLE                = "\xEF\x83\x8E";
    static constexpr const char *LIST                 = "\xEF\x80\xBA";
    static constexpr const char *BARS                 = "\xEF\x83\x89";
    static constexpr const char *ELLIPSIS             = "\xEF\x85\x81";
    static constexpr const char *SLIDERS              = "\xEF\x87\x9E";
    static constexpr const char *LOCK                 = "\xEF\x80\xA3";
    static constexpr const char *LOCK_OPEN            = "\xEF\x8F\x81";
    static constexpr const char *KEY                  = "\xEF\x82\x84";
    static constexpr const char *SHIELD               = "\xEF\x84\xB2";
    static constexpr const char *EYE                  = "\xEF\x81\xAE";
    static constexpr const char *EYE_SLASH            = "\xEF\x81\xB0";
};

#endif /* FONT_AWESOME_H */
