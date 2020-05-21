# Install me

1. Be sure you have:
    
- [x] LBR iiwa (I have 14 kg version)
- [x] Sunrise.Workbench
- [x] Sunrise.FRI

2. Copy files from `FRIClient_SDK_CPP` to `fri-client-sdk` dirictory.

3. Build FRI client.
   
```bash
cd ./fri-client-sdk/build/GNUMake && make
```

4. Build the `iiwa_driver`

```bash
mkdir build && cd build
cmake .. && make
```