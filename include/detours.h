#pragma once

#include <windows.h>

#include <stdint.h>

#include <vector>

#include "hook.h"
#include "dotnet_data_collector.h"
#include "code_start_target.h"
#include "signatures.h"

#include "imgui.h"

typedef BOOL(__stdcall *twglSwapBuffers)(HDC hDc);
typedef void(__stdcall *void_trampoline)();

struct Parameter
{
    bool lock;
    float value;
    uintptr_t offset;
    const char *slider_fmt;
    const char *error_message;
    void (*enable)();
    void (*disable)();
    bool found = false;
};

extern Parameter ar_parameter;
extern Parameter cs_parameter;
extern Parameter od_parameter;

extern bool cfg_relax_lock;
extern bool cfg_aimbot_lock;

extern uintptr_t selected_song_ptr;
extern uintptr_t audio_time_ptr;
extern uintptr_t osu_manager_ptr;
extern uintptr_t binding_manager_ptr;

extern twglSwapBuffers wglSwapBuffersGateway;

extern Hook SwapBuffersHook;

void try_find_hook_offsets();

void init_hooks();

void enable_ar_hooks();
void disable_ar_hooks();

void enable_cs_hooks();
void disable_cs_hooks();

void enable_od_hooks();
void disable_od_hooks();

void enable_notify_hooks();
void disable_notify_hooks();

void set_approach_rate();
void set_circle_size();
void set_overall_difficulty();

void notify_on_beatmap_load();
void notify_on_scene_change();

template <size_t size>
uintptr_t find_opcodes(const uint8_t (&signature)[size], uintptr_t code_start, int start_offset, int end_offset)
{
    for (uintptr_t start = code_start + start_offset; start - code_start <= end_offset; ++start)
        if (memcmp((uint8_t *)start, signature, size) == 0)
            return start - code_start;
    return 0;
}
