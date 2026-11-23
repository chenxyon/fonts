/**
 * @file     cbin_font.cpp
 * @brief    LVGL cbin 字体/图片解析组件实现 — C++ class
 *
 * 功能：解析 lvgl_font_convert / cbin 工具生成的二进制字体文件，
 *       重建为可用的 lv_font_t；同时支持 cbin 图片（lv_img_dsc_t）解析。
 * 修改：2026-11-21 由 C API（cbin_font_create/delete）重构为 CbinFont 静态类；
 *       修复原实现中 malloc 分配却用 lv_free 释放的混用问题（统一改 lv_malloc），
 *       并为 deleteFont 增加 NULL 防护（无字距/无 cmap 字体不再崩溃）
 */
#include "cbin_font.h"

#include <string.h>

#include "lvgl.h"

/**
 * @brief  指针偏移重定位辅助
 *
 * 功能：cbin 二进制内的指针实际是相对偏移，加载后需加上基地址才是有效指针
 */
static inline void addrAdd(void **ptr, uintptr_t base)
{
    if (*ptr != NULL) {
        *ptr = (void *)((uintptr_t)*ptr + base);
    }
}

/* ==================== 图片解析 ==================== */

lv_img_dsc_t *CbinFont::createImgDsc(uint8_t *binAddr)
{
    if (binAddr == NULL) {
        return NULL;
    }

    /* cbin 图片文件开头即 lv_img_dsc_t 结构，直接复制 */
    lv_img_dsc_t *imgDsc = (lv_img_dsc_t *)lv_malloc(sizeof(lv_img_dsc_t));
    if (imgDsc == NULL) {
        return NULL;
    }
    memcpy(imgDsc, binAddr, sizeof(lv_img_dsc_t));

    /* data 指针为相对偏移，重定位到二进制实际数据区 */
    uint8_t *binBase = binAddr + sizeof(lv_img_dsc_t);
    imgDsc->data = binBase + (uintptr_t)imgDsc->data;

    return imgDsc;
}

void CbinFont::deleteImgDsc(lv_img_dsc_t *imgDsc)
{
    if (imgDsc != NULL) {
        lv_free(imgDsc);
    }
}

/* ==================== 字体解析 ==================== */

lv_font_t *CbinFont::createFont(uint8_t *binAddr)
{
    if (binAddr == NULL) {
        return NULL;
    }

    /* 二进制开头即 lv_font_t 结构 */
    lv_font_t *font = (lv_font_t *)binAddr;

    /* 重定位 fmt_txt 描述符（dsc 字段存的是相对偏移） */
    uintptr_t binBase = (uintptr_t)binAddr;
    lv_font_fmt_txt_dsc_t *dsc = (lv_font_fmt_txt_dsc_t *)(binBase + (uintptr_t)font->dsc);
    font->dsc = dsc;

    /* 重定位位图与字形描述表（偏移相对 dsc 位置） */
    addrAdd((void **)&dsc->glyph_bitmap, (uintptr_t)dsc);
    addrAdd((void **)&dsc->glyph_dsc, (uintptr_t)dsc);

    /* cmap 表：cmaps 字段为相对偏移，表内存需复制出来以便单独释放 */
    if (dsc->cmap_num > 0 && dsc->cmaps != NULL) {
        const lv_font_fmt_txt_cmap_t *cmapsAddr =
            (const lv_font_fmt_txt_cmap_t *)((uintptr_t)dsc + (uintptr_t)dsc->cmaps);
        lv_font_fmt_txt_cmap_t *cmaps =
            (lv_font_fmt_txt_cmap_t *)lv_malloc(sizeof(lv_font_fmt_txt_cmap_t) * dsc->cmap_num);
        if (cmaps == NULL) {
            return NULL;
        }
        memcpy(cmaps, cmapsAddr, sizeof(lv_font_fmt_txt_cmap_t) * dsc->cmap_num);

        /* cmap 内部指针均为相对 cmap 表位置的偏移，逐个重定位 */
        for (int i = 0; i < dsc->cmap_num; i++) {
            addrAdd((void **)&cmaps[i].glyph_ids, (uintptr_t)cmapsAddr);
            addrAdd((void **)&cmaps[i].unicode_list, (uintptr_t)cmapsAddr);
        }
        dsc->cmaps = cmaps;
    } else {
        dsc->cmaps = NULL;
    }

    /* 字距表：仅当使用 kern_dsc 时重定位（kern_classes 模式无需处理） */
    if (!dsc->kern_classes && dsc->kern_dsc != NULL) {
        addrAdd((void **)&dsc->kern_dsc, binBase);
    }

    /* 挂接 fmt_txt 标准回调 */
    font->get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt;
    font->get_glyph_bitmap = lv_font_get_bitmap_fmt_txt;

    return font;
}

void CbinFont::deleteFont(lv_font_t *font)
{
    if (font == NULL) {
        return;
    }

    lv_font_fmt_txt_dsc_t *dsc = (lv_font_fmt_txt_dsc_t *)font->dsc;
    if (dsc != NULL) {
        /* cmap 表由 createFont 用 lv_malloc 复制而来，需单独释放 */
        if (dsc->cmaps != NULL) {
            lv_free((void *)dsc->cmaps);
        }
        /* kern_dsc 可能为空（等宽字体），加防护避免 lv_free(NULL) */
        if (!dsc->kern_classes && dsc->kern_dsc != NULL) {
            lv_free((void *)dsc->kern_dsc);
        }
    }
    lv_free(font);
}

#include "fonts_version.h"
#include "version_manager.h"
COMPONENT_VERSION_REGISTER(fonts, FONTS_VERSION_STRING)
