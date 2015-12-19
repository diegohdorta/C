#define _XOPEN_SOURCE 700

#include <kivatz/epnl.h>

int main(void)
{


        debug(stderr, "Testando nova biblioteca para o Kivatz!\n");
        
        ready_socket_t socket;
        
        socket = create_tcp_socket(10000);
        
 	/* to be continued... */       
        
        
        return EXIT_SUCCESS;


}
