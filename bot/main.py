import discord
from discord.ext import commands
'''
class MyClient(discord.Client):
    async def on_ready(self):
        print('Logged on as {0}!.'.format(self.user))
    async def on_message(self,message):
        print('Message form {0.author}: {0.content}'.format(message))
client = MyClient()
client.run('')'''

client = commands.Bot( command_prefix = '-' )
#-hello

@client.event
async def on_ready():
    print("Bot joined {0.user}".format(client))
#comands
@client.command()
async def hello(ctx):
    author = ctx.message.author
    await ctx.send(f"Hi , {author.mention}")

@client.command()
async def all(ctx):
    await ctx.send("{0}everyone".format("@"))

@client.command()
async def zxc(ctx):
    autor = ctx.message.author
    for i in range(5):
        await ctx.send(f"1000-7? {autor.mention}")
        i=i=1

client.run('ODg3NDU4NjAyNjM2NDEwOTMw.YUEcOw.V-ZFeyEV6eiVnwvArlYU2Gvpp-U')