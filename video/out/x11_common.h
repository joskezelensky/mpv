/*
 * This file is part of MPlayer.
 *
 * MPlayer is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * MPlayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with MPlayer; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef MPLAYER_X11_COMMON_H
#define MPLAYER_X11_COMMON_H

#include <stdint.h>
#include <stdbool.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "config.h"

struct vo;

struct vo_x11_state {
    Display *display;
    Window window;
    Window rootwin;
    int screen;
    int display_is_local;

    int screensaver_off;
    int dpms_disabled;
    unsigned int screensaver_time_last;

    XIM xim;
    XIC xic;

    GC vo_gc;

    int wm_type;
    int fs_type;
    int window_state;
    int fs_flip;
    int fs_layer;
    int vm_set;
    int vm_orig_w, vm_orig_h;

    GC f_gc;
    XSizeHints vo_hint;
    unsigned int mouse_timer;
    int mouse_waiting_hide;
    int orig_layer;
    int old_gravity;
    int vo_old_x;
    int vo_old_y;
    int vo_old_width;
    int vo_old_height;

    /* Keep track of original video width/height to determine when to
     * resize window when reconfiguring. Resize window when video size
     * changes, but don't force window size changes as long as video size
     * stays the same (even if that size is different from the current
     * window size after the user modified the latter). */
    int last_video_width;
    int last_video_height;
    /* Video size changed during fullscreen when we couldn't tell the new
     * size to the window manager. Must set window size when turning
     * fullscreen off. */
    bool size_changed_during_fs;

    unsigned int olddecor;
    unsigned int oldfuncs;
    XComposeStatus compose_status;

    int vo_gamma;
    int vo_brightness;
    int vo_contrast;

    Colormap cmap;
    XColor cols[256];
    int cm_size, red_mask, green_mask, blue_mask;

    /* XShm stuff */
    int ShmCompletionEvent;
    /* Number of outstanding XShmPutImage requests */
    /* Decremented when ShmCompletionEvent is received */
    /* Increment it before XShmPutImage */
    int ShmCompletionWaitCount;

    Atom XA_NET_SUPPORTED;
    Atom XA_NET_WM_STATE;
    Atom XA_NET_WM_STATE_FULLSCREEN;
    Atom XA_NET_WM_STATE_ABOVE;
    Atom XA_NET_WM_STATE_STAYS_ON_TOP;
    Atom XA_NET_WM_STATE_BELOW;
    Atom XA_NET_WM_PID;
    Atom XA_NET_WM_NAME;
    Atom XA_NET_WM_ICON_NAME;
    Atom XA_WIN_PROTOCOLS;
    Atom XA_WIN_LAYER;
    Atom XA_WIN_HINTS;
    Atom XAWM_PROTOCOLS;
    Atom XAWM_DELETE_WINDOW;
    Atom XAUTF8_STRING;
    Atom XA_NET_WM_CM;
};

int vo_x11_init(struct vo *vo);
void vo_x11_uninit(struct vo *vo);
int vo_x11_check_events(struct vo *vo);
void vo_x11_fullscreen(struct vo *vo);
Colormap vo_x11_create_colormap(struct vo *vo, XVisualInfo *vinfo);
uint32_t vo_x11_set_equalizer(struct vo *vo, const char *name, int value);
uint32_t vo_x11_get_equalizer(struct vo *vo, const char *name, int *value);
bool vo_x11_screen_is_composited(struct vo *vo);
void fstype_help(void);
void vo_x11_create_vo_window(struct vo *vo, XVisualInfo *vis,
        int x, int y, unsigned int width, unsigned int height, int flags,
	Colormap col_map, const char *classname);
void vo_x11_clearwindow_part(struct vo *vo, Window vo_window,
	int img_width, int img_height);
void vo_x11_clearwindow(struct vo *vo, Window vo_window);
void vo_x11_ontop(struct vo *vo);
void vo_x11_border(struct vo *vo);
void vo_x11_update_screeninfo(struct vo *vo);

double vo_x11_vm_get_fps(struct vo *vo);

void xscreensaver_heartbeat(struct vo_x11_state *x11);

#endif /* MPLAYER_X11_COMMON_H */
