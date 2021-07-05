#include "pain64.h"
#include <stdio.h>
#include <string.h>
#include "SDL2/SDL.h"
#undef      main

typedef struct { SDL_Window *window; SDL_Renderer *renderer; } window_handle;

static window_handle _handles[256];
static int _init = 0;

void pain64_dm_init(void) {
    SDL_Init(SDL_INIT_VIDEO);
    memset(_handles, 0, sizeof(window_handle) * 256);
}

void pain64_dm_draw(int id, uint32_t color, uint32_t x, uint32_t y) {
    int r = color & 0xFF;
    int g = (color >> 8) & 0xFF;
    int b = (color >> 16) & 0xFF;
    SDL_SetRenderDrawColor(_handles[id].renderer, r, g, b, 0xFF);
    SDL_RenderDrawPoint(_handles[id].renderer, x, y);
    return;
}

void pain64_dm_paint(void) {
    for (int i = 0; i < 256; i++) {
        window_handle *handle = &(_handles[i]);

        SDL_Event event;
        while (SDL_PollEvent(&event) > 0) {
            if (event.type == SDL_QUIT) {
                SDL_DestroyRenderer(handle->renderer);
                SDL_DestroyWindow(handle->window);
                memset(handle, 0, sizeof(window_handle));
            }
        }

        SDL_SetRenderDrawColor(handle->renderer, 0, 0, 0, 0xFF);
        SDL_RenderClear(handle->renderer);

        SDL_RenderPresent(handle->renderer);
    }
}

void pain64_dm_free(void) {
    for (int i = 0; i < 256; i++) {
        window_handle *handle = &(_handles[i]);
        SDL_DestroyRenderer(handle->renderer);
        SDL_DestroyWindow(handle->window);
    }
    SDL_Quit();
}

void pain64_dm_open(uint8_t id, uint64_t packet) {
    window_handle *handle = &(_handles[id]);
    uint32_t width;
    uint32_t height;
    
    switch (packet) {
    case 0x20:
        width = 160;
        height = 120;
        break;
    case 0x30:
        width = 320;
        height = 240;
        break;
    case 0x40:
        width = 640;
        height = 480;
        break;
    case 0x50:
        width = 800;
        height = 600;
        break;
    case 0:
    case 0x10:
    default:
        width = 80;
        height = 60;
        break;
    }

    handle->window = SDL_CreateWindow("PAIN64_VIEW", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        width, height, SDL_WINDOW_HIDDEN);
    if (!handle->window) {
        fprintf(stderr, "pain64.dm: cannot create display\n");
        return;
    }
    handle->renderer = SDL_CreateRenderer(handle->window, -1, SDL_RENDERER_ACCELERATED);
    if (!handle->window) {
        fprintf(stderr, "pain64.dm: cannot create display renderer\n");
        return;
    }
    SDL_ShowWindow(handle->window);
}