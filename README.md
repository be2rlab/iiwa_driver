## How to use

### Real-time kernal

...

### Prepare Fast Robot Interface (FRI)

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
