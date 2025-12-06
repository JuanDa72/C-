## Hilos
 Hilos en computación↔Unidad de ejecución que comparte recursos con otros hilos dentro de un proceso.

En computación, un hilo (o thread) es la secuencia de instrucciones más pequeña que un programa puede ejecutar de forma independiente dentro de un proceso, permitiendo a una aplicación realizar varias tareas a la vez (multitarea) de manera concurrente y eficiente, ya que todos los hilos de un mismo proceso comparten los mismos recursos y espacio de memoria.
- 
    - Pasos para crear un hilo 

    - Función Propósito Explicación

    - pthread_t Tipo de Dato Es el tipo de dato que se usa para declarar un identificador de hilo. Similar a pid_t para procesos.

    - pthread_create() Creación Iniciala ejecución de un nuevo hilo. Le pasas la función que quieres que ejecute.

    - pthread_join() Espera Bloquea el hilo que llama (generalmente el hilo principal) hasta que el hilo especificado haya terminado su ejecución. Es vital para la sincronización.

    - pthread_exit() Terminación Finaliza la ejecución del hilo que llama y devuelve un valor de estado.
    
- Recuerda linkear la librería xd. 