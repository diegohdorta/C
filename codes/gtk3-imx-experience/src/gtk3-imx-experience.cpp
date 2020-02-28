/* Copyright (c) 2019 Diego Dorta <diego.dorta@nxp.com>
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
#include <gtkmm.h>
#include <iostream>
#include <stdlib.h>

#include "gtk3-imx-experience.hpp"

int main(int argc, char *argv[])
{
    Gtk::Main app(argc, argv);
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("../gtk-layout/gtk3-imx-experience.glade");
    builder->get_widget_derived("gtk3ImxExperienceWindow", gtk3MlExperienceHandler);


    Gtk::Main::run();

    return EXIT_SUCCESS;
}
