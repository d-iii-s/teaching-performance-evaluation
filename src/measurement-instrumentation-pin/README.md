# Manipulating Binaries with PIN

The example demonstrates how the PIN dynamic binary instrumentation tool can be used to instrument native binaries.

## Running the example

Possibly adjust the `PIN_ROOT` variable in `Makefile` and then use `make` to build the tool libraries.

Use the tool libraries with `pin`:

```shell
/opt/pin/pin -t obj-intel64/routine-call-count.so -logfile routine-call-count.txt -- ls
/opt/pin/pin -t obj-intel64/system-call-dump.so -logfile system-call-dump.txt -- ls
```

The `instruction-count-with-dump` tool library exposes instrumentation internals.
When run, all traces are dumped in their original and instrumented form.
Use disassembly to compare the original and instrumented code.

```shell
/opt/pin/pin -t obj-intel64/instruction-count-with-dump.so -logfile instruction-count-with-dump.txt -- obj-intel64/checksum.exe
for X in *.bin; do [[ "$X" =~ -([0-9a-f]+)\.bin$ ]] && objdump -D -b binary -m i386:x86-64 -M intel --adjust-vma="0x${BASH_REMATCH[1]}" "$X" > "${X%.bin}.asm"; done
```

The checksum computation loop fragment:

```
  4005c0:       0f b6 17                movzx  edx,BYTE PTR [rdi]
  4005c3:       48 83 c7 01             add    rdi,0x1
  4005c7:       48 01 c2                add    rdx,rax
  4005ca:       48 8d 04 12             lea    rax,[rdx+rdx*1]
  4005ce:       48 c1 ea 03             shr    rdx,0x3
  4005d2:       48 31 d0                xor    rax,rdx
  4005d5:       48 39 fe                cmp    rsi,rdi
  4005d8:       75 e6                   jne    0x4005c0
  4005da:       c3                      ret
```

Can then look like this:

```
# movzx edx,BYTE PTR [rdi]
    7f7b4c70a022:       48 b8 e8 63 f9 5d 7b  7f 00 00   movabs rax,0x7f7b5df963e8
    7f7b4c70a02c:       f0 48 83 00 01                   lock add QWORD PTR [rax],0x1
    7f7b4c70a031:       49 8b 7f 40                      mov    rdi,QWORD PTR [r15+0x40]
    7f7b4c70a035:       0f b6 17                         movzx  edx,BYTE PTR [rdi]
# add rdi,0x1
    7f7b4c70a038:       48 b8 e8 63 f9 5d 7b 7f 00 00    movabs rax,0x7f7b5df963e8
    7f7b4c70a042:       f0 48 83 00 01                   lock add QWORD PTR [rax],0x1
    7f7b4c70a047:       48 83 c7 01                      add    rdi,0x1
# add rdx,rax
    7f7b4c70a04b:       48 b8 e8 63 f9 5d 7b 7f 00 00    movabs rax,0x7f7b5df963e8
    7f7b4c70a055:       f0 48 83 00 01                   lock add QWORD PTR [rax],0x1
    7f7b4c70a05a:       49 03 57 78                      add    rdx,QWORD PTR [r15+0x78]
# lea rax,[rdx+rdx*1]
    7f7b4c70a05e:       48 b8 e8 63 f9 5d 7b 7f 00 00    movabs rax,0x7f7b5df963e8
    7f7b4c70a068:       f0 48 83 00 01                   lock add QWORD PTR [rax],0x1
    7f7b4c70a06d:       48 8d 04 12                      lea    rax,[rdx+rdx*1]
    7f7b4c70a071:       49 89 47 78                      mov    QWORD PTR [r15+0x78],rax
# shr rdx,0x3
    7f7b4c70a075:       48 b8 e8 63 f9 5d 7b 7f 00 00    movabs rax,0x7f7b5df963e8
    7f7b4c70a07f:       f0 48 83 00 01                   lock add QWORD PTR [rax],0x1
    7f7b4c70a084:       48 c1 ea 03                      shr    rdx,0x3
# xor rax,rdx
    7f7b4c70a088:       48 b8 e8 63 f9 5d 7b 7f 00 00    movabs rax,0x7f7b5df963e8
    7f7b4c70a092:       f0 48 83 00 01                   lock add QWORD PTR [rax],0x1
    7f7b4c70a097:       49 31 57 78                      xor    QWORD PTR [r15+0x78],rdx
# cmp rsi,rdi
    7f7b4c70a09b:       48 b8 e8 63 f9 5d 7b 7f 00 00    movabs rax,0x7f7b5df963e8
    7f7b4c70a0a5:       f0 48 83 00 01                   lock add QWORD PTR [rax],0x1
    7f7b4c70a0aa:       48 39 fb                         cmp    rbx,rdi
# jne 0x4005c0 
    7f7b4c70a0ad:       48 b8 e8 63 f9 5d 7b 7f 00 00    movabs rax,0x7f7b5df963e8
    7f7b4c70a0b7:       49 89 87 48 29 00 00             mov    QWORD PTR [r15+0x2948],rax
    7f7b4c70a0be:       48 9f                            rex.W lahf
    7f7b4c70a0c0:       0f 90 c0                         seto   al
    7f7b4c70a0c3:       66 41 89 87 f0 00 00 00          mov    WORD PTR [r15+0xf0],ax
    7f7b4c70a0cb:       49 8b 87 48 29 00 00             mov    rax,QWORD PTR [r15+0x2948]
    7f7b4c70a0d2:       f0 48 83 00 01                   lock add QWORD PTR [rax],0x1
    7f7b4c70a0d7:       49 8b 87 f0 00 00 00             mov    rax,QWORD PTR [r15+0xf0]
    7f7b4c70a0de:       3c 81                            cmp    al,0x81
    7f7b4c70a0e0:       48 9e                            rex.W sahf
    7f7b4c70a0e2:       0f 85 20 09 03 00                jne    0x7f7b4c73aa08
    ...    
```
