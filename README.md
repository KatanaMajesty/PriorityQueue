# Завдання

Власна задача:
Візуалізатор (Renderer) ігрового рушія має здатність додавати об'єкти до рендер-баферу. 
Об'єкти, що знаходяться далі від камери (z-координата більша) мають виводитись на екран першими.
Renderer повинен мати змогу отримати об'єкт, який йому потрібно вивести на екран, тим не менш
під час роботи у рендер-бафер можуть додаватись нові об'єкти з різною відстаню від камери.

Цей спосіб виведення об'єктів на екран розв'язує проблему, описану у посиланні:https://computergraphics.stackexchange.com/questions/12215/opengl-transparency-object-behind-is-not-rendered 

## Створити структуру Data для зберігання об’єктів з характеристиками відповідно до обраної задачі:

- 	Обрати певний власний критерій для визначення більш пріоритетного
	об’єкту на основі всіх його характеристик

- 	Перевантажити оператор “менше” (operator<) для порівняння двох
	об’єктів за критерієм

- 	Перевантажити оператор “дорівнює” (operator==) для визначення
	рівності двох об’єктів за цим самим критерієм

## Реалізувати пріоритетну чергу на основі незростаючої бінарної купи:
- 	Створити структуру PriorityQueue, яка буде містити в собі бінарне
	дерево для роботи бінарної купи. Для зберігання бінарного дерева
	можна використати звичайний динамічний масив, що вже був
	реалізований у минулих роботах.

-	Реалізувати основні методи переміщення по бінарному дереву:
 	-	getParent(index) – знайти індекс батьківського вузла
 	-	getLeftChild(index) – знайти індекс лівого дочірнього вузла
 	-	getRightChild(index) – знайти індекс правого дочірнього вузла

Реалізувати внутрішні методи для підтримки властивості незростаючої (max-heap) купи:
 	-	siftUp(index) – просіяти елемент вверх по дереву
 	-	siftDown(index) – просіяти елемент вниз по дереву

- 	Реалізувати основні методи для роботи пріоритетної черги:
 	-	push(object) – додати новий елемент в чергу
 	-	top() – отримати верхній елемент з черги
 	-	pop() – видалити верхній елемент з черги
 	-	size() – знайти кількість елементів в черзі
 	-	empty() – перевірити чергу на пустоту

## Провести тестування, використавши вказану нижче функцію testPriorityQueue(). 
Перевірити правильність та швидкість роботи, порівнявши з 
готовим бібліотечним рішенням STL priority_queue.

## Продумати реалізацію сортування купою (пірамідального сортування) на базі бінарної купи,
вміти обгрунтовано пояснити та показувати в коді.

# Додаткове завдання:
## Реалізувати сортування купою
Порівняти його з готовим бібліотечним рішенням STL std::sort() 
або з іншими алгоритмами сортувань реалізованими в минулих 
роботах – провести тестування з замірами часу на різних вхідних даних, 
зробити аналіз та висновки.