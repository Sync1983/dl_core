# dl_core
PHP Extension for Damerau–Levenshtein distance calc
https://ru.wikipedia.org/wiki/%D0%A0%D0%B0%D1%81%D1%81%D1%82%D0%BE%D1%8F%D0%BD%D0%B8%D0%B5_%D0%94%D0%B0%D0%BC%D0%B5%D1%80%D0%B0%D1%83_%E2%80%94_%D0%9B%D0%B5%D0%B2%D0%B5%D0%BD%D1%88%D1%82%D0%B5%D0%B9%D0%BD%D0%B0

Вычисляет расстояние Дамерау-Левенштейна между текстом и всеми элементами массива
Использутеся в виде вызова dl_array(array, text, offset = 0, length = 0)

Возвращаемое значение - минимальное найденное расстояние
text    - Текст, для которого производится вычисление
offset  - Смещение сравниваемого участка текста от начала
length  - Длина сравниваемого участка
array   - массив элементов вида
[
  'id'  => ...
  'text' => ...
]

Все элементы массива, не имеющие ключа 'text' будут проигнорированы
Во все элементы массива будет добавлен ключ 'distance' с указанием расстояния между текстом и полем по ключу 'text'
Если элемент уже содержит ключ 'distance', то его значение будет увеличино на рассчитанную величину

Алгоритм использует прямую реализацию с рекурсией и сильно зависит от длины сравниваемых текстов
Тексты массива при сравнении будут обрезаны до длины text
offset и length применяются для пошагового сравнения текста частями, чтобы уменьшить общее время сравнения
При этом сравнение текста длиной до 5 символов занимает примерно 0.1 сек
Общий подход при использовании данной функции:

dl_array($rows,$text,0,5);
dl_array($rows,$text,4,5);
$bound = dl_array($rows,$text,9,5)

$answer = dl_filter($rows,$bound,$count = 0)

Функция dl_filter проведет фильтрацию массива $rows по полю 'distance', и вернет все элементы с его значением меньше 
или равным $bound. 
Если передано значение $count, то фильтрация будет производится для $count первых попаданий
Значения результат $answer ссылаются на массив $rows, и будут удалены при очистке массива, поэтому результат требует 
отдельного сохранения, например, переноса значений в другой массив




