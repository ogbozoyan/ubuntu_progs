#!/usr/bin/python3
import sys
from struct import unpack

class Ntfs():
    def __init__(self, image):
    
        self.sector_size    = 0
        self.cluster_size   = 0
        self.mft            = 0
        self.mft_addr       = 0
        self.mft_mirr       = 0
        self.mft_mirr_addr  = 0
        self.mft_size       = 0
        self.image          = image
        self.fd = open(image, 'rb')
        self.data = self.fd.read(512)
        
    def parse(self):
        
        self.sector_sizeH, self.cluster_sizeB, self.mftQ, self.mft_mirrQ, self.mftsizeB = unpack("=11xHB34xQQB", self.data[:65])
        self.mft_addr      = hex(self.sector_size*self.cluster_size*self.mft)
        self.mft_mirr_addr = hex(self.sector_size*self.cluster_size*self.mft_mirr)

        self.mft_size = bin(self.mft_size)[2:]
        invert_mftsize = ''.join(
            '0' if (self.mft_size[i] == '1') else '1'
            for i in range(len(self.mft_size))
        )
        self.mft_size = 2**(int(invert_mftsize, base=2) + 1)

        print(f"""   [!] Образ носителя: {self.image}
   [+] |_Размер сектора (байты): {self.sector_size}
   [+] |_Размер кластера (сектор): {self.cluster_size}
   [+] |_Адрес $MFT: {self.mft_addr}
   [+] |_Адрес $MFTMirr: {self.mft_mirr_addr}
   [+] |_Размер одной таблицы MFT (сектора): {self.mft_size}
            """)

        self.fd.seek(int(self.mft_addr, 16), 0)
        self.data = self.fd.read(self.mft_size)

        _type, offset_arr_markers, size_arr_markers, index_LSN, sequence_number, count_links, offset_atr, flag, real_size_entry, allocated_size_entry, address_base_entry, index_new_atr, index_entry = unpack("=0xIHHQHHHHIIQH2xI", self.data[:48])

        if hex(_type) == '0x454c4946':
            _type = "FILE"
        elif hex(_type) == '0x58444e49':
            _type = "INDX"
        elif hex(_type) == '0x454c4f48':
            _type = "HOLE"
        elif hex(_type) == '0x444b4843':
            _type = "CHKD"
        elif hex(_type) == '0x44414142':
            _type = "BAAD"

        print(f"""   [!] таблица MFT
   [+] |_Тип записи: {_type}
   [+] |_Смещение массива маркеров: {offset_arr_markers}
   [+] |_Количество элементов в массиве маркеров: {size_arr_markers} 
   [+] |_Номер записи в журнале транзакций: {index_LSN}
   [+] |_Порядковый номер: {sequence_number}
   [+] |_Счетчик ссылок: {count_links}
   [+] |_Смещение первого атрибута: {offset_atr}
   [+] |_Флаг: {flag}
   [+] |_Используемый размер записи MFT: {real_size_entry}
   [+] |_Выделенный размер записи MFT: {allocated_size_entry}
   [+] |_Адрес базовой записи MFT: {address_base_entry}
   [+] |_Идентификатор для нового атрибута: {index_new_atr}
   [+] |_Номер файловой записи: {index_entry}
        """)
a=Ntfs("floppy_04.img")
a.parse()