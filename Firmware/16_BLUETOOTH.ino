void printDeviceAddress()
{
  const uint8_t* point = esp_bt_dev_get_address();
  String MAC_CONNECT;
  String MAC_CURR;
  for (int i = 0; i < 6; i++)
  {
    MAC_CURR = String(point[i], HEX);
    MAC_CURR.toUpperCase();
    if (MAC_CURR.length() == 1) MAC_CONNECT += "0" + MAC_CURR;
    else MAC_CONNECT += MAC_CURR;
    if (i < 5) MAC_CONNECT += ":";
  }
  Serial.println(MAC_CONNECT);
}

void callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
  if (event == ESP_SPP_SRV_OPEN_EVT)
  {
    String mess = "M";
    mess.concat(mode);
    Bluetooth.print(mess);
    Bluetooth.write('>');
    connectBL = true;
    drawBmp("/BL_ico.bmp", 192, 2);
    Serial.println("Client CONNECTED");
    delay(100);
  }
  if (event == 27)
  {
    tft.fillRect(192, 2, 12, 16, HEADER);
    connectBL = false;
    Serial.println("Client DISCONNECTED");
  }
}
