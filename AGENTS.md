# Agent guide: building and fixing firmware

This repo is a **ZMK user config** (Miryoku + Lily58). Use **Docker** for local builds. Do **not** use `zmk west build` from the ZMK CLI — that workspace omits Zephyr and cannot compile firmware.

## Prerequisites

- Docker installed and usable without `sudo` (`docker run --rm hello-world` succeeds).
- Image pulled once: `docker pull zmkfirmware/zmk-build-arm:stable`

First build clones ZMK **v0.3** into `.cache/zmk` and runs `west init` / `west update` / `west zephyr-export` inside the container (slow, one-time).

## Build command

From the repository root:

```bash
bash scripts/build-local.sh
```

Defaults:

| Variable | Default | Notes |
|----------|---------|--------|
| `BOARD` | `nice_nano_v2` | CI `build.yaml` uses `nice_nano`; either is usually fine |
| `SHIELDS` | `lily58_left lily58_right settings_reset` | Space-separated |
| `ZMK_REF` | `v0.3` | Matches `.github/workflows/build.yaml` |
| `ARTIFACT_DIR` | `firmware/` | Gitignored output (see `firmware/README.md`) |

Examples:

```bash
# Left half only (faster iteration)
SHIELDS=lily58_left bash scripts/build-local.sh

# Match GitHub Actions board name
BOARD=nice_nano SHIELDS=lily58_left bash scripts/build-local.sh

# Skip image pull on repeat runs
SKIP_DOCKER_PULL=1 SHIELDS=lily58_left bash scripts/build-local.sh
```

Help: `bash scripts/build-local.sh --help`

## What the script does

1. Ensures `.cache/zmk` exists (clone `zmkfirmware/zmk` at `ZMK_REF` if missing).
2. Temporarily prepends `#define MIRYOKU_KEYBOARD_<name>` to `miryoku/custom_config.h` (restored after each shield build), same as CI.
3. Runs `west build` in `zmkfirmware/zmk-build-arm:stable` with `-DZMK_CONFIG=/workdir/miryoku_zmk/config` and `-DSHIELD=...`.
4. Cleans `firmware/` (keeps `README.md`), then copies `zmk.uf2` (or `.bin`/`.hex`) there.

Flash built firmware: `./flash` (pick mount + `.uf2` via `fzf`). CI zips dropped in `firmware/` are extracted on demand.

## Fix loop for agents

1. Run `SHIELDS=lily58_left bash scripts/build-local.sh` (or the shield you are changing).
2. On failure, read **devicetree / preprocessor** errors in the log (often `miryoku.dtsi`, `miryoku/mapping/`, `config/lily58.keymap`, `miryoku/multi_layout/`).
3. Edit sources, rebuild until the command exits 0.
4. Do not commit unless the user asks.

## CI parity

- Workflow: `.github/workflows/build.yaml` → `zmkfirmware/zmk/.github/workflows/build-user-config.yml@v0.3`
- Matrix: `build.yaml` — `nice_nano` + `lily58_left` / `lily58_right` / `settings_reset`
- Mouse keys: `config/lily58.conf` sets `CONFIG_ZMK_POINTING=y`

## Resetting the ZMK tree

If west state is broken or the wrong ZMK version was cloned:

```bash
rm -rf .cache/zmk
bash scripts/build-local.sh
```

## Common failures

| Symptom | Likely cause |
|---------|----------------|
| `permission denied` on docker.sock | User not in `docker` group or daemon not running |
| `unknown command "build"` with `zmk west build` | Wrong tool; use `scripts/build-local.sh` |
| Macro arity errors (`MIRYOKU_LAYOUTMAPPING_LILY58`, `MIRYOKU_WRAP_MIRYOKU`) | Regenerate `miryoku/multi_layout/wrapped_layers.h` with `python3 scripts/gen-wrapped-layers.py`; avoid naming a layer `EMPTY` (Zephyr defines it as empty) |
| Flash overflow | Too many layers/bindings for nice!nano; see `miryoku/multi_layout/README.md` |

## Paths worth knowing

- `config/lily58.keymap` — includes Miryoku layers
- `config/lily58.conf` — Kconfig (e.g. pointing)
- `miryoku/custom_config.h` — patched at build time; avoid leaving manual edits across builds
- `miryoku/multi_layout/` — optional layout profiles (Game HID, etc.); run `scripts/gen-wrapped-layers.py` after changing babel alternatives or `wrap.h`
- `build.yaml` — GitHub Actions build matrix
