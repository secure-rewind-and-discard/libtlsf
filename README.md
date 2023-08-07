# LIBTLSF 
This repository contains a library version of the TLSF (Two-Level Segregated Fit) allocator. 


## How to get started

- This repository can be cloned using the following commands:
```
git clone git@github.com:secure-rewind-and-discard/libtlsf.git
```
- To compile libtlsf, Run `make`  in [src/](./src/).

```
cd ./libtlsf/src
make
```


Before running applications that rely on the TLSF library (`libtlsf.so`) add the TLSF [src/](./src/) directory containing the shared object to the Linux dynamic linker search path:

```
export LD_LIBRARY_PATH='/path/to/libtlsf/src'
```

If the application relies on pre-built binaries which make calls to the `malloc()` family of functions, you additionally need to ensure that `libtlsf.so` is loaded before all other shared libraries to ensure it can override the `malloc()` functions with its own versions. This can be achieved, for example, by setting the `LD_PRELOAD` environmental variable to point to `libtlsf.so` to instruct the Linux dynamic linker to preload `libtlsf.so` before `glibc`.

```
LD_PRELOAD=/path/to/libtlsf/src/libtlsf.so
``` 
## Simple Example
We provide an example that demonstrate the library's use [simple_example/](./example/simple_example)

## Customize Heap Size
By default, the heap domain size is set to `0x200000000 (8GB)`. You can customize this number by using the `APP_HEAP_SIZE` environmental variable. 

##  Multithread Support
To support multithread application, the library should be compiled with `TLSF_MULTITHREAD` option. 

## License 
© Ericsson AB 2022-2023

BSD 3-Clause License

The original TLSF implementation by mattconte/tlsf licensed under BSD 3-Clause License




