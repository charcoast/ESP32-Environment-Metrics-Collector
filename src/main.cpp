/*
  Based on Wifi secure connection example for ESP32
  Running on TLS 1.2 using mbedTLS
  Suporting the following chipersuites:
  "TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384","TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384","TLS_DHE_RSA_WITH_AES_256_GCM_SHA384","TLS_ECDHE_ECDSA_WITH_AES_256_CCM","TLS_DHE_RSA_WITH_AES_256_CCM","TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384","TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384","TLS_DHE_RSA_WITH_AES_256_CBC_SHA256","TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA","TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA","TLS_DHE_RSA_WITH_AES_256_CBC_SHA","TLS_ECDHE_ECDSA_WITH_AES_256_CCM_8","TLS_DHE_RSA_WITH_AES_256_CCM_8","TLS_ECDHE_ECDSA_WITH_CAMELLIA_256_GCM_SHA384","TLS_ECDHE_RSA_WITH_CAMELLIA_256_GCM_SHA384","TLS_DHE_RSA_WITH_CAMELLIA_256_GCM_SHA384","TLS_ECDHE_ECDSA_WITH_CAMELLIA_256_CBC_SHA384","TLS_ECDHE_RSA_WITH_CAMELLIA_256_CBC_SHA384","TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA256","TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA","TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256","TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256","TLS_DHE_RSA_WITH_AES_128_GCM_SHA256","TLS_ECDHE_ECDSA_WITH_AES_128_CCM","TLS_DHE_RSA_WITH_AES_128_CCM","TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256","TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256","TLS_DHE_RSA_WITH_AES_128_CBC_SHA256","TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA","TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA","TLS_DHE_RSA_WITH_AES_128_CBC_SHA","TLS_ECDHE_ECDSA_WITH_AES_128_CCM_8","TLS_DHE_RSA_WITH_AES_128_CCM_8","TLS_ECDHE_ECDSA_WITH_CAMELLIA_128_GCM_SHA256","TLS_ECDHE_RSA_WITH_CAMELLIA_128_GCM_SHA256","TLS_DHE_RSA_WITH_CAMELLIA_128_GCM_SHA256","TLS_ECDHE_ECDSA_WITH_CAMELLIA_128_CBC_SHA256","TLS_ECDHE_RSA_WITH_CAMELLIA_128_CBC_SHA256","TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA256","TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA","TLS_ECDHE_ECDSA_WITH_3DES_EDE_CBC_SHA","TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA","TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA","TLS_DHE_PSK_WITH_AES_256_GCM_SHA384","TLS_DHE_PSK_WITH_AES_256_CCM","TLS_ECDHE_PSK_WITH_AES_256_CBC_SHA384","TLS_DHE_PSK_WITH_AES_256_CBC_SHA384","TLS_ECDHE_PSK_WITH_AES_256_CBC_SHA","TLS_DHE_PSK_WITH_AES_256_CBC_SHA","TLS_DHE_PSK_WITH_CAMELLIA_256_GCM_SHA384","TLS_ECDHE_PSK_WITH_CAMELLIA_256_CBC_SHA384","TLS_DHE_PSK_WITH_CAMELLIA_256_CBC_SHA384","TLS_PSK_DHE_WITH_AES_256_CCM_8","TLS_DHE_PSK_WITH_AES_128_GCM_SHA256","TLS_DHE_PSK_WITH_AES_128_CCM","TLS_ECDHE_PSK_WITH_AES_128_CBC_SHA256","TLS_DHE_PSK_WITH_AES_128_CBC_SHA256","TLS_ECDHE_PSK_WITH_AES_128_CBC_SHA","TLS_DHE_PSK_WITH_AES_128_CBC_SHA","TLS_DHE_PSK_WITH_CAMELLIA_128_GCM_SHA256","TLS_DHE_PSK_WITH_CAMELLIA_128_CBC_SHA256","TLS_ECDHE_PSK_WITH_CAMELLIA_128_CBC_SHA256","TLS_PSK_DHE_WITH_AES_128_CCM_8","TLS_ECDHE_PSK_WITH_3DES_EDE_CBC_SHA","TLS_DHE_PSK_WITH_3DES_EDE_CBC_SHA","TLS_RSA_WITH_AES_256_GCM_SHA384","TLS_RSA_WITH_AES_256_CCM","TLS_RSA_WITH_AES_256_CBC_SHA256","TLS_RSA_WITH_AES_256_CBC_SHA","TLS_ECDH_RSA_WITH_AES_256_GCM_SHA384","TLS_ECDH_RSA_WITH_AES_256_CBC_SHA384","TLS_ECDH_RSA_WITH_AES_256_CBC_SHA","TLS_ECDH_ECDSA_WITH_AES_256_GCM_SHA384","TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA384","TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA","TLS_RSA_WITH_AES_256_CCM_8","TLS_RSA_WITH_CAMELLIA_256_GCM_SHA384","TLS_RSA_WITH_CAMELLIA_256_CBC_SHA256","TLS_RSA_WITH_CAMELLIA_256_CBC_SHA","TLS_ECDH_RSA_WITH_CAMELLIA_256_GCM_SHA384","TLS_ECDH_RSA_WITH_CAMELLIA_256_CBC_SHA384","TLS_ECDH_ECDSA_WITH_CAMELLIA_256_GCM_SHA384","TLS_ECDH_ECDSA_WITH_CAMELLIA_256_CBC_SHA384","TLS_RSA_WITH_AES_128_GCM_SHA256","TLS_RSA_WITH_AES_128_CCM","TLS_RSA_WITH_AES_128_CBC_SHA256","TLS_RSA_WITH_AES_128_CBC_SHA","TLS_ECDH_RSA_WITH_AES_128_GCM_SHA256","TLS_ECDH_RSA_WITH_AES_128_CBC_SHA256","TLS_ECDH_RSA_WITH_AES_128_CBC_SHA","TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256","TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256","TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA","TLS_RSA_WITH_AES_128_CCM_8","TLS_RSA_WITH_CAMELLIA_128_GCM_SHA256","TLS_RSA_WITH_CAMELLIA_128_CBC_SHA256","TLS_RSA_WITH_CAMELLIA_128_CBC_SHA","TLS_ECDH_RSA_WITH_CAMELLIA_128_GCM_SHA256","TLS_ECDH_RSA_WITH_CAMELLIA_128_CBC_SHA256","TLS_ECDH_ECDSA_WITH_CAMELLIA_128_GCM_SHA256","TLS_ECDH_ECDSA_WITH_CAMELLIA_128_CBC_SHA256","TLS_RSA_WITH_3DES_EDE_CBC_SHA","TLS_ECDH_RSA_WITH_3DES_EDE_CBC_SHA","TLS_ECDH_ECDSA_WITH_3DES_EDE_CBC_SHA","TLS_RSA_PSK_WITH_AES_256_GCM_SHA384","TLS_RSA_PSK_WITH_AES_256_CBC_SHA384","TLS_RSA_PSK_WITH_AES_256_CBC_SHA","TLS_RSA_PSK_WITH_CAMELLIA_256_GCM_SHA384","TLS_RSA_PSK_WITH_CAMELLIA_256_CBC_SHA384","TLS_RSA_PSK_WITH_AES_128_GCM_SHA256","TLS_RSA_PSK_WITH_AES_128_CBC_SHA256","TLS_RSA_PSK_WITH_AES_128_CBC_SHA","TLS_RSA_PSK_WITH_CAMELLIA_128_GCM_SHA256","TLS_RSA_PSK_WITH_CAMELLIA_128_CBC_SHA256","TLS_RSA_PSK_WITH_3DES_EDE_CBC_SHA","TLS_PSK_WITH_AES_256_GCM_SHA384","TLS_PSK_WITH_AES_256_CCM","TLS_PSK_WITH_AES_256_CBC_SHA384","TLS_PSK_WITH_AES_256_CBC_SHA","TLS_PSK_WITH_CAMELLIA_256_GCM_SHA384","TLS_PSK_WITH_CAMELLIA_256_CBC_SHA384","TLS_PSK_WITH_AES_256_CCM_8","TLS_PSK_WITH_AES_128_GCM_SHA256","TLS_PSK_WITH_AES_128_CCM","TLS_PSK_WITH_AES_128_CBC_SHA256","TLS_PSK_WITH_AES_128_CBC_SHA","TLS_PSK_WITH_CAMELLIA_128_GCM_SHA256","TLS_PSK_WITH_CAMELLIA_128_CBC_SHA256","TLS_PSK_WITH_AES_128_CCM_8","TLS_PSK_WITH_3DES_EDE_CBC_SHA","TLS_EMPTY_RENEGOTIATION_INFO_SCSV"]
  2017 - Evandro Copercini - Apache 2.0 License.
*/

#include <WiFiClientSecure.h>

const char* ssid     = "";     // SSID da rede que pretende se conectar
const char* password = ""; // Senha da rede que pretende se conectar

const char*  server = "augusto.world";  // URL do servidor (usado para conexão e resolução de dns)


const char* test_root_ca= \
     "-----BEGIN CERTIFICATE-----\n" \
     "MIIEkjCCA3qgAwIBAgIQCgFBQgAAAVOFc2oLheynCDANBgkqhkiG9w0BAQsFADA/\n" \
     "MSQwIgYDVQQKExtEaWdpdGFsIFNpZ25hdHVyZSBUcnVzdCBDby4xFzAVBgNVBAMT\n" \
     "DkRTVCBSb290IENBIFgzMB4XDTE2MDMxNzE2NDA0NloXDTIxMDMxNzE2NDA0Nlow\n" \
     "SjELMAkGA1UEBhMCVVMxFjAUBgNVBAoTDUxldCdzIEVuY3J5cHQxIzAhBgNVBAMT\n" \
     "GkxldCdzIEVuY3J5cHQgQXV0aG9yaXR5IFgzMIIBIjANBgkqhkiG9w0BAQEFAAOC\n" \
     "AQ8AMIIBCgKCAQEAnNMM8FrlLke3cl03g7NoYzDq1zUmGSXhvb418XCSL7e4S0EF\n" \
     "q6meNQhY7LEqxGiHC6PjdeTm86dicbp5gWAf15Gan/PQeGdxyGkOlZHP/uaZ6WA8\n" \
     "SMx+yk13EiSdRxta67nsHjcAHJyse6cF6s5K671B5TaYucv9bTyWaN8jKkKQDIZ0\n" \
     "Z8h/pZq4UmEUEz9l6YKHy9v6Dlb2honzhT+Xhq+w3Brvaw2VFn3EK6BlspkENnWA\n" \
     "a6xK8xuQSXgvopZPKiAlKQTGdMDQMc2PMTiVFrqoM7hD8bEfwzB/onkxEz0tNvjj\n" \
     "/PIzark5McWvxI0NHWQWM6r6hCm21AvA2H3DkwIDAQABo4IBfTCCAXkwEgYDVR0T\n" \
     "AQH/BAgwBgEB/wIBADAOBgNVHQ8BAf8EBAMCAYYwfwYIKwYBBQUHAQEEczBxMDIG\n" \
     "CCsGAQUFBzABhiZodHRwOi8vaXNyZy50cnVzdGlkLm9jc3AuaWRlbnRydXN0LmNv\n" \
     "bTA7BggrBgEFBQcwAoYvaHR0cDovL2FwcHMuaWRlbnRydXN0LmNvbS9yb290cy9k\n" \
     "c3Ryb290Y2F4My5wN2MwHwYDVR0jBBgwFoAUxKexpHsscfrb4UuQdf/EFWCFiRAw\n" \
     "VAYDVR0gBE0wSzAIBgZngQwBAgEwPwYLKwYBBAGC3xMBAQEwMDAuBggrBgEFBQcC\n" \
     "ARYiaHR0cDovL2Nwcy5yb290LXgxLmxldHNlbmNyeXB0Lm9yZzA8BgNVHR8ENTAz\n" \
     "MDGgL6AthitodHRwOi8vY3JsLmlkZW50cnVzdC5jb20vRFNUUk9PVENBWDNDUkwu\n" \
     "Y3JsMB0GA1UdDgQWBBSoSmpjBH3duubRObemRWXv86jsoTANBgkqhkiG9w0BAQsF\n" \
     "AAOCAQEA3TPXEfNjWDjdGBX7CVW+dla5cEilaUcne8IkCJLxWh9KEik3JHRRHGJo\n" \
     "uM2VcGfl96S8TihRzZvoroed6ti6WqEBmtzw3Wodatg+VyOeph4EYpr/1wXKtx8/\n" \
     "wApIvJSwtmVi4MFU5aMqrSDE6ea73Mj2tcMyo5jMd6jmeWUHK8so/joWUoHOUgwu\n" \
     "X4Po1QYz+3dszkDqMp4fklxBwXRsW10KXzPMTZ+sOPAveyxindmjkW8lGy+QsRlG\n" \
     "PfZ+G6Z6h7mjem0Y+iWlkYcV4PIWL1iwBi8saCbGS5jN2p8M+X+Q7UNKEkROb3N6\n" \
     "KOqkqm57TH2H3eDJAkSnh6/DNFu0Qg==\n" \
     "-----END CERTIFICATE-----\n";


WiFiClientSecure client;

void setup() {
  //Inicializa o serial
  Serial.begin(115200);
  WiFi.disconnect(true);
  delay(3000);

  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);

  //DO NOT TOUCH
    //  This is here to force the ESP32 to reset the WiFi and initialise correctly.
 //   Serial.print("WIFI status = ");
  //  Serial.println(WiFi.getMode());
  // WiFi.disconnect(true);
   // delay(3000);
   // WiFi.mode(WIFI_STA);
   // delay(1000);
    //Serial.print("WIFI status = ");
    //Serial.println(WiFi.getMode());
    // End silly stuff !!!

  WiFi.begin(ssid, password);

  // Tenta se conectar na rede wireless
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    // Aguarda 1 segundo antes de tentar novamente
    delay(1000);
  }

  Serial.print("Connected to ");
  Serial.println(ssid);

  client.setCACert(test_root_ca);


  Serial.println("\nStarting connection to server...");
  if (!client.connect(server, 443))
    Serial.println("Connection failed!");
  else {
    Serial.println("Connected to server!");
    // Realiza a requisição HTTP:
    client.println("GET https://www.augusto.world/aplantica/api/ping HTTP/1.1");
    client.println("Host: www.augusto.world");
    client.println("Connection: close");
    client.println();

    while (client.connected()) {
      String line = client.readStringUntil('\n');
      if (line == "\r") {
        Serial.println("headers received");
        break;
      }
    }
    // Se estiver recebendo bytes do servidor,
    // vai ler e imprimir
    while (client.available()) {
      char c = client.read();
      Serial.write(c);
    }

    client.stop();
  }
}

void loop() {
  // Não faz nada
}