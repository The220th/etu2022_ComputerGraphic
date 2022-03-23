# etu2022_ComputerGraphic. Временный README.md

Используется `QT`:

- [Установка](https://github.com/The220th/SharedLib/blob/main/cpp/QT/INSTALL.md) <- тык

- В директории, где есть файл `что-то.pro` выполнить:

``` bash
> qmake

> make
```

В лабораторных работах: 1, 2, 3 - для рисования используется **только** функция [`void QPainter::drawPoint(int x, int y)`](https://doc.qt.io/qt-5/qpainter.html#drawPoint-2).

## lab1

Выполнены варианты 9 и 10.

Для правильной работы, должен быть установлен `Python 3`. На `Linux` добиться того, чтобы `Python` запускался командой `python`, а не `python3`.

Также необходим пакет `scipy` для `Python 3`:

``` bash
> python -m pip install --upgrade pip

> pip3 install scipy
```

В `Windows` запускать, находясь в директории `./lab1`.

## lab2

Кривая Безье n-го порядка

## lab3

Поверхность Безье n-го порядка
