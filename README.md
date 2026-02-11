🤖 ESP8266 OLED Desk Robot

A cute, animated desk robot built using an ESP8266 development board with a 0.96” SSD1306 OLED display.
The OLED acts as the robot’s expressive face, displaying blinking eyes and multiple emotions.

This project combines embedded programming, animation logic, and simple enclosure design to create a compact desktop companion.

✨ Features

🤖 Animated robot face

👀 Natural blinking effect

😊 Multiple expressions:

Happy

Neutral

Sleepy

Surprised

Angry

🎲 Random mood switching

🖥 Smooth SSD1306 graphics rendering

🧱 3D printable enclosure (OpenSCAD model included)

🔌 USB powered

🛠 Hardware Requirements

ESP8266 development board (with built-in 0.96" OLED)

SSD1306 128×64 OLED display (I2C)

Micro USB cable

Optional: 3D printed enclosure

📌 I2C Configuration
Signal	GPIO
SDA	GPIO12
SCL	GPIO14
Address	0x3C
📦 Software Requirements

Arduino IDE

Libraries:

Adafruit GFX

Adafruit SSD1306

Install via:
Sketch → Include Library → Manage Libraries

🚀 Installation

Clone this repository

Open the .ino file in Arduino IDE

Install required libraries

Connect ESP8266

Upload the code

Power the board via USB

Enjoy your desk robot 🤖
