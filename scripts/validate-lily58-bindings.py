#!/usr/bin/env python3
"""Verify multi-layout layers have 58 bindings in MIRYOKU_BIND_LILY58 slot order."""

from __future__ import annotations

import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
WRAPPED = ROOT / "miryoku" / "multi_layout" / "wrapped_layers.h"
GAME = ROOT / "miryoku" / "multi_layout" / "game_layer.h"

SLOT_NAMES = (
    [f"t4{i}" for i in range(40, 46)]
    + [f"s4{i}" for i in range(49, 55)]
    + ["l46"]
    + [f"a0{i}" for i in range(5)]
    + [f"a0{i}" for i in range(5, 10)]
    + ["r55"]
    + ["l47"]
    + [f"a1{i}" for i in range(5)]
    + [f"a1{i}" for i in range(5, 10)]
    + ["r56"]
    + ["l48"]
    + [f"a2{i}" for i in range(5)]
    + [f"a2{i}" for i in range(5, 10)]
    + ["r57"]
    + ["n30", "n31"]
    + [f"k3{i}" for i in range(2, 5)]
    + [f"k3{i}" for i in range(5, 8)]
    + ["n38", "n39"]
)

PHYS = {
    **{f"t4{i}": f"K{i}" for i in range(40, 46)},
    "l46": "K46",
    **{f"a0{i}": f"K0{i}" for i in range(5)},
}


def split_bindings(body: str) -> list[str]:
    body = re.sub(r"\\\s*\n\s*", " ", body)
    parts: list[str] = []
    depth = 0
    start = 0
    for i, c in enumerate(body):
        if c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
        elif c == "," and depth == 0:
            part = body[start:i].strip()
            if part:
                parts.append(part)
            start = i + 1
    tail = body[start:].strip().rstrip("\\").strip()
    if tail:
        parts.append(tail)
    return parts


def extract_layer(path: Path, macro: str) -> list[str]:
    text = path.read_text()
    m = re.search(rf"#define {macro}\s*\\?\s*\n(.*?)(?=\n#define |\Z)", text, re.S)
    if not m:
        raise SystemExit(f"{path}: macro {macro} not found")
    return split_bindings(m.group(1))


def slot(bindings: list[str], name: str) -> str:
    return bindings[SLOT_NAMES.index(name)]


def main() -> int:
    errors: list[str] = []
    layers: list[tuple[str, Path, str]] = [
        ("BASE", WRAPPED, "MIRYOKU_LAYER_BASE"),
        ("GAME", GAME, "MIRYOKU_LAYER_GAME"),
        ("SLOT3", GAME, "MIRYOKU_LAYER_SLOT3"),
    ]
    for name, path, macro in layers:
        bindings = extract_layer(path, macro)
        if len(bindings) != 58:
            errors.append(f"{name}: expected 58 bindings, got {len(bindings)}")
            continue
        if name == "BASE":
            for key in ("t440", "t441", "t442"):
                if slot(bindings, key) != "&none":
                    errors.append(f"{name}: {PHYS[key]} should be &none")
            for key in ("t443", "t444", "t445"):
                if not slot(bindings, key).startswith("ML_SEL_"):
                    errors.append(f"{name}: {PHYS[key]} should be a profile selector")
            for key in ("l46", "l47", "l48", "r55", "r56", "r57"):
                if slot(bindings, key) != "&none":
                    errors.append(f"{name}: {key} outer column should be &none")
            for key in ("s449", "s450", "s451", "s452", "s453"):
                if slot(bindings, key) != "&none":
                    errors.append(f"{name}: {key} should be &none")
        if name == "GAME":
            if slot(bindings, "t440") != "&kp ESC":
                errors.append(f"{name}: K40 should be &kp ESC")
            if slot(bindings, "t441") != "&kp N1":
                errors.append(f"{name}: K41 should be &kp N1")
            if slot(bindings, "t442") != "&kp N2":
                errors.append(f"{name}: K42 should be &kp N2")
            for key in ("t443", "t444", "t445"):
                if not slot(bindings, key).startswith("ML_SEL_"):
                    errors.append(f"{name}: {PHYS[key]} should be a profile selector")
            if not slot(bindings, "l46").startswith("&kp "):
                errors.append(f"{name}: K46 should start the game grid (&kp)")

    if errors:
        for e in errors:
            print(f"error: {e}", file=sys.stderr)
        return 1
    print("OK: BASE, GAME, SLOT3 each have 58 bindings; extended key slots look correct")
    return 0


if __name__ == "__main__":
    sys.exit(main())
