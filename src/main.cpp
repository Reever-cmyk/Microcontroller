#include <Arduino.h>
#include <heltec.h>
#include <WiFi.h>
#include "oled/OLEDDisplayUi.h"
#include "images.h"
#include "WiFiCred.h"
#include "NetScan.h"
#include "pthread.h"

#define BAND 868E6

#define DEMO_DURATION 1000

typedef void (*Demo)(void);

extern Heltec_ESP32 Heltec;

OLEDDisplayUi ui(Heltec.display);

String SSID[5];

void *printThreadId(void *threadid) {
   Serial.println((int)threadid);
}

void wifi_connect()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }
}

/*
void net_scan(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y)
{
    int n = WiFi.scanNetworks();
    display->drawString(0, 0, String(n - 1));
    display->drawString(14, 0, "Netzwerke gefunden:");

    for (int j = 0; j < n - 1; j++)
    {
        display->drawString(x, y + (j + 1) * 9, (String)(j + 1));
        display->drawString(x + 6, y + (j + 1) * 9, ":");
        display->drawString(x + 12, y + (j + 1) * 9, (String)(WiFi.SSID(j)));
        display->drawString(x + 90, y + (j + 1) * 9, " (");
        display->drawString(x + 98, y + (j + 1) * 9, (String)(WiFi.RSSI(j)));
        display->drawString(x + 114, y + (j + 1) * 9, ")");
    }
}
*/

void print_wifi(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y)
{
    String ip = WiFi.localIP().toString();
    String mac = WiFi.macAddress();
    long rssi = WiFi.RSSI();
    display->drawString(x, y, "IP Addresse:");
    display->drawString(x, y + 10, ip);
    display->drawString(x, y + 20, "MAC Addresse:");
    display->drawString(x, y + 30, String(mac));
    display->drawString(x, y + 40, "RSSI:");
    display->drawString(x + 50, y + 40, String(rssi));
}

void msOverlay(OLEDDisplay *display, OLEDDisplayUiState *state)
{
    display->setTextAlignment(TEXT_ALIGN_RIGHT);
    display->setFont(ArialMT_Plain_10);
    display->drawString(128, 0, String(millis()));
}

void drawFrame3(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y)
{
    display->drawXbm(x, y + 5, HelTec_LOGO_width, HelTec_LOGO_height, HelTec_LOGO_bits);
}

static FrameCallback frames[] = {print_wifi, net_scan, drawFrame3};
static int frameCount = 3;

void uiSetup()
{

    ui.setTargetFPS(30);
    ui.setActiveSymbol(activeSymbol);
    ui.setInactiveSymbol(inactiveSymbol);
    ui.setIndicatorPosition(BOTTOM);
    ui.setIndicatorDirection(LEFT_RIGHT);
    ui.setFrameAnimation(SLIDE_LEFT);
    ui.setFrames(frames, frameCount);
    ui.init();
    Heltec.display->flipScreenVertically();
}

void setup(void)
{
    Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, true /*Serial Enable*/, false /*LoRa use PABOOST*/, BAND /*LoRa RF working band*/);
    uiSetup();
    WiFi.disconnect();
    delay(100);
    wifi_connect();
    pthread_t threads[4];
   int returnValue;
 
   for( int i = 0; i< 4; i++ ) {
 
      returnValue = pthread_create(&threads[i], NULL, printThreadId, (void *)i);
 
      if (returnValue) {
         Serial.println("An error has occurred");
      }
   }
}

void loop(void)
{
    int remainingTimeBudget = ui.update();

    String SSID[5] = WiFi.SSID();
    //long RSI[5] = WiFi.RSSI();
    if (remainingTimeBudget > 0)
    {
        delay(remainingTimeBudget);
    }
}
this is my main code test