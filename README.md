## How to use

### Real-time kernal 

*(tested for ubuntu 20.04)*

Install dependancies

```
sudo apt-get install build-essential bc curl ca-certificates fakeroot gnupg2 libssl-dev lsb-release flex bison
```


Download kernal and its patch

```
cd iiwa_driver && mkdir rt-linux && cd rt-linux
curl -SLO https://www.kernel.org/pub/linux/kernel/v5.x/linux-5.4.47.tar.xz
curl -SLO https://www.kernel.org/pub/linux/kernel/projects/rt/5.4/older/patch-5.4.47-rt28.patch.xz
```

Decompress all

```
xz -d linux-5.4.47.tar.xz
xz -d patch-5.4.47-rt28.patch.xz
```


Apply the patch 

```
tar xf linux-5.4.47.tar
cd linux-5.4.47
patch -p1 < ../patch-5.4.47-rt28.patch
```

Make config for `PREEMPT_RT_FULL`

```
make oldconfig
```

check in opened menu `Fully Preemptible Kernel (Real-Time) (PREEMPT_RT) (NEW)`


Next, compile kernel

```
fakeroot sudo make -j8 deb-pkg
```

```
sudo dpkg -i ../linux-headers-5.4.40-rt24_*.deb ../linux-image-5.4.40-rt24_*.deb
```


Reboot computer

```
reboot
```

and check if new kernall is installed.


At the end add real-time permissions to user

```
sudo addgroup realtime
sudo usermod -a -G realtime $(whoami)
```

and add following limits to real-time group

```
@realtime soft rtprio 99
@realtime soft priority 99
@realtime soft memlock 102400
@realtime hard rtprio 99
@realtime hard priority 99
@realtime hard memlock 102400
```


### Setup Fast Robot Interface (FRI)

1. Be sure you have:
        
    - [x] LBR iiwa (I have 14 kg version)
    - [x] Sunrise.Workbench
    - [x] Sunrise.FRI

2. Install packages

    ```
    sudo apt install libyaml-cpp*
    ```

3. Copy files from `FRIClient_SDK_CPP/*` to `extern/fri-client-sdk/` dirictory.

4. Build FRI client.
   
    ```bash
    cd ./extern/fri-client-sdk/build/GNUMake && make
    ```

### Setup network

1. Disable IPv6

2. Set IPv4 to 

```
192.168.10.200
255.255.255.0
```

