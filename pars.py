import struct 

file = open(input('file name: '),'rb')
buf = file.read(512)

sector_size,claster_size,mft_orig,mft_mirr,mft_size = struct.unpack("=11xHB34xQQB",buf[:65])
addr_of_mft = hex(mft_orig*claster_size*mft_orig)
addr_of_mft_mirr = hex(mft_orig*claster_size*mft_mirr)
mft_size = bin(mft_size)[2:]
logical_not_mft_size = ''.join(['1' if i == '0' else '0' for i in mft_size])
mft_size = 2**(int(logical_not_mft_size, base=2) + 1)

file.seek(int(addr_of_mft, 16), 0)
buf = file.read(mft_size)

type_of_zapisi = ['FILE','INDX','HOLE','CHKD','BAAD']

sign,sdvig_mark,size_mark,nomer_jur_trank,order_num,count,offset_first_atr,flag,isp_size_mft,vid_size_zap_mft,addr_baz_mft,ident_of_new_atr,nom_file_zap = struct.unpack("=0xIHHQHHHHIIQH2xI", buf[:48])

if hex(sign) == '0x454c4946':
	sign = type_of_zapisi[0]
elif hex(sign) == '0x58444e49':
	sign = type_of_zapisi[1]
elif hex(sign) == '0x454c4f48':
	sign = type_of_zapisi[2]
elif hex(sign) == '0x444b4843':
	sign = type_of_zapisi[3]
elif hex(sign) == '0x44414142':
	sign = type_of_zapisi[4]

print('')
print("Size of sector",sector_size,'byte')
print("Size of claster",claster_size,'sectors')
print("Size of MFT",mft_size,'byte')
print("Addr of MFT original ",addr_of_mft,'in hex')
print("Addr of MFT Mirror",addr_of_mft_mirr,'in hex')
print('')
print("Type of zapisi", sign)
print("Offset of markers array" , sdvig_mark)
print("Size of marker array", size_mark)
print("Nomer journal of trank", nomer_jur_trank)
print("Porydkoviy nomer", order_num)
print("Count ssilok", count)
print("Smeshenie pervogo attr", offset_first_atr)
print('Flag', flag)
print('Ispol razmer zapisi MFT', isp_size_mft)
print('Videlen razmer zapisi MFT', vid_size_zap_mft)
print('Adr bazov mft', addr_baz_mft)
print('Identifikator for new atr', ident_of_new_atr)
print('Nom file zap', nom_file_zap)
print('')




