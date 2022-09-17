import sys
from struct import unpack
a = input("name_of_file ")
fd = open(a,'rb')
    # Читаем загрузочный сектор
data = fd.read(512)
sector_size, cluster_size, reserv, fat_count, root_size, fat_size, sig = unpack("=11xHBHBH3xH486xH", data)

""" # Проверяем корректность сигнатуры
             if sig != 0xAA55:
                 print("Неверная сигнатура загрузочного сектора")
                 exit(-2)
"""

root_offset = (fat_count * fat_size + reserv) * sector_size
print(f"""Образ носителя: {a}
Размер сектора (байты): {sector_size}
Размер кластера (сектора): {cluster_size}
Количество резервных секторов (шт): {reserv}
Количество таблиц FAT (шт): {fat_count}
Размер одной таблицы FAT (сектора): {fat_size}
Количество записей в корневой директории: {root_size}
Смещение корневой директории (сектора): {root_offset /  sector_size}
Смещение корневой директории (байт) надо перевести это число в 16: {root_offset}
""")
print("Адр второй таблиц = 512 * размер_фат_табл + 512 then to hex")
print("Кол-во_записей_в_рут * 32 = Количество элементов в корневой директории")
