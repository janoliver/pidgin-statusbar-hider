/*
 * Pidgin Hide statusbar
 * 
 * Copyright 2011 Jan Oliver Oelerich <janoliver@oelerich.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#define PURPLE_PLUGINS

#include <glib.h>
#include "plugin.h"
#include "signals.h"
#include "version.h"
#include "gtkblist.h"
#include "gtkplugin.h"

/*
 * Callback that is called when the buddy list is created
 */
void
gtkblist_created_cb(PurpleBuddyList *blist) {
    PidginBuddyList *gtkblist = PIDGIN_BLIST(purple_get_blist());
    gtk_widget_hide(gtkblist->statusbox);
	
}

/*
 * plugin_load
 */
static gboolean
plugin_load(PurplePlugin *plugin) {
    // register callback function
	purple_signal_connect(pidgin_blist_get_handle(), 
	                      "gtkblist-created", 
	                      plugin, 
	                      PURPLE_CALLBACK(gtkblist_created_cb), 
	                      NULL);
	return TRUE;
}

/*
 * plugin_unload
 */
static gboolean
plugin_unload(PurplePlugin *plugin) {
	PidginBuddyList *gtkblist = PIDGIN_BLIST(purple_get_blist());
	gtk_widget_show(gtkblist->statusbox); 
	return TRUE;
}

static void
init_plugin(PurplePlugin *plugin) {}

static PurplePluginInfo info = {
    PURPLE_PLUGIN_MAGIC,
    PURPLE_MAJOR_VERSION,
    PURPLE_MINOR_VERSION,
    PURPLE_PLUGIN_STANDARD,
    PIDGIN_PLUGIN_TYPE,
    0,
    NULL,
    PURPLE_PRIORITY_DEFAULT,

    "statusbar-hider",
    "Statusbar Hider",
    "1.1",

    "Hides the ugly, big status bar of pidgin",          
    "Hides the ugly, big status bar of pidgin and nothing more",          
    "Jan Oliver Oelerich <janoliver@oelerich.org>",                          
    "http://www.oelerich.org",     
    
    plugin_load,                   
    plugin_unload,                          
    NULL,                          
                                   
    NULL,                          
    NULL,                          
    NULL,                        
    NULL,                   
    NULL,                          
    NULL,                          
    NULL,                          
    NULL                           
};  

PURPLE_INIT_PLUGIN(hidestatusbar, init_plugin, info)
