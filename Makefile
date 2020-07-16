# Makefile de ejemplo para programa cliente-servidor en C/C++. Genera los ejecutables 'client' y 'server' basados en archivos con el patrón 'client*.(c|cpp)' y 'server*.(c|cpp)' respectivamente. En ambos ejecutables, incluye elementos encontrados en 'common*.(c|cpp)'.
# Creado: 27/04/2007 - Leandro Lucarella
# Modificado: 01/09/2016 - Pablo Roca
# Copyleft 2004 - Leandro Lucarella, Bajo licencia GPL [http://www.gnu.org/]

# CONFIGURACION
################

# Extensión de los archivos a compilar (c para C, cpp o cc o cxx para C++).
extension = cpp

# Si usa funciones de math.h, descomentar (quitar el '#' a) la siguiente línea.
math = si

# Si usa threads, descomentar (quitar el '#' a) la siguiente línea.
threads = si

sdl = si

jsoncpp = si

# Descomentar si se quiere ver como se invoca al compilador
#verbose = si

# CONFIGURACION "AVANZADA"
###########################

# Opciones para el compilador C/C++ para tratamiento de errores y warnings.
CFLAGS = -Wall -Werror -pedantic -pedantic-errors

# Para optimizar el binario resultante lo mejor posible
CFLAGS += -O3

# Para valgrind o debug
CFLAGS += -ggdb -DDEBUG -fno-inline

# Estandar de C a usar
CSTD = c99

# Estandar de C++ a usar
CXXSTD = c++11

# Si se quiere compilar estaticamente, descomentar la siguiente linea
#static = si


# VARIABLES CALCULADAS A PARTIR DE LA CONFIGURACION
####################################################


# Linkea con libm de ser necesario.
ifdef math
LDFLAGS += -lm
endif

# Linkea con threads de ser necesario. Permite el uso de pthread en C y C++. Permite el uso de built-in threads en C++.
ifdef threads
LDFLAGS += -pthread
endif

ifdef static
LDFLAGS += -static
endif

# Se reutilizan los flags de C para C++ también
CXXFLAGS += $(CFLAGS)

# Se usa enlazador de C++ si es código no C.
ifeq ($(extension), c)
CFLAGS += -std=$(CSTD)
LD = $(CC)
else
CXXFLAGS += -std=$(CXXSTD)
LD = $(CXX)
endif

ifdef jsoncpp
LDFLAGS += -ljsoncpp
endif

ifdef sdl
LDFLAGS += -lz
# LDFLAGS += -lxml2
LDFLAGS += -lSDL2_image
LDFLAGS += -lSDL2_ttf
# LDFLAGS += -ltmx
LDFLAGS += -lSDL2
LDFLAGS += -lSDL2_ttf
LDFLAGS += -lSDL2_mixer
endif

# Si no especifica archivos, tomo todos.
fuentes_client ?= $(wildcard client*.$(extension)) $(wildcard client/*.$(extension)) $(wildcard client/*/*.$(extension))
fuentes_server ?= $(wildcard server*.$(extension)) $(wildcard server/*.$(extension)) $(wildcard server/*/*.$(extension))
fuentes_common ?= $(wildcard common*.$(extension)) $(wildcard common/*.$(extension))
directorios = $(shell find . -type d -regex '.*\w+')

occ := $(CC)
ocxx := $(CXX)
orm := $(RM)
old := $(LD)
ifdef verbose
RM := $(RM) -v
else
CC =  @echo "  CC  $@"; $(occ)
CXX = @echo "  CXX $@"; $(ocxx)
RM =  @echo "  CLEAN"; $(orm)
LD =  @echo "  LD  $@"; $(old)
endif


# REGLAS
#########

.PHONY: all clean install uninstall

all: client server

o_common_files = $(patsubst %.$(extension),%.o,$(fuentes_common))
o_client_files = $(patsubst %.$(extension),%.o,$(fuentes_client))
o_server_files = $(patsubst %.$(extension),%.o,$(fuentes_server))

client: $(o_common_files) $(o_client_files)
	$(LD) $(o_common_files) $(o_client_files) -o argentum-client $(LDFLAGS)

server: $(o_common_files) $(o_server_files)
	$(LD) $(o_common_files) $(o_server_files) -o argentum-server $(LDFLAGS)

clean: clean-client clean-server clean-common

clean-client:
	$(RM) -f $(o_client_files) argentum-client
clean-server:
	$(RM) -f $(o_server_files) argentum-server
clean-common:
	$(RM) -f $(o_common_files)

install:
	mkdir -p /etc/argentum
	mkdir -p /var/argentum
	install -m 755 argentum-client /usr/bin
	install -m 755 argentum-server /usr/bin
	install -m 666 config.json /etc/argentum
	cp -r client/assets /var/argentum
	touch dbfile.bin
	touch indexfile.bin
	touch argentum-client.log
	touch argentum-server.log
	install -m 666 dbfile.bin /var/argentum
	install -m 666 indexfile.bin /var/argentum

uninstall:
	rm -rf /etc/argentum
	rm -rf /var/argentum
	rm /usr/bin/argentum-client
	rm /usr/bin/argentum-server
