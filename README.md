# Este repositorio corresponde al TP 1 - Sistemas Reactivos del grupo 2 de la materia RTOS II

## Los integrantes del grupo son Agustín Navari y Juan Pablo Touron

El repositorio contiene el proyecto para compilar en STM32Cube IDE. El proyecto cuenta con:

- Una tarea para el botón
- Un objeto activo de UI
- Un objeto activo para cada LED

Cada objeto activo contiene su propia cola de mensajes y un handler a la tarea que ejecuta. Además, los objetos activos de LED tienen un color asociado.

El proyecto se realizó con una placa STM32F446RE. Se utilizaron el pulsador y el LED integrados en la placa por lo que no pueden verse distintos LEDs encendidos de
acuerdo al tiempo de presión del botón. Pero si se muestra por mensaje en consola, qué led está prendido y qué tipo de pulsación se realizó. El tiempo de encendido
del LED está hardcodeado en 1 segundo. Podría agregarse un parámetro al mensaje enviado de la UI al LED para hacer el código más escalable.

Link al video de evidencia de funcionamiento: https://drive.google.com/file/d/1BawWnAkhqpGrKg1L9BjTYjb_Z7r5bL1H/view?usp=drive_link
