#!/usr/bin/env bash
# Local ZMK firmware build via Docker (same image as ZMK GitHub Actions).
# Clones ZMK v0.3 into .cache/zmk on first run, then west build inside the container.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
IMAGE="${ZMK_BUILD_IMAGE:-zmkfirmware/zmk-build-arm:stable}"
BOARD="${BOARD:-nice_nano_v2}"
SHIELDS="${SHIELDS:-lily58_left lily58_right settings_reset}"
ZMK_DIR="${ZMK_DIR:-$ROOT/.cache/zmk}"
ZMK_REF="${ZMK_REF:-v0.3}"
FIRMWARE_DIR="${FIRMWARE_DIR:-$ROOT/firmware}"
ARTIFACT_DIR="${ARTIFACT_DIR:-$FIRMWARE_DIR}"
SKIP_DOCKER_PULL="${SKIP_DOCKER_PULL:-}"

usage() {
  cat <<EOF
Usage: $(basename "$0") [options]

Build ZMK firmware in Docker using this repo's config/ (matches CI toolchain).

Environment:
  BOARD              Target board (default: nice_nano_v2)
  SHIELDS            Space-separated shields (default: lily58_left lily58_right settings_reset)
  ZMK_DIR            ZMK checkout used by west (default: .cache/zmk)
  ZMK_REF            ZMK git ref to clone (default: v0.3)
  FIRMWARE_DIR       Firmware output directory (default: firmware/)
  ARTIFACT_DIR       Same as FIRMWARE_DIR unless overridden
  SKIP_DOCKER_PULL   Set to 1 to skip "docker pull" on each run

Examples:
  $(basename "$0")
  BOARD=nice_nano SHIELDS=lily58_left $(basename "$0")
  SHIELDS=lily58_left $(basename "$0")
EOF
}

docker_run() {
  if docker info >/dev/null 2>&1; then
    docker "$@"
  else
    sudo docker "$@"
  fi
}

ensure_zmk() {
  if [[ -d "$ZMK_DIR/.git" ]]; then
    return
  fi
  echo "==> Cloning ZMK ($ZMK_REF) into $ZMK_DIR"
  mkdir -p "$(dirname "$ZMK_DIR")"
  git clone -b "$ZMK_REF" --depth 1 https://github.com/zmkfirmware/zmk.git "$ZMK_DIR"
}

keyboard_base_from_shield() {
  local shield="$1"
  local base="${shield%% *}"
  base="${base%_left}"
  base="${base%_right}"
  base="${base%%@*}"
  printf '%s' "$base"
}

patch_custom_config() {
  local keyboard_base="$1"
  local configfile="$ROOT/miryoku/custom_config.h"
  local config_backup
  config_backup="$(mktemp)"
  cp "$configfile" "$config_backup"

  local tmpfile
  tmpfile="$(mktemp)"
  {
    printf '#define MIRYOKU_KEYBOARD_%s\n' \
      "$(echo "$keyboard_base" | tr -c '[:alnum:]' '_' | tr '[:lower:]' '[:upper:]')"
    cat "$config_backup"
  } >"$tmpfile"
  cp "$tmpfile" "$configfile"
  rm -f "$tmpfile"
  printf '%s' "$config_backup"
}

restore_custom_config() {
  local config_backup="$1"
  local configfile="$ROOT/miryoku/custom_config.h"
  [[ -n "$config_backup" && -f "$config_backup" ]] || return 0
  cp "$config_backup" "$configfile"
  rm -f "$config_backup"
}

clean_firmware_dir() {
  local item base
  mkdir -p "$FIRMWARE_DIR"
  shopt -s dotglob nullglob
  for item in "$FIRMWARE_DIR"/*; do
    [[ -e "$item" ]] || continue
    base="$(basename "$item")"
    [[ "$base" == "README.md" ]] && continue
    rm -rf "$item"
  done
  shopt -u dotglob nullglob
}

build_one() {
  local shield="$1"
  local keyboard_base
  local config_backup=""
  keyboard_base="$(keyboard_base_from_shield "$shield")"

  config_backup="$(patch_custom_config "$keyboard_base")"

  local name="miryoku_zmk"
  [[ -n "$shield" ]] && name="$name-$shield"
  name="$name-$BOARD"

  echo "==> Building $name (board=$BOARD shield=${shield:-<none>})"

  docker_run run --rm \
    -e BOARD="$BOARD" \
    -e SHIELD="$shield" \
    -e ARTIFACT_NAME="$name" \
    -v "$ROOT:/workdir/miryoku_zmk:ro" \
    -v "$ZMK_DIR:/workdir/zmk" \
    -v "$ARTIFACT_DIR:/workdir/artifacts" \
    -w /workdir \
    "$IMAGE" \
    bash -ec '
      set -euo pipefail
      cd /workdir/zmk
      if [[ ! -f .west/config ]]; then
        echo "==> west init (first run; may take several minutes)"
        west init -l app
        west update
        west zephyr-export
      fi
      cd /workdir/zmk/app
      west_args=(-DZMK_CONFIG=/workdir/miryoku_zmk/config)
      if [[ -n "${SHIELD:-}" ]]; then
        west_args+=(-DSHIELD="${SHIELD}")
      fi
      # -p: pristine build dir per shield. Without this, lily58_right reuses the
      # previous lily58_left image and both .uf2 files are identical.
      west build -p -b "${BOARD}" -- "${west_args[@]}"
      mkdir -p /workdir/artifacts
      for ext in uf2 bin hex elf; do
        f="/workdir/zmk/app/build/zephyr/zmk.${ext}"
        if [[ -f "$f" ]]; then
          cp "$f" "/workdir/artifacts/${ARTIFACT_NAME}.${ext}"
          echo "==> Wrote /workdir/artifacts/${ARTIFACT_NAME}.${ext}"
          break
        fi
      done
    '

  restore_custom_config "$config_backup"
}

main() {
  if [[ "${1:-}" == "-h" || "${1:-}" == "--help" ]]; then
    usage
    exit 0
  fi

  ensure_zmk
  echo "==> Cleaning $FIRMWARE_DIR (keeping README.md)"
  clean_firmware_dir
  mkdir -p "$ARTIFACT_DIR"

  if [[ -z "$SKIP_DOCKER_PULL" ]]; then
    echo "==> Pulling $IMAGE"
    docker_run pull "$IMAGE"
  fi

  for shield in $SHIELDS; do
    build_one "$shield"
  done

  left_uf2="$ARTIFACT_DIR/miryoku_zmk-lily58_left-${BOARD}.uf2"
  right_uf2="$ARTIFACT_DIR/miryoku_zmk-lily58_right-${BOARD}.uf2"
  if [[ -f "$left_uf2" && -f "$right_uf2" ]] && cmp -s "$left_uf2" "$right_uf2"; then
    echo "error: lily58_left and lily58_right .uf2 are identical — split will not work" >&2
    echo "error: rebuild with a fresh scripts/build-local.sh (uses west build -p per shield)" >&2
    exit 1
  fi

  echo "Artifacts: $ARTIFACT_DIR"
  ls -la "$ARTIFACT_DIR"
}

main "$@"
