# Qt6 Installation Guide for Ks'Healthcare

## Linux (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install qt6-base-dev qt6-tools-dev-tools qt6-l10n-tools
sudo apt install cmake build-essential
```

## Windows
1. Download Qt Online Installer from https://www.qt.io/download
2. Run installer and select:
   - Qt 6.x.x
   - MSVC 2019/2022 compiler (or MinGW)
   - Qt Creator (optional)
3. Add Qt binaries to PATH:
   - Qt installation dir/6.x.x/mingw_64/bin
   - Qt installation dir/Tools/mingw1120_64/bin

## macOS
```bash
brew install qt6
brew link --force qt6
```

## Verify Installation
```bash
qmake6 --version  # Should show Qt6 version
cmake --version   # Should be 3.5+
```

## Build Ks'Healthcare After Installation
```bash
cd KsHealthcare
chmod +x build.sh
./build.sh