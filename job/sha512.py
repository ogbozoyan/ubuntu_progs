#!/usr/bin/env python 
# -*- coding: utf-8 -*- 
import hashlib
import codecs

def number_format(phone):
	if len(phone) == 12:
		phone = phone[2:]
	elif len(phone) == 11:
		phone = phone[1:]
	return phone
def hasher(var):
	res = hashlib.sha512(var.encode('utf-8'))
	res = res.hexdigest()
	return res

sub_mail = '@'
mail_text = []
nomera = []
with open('mailhash.txt','w+') as mails:
	phones = open('numberhash.txt','w+')

	phone = []
	#открытие файлов
	var = input("Название документа где mail с txt: ")
	with codecs.open(var,"r",encoding='utf-8') as f:
		mail_text = f.read()
	mail_text = mail_text.split()
	var2 = input("Название документа где номера с txt: ")
	with codecs.open(var2,"r",encoding='utf-8') as f1:
		nomera = f1.read()
	nomera = nomera.split(sep='\n')
	#-----------------------------

	for i in range(len(nomera)):
		if nomera[i] == '':
			nomera[i] = '\n'
	#fixing and hashing numbers
	for i in nomera:
		if i.isspace():
			phone.append('\n')
		elif (i[0] == '+' or i.isdigit()) and len(i) in {11, 12}:
			phone.append(i)
	phonefix = [number_format(i) for i in phone]
	for i in phonefix:
		if i == '\n':
			phones.write('\n')
		else:
			i = hasher(i)
			phones.write(i + '\n')
	#hashing mails
	for i in mail_text:
		if sub_mail in i:
			i = i.lower()
			i = hasher(i)
			mails.write(i + '\n')
phones.close()
print("Work done")
