#define _XOPEN_SOURCE 700

#include "../include/epnl.h"

int main(void)
{


        debug(stderr, "Testando nova biblioteca para o Kivatz!\n");
        
        ready_socket_t socket;
        
        socket = create_tcp_socket(1000);
        
        
        
        
        return EXIT_SUCCESS;


}
