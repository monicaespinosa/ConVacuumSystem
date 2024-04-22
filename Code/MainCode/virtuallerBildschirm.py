import serial.tools.list_ports
from graphics import *

def main():
    screen_state=0
    arrow_state=0
    win=GraphWin("Program",500,300)
    aCircle=Circle(Point(300, (arrow_state+2)*20+10), 5)
    aCircle.setFill("blue")
    aCircle.setOutline("blue")

    msg=state_machine(screen_state,arrow_state,win)
    for i in msg:
        i.draw(win)

    state_aux=screen_state

    while True:
        if serialInst.in_waiting:
            packet=serialInst.readline()
            received_string=packet.decode('utf').rstrip('\n')
            print(received_string)
            state=change_state(received_string)
        if state_aux!=screen_state:
            for i in msg: i.undraw()
            msg=state_machine(screen_state,arrow_state,win)
            for i in msg: i.draw(win)
            if screen_state==1: aCircle.draw(win)
            else: aCircle.undraw()
            state_aux=screen_state
        key=win.getKey()
        if (key=="c")|(key=="C"):
            screen_state=screen_state+1
            if screen_state==6: break

''' 
def change_state(in_string):
    char_list=list(in_string)
    counter=0
    for i in char_list:
        if char_list[counter]==" ":
'''


def PressureScreen(TPStatus, BPStatus, pressure1, pressure2):
    msg=[]
    str="Turbo Pump Status: "
    text_cursor=(len(str)/2)+70
    msg.append(Text(Point(text_cursor,50), str))
    text_cursor=text_cursor+len(str)*4.8
    
    if TPStatus==0:
        str="OFF"
        color="red"
    else:
        str="ON"
        color="green"
    msg.append(Text(Point(text_cursor,50), str))
    msg[len(msg)-1].setTextColor(color)
    str="Back Pump Status: "
    text_cursor=(len(str)/2)+70
    msg.append(Text(Point(text_cursor,70), str))
    text_cursor=text_cursor+len(str)*4.8
    if BPStatus==1:
        str="ON"
    else:
        str="OFF"
        color="red"
    msg.append(Text(Point(text_cursor,70), str))
    msg[len(msg)-1].setTextColor(color)
    str="Pressure"
    text_cursor=(len(str)/2)*12
    msg.append(Text(Point(text_cursor,110), str))
    msg[len(msg)-1].setStyle("bold")
    str="ITR090: "
    text_cursor=(len(str)/2)*12
    msg.append(Text(Point(text_cursor,130), str))
    text_cursor=text_cursor+len(str)*6
    msg.append(Text(Point(text_cursor,130), pressure1))
    text_cursor=text_cursor+len(str)*4.8
    msg.append(Text(Point(text_cursor,130), " mbar"))
    str="RPT010: "
    text_cursor=(len(str)/2)*12
    msg.append(Text(Point(text_cursor,150), str))
    text_cursor=text_cursor+len(str)*6
    msg.append(Text(Point(text_cursor,150), pressure2))
    text_cursor=text_cursor+len(str)*4.8
    msg.append(Text(Point(text_cursor,150), " mbar"))
    str="Press OK for settings"
    text_cursor=(len(str)/2)*9
    msg.append(Text(Point(text_cursor,190), str))
    msg[len(msg)-1].setTextColor("blue")


    return msg
    
def MenuScreen(TPStatus, BPStatus):
    msg=[]
    str="Conf. "
    text_cursor=(len(str)/2)+35
    msg.append(Text(Point(text_cursor,20), str))
    msg[len(msg)-1].setStyle("bold")
    str="Turn Back Pump "
    text_cursor=(len(str)/2)+70
    msg.append(Text(Point(text_cursor,50), str))
    text_cursor=text_cursor+len(str)*4.8
    
    if TPStatus==0:
        str="ON"
        color="green"
    else:
        str="OFF"
        color="red"
    msg.append(Text(Point(text_cursor,50), str))
    msg[len(msg)-1].setTextColor(color)
    str="Turn Turbo Pump "
    text_cursor=(len(str)/2)+73
    msg.append(Text(Point(text_cursor,70), str))
    text_cursor=text_cursor+len(str)*4.8
    if BPStatus==1:
        str="OFF"
    else:
        str="ON"
        color="green"
    msg.append(Text(Point(text_cursor,70), str))
    msg[len(msg)-1].setTextColor(color)

    str="Open Temperature Screen"
    text_cursor=(len(str)/2)+100
    msg.append(Text(Point(text_cursor,90), str))
    str="Other settings"
    text_cursor=(len(str)/2)+61
    msg.append(Text(Point(text_cursor,110), str))

    return msg

def TempScreen(temElec, tempMotor, tempPmpBot):
    msg=[]
    str="Temperature Screen"
    text_cursor=(len(str)/2)+80
    msg.append(Text(Point(text_cursor,20), str))
    msg[len(msg)-1].setStyle("bold")
    str="Electronics: "
    text_cursor=(len(str)/2)+50
    msg.append(Text(Point(text_cursor,50), str))
    text_cursor=text_cursor+len(str)*4.8
    msg.append(Text(Point(text_cursor,50), temElec))
    text_cursor=text_cursor+len(temElec)*10
    msg.append(Text(Point(text_cursor,50), " °C"))
    str="Bearings: "
    text_cursor=(len(str)/2)+45
    msg.append(Text(Point(text_cursor,70), str))
    text_cursor=text_cursor+len(str)*4.8
    msg.append(Text(Point(text_cursor,70), tempPmpBot))
    text_cursor=text_cursor+len(temElec)*10
    msg.append(Text(Point(text_cursor,70), " °C"))
    str="Motor: "
    text_cursor=(len(str)/2)+35
    msg.append(Text(Point(text_cursor,90), str))
    text_cursor=text_cursor+len(str)*4.8
    msg.append(Text(Point(text_cursor,90), tempMotor))
    text_cursor=text_cursor+len(temElec)*10
    msg.append(Text(Point(text_cursor,90), " °C"))
    return msg

def TempSettings():
    msg=[]
    str="Temperature Settings Screen"
    text_cursor=(len(str)/2)+110
    msg.append(Text(Point(text_cursor,20), str))
    msg[len(msg)-1].setStyle("bold")
    return msg

def BastaetigungScreen(PumpStatus, PumpSelection):
    msg=[]
    str="Turn "
    text_cursor=(len(str)/2)+170
    msg.append(Text(Point(text_cursor,110), str))
    text_cursor=text_cursor+pow((len(str)),2.55)

    if PumpSelection==0:
        str="Back Pump "
    else:
        str="Turbo Pump "
    msg.append(Text(Point(text_cursor,110), str))
    text_cursor=text_cursor+pow((len(str)),1.77)
    
    if PumpStatus==0:
        str="ON?"
        color="green"
    else:
        str="OFF?"
        color="red"

    msg.append(Text(Point(text_cursor,110), str))
    msg[len(msg)-1].setTextColor(color)
    return msg

def state_machine(screen_state, arrow_state, win):
    match screen_state:
            case 0: msg=PressureScreen(0, 0, 1000, 960)
            case 1: msg=MenuScreen(0,0)
            case 2: msg=TempScreen("19", "20", "21")
            case 3: msg=TempSettings()
            case 4: msg=BastaetigungScreen(0, 0)
            case 5: msg=BastaetigungScreen(0, 1)
            case _: msg=PressureScreen(0, 0, 1000, 960)
    return msg

ports=serial.tools.list_ports.comports()
serialInst = serial.Serial()

portList=[]

for onePort in ports:
    portList.append(str(onePort))
    print (str(onePort))

val = input("Select port: COM")

for x in range(0, len(portList)):
    if portList[x].startswith("COM" + str(val)):
        portVar="COM"+ str(val)
        print(portList[x])

serialInst.baudrate=9600
serialInst.port=portVar
serialInst.open()

main()

serialInst.close()
