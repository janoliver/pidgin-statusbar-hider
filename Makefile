CC=gcc

PIDGIN_CFLAGS=`pkg-config --cflags pidgin purple`
PIDGIN_LIBS=`pkg-config --libs pidgin purple`
PIDGIN_PREFIX=`pkg-config --variable=prefix purple`

GTK_CFLAGS = `pkg-config --cflags gtk+-2.0`
GTK_LIBS=`pkg-config --libs gtk+-2.0`

GOBJECT_CFLAGS=`pkg-config --cflags gobject-2.0`
GOBJECT_LIBS=`pkg-config --libs gobject-2.0 gmodule-2.0`

PREFIX=$(DESTDIR)/$(PIDGIN_PREFIX)
plugin_dir=$(PREFIX)/lib/purple-2
data_dir=$(prefix)/share

CFLAGS+=-O2 -Wall

plugin=hidestatusbar.so
override CFLAGS += -fPIC

.PHONY: all clean

objects = hidestatusbar.o

all: $(plugin)

$(plugin): $(objects)
$(plugin): CFLAGS := $(CFLAGS) $(PIDGIN_CFLAGS) \
							$(GOBJECT_CFLAGS) $(GTK_CFLAGS) $(INTERNAL_CFLAGS)

$(plugin): LIBS := $(PIDGIN_LIBS) $(GTK_LIBS) \
							$(GOBJECT_LIBS)

# $(P)CC shows [CC] and the next line shows the nice output
%.o:: %.c
	$(CC) $(CFLAGS) -Wp,-MMD,$(dir $@).$(notdir $@).d -o $@ -c $<

# Make the shared object/lib
%.so::
	$(CC) -shared -o $@ $^ $(LIBS)  

clean: 
	rm -f $(plugin) $(objects)

install: $(plugin)
	mkdir -p $(plugin_dir)
	install $(plugin) $(plugin_dir)
	
uninstall:
	rm $(PIDGIN_PREFIX)/lib/purple-2/hidestatusbar.so
