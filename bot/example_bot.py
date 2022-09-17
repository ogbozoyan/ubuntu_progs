import discord

client = discord.Client()

@client.event
async def on_ready():
    print('We have logged in as {0.user}'.format(client))

@client.event
async def on_message(message):
    if message.author == client.user:
        return

    if message.content.startswith('-hello'):#if type this bot will answer 15 
        await message.channel.send('Hello!')
    elif message.content.startswith('-help'):
        await message.channel.send('ya nichego ne ymey')

client.run('ODg3NDU4NjAyNjM2NDEwOTMw.YUEcOw.V-ZFeyEV6eiVnwvArlYU2Gvpp-U')