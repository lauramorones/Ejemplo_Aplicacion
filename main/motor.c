/*
  Nombre del archivo: 		motor.c
  Dependencias: 			librerias.h, GPIO.h, motor.h
  Procesador: 				ESP32
  Placa: 					ESP32-PANTHER48
  Versión del programa: 	5.1
  Empresa: 					Espressif Systems
  Descripción: 				Implementación de las funciones a utilizar para el control de los motores.
  Autores: 					Luis Aguilera, Victor Duarte, Laura Morones.
  Actualizado: 				05/2024
  *****************************************************************************************************/

#include "../components/drivers/include/GPIO.h"
#include "../Librerias/librerias.h"
#include "../main/motor.h"

//GPIOS designados para el control de motores
#define enableRightMotor 22
#define rightMotorPin1 16
#define rightMotorPin2 17

#define enableLeftMotor 23
#define leftMotorPin1 18
#define leftMotorPin2 19


/**************************************************************************
Función: 	apagar
Resumen: 	Deshabilita los motores del carro (apaga).
Parámetro: 	Ninguno
Retorno: 	Ninguno.
*****************************************************************************/

void apagar(){

	 GPIO_Escribir(enableRightMotor,BAJO);
	 GPIO_Escribir(enableLeftMotor,BAJO);
   }

/**************************************************************************
Función: 	avanzar
Resumen: 	habilita los motores del carro y avanza.
Parámetro:  Ninguno
Retorno: 	Ninguno.
*****************************************************************************/
void avanzar (){

	 GPIO_Escribir(enableRightMotor, ALTO);
	 GPIO_Escribir(rightMotorPin1, ALTO);
	 GPIO_Escribir(rightMotorPin2, BAJO);

	 GPIO_Escribir(enableLeftMotor,ALTO);
	 GPIO_Escribir(leftMotorPin2, ALTO);
	 GPIO_Escribir(leftMotorPin1, BAJO);
}

/**************************************************************************
Función: 	retroceder
Resumen: 	Configura ambos lados de los motores para usar la reversa.
Parámetro:  Ninguno
Retorno: 	Ninguno.
*****************************************************************************/

void retroceder (){

	 GPIO_Escribir(enableRightMotor,ALTO);
	 GPIO_Escribir(rightMotorPin1, BAJO);
	 GPIO_Escribir(rightMotorPin2, ALTO);

	 GPIO_Escribir(enableLeftMotor,ALTO);
	 GPIO_Escribir(leftMotorPin2, BAJO);
	 GPIO_Escribir(leftMotorPin1, ALTO);
}

/**************************************************************************
Función: 	derecha
Resumen: 	Configura ambos lados de los motores para que pueda dar vuelta a la derecha.
Parámetro:  Ninguno
Retorno: 	Ninguno.
*****************************************************************************/
void derecha (){
	GPIO_Escribir(enableLeftMotor,ALTO);
	GPIO_Escribir(leftMotorPin2, ALTO);
	GPIO_Escribir(leftMotorPin1, BAJO);

	GPIO_Escribir(enableRightMotor,ALTO);
	GPIO_Escribir(rightMotorPin1, BAJO);
	GPIO_Escribir(rightMotorPin2, ALTO);
}

/******************************************************************************************
Función: 	izquierda
Resumen: 	Configura ambos lados de los motores para que pueda dar vuelta a la izquierda.
Parámetro:  Ninguno
Retorno: 	Ninguno.
******************************************************************************************/

void izquierda (){
	GPIO_Escribir(enableRightMotor, ALTO);
    GPIO_Escribir(rightMotorPin1, ALTO);
    GPIO_Escribir(rightMotorPin2, BAJO);

	GPIO_Escribir(enableLeftMotor,ALTO);
	GPIO_Escribir(leftMotorPin2, BAJO);
	GPIO_Escribir(leftMotorPin1, ALTO);
}


/****************************************************************************************************************************
Función: 	init_motor
Resumen: 	Configura los GPIO designados para el control de los motores como salidas y regresa si la operación fue exitosa
Parámetro:  Ninguno
Retorno: 	esp_err_t
****************************************************************************************************************************/
esp_err_t init_motor(void)
{
	GPIO_Salida(enableRightMotor);
	GPIO_Salida(rightMotorPin1);
	GPIO_Salida(rightMotorPin2);

	GPIO_Salida(enableLeftMotor);
	GPIO_Salida(leftMotorPin1);
	GPIO_Salida(leftMotorPin2);

    apagar();

    ESP_LOGI(TAG, "init motor completed");
    return ESP_OK;
}

