# CipherProgram
This program is designed to encrypt specific lines or sections of txt documents. Can be used to redact information.

To encrypt, type "\[${" in the text file to start encryption and "}$]" to end encryption.

This program was written on a Raspberry Pi running raspbian.

The "addBackSlashes(std::string)" function was copied and edited from another project I made called MakeFileMaker. That program will hopefully be uploaded soon.

A default path can be hardcoded. Set "bool defaultFolderIsActive" (line 18) equal to "true" and set "std::string defaultPath" (line 20) equal to your regular directory. For example I might use "/home/pi/Documents/". Remember this was coded on a Linux Machine, Windows may look something more like "C:/Users/User1/Documents/"

This file is largely for personal use and as demonstration of abilities.
I do not plan on updating it, except as for when I need it and may or may not publish updates.
