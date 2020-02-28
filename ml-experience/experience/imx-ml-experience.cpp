/* Copyright (c) 2019 NXP Semiconductors
 *
 * SPDX-License-Identifier: GPL3
 * Diego Dorta <diego.dorta@nxp.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "imx-ml-experience.hpp"
#include "imx-ml-interface.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    WindowHandler *SplashScreenHandler = nullptr; 
    Gtk::Main app(argc, argv, "org.gtkmm.with_signal");    
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file(UI_FILE);
    builder->get_widget_derived("splash_screen_window", SplashScreenHandler);

    Glib::RefPtr<Gtk::CssProvider> cssProvider = Gtk::CssProvider::create();
	cssProvider->load_from_path(CSS_FILE);	
	Glib::RefPtr<Gtk::StyleContext> styleContext = Gtk::StyleContext::create();	
	Glib::RefPtr<Gdk::Screen> screen = Gdk::Screen::get_default();
    styleContext->add_provider_for_screen(screen, cssProvider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);  
     
    Gtk::Main::run(*SplashScreenHandler);
    return 0;
}
