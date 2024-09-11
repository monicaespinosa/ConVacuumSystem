import serial.tools.list_ports
from graphics import *
ports=serial.tools.list_ports.comports()
serialInst = serial.Serial()

portList=[]

"""
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

while True:
    if serialInst.in_waiting:
        packet=serialInst.readline()
        print(packet.decode('utf').rstrip('\n'))

serialInst.close()

"""

def main():
    screen_state=0
    arrow_state=0
    win=GraphWin("Program",500,300)

    msg=PressureScreen(0, 0, 1000, 960)
    for i in msg:
        i.draw(win)
    
    if screen_state==1:
        aCircle=Circle(Point(300, (arrow_state+2)*20+10), 5)
        aCircle.setFill("blue")
        aCircle.setOutline("blue")
        aCircle.draw(win)

    win.getMouse()
    win.close()

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

main()