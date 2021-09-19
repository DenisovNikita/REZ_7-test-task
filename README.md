# Тестовое задание на НИР REZ_7

## Задача:

Реализуйте на вашем любимом языке программирования программу выхода из лабиринта.

На входе - прямоугольная матрица из нулей и единиц и координаты точки старта. Ноль - свободная ячейка, 1 - занятая.
Гарантируется, что точка старта - свободная.
Перемещаться можно на соседнюю свободную ячейку сверху/снизу/слева/справа.

Выход - любая свободная ячейка в крайнем столбце или крайней строке.

## Описание:

Написано на C++17. При невалидном вводе внутри программы вылетают исключения, которые ловятся и в поток ошибок выводится сообщение об ошибке. Если же программе дали валидный ввод и она отработала без ошибок, то в выходном файле будет находиться ответ. Также можно добавлять свои тесты: в папку `tests/` положить файл с тестом и запустить исполняемый файл программы, указав ей в качестве двух параметров файл откуда читать и файл куда писать.

### Формат входных данных

Тест задается в файле, название которого вы можете указать сами (по дефолту это `tests/normal_test.in`).

В первой строке два числа `n` и `m` --- высота и ширина поля. `1 <= n * m <= 100'000`.

В следующих `n` строках задается поле: в каждой строке --- строка длиной `m` состоящая из `0` и `1`.

В новой строке задаются два числа `x` и `y` --- координаты стартовой позиции в лабиринте `1 <= x <= n`, `1 <= y <= m`.
Левый верхний угол имеет координаты `1 1`, правый нижний --- координаты `n m`.

### Формат выходных данных

Реузльтат записывается в файл, название которого вы можете указать сами (по дефолту это `tests/normal_test.out`).

Если можно выбраться из лабиринта, то в первой строке заданы два числа `x` и `y` --- координаты свободной ячейки в крайнем столбце или крайней строке до которой можно дойти из начальной. `1 <= x <= n`, `1 <= y <= m`.
Если же выбраться из лабиринта нельзя, то в первой строке будет записано `-1 -1`.

## Инструкция по сборке:

Если ваша версия cmake меньше 3.20, то обновите cmake, либо поменяйте required версию в файле `CMakeLists.txt`. Узнать свою версию можно
командой `cmake --version`.

Скачиваем репозиторий. Выполняем команду `cmake . && make`. Создастся исполняемый файл `REZ_7_test_task`. Если запустить
его без параметров, то он будет ожидать тест в файле `tests/normal_test.in` и если найдет, то результат запишет в файл `tests/normal_test.out`. 
Также можно указать два параметра: файл откуда читать тест и файл куда записывать результат.
