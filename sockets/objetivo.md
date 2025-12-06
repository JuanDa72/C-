# 🌐 Apuntes: Objetivo de la Comunicación por Sockets

## 🎯 ¿Qué Buscamos con los Sockets?

El objetivo principal de usar **sockets** es permitir que procesos que se ejecutan en **máquinas diferentes** (o en la misma máquina, pero que no tienen relación de parentesco) puedan **intercambiar datos a través de una red** (como Internet o una red local).

Un socket actúa como un **punto final** de comunicación que reside en un proceso específico, permitiendo el envío y recepción de datos. Piensa en un socket como un **número de extensión telefónica** y un **puerto de embarque** al mismo tiempo.



---

## 🔑 Tres Objetivos Fundamentales

### 1. Comunicación Remota (Inter-Máquinas)

A diferencia de los **Pipes** o **FIFOs**, que se limitan al mismo sistema operativo (o, en el caso de FIFOs, al mismo sistema de archivos), los sockets se construyen sobre protocolos de red como TCP/IP (Protocolo de Control de Transmisión/Protocolo de Internet).

* **Logro:** Conectar dos procesos (un **cliente** y un **servidor**) que están geográficamente o lógicamente separados.
* **Ejemplo:** Un navegador web (cliente) y un servidor web (servidor).

### 2. Comunicación Cliente-Servidor

Los sockets establecen el modelo fundamental de la interacción en red: el **Modelo Cliente-Servidor**.

* **Servidor:** Abre un socket, lo **liga** (bind) a una dirección IP y un **puerto** conocido, y se pone a la **escucha** (listen) de conexiones entrantes. Es el proceso que ofrece un servicio.
* **Cliente:** Crea un socket y usa la función **`connect()`** para iniciar la conexión con la dirección IP y el puerto del servidor. Es el proceso que solicita el servicio.

### 3. Flexibilidad y Control (TCP vs. UDP)

Los sockets ofrecen la flexibilidad de elegir el tipo de servicio que necesitamos, utilizando diferentes familias de protocolos:

* **TCP (Socket Stream):** Busca la **confiabilidad**. Garantiza que los datos lleguen en orden y sin pérdidas, manejando la retransmisión si es necesario (ideal para transferencia de archivos y web).
* **UDP (Socket Datagrama):** Busca la **velocidad**. Envía paquetes sin preocuparse por el orden o la garantía de llegada (ideal para *streaming* de video y juegos en tiempo real).

---

## 🗺️ Resumen de Uso

| Técnica | Alcance | Relación Procesos | Objetivo Primario |
| :--- | :--- | :--- | :--- |
| **Pipes/FIFOs** | Local (Misma Máquina) | Emparentados o No Emparentados | Comunicación de datos local de alto rendimiento. |
| **Sockets** | Remoto (Red) | Independientes | Comunicación a través de fronteras de la máquina, estableciendo servicios. |

## Buscar y eliminar un proceso en base a un puerto
Es comun que tengamos algun problema con el socket pero que este continue
esperando solicitudes de clientes por lo tanto mantenga ocupado un puerto,
podemos buscar el proceso asociado a un puerto como:

## lsfo -i: puerto
## sudo kill -9 pid