#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "../lvgl/lvgl.h"

#include "../config.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;

extern uint16_t lvgl_showbuf[MY_DISP_VER_RES * MY_DISP_HOR_RES];
extern lv_touchpad_t indev_touchpad_data;

Uint32 my_timer_callback(void *userdata, SDL_TimerID timerID, Uint32 interval)
{
  lv_tick_inc(1);
  return interval; // 继续执行
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
  if (!SDL_CreateWindowAndRenderer("DisplaySIM", MY_DISP_HOR_RES, MY_DISP_VER_RES, 0, &window, &renderer))
  {
    SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB565, SDL_TEXTUREACCESS_STREAMING, MY_DISP_HOR_RES, MY_DISP_VER_RES);
  if (!texture)
  {
    SDL_Log("Couldn't create texture: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  SDL_TimerID timer = SDL_AddTimer(1, my_timer_callback, NULL);

  lv_init();
  lv_port_disp_init();
  lv_port_indev_init();

  app_main();

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
  if (event->type == SDL_EVENT_QUIT)
  {
    return SDL_APP_SUCCESS;
  }

  if (event->type == SDL_EVENT_KEY_DOWN)
  {
    SDL_Keycode key = event->key.key;
  }

  if (event->type == SDL_EVENT_MOUSE_MOTION || event->type == SDL_EVENT_MOUSE_BUTTON_DOWN || event->type == SDL_EVENT_MOUSE_BUTTON_UP)
  {
    indev_touchpad_data.last_x = (int)(event->motion.x);
    indev_touchpad_data.last_y = (int)(event->motion.y);
  }

  if (event->type == SDL_EVENT_MOUSE_BUTTON_UP)
  {
    indev_touchpad_data.is_pressed = 0;
  }

  if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN)
  {
    indev_touchpad_data.is_pressed = 1;
  }

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
  lv_timer_handler();

  SDL_UpdateTexture(texture, NULL, lvgl_showbuf, MY_DISP_HOR_RES * sizeof(uint16_t));
  SDL_RenderTexture(renderer, texture, NULL, NULL);

  SDL_RenderPresent(renderer);

  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
}