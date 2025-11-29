# Raspberry Pi Christmas Tree

# Hardware

* Raspberry RP2350-PiZero board
* 3D Xmas tree - https://thepihut.com/products/3d-xmas-tree-for-raspberry-pi

# Building

Ensure that ARM GCC tools are installed and available in your PATH.

```bash
git submodule update --init --recursive
cmake -S . -B build
cd build/
make -j
```

# Running

Flashing requires the use of the Raspberry Pi variant of OpenOCD. Installing this can be done as follows:

```bash
sudo apt install libusb-1.0-0-dev libhidapi-dev pkg-config libjim-dev
git clone https://github.com/raspberrypi/openocd.git rpi_openocd
cd rpi_openocd
git submodule update --init --recursive
./bootstrap
./configure --prefix=/<path to openocd> --enable-cmsis-dap=yes
make -j
# will install to /<path to openocd>
sudo make install
```

To flash the device using OpenOCD, run the following command:
```bash
/<path to openocd>/bin/openocd -s /<path to openocd>/share/openocd/scripts -f rp2350-pizero.cfg -c "program \"build/rp2350_tree.elf\"" -c reset -c shutdown
```