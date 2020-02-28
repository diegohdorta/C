/* Copyright (c) 2019 NXP Semiconductors
 * Diego Dorta <diego.dorta@nxp.com>
 * SPDX-License-Identifier: MIT
 */
#include "imx-ml-helper.hpp"

int CSV_Helper::run(void)
{
    this->filePath.append(file);
    if (getDataFileSizeLines()) {
        g_print("Something went wrong with files");
        return 1;
    }
    if (readDataFileAndSaveContent()) {
        g_print("Something went wrong with reading files");
        return 1;
    }
    return 0;
}
int CSV_Helper::getDataFileSizeLines(void)
{
    ifs.open(this->filePath, std::ifstream::in);
    if (ifs.fail()) {
        return 1;
    }
    while (getline(ifs, this->str)) {
        this->csvLines++;
    }
    ifs.close();
    return 0;
}
int CSV_Helper::readDataFileAndSaveContent(void)
{
    ifs.open(this->filePath, std::ifstream::in);
    if (ifs.fail()) {
        return 1;
    }
    while (getline(ifs, this->entireLine)) {
        this->inferencesArray.push_back(this->entireLine);
    }        
    ifs.close();
    return 0;
}
