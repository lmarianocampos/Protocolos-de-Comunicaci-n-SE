# Control de Motor paso a paso con freeRTOS y sAPI. 

Aclaraciones del proyecto:
Comandos: 
la aplicación identifica como comando hasta que detecta un '\n'.
El eje del motor gira un paso (7.5°) cada  vez que recibe un pulso.
ME\n : habilita el motor 
MD\n :deshabilita el motor
MLP0010: El eje del motor gira a la izquierda  10 pasos 
MRP0015: El eje del motor gira a la derecha  10 pasos 
MLA0045: El eje del motor gira a la izquierda  45°
MRA0090: El eje del motor gira a la derecha 90°  

Led Amarillo: su parpadeo representa  el tren de pulso
Led Rojo: encendido-> Motor habilitado  Apagado -> motor Deshabilitados 
Led verde: encendido-> Sentido de giro Derecho Apagado -> Sentido de giro izquiero 

Enlace del video
https://youtu.be/Ua47b0WDjeo


