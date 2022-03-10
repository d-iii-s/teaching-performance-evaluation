# Using JVMTI

## Running the example

```shell
make
java -agentpath:./compilation.so -version
java -agentpathlib:./heaplivesize.so -version
java -agentpathlib:./vmallocations.so -version
```

Or run any application in place of the `version` argument.
