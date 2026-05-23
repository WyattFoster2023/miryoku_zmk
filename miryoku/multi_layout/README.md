# Multi-layout firmware notes

This branch adds runtime profile switching (Miryoku / Game HID / Empty) on Lily58
extended keys. Enable with `#define MIRYOKU_MULTI_LAYOUT` in `custom_config.h`.

## Layout selectors

Right-half top row, left to right:

| Key | Profile |
|-----|---------|
| K49 | Miryoku (`&to` Base layer) |
| K50 | Game HID |
| K51 | Slot 3 (blank profile) |

These bindings are duplicated on every layer so you can switch profiles from any Miryoku layer or from Game/Empty.

## Extended Lily58 keys (K40–K57)

| Keys | Role in Miryoku mode |
|------|----------------------|
| K40–K45 | F13–F18 (left top row) |
| K46–K48 | F19–F21 (left outer column) |
| K52–K54 | Unused (`U_NA`) |
| K55–K57 | F22–F24 (right outer column) |

Inner thumb `XXX` positions stay unassigned. Remap F13–F24 in software (e.g. Via, keyd, Kanata).

## Game HID layout

Left-hand 4×6 grid + three thumb keys (plain `&kp`, press on key down):

```
I  Q  W  E  R  T
K  A  S  D  F  G
M  Z  X  C  V  B
```

Thumb: LCTRL, LALT, SPACE. Right half is unassigned except layout selectors.

## Known limitations

### Firmware size

Each profile adds full layer bindings (56 positions × 12 layers vs 46 × 10). This fits on nice!nano but leaves less headroom for future features. If builds fail with flash overflow, consider dropping the Empty slot or compiling profiles separately.

### Layout persistence

`&to` resets to Miryoku Base (layer 0) on reboot. Active profile is not stored in ZMK settings yet.

### Press vs release (Miryoku only)

Game mode uses standard `&kp` (activate on press, release on key up). Miryoku still uses hold-tap / mod-tap with `tap-preferred`, where the tap action can fire on **release** if you hold longer than the tapping term. That does not affect Game HID mode but remains true in Miryoku.

### QWERTY-only wrap

Miryoku layers (Base–Fun) are pre-expanded in `wrapped_layers.h`. After changing `miryoku_babel/miryoku_layer_alternatives.h` or `wrap.h`, run `python3 scripts/gen-wrapped-layers.py`. `MIRYOKU_WRAP_MIRYOKU` in `wrap.h` is wired for `MIRYOKU_ALPHAS_QWERTY` (non-flip).

### Thumb combos

Combo key-position indices were updated for the extended matrix (51/52 left, 56/57 right). If combos behave oddly, re-verify positions against your physical PCB.

### Empty slot

Slot 3 is intentionally blank—a placeholder for a future profile. All keys are inert except the three layout selectors.
