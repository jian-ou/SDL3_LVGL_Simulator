#include "config.h"

void btn_event_cb(lv_event_t *e)
{
  printf("Clicked\n");
}

void App_main(void)
{
  lv_obj_t *slider = lv_slider_create(lv_screen_active());
  lv_slider_set_value(slider, 70, LV_ANIM_OFF);
  lv_obj_set_size(slider, 300, 20);
  lv_obj_center(slider);

  /*Add local styles to MAIN part (background rectangle)*/
  lv_obj_set_style_bg_color(slider, lv_color_hex(0x0F1215), LV_PART_MAIN);
  lv_obj_set_style_bg_opa(slider, 255, LV_PART_MAIN);
  lv_obj_set_style_border_color(slider, lv_color_hex(0x333943), LV_PART_MAIN);
  lv_obj_set_style_border_width(slider, 5, LV_PART_MAIN);
  lv_obj_set_style_pad_all(slider, 5, LV_PART_MAIN);

  /*Create a reusable style sheet for the INDICATOR part*/
  static lv_style_t style_indicator;
  lv_style_init(&style_indicator);
  lv_style_set_bg_color(&style_indicator, lv_color_hex(0x37B9F5));
  lv_style_set_bg_grad_color(&style_indicator, lv_color_hex(0x1464F0));
  lv_style_set_bg_grad_dir(&style_indicator, LV_GRAD_DIR_HOR);
  lv_style_set_shadow_color(&style_indicator, lv_color_hex(0x37B9F5));
  lv_style_set_shadow_width(&style_indicator, 15);
  lv_style_set_shadow_spread(&style_indicator, 5);

  /*Add the style sheet to the slider's INDICATOR part*/
  lv_obj_add_style(slider, &style_indicator, LV_PART_INDICATOR);

  /*Add the same style to the KNOB part too and locally overwrite some properties*/
  lv_obj_add_style(slider, &style_indicator, LV_PART_KNOB);

  lv_obj_set_style_outline_color(slider, lv_color_hex(0x0096FF), LV_PART_KNOB);
  lv_obj_set_style_outline_width(slider, 3, LV_PART_KNOB);
  lv_obj_set_style_outline_pad(slider, -5, LV_PART_KNOB);
  lv_obj_set_style_shadow_spread(slider, 2, LV_PART_KNOB);
}
