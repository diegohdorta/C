#include <glib/gprintf.h>
#include <string.h>

typedef GHashTable dict;

dict *new_dict(void)
{
	return g_hash_table_new(g_str_hash, g_str_equal);
}

void free_dict(dict *d)
{
	g_hash_table_unref(d);
}

void dict_insert(dict *d, char *key, void *value)
{
	g_hash_table_insert(d, key, value);	
}

void *dict_get(dict *d, const char *key)
{
	return g_hash_table_lookup(d, key);
}

int main(void)
{
	dict *clientes;

	char buffer[20];
	char **tokens, **i;
	char *nova_string, *s2;
	int x;
	int *y;
	g_printf("Hello\n");

	scanf("%s", buffer);

	printf("Você digitou: %s\n", buffer);

	tokens = g_strsplit(buffer, "#", 0);

	for (i = tokens; i != NULL && *i != NULL; i++)
		printf("token: %s\n", *i);

	s2 = g_strjoinv("$", tokens);

	printf("%s\n", s2);

	g_free(s2);

	g_strfreev(tokens);

	scanf("%d", &x);

	nova_string = g_strdup_printf("Soma 1: %d", x+1);

	puts(nova_string);

	g_free(nova_string);

	clientes = new_dict();
	dict_insert(clientes, "dorta", &x);
	dict_insert(clientes, "hdante", buffer);

	y = dict_get(clientes, "dorta");
	printf("%d\n", *y);
	printf("%s\n", dict_get(clientes, "hdante"));

	free_dict(clientes);

	return 0;
}
