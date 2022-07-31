#  TP2 - Sala de Escape Pokemon

## Introducción

2. Desarrollo del trabajo
Vamos a reutilizar la mayor parte del TP1 implementado al principio del cuatrimestre. Para esta segunda parte
se pide incorporar algunos cambios y explicar algunas cuestiones detalladas en los siguientes items:
La definicion de la estructura de la sala fue movida al archivo sala.c.
Haga las modificaciones que crea nacesarias a la estructura sala, de modo tal que se utilicen los TDA imple-
mentados a lo largo del cuatrimestre.
Explique y justifique por qué utiliza los TDA seleccionados para cada caso.
¿Falla alguna prueba al realizar estos cambios? ¿Por qué?
En caso de que alguna prueba falle, muestre como arreglarla.
La definicion del enumerado de acciones fue movido al .h de sala. Recuerde que este archivo es el único archivo
de cabecera visible pare el usuario de la biblioteca (el único archivo que puede ser incluı́do desde el o los archivos
que implementen la lógica del juego.)
Se agrega al enumerado el tipo de acción ESCAPAR que corresponde al caracter ’g’ en los archivos de acción.
Implemente las nuevas funciones agregadas a sala.h
Implemente en el archivo escape pokemon.c la lógica del juego (utilizando la sala).
Si lo necesita, puede crear archivos extra dentro de src para separar funcionalidades. Recuerde que NO está
permitido incluir los archivos de cabecera privados. Solamente está permitido hacer include de sala.h.
2.1.
El juego
El juego a desarrollar debe presentar una interfaz basada en texto donde el jugador pueda ingresar comandos y
ası́ dirigir cada una de las acciones del protagonista. Existen 4 comandos básicos que deben ser implementados:
ayuda: Muestra un mensaje de ayuda para recordarle al jugador los comandos disponibles.
agarrar ¡objeto¿: Intenta agarrar alguno de los objetos conocidos de la sala.
describir ¡objeto¿: Describe uno de los objetos conocidos de la sala.
salir: Sale del juego.
Además de estos comandos, se deben aceptar comandos a determinar por el archivo de interacciones que van a
permitir interactuar con los diferentes objetos de la sala. Por ejemplo:
examinar habitacion: Si el verbo examinar existe para la habitación, se ejecuta la acción especificada en el
archivos de interacciones.
usar llave cajon: Si el verbo usar existe para la llave con el objeto cajon, se ejecuta la acción especificada en
el archivos de interacciones.
