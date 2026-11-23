/**
 * @file     cbin_font.h
 * @brief    LVGL cbin 字体/图片解析组件 — C++ class
 *
 * 功能：解析 lvgl_font_convert / cbin 工具生成的二进制字体文件，
 *       重建为可用的 lv_font_t；同时支持 cbin 图片（lv_img_dsc_t）解析。
 *       字体二进制可放在 Flash/PSRAM/文件系统中，运行时动态加载，
 *       避免把大量字库编进固件。
 * 修改：2026-11-21 由 C API（cbin_font_create/delete）重构为 CbinFont 静态类；
 *       修复原实现中 malloc 分配却用 lv_free 释放的混用问题（统一改 lv_malloc）
 */
#ifndef CBIN_FONT_H
#define CBIN_FONT_H

#include <stdint.h>

#include "lvgl.h"

/**
 * cbin 字体/图片解析类（纯静态工具类，无实例状态）
 */
class CbinFont {
public:
    /**
     * @brief  从 cbin 二进制创建图片描述符
     *
     * 功能：cbin 图片文件开头即 lv_img_dsc_t 结构，直接复制后
     *       把 data 指针重定位到二进制实际数据区
     *
     * @param binAddr cbin 图片二进制起始地址
     * @return 成功返回图片描述符（用 deleteImgDsc 释放）；失败返回 nullptr
     */
    static lv_img_dsc_t *createImgDsc(uint8_t *binAddr);

    /** 释放 createImgDsc 创建的图片描述符（可传 nullptr） */
    static void deleteImgDsc(lv_img_dsc_t *imgDsc);

    /**
     * @brief  从 cbin 二进制创建字体
     *
     * 功能：重建 lv_font_t 及其内部 fmt_txt 描述、cmap 表、kern 表，
     *       并把所有相对偏移指针重定位到二进制实际地址
     *
     * @param binAddr cbin 字体二进制起始地址
     * @return 成功返回字体（用 deleteFont 释放）；失败返回 nullptr
     */
    static lv_font_t *createFont(uint8_t *binAddr);

    /** 释放 createFont 创建的字体及其内部分配（可传 nullptr） */
    static void deleteFont(lv_font_t *font);
};

#endif /* CBIN_FONT_H */
