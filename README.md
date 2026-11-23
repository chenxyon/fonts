# Fonts 组件 v1.0（C++ class 版）

## 简介

Fonts 组件提供 ESP32 嵌入式开发所需的字体资源，包含中文基础字体、Font Awesome 图标字体，以及 cbin 字体/图片的运行时动态解析能力。所有字体均已转换为 LVGL 可用的格式，可直接用于显示驱动组件。

## 功能特性

- **中文字体**：常用中文基础字库（14px，`font_puhui_basic_14_1`）
- **图标字体**：Font Awesome 6.5.2 免费图标库（14px，`font_awesome_14_1`），100 个常用图标
- **图标查询**：`FontAwesome` 静态类，支持按名查询与常量直用两种方式
- **cbin 动态解析**：`CbinFont` 静态类，运行时从 Flash/PSRAM/文件系统加载 cbin 字体与图片，避免把大量字库编进固件
- **LVGL 兼容**：所有字体均为 LVGL 9 font 格式

## 文件结构

```
fonts/
├── cbin_font.h              # cbin 字体/图片解析类声明
├── cbin_font.cpp            # cbin 字体/图片解析实现
├── font_awesome.h           # FontAwesome 图标类声明（含图标常量）
├── font_awesome.cpp         # 图标符号表与按名查询实现
├── font_awesome_14_1.c      # Font Awesome 14px 字体数据（导出 font_awesome_14_1）
├── font_puhui_basic_14_1.c  # 中文基础 14px 字体数据（导出 font_puhui_basic_14_1）
├── library.json             # PlatformIO 库描述
└── README.md
```

## 支持的字体

| 字体名称 | 尺寸 | 字符集 | 文件 | 导出符号 |
|----------|------|--------|------|----------|
| Font Awesome | 14px | 100 图标 | font_awesome_14_1.c | `font_awesome_14_1` |
| 中文基础字体 | 14px | 常用中文 | font_puhui_basic_14_1.c | `font_puhui_basic_14_1` |

## API 参考

### FontAwesome 图标类

```cpp
#include "font_awesome.h"

/* 方式一：常量直用 */
lv_label_set_text(label, FontAwesome::WIFI);

/* 方式二：按名查询（找不到返回空串 ""） */
const char *icon = FontAwesome::getUtf8("play");

/* 符号表遍历（如做图标选择器） */
for (size_t i = 0; i < FontAwesome::SYMBOL_COUNT; i++) {
    printf("%s -> %s\n", FontAwesome::SYMBOLS[i].name, FontAwesome::SYMBOLS[i].utf8);
}
```

常用常量：`HOME / GEAR / USER / SEARCH / PLAY / PAUSE / STOP / VOLUME_UP /
VOLUME_DOWN / VOLUME_MUTE / MUSIC / HEART / STAR / CHECK / XMARK /
ARROW_UP / ARROW_DOWN / ARROW_LEFT / ARROW_RIGHT / CHEVRON_* / ANGLE_* /
CLOCK / CALENDAR / CAMERA / IMAGE / FOLDER / FILE / SAVE / DOWNLOAD / UPLOAD /
WIFI / BLUETOOTH / BATTERY_FULL / BATTERY_HALF / BATTERY_EMPTY / POWER_OFF /
SIGNAL / BELL / LOCK / LOCK_OPEN / KEY / SHIELD / EYE / EYE_SLASH / NEUTRAL` 等，
完整列表见 `font_awesome.h`。

### CbinFont 动态字体解析

```cpp
#include "cbin_font.h"

/* 从文件/Flash 读入 cbin 字体二进制（缓冲须用 lv_malloc 分配） */
uint8_t *bin = (uint8_t *)lv_malloc(bin_size);
/* ... 填充 bin ... */

lv_font_t *font = CbinFont::createFont(bin);   /* 字体接管 bin 缓冲 */
if (font != NULL) {
    lv_obj_set_style_text_font(label, font, 0);
    /* ... 使用完毕 ... */
    CbinFont::deleteFont(font);                /* 释放字体并归还 bin 缓冲 */
}

/* cbin 图片同理（图片不接管 bin 缓冲，需自行释放） */
lv_img_dsc_t *img = CbinFont::createImgDsc(bin);
/* ... */
CbinFont::deleteImgDsc(img);
```

## 在 LVGL 中使用图标

```cpp
#include "font_awesome.h"

LV_FONT_DECLARE(font_awesome_14_1);

lv_obj_t *wifi_label = lv_label_create(lv_scr_act());
lv_obj_set_style_text_font(wifi_label, &font_awesome_14_1, 0);
lv_label_set_text(wifi_label, FontAwesome::WIFI);
lv_obj_align(wifi_label, LV_ALIGN_TOP_RIGHT, 0, 0);
```

## 注意事项

- **内存占用**：中文字体数据较大，建议仅包含常用字符以减小固件体积
- **字体大小**：当前版本仅支持 14px 尺寸，如需其他尺寸需重新生成字体文件
- **cbin 缓冲归属**：`createFont` 成功后字体接管传入的 bin 缓冲，`deleteFont` 一并释放；
  因此 bin 缓冲必须用 `lv_malloc` 分配。`createImgDsc` 不接管缓冲
- **图标编码**：Font Awesome 图标使用 UTF-8 编码，源码文件须保存为 UTF-8 格式

## 版本历史

| 版本 | 日期 | 说明 |
|------|------|------|
| v1.0.0 | 2026-11-21 | 重构为 C++ class（CbinFont / FontAwesome）；修复 cbin_font malloc 与 lv_free 混用、deleteFont 空指针崩溃问题 |
| v1.0.0 | 2026-06-29 | 初始版本，包含 Font Awesome 14px 和中文基础字体 14px |

## 许可证

MIT License
