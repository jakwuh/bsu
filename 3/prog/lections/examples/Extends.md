```java
class A extends B {
	// super.f();
}
```  
```java
A a = new B(); - correct 
B b = new A(); - incorrect

a instanceof A // true
b instanceof A // true
a instanceof B // false

A x = new B();
x.foo() // it is B::foo(), not A::foo()

A instanceof B // boolean
```  
```java
if (m == true) // bad way
if (m) // nice
```  