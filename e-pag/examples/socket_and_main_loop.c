#include <glib.h>
#include <gio/gio.h>

void on_connect(GSocketListener *source, GAsyncResult *res, gpointer user_data)
{
	GSocketConnection *filho;

	filho = g_socket_listener_accept_finish(source, &result, 
}

int main(void)
{
	GSocketService *service;
	GMainLoop *loop;

	loop = g_main_loop_new(NULL);

	service = g_socket_service_new();
	g_socket_listener_add_inet_port(service, 10000, NULL, NULL);
	g_socket_listener_accept_async(service, NULL, on_connect, NULL);

	g_main_loop_run(loop);
}
