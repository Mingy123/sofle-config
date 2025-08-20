# sofle-config

Build files for my sofle rgb keyboard's QMK configuration

# Installation

Pull the qmk firmware repository from Dane Evans' fork:  
```git clone https://github.com/DaneEvans/qmk_firmware```

Put this repo in keyboards/sofle/keymaps/:  
```
cd keyboards/sofle/keymaps/
git clone https://github.com/Mingy123/sofle-config <KEYMAP_NAME>
```

Copy glcdfont.c over to drivers/oled/

Flash to keyboard: `qmk flash -kb sofle/rev1 -km <KEYMAP_NAME>`
