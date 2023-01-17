from telethon.sync import TelegramClient
from telethon import TelegramClient
from telethon.tl.functions.messages import GetDialogsRequest
from telethon.tl.types import InputPeerEmpty
import details as ds
import csv
import os
#apiID = 14083279
#apiHash = '81090a24b245e6ec777f19b6024f684f'
#number = '89504824072'

#Login details
api_id = ds.apiID
api_hash = ds.apiHash
phone = ds.number
client = TelegramClient(phone, api_id, api_hash)

client.connect()
if not client.is_user_authorized():
    client.send_code_request(phone)
    client.sign_in(phone, input('Введите код подтверждения: '))

chats = []
last_date = None
chunk_size = 200
groups=[]

result = client(GetDialogsRequest(
             offset_date=last_date,
             offset_id=0,
             offset_peer=InputPeerEmpty(),
             limit=chunk_size,
             hash = 0
         ))
chats.extend(result.chats)

for chat in chats:
    try:
        if chat.megagroup == True:
            groups.append(chat)
    except:
        continue
print('Choose a group to scrape members from:')

for i, g in enumerate(groups):
    print(f'{str(i)}- {g.title}')
g_index = input("Enter a Number: ")
target_group = groups[int(g_index)]

print(f'Fetching members for{target_group.title}...')
all_participants = []
all_participants = client.get_participants(target_group, aggressive=True)
print(all_participants)
print('Saving to ./memberlists...')
directory = './memberlists'
try:
    os.makedirs(directory)
except FileExistsError:
    pass

name_clean = target_group.title
alphanumeric = "".join(
    character for character in name_clean if character.isalnum()
)
file_name = f"./memberlists/{alphanumeric}_members.csv"
value_users = all_participants.total
print('Writing in to file...')
with open(file_name,"w",encoding='UTF-8') as f:
    writer = csv.writer(f,delimiter=",",lineterminator="\n")
    writer.writerow(['Количество пользователей' + ' '+ str(value_users)])
    writer.writerow(['||Логин||'+'||Имя||'+'||ID||'+'||phone||'])#+'|Название Чата|'+'|Чат ID|'
    for user in all_participants:
        username = user.username or ""
        first_name = user.first_name or ""
        last_name = user.last_name or ""
        phone_num = user.phone or ""
        name = f'{first_name} {last_name}'.strip()
        writer.writerow(['||'+"Login:"+str(username)+'||'+"Name:"+str(name)+'||'+"ID:"+str(user.id)+'||'+"||"+'+'+str(phone_num)]) #+'|'+str(target_group.title)+'|'+str(target_group.id)+'|'

print('Done.')

again = input('Again? (y/n)')
if again == 'y':
    print('Restarting...')
    exec(open("members.py").read())
launcher = input('Do you want to return to the launcher? (y/n)')
if launcher == 'y':
    print('Restarting...')
    exec(open("telepathy.py").read())
else:
    print('Bye')
