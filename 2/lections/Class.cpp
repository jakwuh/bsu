namespace Class {
	
	Абстрактные типы данных - множество объектов и набор функций, которые можно выполнять над этими объектами.
	
	Набор функций называют интерфейсом класса.

	Класс - это пользовательский ТИП данных, реализующий абстрактный тип данных.

	Объект класса - экземпляр соответсвующего типа.

	Данные класса называют атрибутами класса, переменными-членами классами, полями класса.

	Функции класса называют функцииями-членами класса, методами класса.

	Способы объявить класс {
		class class_name{}; // ;!
		struct class_name{};
		union class_name{};
	}

	Функция, обеспечивающая создание объектов этого класса и инициализацию данных называется конструктором.
	Функция, предназначенная для разрушения объектов, называется деструктором.

	Правила для конструкторов\деструкторов {
		Конструкторы и деструкторы не могут возвращать значения (включая void)
		Конструктор имеет имя совпадающее с именем класса.
		Деструктор имеет имя, совпадающее с именем класса, с предшествующей ~.
		Конструкторы могут иметь аргументы
		Класс может иметь несколько конструкторов
		Конструктор без параметров называют конструктором по умолчанию
		Деструктор не может иметь параметров
		Если конструкторы и деструкторы не написаны программистом, то их генерирует компилятор( конструктор по умолчанию и конструктор копирования )
		Чаще всего конструктор по умолчанию (предоставляемый компилятором) инициирует значения нулями
		Компилятор автоматически вставляет вызовы конструктора и деструктора при создании\уничтожении объектов
		Деструктор автоматически вызывается в нескольких случаях {
			При выходе из области видимости
			При создании временных объектов, для преобразования какого-либо выражения, или при передаче функции аргумента			
			Когда возвращенные функцией значения более не нужны
			При выполнении операции delete
		}
		Деструктор может быть вызван явно.

		Конструктор в абсолютном большинстве случаев вызывается неявно и не может быть вызван как обычная функция {
			Class_name class_object; // конструктор вызываетя неявно
			Class_name class_object(); // the best! :)
			Class_name class_object(parameters); 
			Class_name class_object = parameter; 
			Class_name* class_object = new Class_name;
			Class_name class_object = Class_name(parameters);
			Class_name* class_object = new Class_name(parameters);
		}
		Членами класса могут быт константные поля. В этом случае программист обязан написать конструктор, 
		который инициализирует это константное поле при создании объекта. Причем эта инициализация делается 
		не в теле конструктора, а в СПИСКЕ ИНИЦИАЛИЗАЦИИ:

		Список инициализации: в конструкторе после () но перед {} можно указывать функциональную форму инициализации данных.

		Class Example #1
	}

	Основные свойства объектно-ориентированного программиования {
		- Абстракция
		- Инкапсуляция {
			- Интегрирование в объект данных и методов работы с ними.
			- Сокрытие реализации от интерфейса (private, protected, private)
		}
		- Наследование {
			- Иерархия
			- Private данные не наследуются
			- У наследников появляются новые данные и методы
			- У одного потомка может быть несколько предков (не всегда хорошо, одинаковые имена методов, данных. Пример - ромбовидное наследование). 
			Java отказалось от множественного наследования полностью
			- Наследование реализуется контейнерным способом
		}
		- Полиморфизм
			- Функциональный полиморфизм
				Полиморфизм в С++ нашел отражение в функциональном полиморфизме(перегрузка функций, операторов)
					У перегруженных функций совпадают имена, но отличаются сигнатуры (список параметров)
					Class Example #2
			- Специальный полиморфизм для приведения типов
				Можно абстрагировать работу с базовым классом, а потом вызывать эти методы для дочерних классов 
				(в т.ч. можно ипользовать поля, которые у предка нет, а у потомков есть)
				Не разрешается делать неявное приведение типа от предка к потомку
			- Параметрический тип полиморфизма - тип полиморфизма, основанный на применении шаблонов (зависящие от параметров)
			- Чистый полиморфизм (включение)
				В C++ реализован через виртуальные функции
				У виртуальных функций полностью совпадают имя и сигнатура
				Позднее связывание - механизм, позволяющий на этапе выполнения программы для указателя на объект динамически выбрать из таблицы виртуальных методов 
				функцию, соответсвующую типу объекта (предку или потомку)
				Примечание: в C++ одинакоая сигнатура функций еще не означает виртуализацию (необходимо слово virtual)
	}

	Термины ООП в C++ {
		Класс - новый пользовательский тип данных
		Объект - экземпляр ранее описанного класса (типа данных)
		Данные состояния - переменные экземпляра класса (объекта)
		Сообщение - вид функции, доступную для вызова
		Метод - реализация функции класса (функций-членов класса)
		Подкласс - производный класс
	}

	Неотъемлемой частью любого класса является дополнительная переменная(this), которая является указателем на адрес, по которому размещается данный объект.
		Class Example #3 (несмотря на то, что у каждого объекта класса присутствует указатель this, sizeof не учитывает его вес(почему?))
		Class Example #4 (использование this)

	Особенности инкапсуляции {
		- В любом месте описания класса в произвольном порядке(произвольное число раз) можно использовwать private, protected, public. По умолчанию используется
		поле private;
		- static данные и переменные. static данные принадлежат не объекту, но классу. Это означает что они могут быть созданы только в единственном экземпляре,
		независимо от того, сколько объектов данного типа создано. Доступ к элементу static производится через имя класса с использованием
		оператора разрешения области видимости. static данные инициализируются в глобальной области(!)
		- static метод - должны работать со static переменными
	}

	namespace Friends {
		friend functions {
			Функции, которые описаны с определением friend объявлении класса (назависимо в каком блоке - private, public или protected) 
			не является функцией-членом класса, но при этом является функцией, имеющей доступ ко всем элементам класса.

			Объект класса для такой функции передается как параметр(чаще всего по ссылке (возможо константной)).
		}
		friend class {
			Один класс может быть дружественным для другого класса. Это означает, что первый имеет доступ ко всем членам второго класса.
		}
	}
	
	namespace Overload {
		operator ++ ... могут быть как членами класса, так и дружественными функциями.
		бинарные операторы, унарные операторы.

		функция-член класса имеет на один аргументаент меньше, чем соответствующая дружественная функция(?)
		нельзя объявлять operator = как friend(?)

		operator ++ (int) // int - фиктивный параметр(тип)

		консруктор копирования вызывается:
			 - неявно
			 - явно при возвращении значени функции по значению

		Класс, в котором присутствует только оператор перегрузки () называется функциональным классом(функтором)
		Нельзя перегружать operator :: . :* ? # ##
		При перегрузке операций нельзя задавать defaults value
	}

	namespace Inheritance {
		Наследование - это механизм, посредством которого один класс может наследовать свойства и методы другого класса.
		Наследование позволяет строить иерархию класса, переходя от более общих классов к более специальным классам.
		При наследовании класс, который наследуется, называется Базовым классом, а наследник - производным классом.

		Base Class\Inherited class private protected public
		private 					  -        -       -
		protected 				   private protected protected
		public 					   private protected public

		Вызов конструктор базового класса должен быть только в списке инициализации
		
		Виртуальные методы(полиморфизм) {
			Функция, которая в базовом и дочернем классах имеют разную реализацию называются виртуальными
		}

		Абстрактные методы {
			Метод, который не имеет тела, называют абстрактным. Класс, в котором есть хотя бы 1(!) асбтрактный метод - 
			абстрактный. Класс, в котором все методы абстрактные, часто называют интерфейсом.
			Нельзя создать объект абстрактного класса.
			У абстрактного класса обязаны быть потомки, и у него должны быть реализованы эти методы.
		}

		Деструктор должен быть виртуальным(!)
		Указателю базового класса можно присвоить ссылку на потомка. Базовый класс может быть проинициализирован потомком.
		Для работы полиморфизма параметры функций должны быть либо ссылками, либо указателями.
		Реализуемый класс обязан реализовать все методы интерфейса
		Нельзя присваивать указателю на потомка присваивать адрес предка
		static_cast применяется в случаях, когда поле одной длины может быть интерпретировано как другой тип
	}

}