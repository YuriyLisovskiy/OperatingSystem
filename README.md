## Simple OS
Fun with cpu kernel programming. This is a horrible project written in c language while I have no idea how to write programs =D
### Download
Download zip archive or clone a repository:
```
$ https://github.com/YuriyLisovskiy/simple-os.git
```
### Build and Run
Requirements (Ubuntu 16.04 LTS):
* `gcc` and `nasm` compilers to build the kernel
* `qemu` emulator to run the kernel

Install requirement software:
```
$ sudo make requirements
```
Build the kernel:
```
$ make build
```
Clean the output:
```
$ make clean
```
Run the kernel:
```
$ make run
```
Make and run the project:
```
$ make
```
### Author
* [Yuriy Lisovskiy](https://github.com/YuriyLisovskiy)
### License
 This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.