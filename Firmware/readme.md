# Hackclub Macropad (Seeed XIAO RP2040)

A 5-key + 2-encoder macropad, direct-pin wired (no diodes / no matrix).

Pin mapping was extracted directly from `Hackclub.kicad_sch` / `Hackclub.kicad_pcb`:

| Part | Function | XIAO pin | RP2040 GPIO |
|---|---|---|---|
| SW1 | key | D10 | GP3 |
| SW2 | key | D9  | GP4 |
| SW3 | key | D8  | GP2 |
| SW4 | key | D0  | GP26 |
| SW5 | key | D7  | GP1 |
| SW6 | encoder A | D4 | GP6 |
| SW6 | encoder B | D5 | GP7 |
| SW6 | encoder push | D6 | GP0 |
| SW7 | encoder A | D1 | GP27 |
| SW7 | encoder B | D2 | GP28 |
| SW7 | encoder push | D3 | GP29 |

All switch/encoder-push "other" pins go straight to GND — that's why this uses
`matrix_pins.direct` in `keyboard.json` instead of rows/cols + diodes.

## Folder layout

```
hackclub_macropad/
├── keyboard.json          # pins, encoders, USB IDs, physical layout
├── readme.md
└── keymaps/
    ├── default/
    │   ├── keymap.c        # plain keymap, F-key layer via SW6 click
    │   └── rules.mk
    └── via/
        ├── keymap.c        # same, but remappable live via the VIA app
        ├── rules.mk
        └── via.json        # custom definition to import into VIA
```

## 1. Set up QMK

If you haven't already:
```bash
git clone https://github.com/qmk/qmk_firmware.git
cd qmk_firmware
python3 -m pip install -r requirements.txt
qmk setup   # if you didn't clone this way already
```

## 2. Drop this keyboard in

Copy the whole `hackclub_macropad` folder into:
```
qmk_firmware/keyboards/hackclub_macropad/
```

## 3. Build

```bash
qmk compile -kb hackclub_macropad -km default
```
This produces `hackclub_macropad_default.uf2` in `qmk_firmware/`.

For the VIA-enabled version instead:
```bash
qmk compile -kb hackclub_macropad -km via
```

## 4. Flash

The XIAO RP2040 uses UF2 bootloader (BOOTSEL):
1. Unplug the board.
2. Hold the **BOOT** button on the XIAO, plug in USB-C while still holding it.
3. It mounts as a USB drive called `RPI-RP2`.
4. Drag the `.uf2` file onto that drive. It reboots automatically running your firmware.

(You can also do `qmk flash -kb hackclub_macropad -km default` and QMK will
prompt you to put it in bootloader mode.)

## 5. Default keymap behavior

- SW1–SW5 → `1 2 3 4 5`
- SW6 (left encoder push) → momentary layer (`FN`) → SW1–SW5 become F1–F5 while held
- SW7 (right encoder push) → Mute
- Left encoder (SW6) rotate → Volume down/up
- Right encoder (SW7) rotate → Left/Right arrow (Page Up/Down on FN layer)

Edit `keymaps/default/keymap.c` to change any of this — swap in whatever
keycodes you want (media keys, macros, `LCTL(KC_C)`, etc).

## 6. Using VIA instead of recompiling every time

1. Build/flash the `via` keymap (step 3/4 above).
2. Open the [VIA app](https://usevia.app/).
3. Since this uses an unregistered VID/PID (`0xFEED`/`0x0001`, QMK's default
   test IDs — fine for personal use, but if you want to share this keyboard
   publicly you should generate your own via `qmk generate-usb2json` or by
   picking your own PID), go to **Settings → Show Design tab**, then
   **Design → Import** and load `keymaps/via/via.json`.
4. Your macropad should now show up live in VIA and you can remap keys
   without ever touching the firmware again.

## Notes / things worth double-checking

- I assumed `COL2ROW`-style logic doesn't apply here since there's no matrix
  at all — every switch is direct GPIO-to-GND, debounced by QMK in firmware.
- The physical key positions in `keyboard.json` are approximated from the
  X/Y coordinates of each footprint on your PCB (in mm, converted to key
  units). This only affects how QMK Configurator visually draws the layout —
  it has zero effect on how the firmware actually behaves.
- If BOOTSEL / flashing doesn't work, double check your XIAO RP2040 board
  variant is genuinely RP2040-based (not the ESP32-C3 or SAMD21 XIAO, which
  need different firmware entirely) — the schematic lib_id said
  `XIAO_RP2040`, so this should be right, but worth a quick glance at the
  silkscreen on your board to confirm.
