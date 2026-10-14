# IJC Project 1 – Bit Arrays, Primes & Steganography

First project for the **IJC (The C Programming Language)** course, written in C (ISO C11).

## Overview
- **`bitset` & `primes`**: Custom bit-array data structure implemented via both preprocessor macros and inline functions, used to compute prime numbers via the Sieve of Eratosthenes.
- **`steg-decode`**: A steganography decoder that extracts hidden UTF-8 messages stored inside the least significant bits (LSBs) of prime-indexed bytes in binary `.ppm` images.

## Build & Usage
```bash
make
./primes
./steg-decode du1-obrazek.ppm
```
