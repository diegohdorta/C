/*
 * lwib - Simple Lightweight and Speedy Low Latency iMX Web Browser
 * Copyright (c) 2019 Diego Dorta <diego.dorta@nxp.com>
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
 *
 * https://tools.ietf.org/html/rfc2616#section-9.3
 */
#include <fstream>
#include <limits.h>
#include <unistd.h>
#include "browser.h"

int main (int argc, char **argv)
{
	try {
		// get path contains exe file
		char result[PATH_MAX];
		ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
		string exe_path = string(result, (count > 0) ? count : 0);
		exe_path = fs::path(exe_path).parent_path().string();
		cout << "exe_path: " << exe_path << endl;
		
		Glib::RefPtr<Gtk::Application>
		app = Gtk::Application::create(argc, argv, "dbt.tbrowser");
		Browser browser(exe_path);		
		app->run(browser);
	} catch(exception const& e) {
		//~ cerr << e.what() << endl;
		
		std::ofstream log("error.txt", std::ios_base::out | std::ios_base::app);
		log << e.what() << std::endl;
	}
}
