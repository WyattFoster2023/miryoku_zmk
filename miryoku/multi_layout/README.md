# Multi-layout firmware notes

This branch adds runtime profile switching (Miryoku / Game HID / Empty) on Lily58
extended keys. Enable with `#define MIRYOKU_MULTI_LAYOUT` in `custom_config.h`.

## Layout selectors

Left top row **K43–K45** (central half — use these if the right side is not connected):

| Key | Profile |
|-----|---------|
| K43 | Miryoku (`&to` Base layer) |
| K44 | Game HID |
| K45 | Slot 3 (blank profile) |

**K40–K42** and **K49–K53** are unassigned on Miryoku layers. **K54** remains the split diagnostic key.

See [SPLIT_DIAGNOSTICS.md](SPLIT_DIAGNOSTICS.md) for split pairing and **K54** connectivity tests.

## Extended Lily58 keys (K40–K57)

| Keys | Role in Miryoku mode |
|------|----------------------|
| K40–K42 | Unassigned (`&none`) |
| K43–K45 | Profile selectors (Miryoku / Game / Empty) |
| K46–K48 | Unassigned (`&none`, left outer column) |
| K49–K53 | Unassigned (`&none`) |
| K54 | Split diagnostic digit per layer (see SPLIT_DIAGNOSTICS.md) |
| K55–K57 | Unassigned (`&none`, right outer column) |

## Game HID layout

Left top row **K40–K42**: ESC, `1`, `2`. Selectors on **K43–K45** (same as Miryoku).

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

Miryoku layers (Base–Fun) are pre-expanded in `wrapped_layers.h`. After changing `miryoku/custom_config.h` (`MIRYOKU_ALPHAS_*`), `miryoku_babel/miryoku_layer_alternatives.h`, or `wrap.h`, run `python3 scripts/gen-wrapped-layers.py`.

### Thumb combos

Combo key-position indices were updated for the extended matrix (51/52 left, 56/57 right). If combos behave oddly, re-verify positions against your physical PCB.

### Empty slot

Slot 3 is intentionally blank—a placeholder for a future profile. All keys are inert except the three layout selectors.
