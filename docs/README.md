# Cómo funciona

El microcontrolador trata de conectarse a la red WiFi guardada en su memoria EEPROM. En caso de no poder, crea una red WiFi (Access Point) con el nombre `MixNDrink`.
Para poder enviarle peticiones HTTP se debe estar en la misma red WiFi que en la que se encuentra el microcontrolador, por lo que si este crea su propia red el dispositivo con el cual se desean enviar las peticiones debe estar conectado a la misma.

---

# Requisitos y configuración

Para poder enviar peticiones desde una computadora (PC, Mac o Linux) es recomendable usar la aplicación [Postman](https://www.postman.com/downloads/).
Al abrir la aplicación se debe importar (Menu > File > Import ó Ctrl + O) y seleccionar el archivo `.json` dentro de la carpeta `docs/postman` de este repositorio.

---

# Flujo paso a paso
1. El microcontrolador intenta conectarse a la red WiFi
2. Si falla, el microcontrolador crea su propia red WiFi
3. El microcontrolador muestra por el puerto serie la IP asignada
4. En caso de que el microcontrolador haya creado su red:
    1. Desde Postman enviar la peticion de [configuración del WiFi](#configurar-wifi) con las credenciales de la red WiFi a la que se desea conectar el microcontrolador.
    2. Reiniciar el microcontrolador.
5. Enviar la petición de [comprobación del estado](#compobación-del-estado) y verificar que la respuesta sea la esperada
6. Enviar las peticiones de [preparar trago](#preparar-trago) que se deseen

---

# Peticiones HTTP
## **Compobación del estado**
**Método:** `GET`  
**Ruta:** `/ping`  
**Descripción:** Comprueba que el servidor esté funcionando correctamente  
**Respuesta:** `200 (OK): pong`  

## **Configurar WiFi**
**Método:** `PUT`  
**Ruta:** `/config/wifi`  
**Descripción:** Reemplaza las credenciales para conectarse a la red WiFi.   
**Respuesta:** `200 (OK): WiFi credentials saved`  
**Cuerpo:**
```json
{
    "ssid": "nombre-de-la-red-wifi",
    "password": "contrasenia-de-la-red-wifi"
}
```

## **Preparar trago**
**Método:** `POST`  
**Ruta:** `/prepare`  
**Descripción:** Envía los comandos para surtir la cantidad deseada de cada bebida en órden.  
**Respuesta:** `200 (OK): Preparing`  
**Cuerpo:**
```json
{
    "slots": [ // Slots ordenados como se desea surtir
        {
            "slot": 1, // Número de slot
            "percentage": 30 // Porcentaje a surtir en ese slot
        },
        {
            "slot": 3,
            "percentage": 70
        },
        {
            "slot": 2,
            "percentage": 0
        },
        {
            "slot": 0,
            "percentage": 0
        }
    ]
}
```
