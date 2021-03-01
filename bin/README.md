# Helper Scripts

## Java Disassembler

The `compile-hsdis-fedora.sh` script will compile the plugin that can be used
to disassemble the output of individual JIT compilation events with the JDK.

The script was tested with Fedora 31.

Once compiled, place the plugin in the current directory or on `LD_LIBRARY_PATH` and use:

```shell
java -XX:+UnlockDiagnosticVMOptions -XX:+PrintAssembly MainClass
java -XX:+UnlockDiagnosticVMOptions -XX:CompileCommand=print,Class.method MainClass
```

Add `-XX:PrintAssemblyOptions=help` to see additional disassembly configuration switches.
