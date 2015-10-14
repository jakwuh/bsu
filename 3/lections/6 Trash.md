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
* Использовать статический импорт `import static className.staticFieldName`

```java
import p1.x;
import p2.x;
// compilation error
```