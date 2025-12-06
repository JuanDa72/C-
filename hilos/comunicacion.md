## Mutex para la sincronizacion 

Proceso de sincronización para que solamente un hilo acceda la zona critica. Un mutex es una única llave, solamente una hilo puede entrar a la vez. El hilo dueño es aquel que hace: 
pthread_mutex_lock()

- 
    ## Métodos importantes 
     
    ## pthread_mutex_init()
    - Inicializa el mutex antes de usarlo.
    - pthread_mutex_t mutex;
    - pthread_mutex_init(&mutex, NULL);
    - 
    ## pthread_mutex_destroy()
    - Libera la memoria interna del mutex cuando ya no lo vas a usar.
    - pthread_mutex_destroy(&mutex);
    - 
    ## pthread_mutex_lock()
    - Bloquea el mutex.
    - Si ya está bloqueado por otro hilo→este hilo se queda esperando.
    - pthread_mutex_lock(&mutex);
    - 
    ## pthread_mutex_unlock()
    - Desbloquea el mutex.
    - Solo lo puede desbloquear el hilo que hizo lock (ownership).
    - pthread_mutex_unlock(&mutex);