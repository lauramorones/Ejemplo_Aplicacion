/*
  Nombre del archivo: 		motor.h
  Dependencias: 			librerias.h
  Procesador: 				ESP32
  Placa: 					ESP32-PANTHER48
  Versión del programa: 	5.1
  Empresa: 					Espressif Systems
  Descripción: 				Define los prototipos de las funciones a utilizar para el carro robot (evitando la declaración implícita)
  Autores: 					Luis Aguilera, Victor Duarte, Laura Morones.
  Actualizado: 				05/2024
  *********************************************************************************************************************************************************************/
#define motor_H_
static const char *TAG = "motor";

extern esp_err_t init_motor(void);
extern void apagar(void);
extern void derecha(void);
extern void izquierda(void);
extern void retroceder(void);
extern void avanzar(void);
