import discord
import serial

LEFT   = 3
RIGHT  = 2
UP     = 4
DOWN   = 5
CENTER = 6

ser = serial.Serial('COM3', 9600, timeout=1)
ser.read(), ser.read() # These are required for some reason

with open('../../CAMERABOT_TOKEN') as tokenFile:
    TOKEN = tokenFile.readline()

client = discord.Client()

@client.event
async def on_message(message):
    # Ignore messages sent by beanbot.
    if message.author == client.user:
        return

    if message.content.startswith('!left'):
        ser.write(LEFT.to_bytes(1, byteorder='big'))
    
    if message.content.startswith('!right'):
        ser.write(RIGHT.to_bytes(1, byteorder='big'))

    if message.content.startswith('!up'):
        ser.write(UP.to_bytes(1, byteorder='big'))
    
    if message.content.startswith('!down'):
        ser.write(DOWN.to_bytes(1, byteorder='big'))

    if message.content.startswith('!center'):
        ser.write(CENTER.to_bytes(1, byteorder='big'))

@client.event
async def on_ready():
    print('Logged in!')

try:
    client.run(TOKEN)
except:
    ser.close()
