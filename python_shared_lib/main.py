import ctypes

libc = ctypes.CDLL("./libclib1.so")

# Пример вызова простой функции
libc.about()
print('-' * 50)

# Пример функции которая сохраняет значение
libc.simple_function()
print(libc.simple_function())
print('-' * 50)

# Пример того, что передача обычных типов не работает,
# и надо предварительно конвертировать питоновские типы в C типы
original_string = "starting string"
print("Before:", original_string)
x = libc.add_one_to_string(original_string)
print("After: ", original_string, "\n")

mutable_string = ctypes.create_string_buffer(original_string.encode())
print("Before:", mutable_string.value)
libc.add_one_to_string(mutable_string)
print("After: ", mutable_string.value)
print('-' * 50)

# Пример описания возвращаемого значения функции.
alloc_func = libc.alloc_C_string  # Берем объект функции
alloc_func.restype = ctypes.POINTER(ctypes.c_char)  # Обозначаем что функция возвращает указатель на char
char_pointer = alloc_func()  # Вызываем функцию
print("char_pointer:", char_pointer)
print('-' * 50)

# Берем значение по указателю и печатаем.
phrase = ctypes.c_char_p.from_buffer(char_pointer)
print("Bytes in Python {0}".format(phrase.value))
print('-' * 50)

# Пример описания принимаего функцией значения
free_func = libc.free_C_string  # Берем объект функции
free_func.argtypes = [ctypes.POINTER(ctypes.c_char)]  # Обозначаем что функция принимает указатель на char
free_func(char_pointer)  # Вызываем функцию и передаем в нее указатель

