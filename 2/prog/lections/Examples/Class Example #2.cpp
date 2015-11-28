// Bad example
// Imagine we have two instances of myclass with field m, which contains pointer to array
object1.m = object2.m
// when objects2's destructor executes object1.m will point to destroyed data
// that's why you should implement explicitly all your constructors!!
