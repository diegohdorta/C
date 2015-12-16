GLIB := `pkg-config glib-2.0 --cflags --libs`
aaa: aaa.c
	clang -o aaa aaa.c $(GLIB) -g

clean:
	$(RM) aaa

