"""
@bot.message_handler(commands=["start"])

def start(m, res=False,buf = []):
       
        
        markup=types.ReplyKeyboardMarkup(resize_keyboard=True)
        item1=types.KeyboardButton("1")
        item2=types.KeyboardButton("2")
        markup.add(item1)
        markup.add(item2)

        buf = randomstroka()
        bot.send_message(m.chat.id,"Из какого это файла :\n" + '"'+buf[0]+'"',reply_markup=markup)
        
        @bot.message_handler(content_types=["text"])
        
        def handle_text(message):
            
            get = message.text.strip()
            
            if get == buf[1]:
                answer = "правильно :)"
                bot.send_message(message.chat.id, answer)

            else:
                answer = "gg"
                bot.send_message(message.chat.id, answer)
               """ 