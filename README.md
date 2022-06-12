# AntiKernelDebug-poc

## What's this?
A POC about how to detect windows kernel debug by pool tag.

## How does this poc actually work?
Query system pool tag information matches TagUlong == 'oIdK'.

Tested in Win10 1809


![image](https://github.com/gmh5225/AntiKernelDebug-poc/blob/main/images/1.png)

## Compile
- Visual Studio 2019
- llvm-msvc [[link]](https://github.com/NewWorldComingSoon/llvm-msvc-build)
