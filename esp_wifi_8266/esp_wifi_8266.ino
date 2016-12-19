/**
 * @example ConnectWiFi.ino
 * @brief The ConnectWiFi demo of library WeeESP8266. 
 * @author Wu Pengfei<pengfei.wu@itead.cc> 
 * @date 2015.03
 * 
 * @par Copyright:
 * Copyright (c) 2015 ITEAD Intelligent Systems Co., Ltd. \n\n
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version. \n\n
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "ESP8266.h"


#define SSID        "IncaElmasTeknoloji"
#define PASSWORD    "ElmasTek28"

SoftwareSerial mySerial(3, 2); // uno sw RX(pin3) --> esp8266 TX, uno sw TX(pin2) --> esp8266 RX

ESP8266 wifi(mySerial);

const static char pubkey[] = "pub-c-e2ee5a1d-a8cc-4f66-8d66-624a93955d01";
const static char subkey[] = "sub-c-fa790632-c47e-11e6-8164-0619f8945a4f";
const static char channel[] = "hello_world";

void setup(void)
{
  //ESP8266 wifi(mySerial, 115200);
    Serial.begin(9600);
    Serial.print("setup begin\r\n");

    Serial.print("FW Version: ");
    Serial.println(wifi.getVersion().c_str());
    
    
    if (wifi.setOprToStation()) {
        Serial.print("to station ok\r\n");
    } else {
        Serial.print("to station err\r\n");
    }

    if (wifi.joinAP(SSID, PASSWORD)) {
        Serial.print("Join AP success\r\n");
        Serial.print("IP: ");       
        Serial.println(wifi.getLocalIP().c_str());
    } else {
        Serial.print("Join AP failure\r\n");
    }
    
    Serial.print("setup end\r\n");
}

void loop(void)
{
   
   char msg[] = "\"Yo!\"";
   int length = 0;
   String data ="{\"protocol\":\"v2\"}";
   length = data.length();
   
}

