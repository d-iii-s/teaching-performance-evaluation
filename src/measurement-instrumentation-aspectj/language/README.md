# Manipulating Java Bytecode with AspectJ

## Method timing

The `Measurement` aspect measures the execution time of all methods in the `Main` class.
The `pom.xml` file includes the weaver plugin that performs aspect weaving during compilation.

```shell
mvn compile
mvn exec:java
```
