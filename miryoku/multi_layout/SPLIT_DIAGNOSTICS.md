# Split keyboard diagnostics

## What you were seeing (Problem 1)

| Observation | Explanation |
|---------------|-------------|
| `qwer` on the row above home, `asdf` on K10–K13 | **Miryoku Base (layer 0)** on the **left half only**. That is standard QWERTY alpha positions with Miryoku mod-tap on A (K10). |
| K10 hold → Windows key | `U_MT(LGUI, A)` on Base — expected Miryoku, not Game. |
| K49–K53 “do nothing” | Selectors moved to **K43–K45** on the left top row; right top row keys are unassigned except K54. |
| Right half “dead” | Same: no split link, or wrong `.uf2` on the right (e.g. left image flashed to both sides). |

Game HID is **layer 10** (`U_GAME`). Firmware always boots to **layer 0 (Base)**. You were not on Game unless `&to 10` ran successfully from a working selector key.

“Mixed” QWERTY + Miryoku is not a corrupt keymap — it is **Base** behaving as designed on one half.

## Required hardware setup

1. Flash **`lily58_left`** build to the **left** nice!nano (USB / central).
2. Flash **`lily58_right`** build to the **right** nice!nano (peripheral).
3. Power both; pair over **BLE split** (right joins left). Until paired, only the left matrix produces key events.

ZMK enables `CONFIG_ZMK_SPLIT` automatically for these shields; left is `ZMK_SPLIT_ROLE_CENTRAL`.

## Profile switching (after fix)

- **Left top row K43–K45**: Miryoku / Game / Empty — works on the central half **without** the right connected.

## Split connectivity test (Problem 2)

**K54** (right top row, last key) sends a **number** that identifies the active ZMK layer:

| Layer | Key on K54 |
|-------|------------|
| Base | `1` |
| Extra | `2` |
| Tap | `3` |
| … | … |
| Fun | `0` |
| Game | `A` |
| Empty | `B` |

**How to test**

1. Stay on Base; press K54 → should type `1` if the right half is connected.
2. Tap left **K43** (Miryoku selector) / use layers as needed; on each layer, K54 should emit that layer’s digit.
3. Tap left **K44** (Game); K54 should type `A`. Game layer **K40–K42** are ESC / `1` / `2`.

If left keys work but K54 never produces output, the split link or right firmware is still wrong.
