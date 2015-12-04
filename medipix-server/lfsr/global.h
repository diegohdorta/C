/*Header FILE
--------------------------------------------------------------------------------
--!@brief GLOBAL.H
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! CABEÇALHO GLOBAL DO PROGRAMA PACKET RECEIVE
--!
--! DETAILS:      
--!
--!- Project Name: global
--!- Module Name: global.h
--!- Tools: gedit 
--!- Author: Franz Wagner
--!- Company: LABORATORIO NACIONAL DE LUZ SINCROTRON - GRUPO DETECTORES
--!- Create Date: 08/05/2014     
--!- Version: 1.0.0 (mai/2014) 
--------------------------------------------------------------------------------
-- LNLS - DET - 2014
--------------------------------------------------------------------------------
Header*/
#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#define BUFLEN  257							//Max length of buffer
#define NPACK1  65							//Number of packets for 1x1bit
#define NPACK6  385							//Number of packets for 1x6bit
#define NPACK12 769							//Number of packets for 1x12bit
#define NPACK24 1537     					//Number of packets for 1x24bit
#define PORT    3000  						//The port on which to listen for incoming data

typedef int mem_aloc[BUFLEN];
mem_aloc buff1[NPACK1];
mem_aloc buff6[NPACK6];
mem_aloc buff12[NPACK12];
mem_aloc buff24[NPACK24];

int Image_Flip [256][256];
int Image_Flip2 [256][256];

unsigned int LFSR6bits[64];
unsigned int LFSR12bits[4096];

void Generate6BitTable();
void Generate12BitTable();

#endif
