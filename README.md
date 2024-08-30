# Свойства хорошего кода. Принципы DRY и SOLID
# Ошибки в изначальном коде:

## Принцип единственной ответственности
Класс *Printable* и наследуемый от него *Data* содержат методы сохранения информации в различных форматах. Поэтому вместо этих классов были созданы базовый класс *Data* и наследуемые от него классы, каждый из которых отвечает за сохранение в разных форматах.

## Принцип открытости/закрытости
В функции *saveTo(..)* вызывались различные методы в зависимости от формата данных, такого быть не должно, иначе код будет увеличиваться при увеличении данных, будет расти количество case.

## Принцип подстановки Барбары Лисков
В функции *saveTo(..)* следует использовать свойство полиморфизма.