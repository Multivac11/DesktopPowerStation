/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_screen(lv_ui *ui)
{
    //Write codes screen
    ui->screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen, 376, 960);
    lv_obj_set_scrollbar_mode(ui->screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_cont_11
    ui->screen_cont_11 = lv_obj_create(ui->screen);
    lv_obj_set_pos(ui->screen_cont_11, 65, 769);
    lv_obj_set_size(ui->screen_cont_11, 305, 185);
    lv_obj_set_scrollbar_mode(ui->screen_cont_11, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_cont_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_cont_11, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_cont_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_cont_11, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_cont_11, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_cont_11, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_cont_11, 179, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_cont_11, lv_color_hex(0x3b3b3b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_cont_11, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_cont_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_cont_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_cont_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_cont_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_cont_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_bar_1
    ui->screen_bar_1 = lv_bar_create(ui->screen_cont_11);
    lv_obj_set_pos(ui->screen_bar_1, 55, 16);
    lv_obj_set_size(ui->screen_bar_1, 7, 160);
    lv_obj_set_style_anim_duration(ui->screen_bar_1, 1000, 0);
    lv_bar_set_mode(ui->screen_bar_1, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->screen_bar_1, 0, 100);
    lv_bar_set_value(ui->screen_bar_1, 50, LV_ANIM_OFF);

    //Write style for screen_bar_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_1, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_1, lv_color_hex(0xe00022), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_bar_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_bar_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_1, lv_color_hex(0xe00022), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_1, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes screen_bar_6
    ui->screen_bar_6 = lv_bar_create(ui->screen_cont_11);
    lv_obj_set_pos(ui->screen_bar_6, 157, 19);
    lv_obj_set_size(ui->screen_bar_6, 7, 160);
    lv_obj_set_style_anim_duration(ui->screen_bar_6, 1000, 0);
    lv_bar_set_mode(ui->screen_bar_6, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->screen_bar_6, 0, 100);
    lv_bar_set_value(ui->screen_bar_6, 50, LV_ANIM_OFF);

    //Write style for screen_bar_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_6, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_6, lv_color_hex(0xebff00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_6, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_bar_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_bar_6, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_6, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_6, lv_color_hex(0xebff00), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_6, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_6, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes screen_bar_11
    ui->screen_bar_11 = lv_bar_create(ui->screen_cont_11);
    lv_obj_set_pos(ui->screen_bar_11, 108, 13);
    lv_obj_set_size(ui->screen_bar_11, 7, 160);
    lv_obj_set_style_anim_duration(ui->screen_bar_11, 1000, 0);
    lv_bar_set_mode(ui->screen_bar_11, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->screen_bar_11, 0, 100);
    lv_bar_set_value(ui->screen_bar_11, 50, LV_ANIM_OFF);

    //Write style for screen_bar_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_11, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_11, lv_color_hex(0x00a8ff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_11, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_11, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_bar_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_bar_11, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_11, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_11, lv_color_hex(0x00a8ff), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_11, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_11, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes screen_cont_33
    ui->screen_cont_33 = lv_obj_create(ui->screen);
    lv_obj_set_pos(ui->screen_cont_33, 65, 387);
    lv_obj_set_size(ui->screen_cont_33, 305, 185);
    lv_obj_set_scrollbar_mode(ui->screen_cont_33, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_cont_33, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_cont_33, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_cont_33, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_cont_33, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_cont_33, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_cont_33, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_cont_33, 179, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_cont_33, lv_color_hex(0x3b3b3b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_cont_33, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_cont_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_cont_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_cont_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_cont_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_cont_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_bar_3
    ui->screen_bar_3 = lv_bar_create(ui->screen_cont_33);
    lv_obj_set_pos(ui->screen_bar_3, 53, 18);
    lv_obj_set_size(ui->screen_bar_3, 7, 160);
    lv_obj_set_style_anim_duration(ui->screen_bar_3, 1000, 0);
    lv_bar_set_mode(ui->screen_bar_3, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->screen_bar_3, 0, 100);
    lv_bar_set_value(ui->screen_bar_3, 50, LV_ANIM_OFF);

    //Write style for screen_bar_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_3, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_3, lv_color_hex(0xe00022), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_3, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_bar_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_bar_3, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_3, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_3, lv_color_hex(0xe00022), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_3, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_3, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes screen_bar_7
    ui->screen_bar_7 = lv_bar_create(ui->screen_cont_33);
    lv_obj_set_pos(ui->screen_bar_7, 150, 15);
    lv_obj_set_size(ui->screen_bar_7, 7, 160);
    lv_obj_set_style_anim_duration(ui->screen_bar_7, 1000, 0);
    lv_bar_set_mode(ui->screen_bar_7, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->screen_bar_7, 0, 100);
    lv_bar_set_value(ui->screen_bar_7, 50, LV_ANIM_OFF);

    //Write style for screen_bar_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_7, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_7, lv_color_hex(0xebff00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_7, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_bar_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_bar_7, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_7, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_7, lv_color_hex(0xebff00), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_7, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_7, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes screen_bar_12
    ui->screen_bar_12 = lv_bar_create(ui->screen_cont_33);
    lv_obj_set_pos(ui->screen_bar_12, 101, 16);
    lv_obj_set_size(ui->screen_bar_12, 7, 160);
    lv_obj_set_style_anim_duration(ui->screen_bar_12, 1000, 0);
    lv_bar_set_mode(ui->screen_bar_12, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->screen_bar_12, 0, 100);
    lv_bar_set_value(ui->screen_bar_12, 50, LV_ANIM_OFF);

    //Write style for screen_bar_12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_12, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_12, lv_color_hex(0x00a8ff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_12, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_12, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_bar_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_bar_12, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_12, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_12, lv_color_hex(0x00a8ff), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_12, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_12, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes screen_cont_22
    ui->screen_cont_22 = lv_obj_create(ui->screen);
    lv_obj_set_pos(ui->screen_cont_22, 65, 578);
    lv_obj_set_size(ui->screen_cont_22, 305, 185);
    lv_obj_set_scrollbar_mode(ui->screen_cont_22, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_cont_22, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_cont_22, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_cont_22, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_cont_22, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_cont_22, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_cont_22, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_cont_22, 180, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_cont_22, lv_color_hex(0x3b3b3b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_cont_22, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_cont_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_cont_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_cont_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_cont_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_cont_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_bar_2
    ui->screen_bar_2 = lv_bar_create(ui->screen_cont_22);
    lv_obj_set_pos(ui->screen_bar_2, 55, 17);
    lv_obj_set_size(ui->screen_bar_2, 7, 160);
    lv_obj_set_style_anim_duration(ui->screen_bar_2, 1000, 0);
    lv_bar_set_mode(ui->screen_bar_2, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->screen_bar_2, 0, 100);
    lv_bar_set_value(ui->screen_bar_2, 50, LV_ANIM_OFF);

    //Write style for screen_bar_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_2, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_2, lv_color_hex(0xe00022), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_2, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_bar_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_bar_2, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_2, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_2, lv_color_hex(0xe00022), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_2, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_2, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes screen_bar_8
    ui->screen_bar_8 = lv_bar_create(ui->screen_cont_22);
    lv_obj_set_pos(ui->screen_bar_8, 157, 16);
    lv_obj_set_size(ui->screen_bar_8, 7, 160);
    lv_obj_set_style_anim_duration(ui->screen_bar_8, 1000, 0);
    lv_bar_set_mode(ui->screen_bar_8, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->screen_bar_8, 0, 100);
    lv_bar_set_value(ui->screen_bar_8, 50, LV_ANIM_OFF);

    //Write style for screen_bar_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_8, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_8, lv_color_hex(0xebff00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_8, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_8, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_bar_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_bar_8, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_8, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_8, lv_color_hex(0xebff00), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_8, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_8, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes screen_bar_13
    ui->screen_bar_13 = lv_bar_create(ui->screen_cont_22);
    lv_obj_set_pos(ui->screen_bar_13, 105, 14);
    lv_obj_set_size(ui->screen_bar_13, 7, 160);
    lv_obj_set_style_anim_duration(ui->screen_bar_13, 1000, 0);
    lv_bar_set_mode(ui->screen_bar_13, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->screen_bar_13, 0, 100);
    lv_bar_set_value(ui->screen_bar_13, 50, LV_ANIM_OFF);

    //Write style for screen_bar_13, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_13, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_13, lv_color_hex(0x00a8ff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_13, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_13, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_bar_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_bar_13, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_13, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_13, lv_color_hex(0x00a8ff), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_13, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_13, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes screen_cont_44
    ui->screen_cont_44 = lv_obj_create(ui->screen);
    lv_obj_set_pos(ui->screen_cont_44, 65, 196);
    lv_obj_set_size(ui->screen_cont_44, 305, 185);
    lv_obj_set_scrollbar_mode(ui->screen_cont_44, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_cont_44, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_cont_44, 180, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_cont_44, lv_color_hex(0x3b3b3b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_cont_44, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_cont_44, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_cont_44, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_cont_44, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_cont_44, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_cont_44, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_cont_44, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_cont_44, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_cont_44, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_cont_44, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_cont_44, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_bar_4
    ui->screen_bar_4 = lv_bar_create(ui->screen_cont_44);
    lv_obj_set_pos(ui->screen_bar_4, 52, 13);
    lv_obj_set_size(ui->screen_bar_4, 7, 160);
    lv_obj_set_style_anim_duration(ui->screen_bar_4, 1000, 0);
    lv_bar_set_mode(ui->screen_bar_4, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->screen_bar_4, 0, 100);
    lv_bar_set_value(ui->screen_bar_4, 50, LV_ANIM_OFF);

    //Write style for screen_bar_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_4, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_4, lv_color_hex(0xe00022), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_4, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_bar_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_bar_4, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_4, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_4, lv_color_hex(0xe00022), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_4, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_4, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes screen_bar_9
    ui->screen_bar_9 = lv_bar_create(ui->screen_cont_44);
    lv_obj_set_pos(ui->screen_bar_9, 148, 15);
    lv_obj_set_size(ui->screen_bar_9, 7, 160);
    lv_obj_set_style_anim_duration(ui->screen_bar_9, 1000, 0);
    lv_bar_set_mode(ui->screen_bar_9, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->screen_bar_9, 0, 100);
    lv_bar_set_value(ui->screen_bar_9, 50, LV_ANIM_OFF);

    //Write style for screen_bar_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_9, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_9, lv_color_hex(0xebff00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_9, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_9, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_bar_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_bar_9, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_9, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_9, lv_color_hex(0xebff00), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_9, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_9, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes screen_bar_14
    ui->screen_bar_14 = lv_bar_create(ui->screen_cont_44);
    lv_obj_set_pos(ui->screen_bar_14, 99, 12);
    lv_obj_set_size(ui->screen_bar_14, 7, 160);
    lv_obj_set_style_anim_duration(ui->screen_bar_14, 1000, 0);
    lv_bar_set_mode(ui->screen_bar_14, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->screen_bar_14, 0, 100);
    lv_bar_set_value(ui->screen_bar_14, 50, LV_ANIM_OFF);

    //Write style for screen_bar_14, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_14, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_14, lv_color_hex(0x00a8ff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_14, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_14, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_bar_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_bar_14, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_14, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_14, lv_color_hex(0x00a8ff), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_14, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_14, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes screen_cont_55
    ui->screen_cont_55 = lv_obj_create(ui->screen);
    lv_obj_set_pos(ui->screen_cont_55, 65, 5);
    lv_obj_set_size(ui->screen_cont_55, 305, 185);
    lv_obj_set_scrollbar_mode(ui->screen_cont_55, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_cont_55, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->screen_cont_55, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_cont_55, 181, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_cont_55, lv_color_hex(0x3b3b3b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_cont_55, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_cont_55, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_cont_55, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_cont_55, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_cont_55, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_cont_55, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_cont_55, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_cont_55, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_cont_55, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_cont_55, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_bar_5
    ui->screen_bar_5 = lv_bar_create(ui->screen_cont_55);
    lv_obj_set_pos(ui->screen_bar_5, 51, 15);
    lv_obj_set_size(ui->screen_bar_5, 7, 160);
    lv_obj_set_style_anim_duration(ui->screen_bar_5, 1000, 0);
    lv_bar_set_mode(ui->screen_bar_5, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->screen_bar_5, 0, 100);
    lv_bar_set_value(ui->screen_bar_5, 50, LV_ANIM_OFF);

    //Write style for screen_bar_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_5, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_5, lv_color_hex(0xe00022), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_5, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_bar_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_bar_5, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_5, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_5, lv_color_hex(0xe00022), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_5, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_5, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes screen_bar_10
    ui->screen_bar_10 = lv_bar_create(ui->screen_cont_55);
    lv_obj_set_pos(ui->screen_bar_10, 144, 21);
    lv_obj_set_size(ui->screen_bar_10, 7, 160);
    lv_obj_set_style_anim_duration(ui->screen_bar_10, 1000, 0);
    lv_bar_set_mode(ui->screen_bar_10, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->screen_bar_10, 0, 100);
    lv_bar_set_value(ui->screen_bar_10, 50, LV_ANIM_OFF);

    //Write style for screen_bar_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_10, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_10, lv_color_hex(0xebff00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_10, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_10, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_bar_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_bar_10, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_10, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_10, lv_color_hex(0xebff00), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_10, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_10, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes screen_bar_15
    ui->screen_bar_15 = lv_bar_create(ui->screen_cont_55);
    lv_obj_set_pos(ui->screen_bar_15, 97, 15);
    lv_obj_set_size(ui->screen_bar_15, 7, 160);
    lv_obj_set_style_anim_duration(ui->screen_bar_15, 1000, 0);
    lv_bar_set_mode(ui->screen_bar_15, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->screen_bar_15, 0, 100);
    lv_bar_set_value(ui->screen_bar_15, 50, LV_ANIM_OFF);

    //Write style for screen_bar_15, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_15, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_15, lv_color_hex(0x00a8ff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_15, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_15, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_bar_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_bar_15, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_15, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_15, lv_color_hex(0x00a8ff), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_15, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_15, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes screen_label_1
    ui->screen_label_1 = lv_label_create(ui->screen);
    lv_obj_set_pos(ui->screen_label_1, 272, 826);
    lv_obj_set_size(ui->screen_label_1, 66, 28);
    lv_label_set_text(ui->screen_label_1, "Label");
    lv_label_set_long_mode(ui->screen_label_1, LV_LABEL_LONG_WRAP);

    //Write style for screen_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_1, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen);

}
