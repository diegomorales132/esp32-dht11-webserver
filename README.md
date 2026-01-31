# DHT11 Environmental Sensing & Web Hosting

Project by: Diego Morales | Date: 1/31/26
This project is my first deep dive into gathering data from the physical world and serving it over a network. I used a DHT11 sensor to pull temperature and humidity data and hosted it on a local web server using the ESP32.

The Build Process:
Setting up this project involved researching how to bridge hardware sensors with the network. 

* Libraries: I learned that the code won't compile without the DHT.h library and the Adafruit Unified Sensor dependency. This was my first lesson in knowing what library dependencies in the Arduino IDE are and why they are needed.
* WiFi & Web Server: I spent a lot of time understanding the WiFi.h library. The most challenging part was learning how to wait for a connection and then give very basic HTML code to a browser. I focused on making a simple STA connection to my home router to send data to my computer, as it easiest thing to understand in my situation. In the end I followed a template online and implemented it into my code, it took a lot of trial and error, a big part of that time was me not remembering the SSID of my router since it had changed and it wasn't the same as it was shown in the back, had to ask my parents what it was. 

Hardware Used:
* Microcontroller: ESP32 
* Sensor: DHT11 
* Logic Voltage: 3.3V - Verified with a multimeter

Decisions regarding the wifi code
* Simplified Server Logic: I chose to use a linear 'while(client.connected())' loop to handle browser requests. This made the code easier to debug and ensures the data is sent only when I actually visit the IP address.
* Manual Refreshing: I used an HTML refresh link that refreshes the data the sensor is sending. This made the code easier to implement and makes sure that the numbers of the sensor data are being shown in my computer when I click the link.
* Some error proofing I implemented: I included `isnan()` checks to make sure that if a wire comes loose, the website displays a "Sensor Error" instead of just showing zero or crashing, this way I wouldn't have to worry if it was something else and trying to look up some errors in the wifi part of the code when it could just the wiring being faulty.

What I learned: 
The biggest takeaway was how data from the sensor moved to my computer
---
Next Step: Now that I can host a basic website, I plan to move to some motor projects. My goal is to create a web-based control panel with buttons that can drive a mini RC car while livestreams to a local server using an ESP32-CAM.
