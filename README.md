# IPASS libraries (MFRC522, DS3231 and HCSR501)
## Introduction
This is a school project! The school assignemt is called IPASS(Individual Propedeuse Assessment).
The whole project can be found here: https://github.com/YouriMulder/IPASS_2018. <br>
<br>
The libraries are written on top of HWLIB and BMPTK. <br>
Special thanks to (c) Wouter van Ooijen (wouter@voti.nl) 2017 for creating the Arduino Due toolchain. <br>
HWLIB (hardware library): https://github.com/wovo/hwlib <br>
BMPTK (Bare Metal Programming Tool Kit): https://github.com/wovo/bmptk
<br>
Before installing my software you should've installed BMPTk and HWLIB. My libraries DON'T work without HWLIB and BMPTK
<br>
## Boost License:
Distributed under the Boost Software License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

## Requirements
HWLIB (hardware library): https://github.com/wovo/hwlib <br>
BMPTK (Bare Metal Programming Tool Kit): https://github.com/wovo/bmptk<br>
Codelite IDE (recommended! not necessary): https://codelite.org/

## Installation
After installing HWLIB and BMPTK you have to clone my github repo: https://github.com/YouriMulder/IPASS_2018.
Choose the library you want to use in the Libraries folder.
After choosing the library you should test if your chip is working correctly. (check the testing section)

## Import library to your own project
To use a library in your own project you should just copy the folder or files to the directory of your own projected and add the files to your makefile (Note that you need HWLIB and BMPTK for using the libraries!). 

## Testing
When you want to test the libraries or your chip you need to run the main.cpp located in the folder of the library.

## Author
The project is made by: Youri Mulder - Computer science year 1 (Hogeschool Utrecht)

## Used sites/datasheets
https://www.mpja.com/download/31227sc.pdf <br>
https://datasheets.maximintegrated.com/en/ds/DS3231.pdf <br>
https://www.nxp.com/docs/en/data-sheet/MF1S50YYX_V1.pdf <br>
https://www.nxp.com/docs/en/data-sheet/MFRC522.pdf <br>
http://www.radio-electronics.com/info/wireless/nfc/near-field-communications-modulation-rf-signal-interface.php <br>
http://www.nedapidentification.com/news/insights/understanding-the-confusing-world-of-rfid-tags-and-readers-in-access-control.html <br>
