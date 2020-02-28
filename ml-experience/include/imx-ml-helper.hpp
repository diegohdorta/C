/* Copyright (c) 2019 NXP Semiconductors
 * Diego Dorta <diego.dorta@nxp.com>
 * SPDX-License-Identifier: MIT
 */
#ifndef IMX_ML_HELPER_H_
#define IMX_ML_HELPER_H_

#include <gtkmm.h>
#include <fstream>

#define DATAPATH "../data/"
#define DATAFILE_PATH "data-tree"

class CSV_Helper {
    public:
        std::vector<std::string> inferencesArray;
        std::vector<std::string> temporaryApplicationsArray;
        std::string str;
        std::string entireLine;
        std::ifstream ifs;
        unsigned int csvLines = 0;
        std::string filePath = DATAPATH;
        std::string file = DATAFILE_PATH;
   
        int run(void);
        int getDataFileSizeLines(void);
        int readDataFileAndSaveContent(void);
};

#endif /* IMX_ML_HELPER_H_ */
