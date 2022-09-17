import os
import random
import csv
import telebot
from telebot import types
bot = telebot.TeleBot('5147509582:AAHmdcKf7Vja3n9Wt22L1Bg7z36xTW2g9nU');

class Stack:
    def __init__(self):
        self.stack = []
    def push(self, item):
        self.stack.append(item)
    def pop(self):
        if len(self.stack) == 0:
            return None
        removed = self.stack.pop()
        return removed

def read_file(file):
    f1 = []
    with open(file, encoding='utf-8') as r_file:
    
        file_reader = csv.reader(r_file, delimiter = ",")
        for row in file_reader:
            f1.append(row[1])
    return f1

def randomstroka():
    f1 = []
    f2 = []
    tmp = 0
    buf = []
    f1,f2 = read_file("test.csv"),read_file("train.csv")

    randomfile = random.randint(1,2)
    if randomfile == 1:
        randomfile = f1
        tmp = 1
    elif randomfile == 2:
        randomfile = f2
        tmp = 2
    nomer = random.randint(0,len(f1))

    buf.append(randomfile[nomer])
    buf.append(str(tmp))
    return buf

@bot.message_handler(commands=["start"])

def start(message, res=False,buf = []):
       
        
        markup=types.ReplyKeyboardMarkup(resize_keyboard=True)
        item1=types.KeyboardButton("1")
        item2=types.KeyboardButton("2")
        item3 = types.KeyboardButton("/start")
        markup.add(item1)
        markup.add(item2)
        markup.add(item3)

        buf = randomstroka()
        bot.send_message(message.chat.id,"Из какого это файла :\n" + '"'+buf[0]+'"',reply_markup=markup)
        
        @bot.message_handler(content_types=["text"])
        
        def handle_text(message):
            
            get = message.text.strip()
            
            if get == buf[1]:
                answer = "правильно :) Жми на старт для перезапуска"
                bot.send_message(message.chat.id, answer)

            else:
                answer = "gg Жми на старт для перезапуска"
                bot.send_message(message.chat.id, answer)

#bot.infinity_polling()
bot.polling(none_stop=True, interval=0)