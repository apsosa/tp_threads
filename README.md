# Trabajo práctico 1 - Threading


 

## Compilación
* El `Makefile` debería permitirles compilar el código con el comando `make`.
  El ejecutable generado estará en la carpeta `build`.
* El ejecutable se puede correr de la siguiente forma:
  ```
  ./ContarPalabras <threads_lectura> <threads_maximo> <archivo1> [<archivo2>...]
  ```
  donde:
  * `threads_lectura` es la cantidad de threads que se usará para leer archivos,
  * `threads_maximo` es la cantidad de threads que se usará para computar
    la palabra con más apariciones, y
  * `archivo1`, `archivo2`, etc. son los nombres de los archivos a procesar.

## Experimentación

Antes que nada para la experimentación se crearon unos archivos llamados `experimento1.sh` y `experimento2.sh` los cuales son los encargados de ejectar los experimentos. Además de eso será necesario de forma imprecindible la instalación de `jupyter notebook` para poder ejecutar de manera ordenada los datasets creados en el mismo programa y también los gráficos de nuestro proyecto.

Para lograrlo de contar con el programa pip o pip3.
* Aquí encontrará información para instalar pip https://pip.pypa.io/en/stable/
* Una vez instalado pip o pip3 ustede deberá ejecutar el siguiente comando: `pip install notebook` o en su defecto `pip3 install notebook`. Esta misma notebook ya instala las dependencias necesarias para poder replciar nuestro proyecto.    
Una vez instalado pararse en el directorio `experimentación` en la raiz del proyecto y ejecutar el comando `jupyter notebook`.

Una vez dentro de de jupyter notebook usted entontrará 2 archivos.
* Uno llamado `generador-de-instancias` el cual genera los datasets que utilizamos en nuestros experimentos y además de ello ejecuta los arhivos .sh para guardar los resultados en archivos .csv
* Y el otro `graficos` el cual levanta los archivos .csv generados y se encarga de graficar el trabajo realizado.

## Tests
* Ejecutando `make test` podrán compilar y ejecutar una pequeña suite de tests
  unitarios. Estos tests solo pretenden facilitarles el proceso de desarrollo
  verificando algunos aspectos básicos del funcionamiento del código.
  **No evalúan aspectos de concurrencia** y por lo tanto no brindan ninguna
  garantía de que el código escrito sea correcto.
