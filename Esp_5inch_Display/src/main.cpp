#include <Arduino.h>
#include <stdio.h>
#include <string.h>
#include <esp32_smartdisplay.h>
#include "lvgl.h"
#include <src/extra/libs/qrcode/lv_qrcode.h>

//Test Git
static lv_obj_t * meter;

void lv_background(void)
{
  static lv_style_t style;
  lv_style_init(&style);

    /*Set a background color and a radius*/
  lv_style_set_radius(&style, 5);
  lv_style_set_bg_opa(&style, LV_OPA_COVER);
  lv_style_set_bg_color(&style, lv_color_white());

    /*Add a shadow*/
  lv_style_set_shadow_width(&style, 55);
  lv_style_set_shadow_color(&style, lv_palette_main(LV_PALETTE_BLUE));
    //    lv_style_set_shadow_ofs_x(&style, 10);
    //    lv_style_set_shadow_ofs_y(&style, 20);

    /*Create an object with the new style*/
  lv_obj_t * obj = lv_obj_create(lv_scr_act());
  lv_obj_add_style(obj, &style, 0);
  lv_obj_center(obj);
  lv_obj_set_size(obj, 470, 790);
}

void lv_soil_temp_icon(int pos_x, int pos_y) {

  lv_obj_t * img;
  
  LV_IMG_DECLARE(soil_temp_icon);
  img = lv_img_create(lv_scr_act());
  lv_img_set_src(img, &soil_temp_icon);

  lv_obj_align(img, LV_ALIGN_TOP_LEFT, pos_x, pos_y);
  lv_obj_set_size(img, 100, 100);
}

void lv_soil_humi_icon(int pos_x, int pos_y) {

  lv_obj_t * img;
  
  LV_IMG_DECLARE(soil_humi_icon);
  img = lv_img_create(lv_scr_act());
  lv_img_set_src(img, &soil_humi_icon);

  lv_obj_align(img, LV_ALIGN_TOP_LEFT, pos_x, pos_y);
  lv_obj_set_size(img, 100, 100);
}

void lv_air_temp_icon(int pos_x, int pos_y) {

  lv_obj_t * img;
  
  LV_IMG_DECLARE(air_temp_icon);
  img = lv_img_create(lv_scr_act());
  
  lv_img_set_src(img, &air_temp_icon);
  lv_obj_align(img, LV_ALIGN_TOP_LEFT, pos_x, pos_y);
  lv_obj_set_size(img, 100, 100);
}

void lv_air_humi_icon(int pos_x, int pos_y) {

  lv_obj_t * img;
  
  LV_IMG_DECLARE(air_humi_icon);
  img = lv_img_create(lv_scr_act());
  lv_img_set_src(img, &air_humi_icon);

  lv_obj_align(img, LV_ALIGN_TOP_LEFT, pos_x, pos_y);
  lv_obj_set_size(img, 100, 100);
}

void lv_n_icon(int pos_x, int pos_y) {

  lv_obj_t * img;
  
  LV_IMG_DECLARE(n_icon);
  img = lv_img_create(lv_scr_act());
  lv_img_set_src(img, &n_icon);

  lv_obj_align(img, LV_ALIGN_TOP_LEFT, pos_x, pos_y);
  lv_obj_set_size(img, 100, 100);
}

void lv_p_icon(int pos_x, int pos_y) {

  lv_obj_t * img;
  
  LV_IMG_DECLARE(p_icon);
  img = lv_img_create(lv_scr_act());
  lv_img_set_src(img, &p_icon);

  lv_obj_align(img, LV_ALIGN_TOP_LEFT, pos_x, pos_y);
  lv_obj_set_size(img, 100, 100);
}

void lv_k_icon(int pos_x, int pos_y) {

  lv_obj_t * img;
  
  LV_IMG_DECLARE(k_icon);
  img = lv_img_create(lv_scr_act());
  lv_img_set_src(img, &k_icon);

  lv_obj_align(img, LV_ALIGN_TOP_LEFT, pos_x, pos_y);
  lv_obj_set_size(img, 100, 100);
}

void lv_ec_icon(int pos_x, int pos_y) {

  lv_obj_t * img;
  
  LV_IMG_DECLARE(ec_icon);
  img = lv_img_create(lv_scr_act());
  lv_img_set_src(img, &ec_icon);

  lv_obj_align(img, LV_ALIGN_TOP_LEFT, pos_x, pos_y);
  lv_obj_set_size(img, 100, 100);
}

void lv_ph_icon(int pos_x, int pos_y) {

  lv_obj_t * img;
  
  LV_IMG_DECLARE(ph_icon);
  img = lv_img_create(lv_scr_act());
  lv_img_set_src(img, &ph_icon);

  lv_obj_align(img, LV_ALIGN_TOP_LEFT, pos_x, pos_y);
  lv_obj_set_size(img, 100, 100);
}

void lv_bar (float value, int pos_x, int pos_y){
  static lv_style_t style_indic;
  lv_style_init(&style_indic);
  lv_style_set_bg_opa(&style_indic, LV_OPA_COVER);
  lv_style_set_bg_color(&style_indic, lv_palette_main(LV_PALETTE_BLUE));
  lv_style_set_bg_grad_color(&style_indic, lv_palette_main(LV_PALETTE_RED));
  lv_style_set_bg_grad_dir(&style_indic, LV_GRAD_DIR_HOR);

  lv_obj_t * bar = lv_bar_create(lv_scr_act());
  lv_obj_add_style(bar, &style_indic, LV_PART_INDICATOR);
  lv_obj_set_size(bar, 100, 10);

  lv_obj_align(bar, LV_ALIGN_TOP_LEFT, pos_x, pos_y);
  lv_bar_set_value(bar, value, LV_ANIM_ON);
  lv_bar_set_range(bar, -5, 100);
}

void lv_bar_ver (float value, int pos_x, int pos_y){
  static lv_style_t style_indic;
  lv_style_init(&style_indic);
  lv_style_set_bg_opa(&style_indic, LV_OPA_COVER);
  lv_style_set_bg_color(&style_indic, lv_palette_main(LV_PALETTE_GREEN));
  lv_style_set_bg_grad_color(&style_indic, lv_palette_main(LV_PALETTE_BLUE));
  lv_style_set_bg_grad_dir(&style_indic, LV_GRAD_DIR_VER);

  lv_obj_t * bar = lv_bar_create(lv_scr_act());
  lv_obj_add_style(bar, &style_indic, LV_PART_INDICATOR);
  lv_obj_set_size(bar, 15, 90);

  lv_obj_align(bar, LV_ALIGN_TOP_LEFT, pos_x, pos_y);
  lv_bar_set_value(bar, value, LV_ANIM_ON);
  lv_bar_set_range(bar, 0, 10);
}

void lv_text_float(float value, int pos_x, int pos_y){
  char value_c[8];
  dtostrf(value, 6,2, value_c);
  LV_FONT_DECLARE(font_dosis_36_1pbb);
  lv_obj_t * label = lv_label_create(lv_scr_act());
  lv_label_set_text_fmt(label, value_c);
  lv_obj_set_style_text_font(label, &font_dosis_36_1pbb, 0);
  lv_obj_align(label, LV_ALIGN_TOP_LEFT, pos_x, pos_y);
}

void lv_text_int(int value, int pos_x, int pos_y){
  char value_i[4];
  itoa(value, value_i, 10);
  LV_FONT_DECLARE(font_dosis_60_1pbb);
  lv_obj_t * label = lv_label_create(lv_scr_act());
  lv_label_set_text_fmt(label, value_i);
  lv_obj_set_style_text_font(label, &font_dosis_60_1pbb, 0);
  lv_obj_align(label, LV_ALIGN_TOP_LEFT, pos_x, pos_y);
}

static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");
    }
    else if(code == LV_EVENT_VALUE_CHANGED) {
        LV_LOG_USER("Toggled");
    }
}

void lv_btn_start(void)
{
  lv_obj_t * label;

  lv_obj_t * btn_start = lv_btn_create(lv_scr_act());
  lv_obj_add_event_cb(btn_start, event_handler, LV_EVENT_ALL, NULL);
  lv_obj_set_size(btn_start, 190, 100);
  lv_obj_align(btn_start, LV_ALIGN_TOP_LEFT, 250 , 680);

  LV_FONT_DECLARE(font_dosis_50_1pbb);
  label = lv_label_create(btn_start);
  lv_obj_set_style_text_font(label, &font_dosis_50_1pbb, 0);
  lv_label_set_text(label, "START");
  lv_obj_center(label);
}

void lv_qrcode_gen(void)
{
    //dtostrf(lat_pos, 4,10, lat_c);
    //dtostrf(long_pos, 4,10, long_c);
    auto ui_qrcode = lv_qrcode_create(lv_scr_act() ,180, lv_color_black(), lv_color_white());
    char *qr_data = "https://www.google.com/";
    lv_qrcode_update(ui_qrcode, qr_data, strlen(qr_data));
    lv_obj_center(ui_qrcode);
}

static void set_value(void * indic, int32_t v)
{
    lv_meter_set_indicator_end_value(meter,(lv_meter_indicator_t *)indic, v);
}

void lv_example_meter_2(void)
{
    meter = lv_meter_create(lv_scr_act());
    lv_obj_set_size(meter, 300, 300);

    /*Remove the circle from the middle*/
    lv_obj_remove_style(meter, NULL, LV_PART_INDICATOR);

    /*Add a scale first*/
    lv_meter_scale_t * scale = lv_meter_add_scale(meter);
    lv_meter_set_scale_ticks(meter, scale, 11, 2, 10, lv_palette_main(LV_PALETTE_GREY));
    lv_meter_set_scale_major_ticks(meter, scale, 1, 2, 30, lv_color_hex3(0xeee), 15);
    lv_meter_set_scale_range(meter, scale, 0, 100, 270, 90);

    /*Add a three arc indicator*/
    lv_meter_indicator_t * indic1 = lv_meter_add_arc(meter, scale, 10, lv_palette_main(LV_PALETTE_RED), 0);
    lv_meter_indicator_t * indic2 = lv_meter_add_arc(meter, scale, 10, lv_palette_main(LV_PALETTE_GREEN), -10);
    lv_meter_indicator_t * indic3 = lv_meter_add_arc(meter, scale, 10, lv_palette_main(LV_PALETTE_BLUE), -20);

    /*Create an animation to set the value*/
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, set_value);
    lv_anim_set_values(&a, 0, 100);
    //lv_anim_set_repeat_delay(&a, 100);
    //lv_anim_set_playback_delay(&a, 100);
    //lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);

    lv_anim_set_time(&a, 2000);
    lv_anim_set_playback_time(&a, 500);
    lv_anim_set_var(&a, indic1);
    lv_anim_start(&a);

    lv_anim_set_time(&a, 1000);
    //lv_anim_set_playback_time(&a, 1000);
    lv_anim_set_var(&a, indic2);
    lv_anim_start(&a);

    lv_anim_set_time(&a, 1000);
    //lv_anim_set_playback_time(&a, 2000);
    lv_anim_set_var(&a, indic3);
    lv_anim_start(&a);
}

void setup()
{
    int top_pos_y = 40;

    delay(1000);

    Serial.begin(115200);
    Serial.setDebugOutput(true);
    log_i("Board: %s", BOARD_NAME);
    log_i("CPU: %s rev%d, CPU Freq: %d Mhz, %d core(s)", ESP.getChipModel(), ESP.getChipRevision(), getCpuFrequencyMhz(), ESP.getChipCores());
    log_i("Free heap: %d bytes", ESP.getFreeHeap());
    log_i("Free PSRAM: %d bytes", ESP.getPsramSize());
    log_i("SDK version: %s", ESP.getSdkVersion());

    smartdisplay_init();
    
    __attribute__((unused)) auto disp = lv_disp_get_default();
    // lv_disp_set_rotation(disp, LV_DISP_ROT_90);
    // lv_disp_set_rotation(disp, LV_DISP_ROT_180);
    lv_disp_set_rotation(disp, LV_DISP_ROT_270);

    lv_background();
    lv_soil_temp_icon(10, top_pos_y+10);
    lv_soil_humi_icon(130, top_pos_y+10);
    lv_air_temp_icon(250, top_pos_y+10);
    lv_air_humi_icon(370, top_pos_y+10);
    lv_text_float(99.9, 15, top_pos_y+120);
    lv_text_float(99.9, 130, top_pos_y+120);
    lv_text_float(99.9, 250, top_pos_y+120);
    lv_text_float(99.9, 370, top_pos_y+120);

    lv_bar(22.22, 10, top_pos_y+160);
    lv_bar(44.22, 125, top_pos_y+160);
    lv_bar(66.22, 245, top_pos_y+160);
    lv_bar(88.22, 365, top_pos_y+160);

    int top_pos_ver = top_pos_y+190;

    lv_n_icon(20, top_pos_ver);
    lv_p_icon(20, top_pos_ver+110);
    lv_k_icon(20, top_pos_ver+220);
    lv_ph_icon(20, top_pos_ver+330);
    lv_ec_icon(20, top_pos_ver+440);
    
    lv_text_int(999, 150, top_pos_ver+30);
    lv_text_int(999, 150, top_pos_ver+110+30);
    lv_text_int(999, 150, top_pos_ver+220+30);
    lv_text_int(999, 150, top_pos_ver+330+30);
    lv_text_int(999, 150, top_pos_ver+440+30);

    lv_bar_ver(999, 125, top_pos_ver+5);
    lv_bar_ver(999, 125, top_pos_ver+110+5);
    lv_bar_ver(999, 125, top_pos_ver+220+5);
    lv_bar_ver(999, 125, top_pos_ver+330+5);
    lv_bar_ver(999, 125, top_pos_ver+440+5);

    lv_btn_start();
    lv_qrcode_gen();
}

void loop()
{
    lv_timer_handler();
}
