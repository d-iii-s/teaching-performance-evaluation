# Manipulating Java Bytecode with AspectJ

## Method timing

The `Measurement` class implements an aspect that measures the execution time of all methods in the `Main` class.
The `aop.xml` file instructs the runtime weaver to weave the `Measurement` aspect.
The `pom.xml` file includes the JVM to use the runtime weaver.

```shell
mvn test
```
