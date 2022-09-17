#!/usr/bin/python3
# -*- encoding: utf-8 -*-

"""
Содлать образ можно командой:
mkdosfs floppy.img -C 1440
"""

import sys
from struct import unpack

if len(sys.argv) != 2:
    print("Использовать: " + sys.argv[0] + " <имя образа>")
    exit(0)

# Открываем файл образа
with open(sys.argv[1], 'rb') as fd:
    # Читаем загрузочный сектор
    data = fd.read(512)
    if not data:
        print("Ошибка чтения файла")
        exit(-1)
        
    # Выделяем основные элементы
    sector_size, cluster_size, reserv, fat_count, root_size, fat_size, sig = unpack("=11xHBHBH3xH486xH", data)

    # Проверяем корректность сигнатуры
    if sig != 0xAA55:
        print("Неверная сигнатура загрузочного сектора")
        exit(-2)
        
    # Вычисляем смещение до корневой директории
    root_offset = (fat_count * fat_size + reserv) * sector_size

    # Печатаем геометрию носителя
    print(f"""Образ носителя: {sys.argv[1]}
    Размер сектора (байты): {sector_size}
    Размер кластера (сектора): {cluster_size}
    Количество резервных секторов (шт): {reserv}
    Количество таблиц FAT (шт): {fat_count}
    Размер одной таблицы FAT (сектора): {fat_size}
    Количество записей в корневой директории: {root_size}
    Смещение корневой директории (сектора): {root_offset /  sector_size}
    Смещение корневой директории (байт): {root_offset}
    """)
    print("Адр второй таблиц = 512 * размер_фат_табл + 512 then to hex")
    print("Кол-во_записей_в_рут * 32 = Количество элементов в корневой директории")
    try:
        # Смещаемся к корневой директории
        offset = fd.seek(root_offset)
        # Проверяем файкт смещения
        if offset != root_offset:
            # Если перешли не туда, то генерируем исключение
            raise
    except:
        # Если seek или мы вызвали исключение -
        # завершаем работу программы
        print("Ошибка перемещения по файлу")
        exit(-3)

    # Читаем записи в корневом каталоге
    for idx in range(root_size):
        # Читаем запись
        data = fd.read(32)
        if not data:
            print("Ошибка чтения файла")
            exit(-(4+idx))
        #Получаем первый байт, который определяет состояние запсис
        #  и 12 байт, которые определяет тип записи
        status, attr = unpack("=B10xB", data[:12])

        # Если запись не выделялась, то пропускаем
        if status == 0: continue

        # Выводим информацию о выделенных когда-то записях
        print(f"{idx+1}:", "[удалена]" if status == 0xe5 else "[активна]", end=' ')
        if attr == 0x0f: print("длинное имя файла")
        elif (attr & 0x10) == 0x10 : print("каталог")
        else: print("обычный файл")
