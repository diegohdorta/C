/* Copyright (c) 2019 Diego Dorta <diego.dorta@nxp.com>
 * SPDX-License-Identifier:	GPL-3.0+
 */
#ifndef GTK_MAIN_EXPERIENCE_H_
#define GTK_MAIN_EXPERIENCE_H_
 
#ifdef USE_NAME_GTK    
#define MW_TITLE           "GTK NXP Machine Learning"
#else
#define MW_TITLE           "NXP Machine Learning"
#endif

#define MW_WIDTH           1280
#define MW_HEIGHT          720
#define GTK_CSS_PROVIDER_COLOR_PATH "../gtk-widgets/gtk-widgets.css"

void destroy(void);

#endif /* GTK_MAIN_EXPERIENCE_H_ */
