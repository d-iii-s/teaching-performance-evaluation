# Using JVMTI

## Running the example

```shell
make
java -agentpath:./libcompilation.so -version
java -agentpath:./libheaplivesize.so -version
java -agentpath:./libvmallocations.so -version
```

Or run any application in place of the `version` argument.
