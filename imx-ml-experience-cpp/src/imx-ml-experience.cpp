/* Copyright (c) 2019 NXP Semiconductors
 *
 * SPDX-License-Identifier: MIT
 * Diego Dorta <diego.dorta@nxp.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "imx-ml-interface.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    WindowHandler *SplashScreenHandler = nullptr; 
    Gtk::Main app(argc, argv, "org.gtkmm.with_signal");    
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("../gtk3-ui/imx-ml-experience.glade");
    builder->get_widget_derived("splash_screen_window", SplashScreenHandler);

     // Add gnome themes using .css files
      Glib::RefPtr<Gtk::CssProvider> cssProvider = Gtk::CssProvider::create();
	  cssProvider->load_from_path("../gtk3-css/gtk.css");	
	  Glib::RefPtr<Gtk::StyleContext> styleContext = Gtk::StyleContext::create();	
	  Glib::RefPtr<Gdk::Screen> screen = Gdk::Screen::get_default();
      styleContext->add_provider_for_screen(screen, cssProvider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
     
     
    Gtk::Main::run(*SplashScreenHandler);
    return 0;
}
