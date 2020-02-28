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
#include <iostream>
#include <vector>
#include <assert.h>
#include <png++/png.hpp>

#include "robin-nn.h"

using namespace std;

double stepFunction(double x)
{
    if(x>0.9){
        return 1.0;
    }
    if(x<0.1){
        return 0.0;
    }
    return x;
}

vector<double> readImage(const char *filename)
{
    int height=32, width=32;

    png::image<png::rgb_pixel> image(filename);
    assert(image.get_width()==width && image.get_height()==height);

    int red,green,blue,p=0;

    vector<double> v(height*width);
    for (int i=0 ; i<height ; i++)
    {
        for (int j=0 ; j<width ; j++)
        {
            red = (int)image[i][j].red;
            green = (int)image[i][j].green;
            blue = (int)image[i][j].blue;
            if(red==255 && green==255 && blue==255) // white pixels are 0 and black pixels are 1 (like the training set)
                v[p++]=0.0;
            else
                v[p++]=1.0;
        }
    }

    return v;
}

int main(int argc, char **argv) {
     vector<double> image = readImage("media/number.png");

     RobinNN net("params");
     cout << net.computeOutput(image).applyFunction(stepFunction);
}
