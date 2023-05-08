# Se desarrolla una simulación en WOKWI donde se demuestra la conexión del ESP32 tanto para topicos de Temperatura y humedad, como para publicar en el MQTT y comandar un LED

## Enlace de la simulación: https://wokwi.com/projects/364173487063806977

#  Configuración necesaria para visualizar los mensajes MQTT publicados por el cliente MQTT.

##  1) Abrir la URL descripta y cliquear el boton conectar
     http://www.hivemq.com/demos/websocket-client/

## 2) Adicione los tópicos que el ESP32 usa:
     topic_on_off_led/#
     topic_sensor_temperature/#
     topic_sensor_humidity/#

## 3) Publicar en el topico topic_on_off_led con un mensaje 1 ó 0
     para prender o apagar el LED"
##  IMPORTANTE: es necesario ejecutar Wokwi Gateway y habilitar la opción "Enable Private Wokwi IoT Gateway" a través de la tecla de atajo F1 en el editor de código.

##  Para descargar Wokwi IoT Network Gateway aceda al siguiente link: https://github.com/wokwi/wokwigw/releases/ o descargue a continuación:
[wokwigw_v1.1.0_Windows_64bit.zip](https://github.com/ISPC-TST-ARQUITECTURA-Y-CONECTIVIDAD/tarea3-grupo-4/files/11424774/wokwigw_v1.1.0_Windows_64bit.zip)
