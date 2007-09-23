/* Jinete - a GUI library
 * Copyright (c) 2003, 2004, 2005, 2007, David A. Capello
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of the Jinete nor the names of its contributors may
 *     be used to endorse or promote products derived from this software
 *     without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <allegro.h>
#include <stdio.h>

#include "jinete.h"

static void handle_menuitem_selected (JWidget widget, int user_data);

static struct jquickmenu quickmenu[] =
{
  {  0, "&File",	NULL,		NULL,			  0 },
  {  1, "&New",		NULL,		NULL,			  0 },
  {  2, "&Sprite",	NULL,		handle_menuitem_selected, 0 },
  {  2, "&Image",	NULL,		handle_menuitem_selected, 0 },
  {  2, "&Font",	NULL,		handle_menuitem_selected, 0 },
  {  2, "&Palette",	NULL,		handle_menuitem_selected, 0 },
  {  1, "&Open",	"<Ctrl+O>",	handle_menuitem_selected, 0 },
  {  1, "&Save",	"<Ctrl+S>",	handle_menuitem_selected, 0 },
  {  1, NULL,		NULL,		NULL,			  0 },
  {  1, "&Quit",	"<Ctrl+Q> <Alt+X> <Esc>", handle_menuitem_selected, 0 },
  {  0, "&Edit",	NULL,		NULL,			  0 },
  {  1, "Cu&t",		"<Shift+Del>",	handle_menuitem_selected, 0 },
  {  1, "&Copy",	"<Ctrl+Ins>",	handle_menuitem_selected, 0 },
  {  1, "&Paste",	"<Shift+Ins>",	handle_menuitem_selected, 0 },
  {  1, "C&lear",	"<Ctrl+Del>",	handle_menuitem_selected, 0 },
  {  0, "&Tools",	NULL,		handle_menuitem_selected, 0 },
  {  0, "&Help",	NULL,		handle_menuitem_selected, 0 },
  { -1, NULL,		NULL,		NULL,			  0 },
};

int main (int argc, char *argv[])
{
  JWidget manager, window, box, button, menubar;

  allegro_init ();
  if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 320, 200, 0, 0) < 0) {
    if (set_gfx_mode(GFX_AUTODETECT, 320, 200, 0, 0) < 0) {
      allegro_message("%s\n", allegro_error);
      return 1;
    }
  }
  install_timer ();
  install_keyboard ();
  install_mouse ();

  manager = jmanager_new ();
  ji_set_standard_theme ();

  window = jwindow_new ("Menus");
  box = jbox_new (JI_VERTICAL);
  button = jbutton_new ("&Close");
  menubar = jmenubar_new_quickmenu (quickmenu);

  jwidget_add_child (window, box);
  jwidget_add_child (box, menubar);
  jwidget_add_child (box, button);

  jwindow_open_bg (window);

  jmanager_run (manager);
  jmanager_free (manager);
  return 0;
}

END_OF_MAIN ();

static void handle_menuitem_selected (JWidget widget, int user_data)
{
  printf ("Selected item: %s\n", widget->text);
}

