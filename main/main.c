/*
  Nombre del archivo: 		main.c
  Dependencias: 			librerias.h, motor.h
  Procesador: 				ESP32
  Placa: 					ESP32-PANTHER48
  Versión del programa: 	5.1
  Empresa: 					Espressif Systems
  Descripción: 				Implementación de las funciones necesarias para controlar el
  	  	  	  	  	  	  	movimiento de un vehículo mediante el uso de motores. Se manejan
  	  	  	  	  	  	  	diversas acciones como avanzar,retroceder, girar a la izquierda,
  	  	  	  	  	  	  	girar a la derecha y detenerse, las cuales son activadas a través
  	  	  	  	  	  	  	de solicitudes HTTP recibidas por el servidor web integrado en el
  	  	  	  	  	  	  	dispositivo.
  Autores: 					Luis Aguilera, Victor Duarte, Laura Morones.
  Actualizado: 				05/2024
  *************************************************************************************/

#include "../Librerias/librerias.h"
#include "../main/motor.h"

esp_err_t init_motor(void);

/* An HTTP GET handler */
static esp_err_t root_get_handler(httpd_req_t *req)
{
    extern unsigned char view_start[] asm("_binary_view_html_start");
    extern unsigned char view_end[] asm("_binary_view_html_end");
    size_t view_len = view_end - view_start;
    char viewHtml[view_len];

    memcpy(viewHtml, view_start, view_len);
    ESP_LOGI(TAG, "URI: %s", req->uri);

    if (strcmp(req->uri, "/?action=up") == 0)
    {
    	 apagar();
    	 avanzar();
    }
    else if (strcmp(req->uri, "/?action=down") == 0)
    {
    	apagar();
    	retroceder();
    }
    else if (strcmp(req->uri, "/?action=left") == 0)
    {
    	apagar();
   		izquierda();
    }
    else if (strcmp(req->uri, "/?action=right") == 0)
    {
    	apagar();
    	derecha();
    }

    else if (strcmp(req->uri, "/?action=stop") == 0)
      {
    	apagar();
      }

    httpd_resp_set_type(req, "text/html");
    httpd_resp_send(req, viewHtml, view_len);
    return ESP_OK;
}

static const httpd_uri_t root = {
    .uri = "/",
    .method = HTTP_GET,
    .handler = root_get_handler};

static httpd_handle_t start_webserver(void)
{
    httpd_handle_t server = NULL;

    // Start the httpd server
    ESP_LOGI(TAG, "Starting server");

    httpd_ssl_config_t conf = HTTPD_SSL_CONFIG_DEFAULT();
    conf.transport_mode = HTTPD_SSL_TRANSPORT_INSECURE;
    esp_err_t ret = httpd_ssl_start(&server, &conf);
    if (ESP_OK != ret)
    {
        ESP_LOGI(TAG, "Error starting server!");
        return NULL;
    }

    // Set URI handlers
    ESP_LOGI(TAG, "Registering URI handlers");
    httpd_register_uri_handler(server, &root);
    return server;
}

static void stop_webserver(httpd_handle_t server)
{
    // Stop the httpd server
    httpd_ssl_stop(server);
}

static void disconnect_handler(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data)
{
    httpd_handle_t *server = (httpd_handle_t *)arg;
    if (*server)
    {
        stop_webserver(*server);
        *server = NULL;
    }
}

static void connect_handler(void *arg, esp_event_base_t event_base,
                            int32_t event_id, void *event_data)
{
    httpd_handle_t *server = (httpd_handle_t *)arg;
    if (*server == NULL)
    {
        *server = start_webserver();
    }
}


void app_main(void)
{
    ESP_ERROR_CHECK(init_motor());
    static httpd_handle_t server = NULL;
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &connect_handler, &server));
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &disconnect_handler, &server));
    ESP_ERROR_CHECK(example_connect());
}
