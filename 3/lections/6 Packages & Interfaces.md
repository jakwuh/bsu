## Пакеты

Состоят из классов и интерфейсов;  
Имя пакета: и1.и2.и3  
Обратный URL. Пример: http://fpmi.bsu.by -> package by.bsu.fpmi  
Переменная CLASSPATH  

di\java\by\bsu\fpmi.class  

`public` доступен везде (внутри и вне package)  
`private` доступен только внутри класса  
`protected` доступен наследникам + классам внутри того же пакета  

## Доступ к классам и интерфейсам

* `public` вне и внутри пакета

## Использование классов и интерфейсов

* По полному имени packageName.className `java.lang.String`
* По сокращенному имени, предварительно импортировав. `import packageName.className`
* Импортировать весь пакет `import packageName.*`
* Использовать статический импорт `import static className.staticFieldName` или `import static className.*`

```java
import p1.x;
import p2.x;
// compilation error
```  
```java
import static java.lang.System.out;
out.println("Hello!");
// или
import static java.lang.Math.*
double с = sqrt(pow(2, 3));
```

## Документация Java

`deprecated` - устаревшие (методы|классы|интерфейсы)

> В составе jdk входит пакет javadoc, который анализирует комментарии к коду и генерирует документацию  