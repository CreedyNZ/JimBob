#!/usr/bin/env python

""" 
  Core code for Hexapod         
  Copyright (c)  2015 Andrew Creahan.  All rights reserved.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software Foundation,
  Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
"""

import sys, time, os
import serial     
import RPi.GPIO as GPIO
#import SerialOut
import config
from espeak import espeak
#from lidar_lite import Lidar_Lite
from AnaSensorData import readsensor
import PServo

##lidar = Lidar_Lite()
anasensor = readsensor()
Maestro = Controller()

a = 0
s = 0
l = 0
r = 0
start_time = time.time()
delay = 0.1  # set rest time between command sends
checksum = 0
GPIO.setmode(GPIO.BCM)
#sensors = ('IR1','IR2','IR3','US')
Maestro.setTarget (5,700)

def startup():
 #   SerialOut.reset()
    Maestro.setTarget (5,700)
    Maestro.setTarget (4,100)
    
def rise():
    x = 0
    while x < 5:
  #      SerialOut.translate(0,0,90)
        time.sleep(0.1)
        x +=1
    x = 0    
    while x < 5:
   #     SerialOut.translate(0,0,-90)
        time.sleep(0.1)
        x +=1
    

def reset():
  #rise()
  pin = 20
  ResetServo()
  time.sleep(5)
  LookL()
  time.sleep(5)
  LookR()
  time.sleep(5)
  ResetServo()
  time.sleep(5)
  #GPIO.setup(pin, GPIO.OUT)
  #GPIO.output(pin, GPIO.HIGH)
  #time.sleep(0.12)
  #GPIO.output(pin, GPIO.LOW)
  #time.sleep(0.12)
  #GPIO.output(pin, GPIO.HIGH)
#Travel = t then angle (0 - 360),speed (0 - 120),rotate (-100 - 100), repeat (0+)
#Rotate = r then left,right,up, repeat
#Translate = r then left,right,up, repeat

walktest = [('t',0,75,0,30),('t',180,75,0,30),('t',90,100,0,20),('t',270,100,0,20),('t',45,50,0,30),('t',135,50,0,30),('t',0,0,50,10),('t',0,0,-50,30)]

""" Startup """
#startup()

#Travel angle,speed,rotate
#Rotate left,right,up
#Translate left,right,up
"""
class Move:
    Class to create movements
    def __init__(self, movearray):
        self.movecount = 0
        self.movearray = movearray

    def moves(self):
          #create move commands for sending to the Arbotix_M
          for k in self.movearray:   
             movearray[k,1] = atrib[k] + 128
          checksum = 0
          self.ser.write(chr(255))
          for k in self.commandtypes:   
             self.ser.write(chr(atrib[k]))
             checksum += int(atrib[k])
          checksum = (255 - (checksum%256))
          print checksum
          self.ser.write(chr(checksum))

          response = serout.read()
          print (">>" ,response)
          self.movecount += 1
          print self.movecount
          print'*'
          print atrib['i_ComMode']

          move_time = time.time()
        
stdpkt  = Move(config.stdatrib, config.addatrib)  #create standard packet 
g=0"""
reset()
startup()
connected = lidar.connect(1)
espeak.synth("Hello, Jim Bob ready to go")
c = 0
config.atrib['i_Gait'] = 0
#SerialOut.wait(25)
print "here1"
sensordata = readsensor()
lidar = lidar.getDistance()
priorread = time.time()+2
print "lidar"
print lidar
print sensordata


def walk():
 #   SerialOut.travel(a,100,0)
    print ('walk ', a)
    
def run():
    global s
    if s == 0:
     espeak.synth("I'm off for a run")
     s = 1  
    config.atrib['i_Gait'] = 5
    print ('run')
  #  SerialOut.travel(a,100,0)

def turnR():
    config.atrib['i_Gait'] = 0
    x = 0
    while x < 5:
   #        SerialOut.travel(0,0,90)
           print ('right')
           time.sleep(0.1)
           x +=1

def turnL():
    x = 0
    config.atrib['i_Gait'] = 0
    while x < 5:
    #       SerialOut.travel(0,0,-90)
           print ('left')
           time.sleep(0.1)
           x +=1         
                      


available_actions = {"walk": walk,
                     "turnR": turnR,
                     "turnL": turnL,
                     "rise": rise,
                     "fastwalk": run}
while 1:
  
  #'RF','LF','FF','PX','PY','LR','DF','PR'
  
  rawdata = readsensor()
  laser  = lidar.getDistance()
  sensordata = {   "LL" : int(laser),
              "US" : int(rawdata[0]),
              "LF" : int(rawdata[1]),
              "RF" : int(rawdata[2])}
  if c > 50:
     s = 0
     l = 0
     r = 0
     c = 0
     #SerialOut.getpkt()
  c += 1  
  if (sensordata["LL"] > 65 and sensordata["LF"] > 40 and sensordata["RF"] > 40):
    if config.atrib['i_Gait'] != 5:
     # SerialOut.wait(10)
      config.atrib['i_Gait'] = 5
      #SerialOut.wait(10)
    a = 0
    global s
    if s == 0:
     espeak.synth("I'm off for a run")
     s = 1  
    action = 'walk'
  elif (sensordata['LL'] > 50 and (sensordata['LF'] > 40 or sensordata ['RF'] > 40)):
    a = 0
    if (sensordata ['LF'] < 25):
       a = (sensordata['RF'] - sensordata ['LF'])
    elif (sensordata ['RF'] < 25):
       a = 360 - (sensordata['LF'] - sensordata ['RF'])
    if config.atrib['i_Gait'] != 0:
      #SerialOut.wait(10)
      config.atrib['i_Gait'] = 0
      #SerialOut.wait(10)
    action = 'walk'
  elif ((sensordata['RF'] > 25) and (sensordata['RF'] > 25)):
     if (sensordata['RF']  > sensordata['RF']):
         action = 'turnL'
     else:
         action = 'turnR'    
  elif (sensordata['RF'] < 25):
     if l == 0:
       espeak.synth("Stuff to my right")
       l = 1  
     action = 'turnL'
  elif (sensordata['LF'] < 25):
    if r == 0:
       espeak.synth("Danger to the left")
       r = 1  
    action = 'turnR'
  else: 
    a = 180 
    espeak.synth("I see trouble ahead")
    action = 'walk'                   
  try:
      available_actions[action]()
  except KeyError:
      print "Unrecognized command ", action
  except NameError:
      print "Unrecognized name "
  time.sleep(0.5)

