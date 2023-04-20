import pygame
import websockets
import asyncio
#from websockets.sync.client import connect

#import requests

pygame.joystick.init()

joysticks = [pygame.joystick.Joystick(x) for x in range(pygame.joystick.get_count())]

pygame.init()
JOYSTIC = pygame.joystick.Joystick(0)

#connect to websocket server
async def connect(msg):
   url="ws://localhost:8000"

   async with websockets.connect(url) as websocket:
      await websocket.send(msg)
      

# maping function to convert analog from -1 , 1 to 0 , 255

def translate(value, leftMin, leftMax, rightMin, rightMax):
    # Figure out how 'wide' each range is
    leftSpan = leftMax - leftMin
    rightSpan = rightMax - rightMin

    # Convert the left range into a 0-1 range (float)
    valueScaled = float(value - leftMin) / float(leftSpan)

    # Convert the 0-1 range into a value in the right range.
    return rightMin + (valueScaled * rightSpan)


send_request = ""
program = True

#program loop
while program:

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            program = False

        # تظبيط الزراير اللي ينفع يتداس عليها
        '''if event.type == pygame.JOYBUTTONDOWN:
             if JOYSTIC .get_button(0):
                 events = "X"
             elif JOYSTIC .get_button(1):
                 events = "O"
             elif JOYSTIC .get_button(2):
                 events = "SHOOT"
             elif JOYSTIC .get_button(3):
                 events = "THROW"
             elif JOYSTIC .get_button(4):
                 events = "PAUSE"
             elif JOYSTIC .get_button(5):
                 events = "PS"
             elif JOYSTIC .get_button(6):
                 events = "START"
             elif JOYSTIC .get_button(7):
                 events = "L3"
             elif JOYSTIC .get_button(8):
                 events = "R3"
             elif JOYSTIC .get_button(9):
                 events = "L1"
             elif JOYSTIC .get_button(10):
                 events = "R1"
             elif JOYSTIC .get_button(11):
                 events = "UP"
             elif JOYSTIC .get_button(12):
                 events = "DOWN"
             elif JOYSTIC .get_button(13):
                 events = "RIGHT"
             elif JOYSTIC .get_button(14):
                 events = "Left"
             elif JOYSTIC .get_button(15):
                 events = "SPACE"
             
             print(events)'''

        if event.type == pygame.JOYBUTTONDOWN:
            # L1 is used For stop car
            if JOYSTIC.get_button(10):
                send_request = "R1_Stop"
                print(send_request)
         
               #Send data
                asyncio.get_event_loop().run_until_complete(connect(send_request))
                #requests.request(method="get", url="http://localhost:8000",json={"request" : send_request})

            # shutdown and stop car using PS button
            if JOYSTIC.get_button(5):
                send_request = "PS_Quit"
                print(send_request)
                program = False
                #Send data
                asyncio.get_event_loop().run_until_complete(connect(send_request))
                


        # تظبيط الانالوج علشان مهم
        elif event.type == pygame.JOYAXISMOTION and not JOYSTIC.get_button(10):
           

           # Left analog is used for direction range 0-255 right and same to left
            if JOYSTIC.get_axis(0):
                state = JOYSTIC.get_axis(0)
                if state > .01:
                    Right = translate(state, 0, 1, 0, 255)
                    send_request = "AR_" + str(int(Right)).zfill(3)
                    print(send_request)
                    #Send data
                    asyncio.get_event_loop().run_until_complete(connect(send_request))
                    

                elif state < 0:
                    Left = translate(state, 0, -1, 0, 255)
                    send_request = "AL_" + str(int(Left)).zfill(3)
                    #Send data
                    asyncio.get_event_loop().run_until_complete(connect(send_request))
                    print(send_request)

            '''if JOYSTIC.get_axis(1) > .5 and JOYSTIC.get_axis(0) < -.5:
                print ("down left")  

            elif JOYSTIC.get_axis(1) >.5 and JOYSTIC.get_axis(0) > .5:
                print ("Down right") 

            elif JOYSTIC.get_axis(1) < -.5 and JOYSTIC.get_axis(0) > .5:
                print ("UP right")  

            elif JOYSTIC.get_axis(1) < -.5 and JOYSTIC.get_axis(0) < -.5:
                print ("UP Left")  
'''

            # L2 is used for revers motion range 0-255
            if JOYSTIC.get_axis(4) > -1:
                L2 = JOYSTIC.get_axis(4)
                L2 = translate(L2, -1, 1, 0, 255)
                send_request = "L2_" + str(int(L2)).zfill(3)
                print(send_request)
                #Send data
                asyncio.get_event_loop().run_until_complete(connect(send_request))
                


            # R2 is used for forward motion range 0-255
            elif JOYSTIC.get_axis(5) > -1:
                R2 = JOYSTIC.get_axis(5)
                R2 = translate(R2, -1, 1, 0, 255)
                send_request = "R2_" + str(int(R2)).zfill(3)
                print(send_request)
                #Send data
                asyncio.get_event_loop().run_until_complete(connect(send_request))
                


           # check if joystic disconnected
        if event.type == pygame.JOYDEVICEREMOVED:
            send_request = "Q_Stop"
            print(send_request)
            program = False
            #Send data
            asyncio.get_event_loop().run_until_complete(connect(send_request))
            


    
    

    