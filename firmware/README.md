# Firmware output

This directory is gitignored except this file.

**Local builds** (`bash scripts/build-local.sh`) write `.uf2` files here and remove previous builds first.

**GitHub Actions** artifacts are zip files. Drop a zip here and run `./flash` from the repository root; it will extract under `.extracted/` and let you pick a `.uf2`.

**Flash:** with the keyboard in UF2 bootloader mode (double-tap reset), run:

```bash
./flash
```

Use `./flash --help` for non-interactive options (`--uf2`, `--zip`, `--device`).
