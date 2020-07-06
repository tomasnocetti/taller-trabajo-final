# TP Final - Taller de Programación
## Argentum

#### Alumnos: 
- Tomas A Nocetti   - 100853
- Fernando Fabbiano - 102464
- Lautaro Fritz     - 102320

#### Repositorio: https://github.com/tomasnocetti/taller-trabajo-final/
___

### Introducción
El siguiente trabajo practico tiene como objetivo la implementación de una version simplificada del juego Argentum. Para una completa guia de instalacion se recomienda la lectura del Manual del Usuario ubicado en la carpeta manuales. Allí tambien se encontrará un Manual Técnico que detalla partes de la implementación y un Manual de Proyecto que detalla como se procedió a realizar dicho trabajo.

### Plataformas
El trabajo fue desarrollado para su correcto funcionamiento en el OS Linux.

### Dependencias
* GCC 
* SDL2 (para instalar ejecutar \texttt{sudo apt-get install libsdl2-dev} en la terminal)
* SDL2_image (para instalar ejecutar \texttt{sudo apt-get install libsdl2-image-dev} en la terminal)
* SDL2_ttf (para instalar ejecutar \texttt{sudo apt-get install libsdl2-ttf-dev} en la terminal)
* SDL2_mixer (para instalar ejecutar \texttt{sudo apt-get install libsdl2-mixer-dev} en la terminal)
* JsonCpp (para instalar ejecutar \texttt{sudo apt-get install libjsoncpp-dev} en la terminal)
* MsgPack 

### Instalación

1) make
2) sudo make install

En caso de querer desinstalar el programa.

3) sudo make uninstall

### Ejecución

#### Servidor
Iniciara una instancia servidor del juego Argentum. Esto es obligatorio para el correcto funcionamiento del juego.

* argentum-server (ruta del archivo de configuracion) (puerto)

#### Cliente
Esta es el programa que usarán los jugadores. 

* argentum-client (hostname) (puerto)

