# sofle-config

Build files for my sofle rgb keyboard's QMK configuration

# Installation
Pull the qmk firmware repository: `git pull https://github.com/qmk/qmk_firmware/`  
Reset it to a legacy version: `git reset --hard d2892685c52a8a0892b28872cfc43e8f7fa37465`  
Copy glcdfont.c over to drivers/oled/  
Flash to keyboard: `qmk flash -kb sofle/rev1 -km <KEYMAP_NAME>`
