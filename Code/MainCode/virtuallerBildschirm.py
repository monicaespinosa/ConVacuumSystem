<<<<<<< HEAD
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
=======
import serial.tools.list_ports
import matplotlib.pyplot as plt
import time
from graphics import *
plt.ion()


def main():

    # Plotting settings
    start_time=time.time()
    pressure_array=[1000, 1000]
    time_array=[0,0.1]
    graph=plt.plot(time_array, pressure_array)[0]
    plt.xlabel('Time (s)')
    plt.ylabel('Pressure (mbar)')
    plt.title('RPT 010 Sensor Pressure read')
    ####

    screen_state=0
    arrow_state=0
    
    win=GraphWin("Program",500,300)
    aCircle=Circle(Point(300, (arrow_state+2)*20+10), 5)
    aCircle.setFill("blue")
    aCircle.setOutline("blue")

    msg=state_machine(0,0,0,0,0,0,0,0)
    aux_dict=dict(
        BPStatus='0',
        TPStatus='0',
        pressure1='0',
        pressure2='0',
        temElec='0',
        tempMotor='0',
        tempPmpBot='0',
        screen_state='0',
        arrow_state='0'
    )
    printed_dict=aux_dict
    for i in msg:
        i.draw(win)

    state_aux=screen_state
    

    while True:
        if serialInst.in_waiting:
            packet=serialInst.readline()
            received_string=packet.decode('utf').rstrip('\n')
            decoded_string=read_string(received_string)
            print(decoded_string)
            if (decoded_string['BPStatus']=='0')|(decoded_string['BPStatus']=='1'):
                printed_dict=decoded_string
                if float(decoded_string['pressure1'])!=0: pressure_array.append(float(decoded_string['pressure2']))
                else: pressure_array.append(pressure_array[-1])
                time_array.append(time.time()-start_time)
                graph.remove()
                graph=plt.plot(time_array,pressure_array)[0]
        
        if aux_dict!=printed_dict:
            print("enters")
            for i in msg: i.undraw()
            msg=state_machine(int(printed_dict['screen_state']), 
                              printed_dict['TPStatus'], 
                              printed_dict['BPStatus'], 
                              printed_dict['pressure1'], 
                              printed_dict['pressure2'], 
                              int(printed_dict['temElec']), 
                              int(printed_dict['tempMotor']), 
                              int(printed_dict['tempPmpBot']))
            for i in msg: i.draw(win)
            if printed_dict['screen_state']=='1':
                aCircle.undraw()
                aCircle=Circle(Point(300, (int(printed_dict['arrow_state'])+2)*20+10), 5)
                aCircle.setFill("blue")
                aCircle.setOutline("blue")
                aCircle.draw(win)
            else: aCircle.undraw()
            aux_dict=printed_dict


def read_string(in_string):
    rows=9
    cols=7
    char_matrix=[['0' for _ in range(cols)] for _ in range(rows)]
    char_list=list(in_string)
    row_count=0
    col_count=0
    counter=0
    for i in char_list:
        if char_list[counter]=='h':
            if row_count<8: row_count=row_count+1
            col_count=0
        else: 
            char_matrix[row_count][col_count]=char_list[counter]
            if col_count<6: col_count=col_count+1
        counter=counter+1
    
    in_data=dict(
        BPStatus=char_matrix[0][0],
        TPStatus=char_matrix[1][0],
        pressure1=''.join(char_matrix[2][:]),
        pressure2=''.join(char_matrix[3][:]),
        temElec=''.join(char_matrix[4][:]),
        tempMotor=''.join(char_matrix[5][:]),
        tempPmpBot=''.join(char_matrix[6][4:5]),
        screen_state=char_matrix[7][0],
        arrow_state=char_matrix[8][0]
    )
    return in_data
            
def PressureScreen(TPStatus, BPStatus, pressure1, pressure2):
    msg=[]
    str="Turbo Pump Status: "
    text_cursor=(len(str)/2)+70
    msg.append(Text(Point(text_cursor,50), str))
    text_cursor=text_cursor+len(str)*4.8
    
    if TPStatus=='0':
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
    if BPStatus=='1':
        str="ON"
        color='green'
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
    text_cursor=text_cursor+len(str)*10
    msg.append(Text(Point(text_cursor,130), pressure1))
    text_cursor=text_cursor+len(str)*8
    msg.append(Text(Point(text_cursor,130), " mbar"))
    str="RPT010: "
    text_cursor=(len(str)/2)*12
    msg.append(Text(Point(text_cursor,150), str))
    text_cursor=text_cursor+len(str)*10
    msg.append(Text(Point(text_cursor,150), pressure2))
    text_cursor=text_cursor+len(str)*8
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
    
    if TPStatus=='0':
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
    if BPStatus=='1':
        str="OFF"
        color="red"
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
    
    if PumpStatus=='0':
        str="ON?"
        color="green"
    else:
        str="OFF?"
        color="red"

    msg.append(Text(Point(text_cursor,110), str))
    msg[len(msg)-1].setTextColor(color)
    return msg

def state_machine(screen_state, TPStatus, BPStatus, pressure1, pressure2, temElec, tempMotor, tempPmpBot):
    match screen_state:
            case 0: msg=PressureScreen(TPStatus, BPStatus, pressure1, pressure2)
            case 1: msg=MenuScreen(TPStatus, BPStatus)
            case 2: msg=TempScreen(temElec, tempMotor, tempPmpBot)
            case 3: msg=TempSettings()
            case 4: msg=BastaetigungScreen(BPStatus, 0)
            case 5: msg=BastaetigungScreen(TPStatus, 1)
            case _: msg=PressureScreen(TPStatus, BPStatus, pressure1, pressure2)
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
print("end")
>>>>>>> main
