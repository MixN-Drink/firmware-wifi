# firmware-wifi

# Endpoints
<table>
<tr>
<th>Método</th>
<th>URL</th>
<th>Body</th>
<th>Descripción</th>
</tr>
<tr>
<td>

`GET`
</td>
<td>

`/ping`
</td>
<td></td>
<td>Comprueba que el servidor esté funcionando correctamente</td>
<tr>

<tr>
<td>

`PUT`
</td>
<td>

`/config/wifi`
</td>
<td>

```json
{"ssid":"your_ssid","password":"your_password"}
```
</td>
<td>Cambia las credenciales de la conexión WIFI</td>
<tr>

<tr>
<td>

`POST`
</td>
<td>

`/prepare`
</td>
<td>

```json
{
  "slots":[
    {"slot":3,"percentage":70},
    {"slot":0,"percentage":30},
    {"slot":1,"percentage":0},
    {"slot":2,"percentage":0}
  ]
}
```
</td>
<td>Encola los slots para surtir en órden con sus respectivos porcentajes</td>
<tr>
<tr>
<td>

`POST`
</td>
<td>

`/stop`
</td>
<td>
</td>
<td>Detiene los motores y vacía la cola</td>
<tr>
<tr>
<td>

`POST`
</td>
<td>

`/calibration/start`
</td>
<td>
</td>
<td>Inicia la calibración del vaso</td>
<tr>
<tr>
<td>

`POST`
</td>
<td>

`/calibration/end`
</td>
<td>
</td>
<td>Termina la calibración del vaso</td>
<tr>
</table>