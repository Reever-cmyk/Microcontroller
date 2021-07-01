void net_scan(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y,SSID,RSSI)
{
    int n = WiFi.scanNetworks();
    display->drawString(0, 0, String(n));
    display->drawString(14, 0, "Netzwerke gefunden:");

    display->drawString(x, y + 9, (String)(1));
    display->drawString(x + 6, y + 9, ":");
    display->drawString(x + 12, y + 9, (String)(SSID));
    display->drawString(x + 90, y + 9, " (");
    display->drawString(x + 98, y + 9, (String)(RSSI));
    display->drawString(x + 114, y + 9, ")");

    display->drawString(x, y + 18, (String)(2));
    display->drawString(x + 6, y + 18, ":");
    display->drawString(x + 12, y + 18, (String)(SSID));
    display->drawString(x + 90, y + 18, " (");
    display->drawString(x + 98, y + 18, (String)(RSSI));
    display->drawString(x + 114, y + 18, ")");

    display->drawString(x, y + 27, (String)(3));
    display->drawString(x + 6, y + 27, ":");
    display->drawString(x + 12, y + 27, (String)(SSID));
    display->drawString(x + 90, y + 27, " (");
    display->drawString(x + 98, y + 27, (String)(RSSI));
    display->drawString(x + 114, y + 27, ")");

    display->drawString(x, y + 36, (String)(4));
    display->drawString(x + 6, y + 36, ":");
    display->drawString(x + 12, y + 36, (String)(SSID));
    display->drawString(x + 90, y + 36, " (");
    display->drawString(x + 98, y + 36, (String)(RSSI));
    display->drawString(x + 114, y + 36, ")");
}
