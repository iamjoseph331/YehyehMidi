#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Feb  4 17:59:44 2018

@author: Joseph Chen
"""
import tkinter as tk
import os
import sys
def show_values():
    dname = os.path.dirname(sys.argv[0])
    os.chdir(dname)
    file = open('../../configs/config1','w')
    file.write('SET_TEMPO:\t%s\n'%w1.get())
    file.write('SET_NOTE_SHRINK:\t%s\n'%w2.get())
    file.write('SET_SINGLE_NOTE_LEN:\t%s\n'%w3.get())
    file.write('SET_DISAPPEAR_TIME1:\t%s\n'%dis1.get())
    file.write('SET_DISAPPEAR_TIME2:\t%s\n'%dis2.get())
    file.write('SET_DISAPPEAR_TIME3:\t%s\n'%dis3.get())
    file.write('SET_DISAPPEAR_TIME4:\t%s\n'%dis4.get())
    file.write('SET_DISAPPEAR_TIME5:\t%s\n'%dis5.get())
    file.write('SET_DISAPPEAR_TIME6:\t%s\n'%dis6.get())
    file.write('SET_PLINDROME_LAST:\t%s\n'%w4.get())
    file.write('SET_IMAGE_SIZE:\t%s\n'%w5.get())
    file.write('SET_SHRINK_SPEED:\t%s\n'%w6.get())
    file.write('SET_CHORD_GAP:\t%s\n'%w7.get())
    file.write('SET_LAYERS:\t%s\n'%w8.get())
    file.write('SET_TRIO_GAP:\t%s\n'%w9.get())
    master.destroy()

master = tk.Tk()
master.resizable(width=False, height=False)
master.geometry('{}x{}'.format(800, 900))

w1 = tk.Scale(master, from_=1, to=30, length=600, width=10, orient=tk.HORIZONTAL,label='SET_TEMPO')
w1.set(10)
w1.pack()

w2 = tk.Scale(master, from_=1, to=30, length=600, width=10, orient=tk.HORIZONTAL,label='SET_NOTE_SHRINK')
w2.set(8)
w2.pack()

w3 = tk.Scale(master, from_=1, to=1000, length=600, width=10, orient=tk.HORIZONTAL,label='SET_SINGLE_NOTE_LEN')
w3.set(120)
w3.pack()

dis1 = tk.Scale(master, from_=1, to=3000, length=600, width=10, orient=tk.HORIZONTAL,label='SET_DISAPPEAR_TIME1')
dis1.set(2000)
dis1.pack()

dis2 = tk.Scale(master, from_=1, to=3000, length=600, width=10, orient=tk.HORIZONTAL,label='SET_DISAPPEAR_TIME2')
dis2.set(300)
dis2.pack()

dis3 = tk.Scale(master, from_=1, to=3000, length=600, width=10, orient=tk.HORIZONTAL,label='SET_DISAPPEAR_TIME3')
dis3.set(300)
dis3.pack()

dis4 = tk.Scale(master, from_=1, to=3000, length=600, width=10, orient=tk.HORIZONTAL,label='SET_DISAPPEAR_TIME4')
dis4.set(300)
dis4.pack()

dis5 = tk.Scale(master, from_=1, to=3000, length=600, width=10, orient=tk.HORIZONTAL,label='SET_DISAPPEAR_TIME5')
dis5.set(300)
dis5.pack()

dis6 = tk.Scale(master, from_=1, to=3000, length=600, width=10, orient=tk.HORIZONTAL,label='SET_DISAPPEAR_TIME6')
dis6.set(2000)
dis6.pack()

w4 = tk.Scale(master, from_=1, to=3000, length=600, width=10, orient=tk.HORIZONTAL,label='SET_PLINDROME_LAST')
w4.set(1202)
w4.pack()

w5 = tk.Scale(master, from_=1, to=20, length=600, width=10, orient=tk.HORIZONTAL,label='SET_IMAGE_SIZE')
w5.set(3)
w5.pack()

w6 = tk.Scale(master, from_=1, to=10, length=600, width=10, orient=tk.HORIZONTAL,label='SET_SHRINK_SPEED')
w6.set(1)
w6.pack()

w7 = tk.Scale(master, from_=1, to=50, length=600, width=10, orient=tk.HORIZONTAL,label='SET_CHORD_GAP')
w7.set(20)
w7.pack()

w8 = tk.Scale(master, from_=1, to=87, length=600, width=10, orient=tk.HORIZONTAL,label='SET_LAYERS')
w8.set(3)
w8.pack()

w9 = tk.Scale(master, from_=1, to=2000, length=600, orient=tk.HORIZONTAL,label='SET_TRIO_GAP')
w9.set(200)
w9.pack()

tk.Button(master, text='Next', command=show_values).pack()

tk.mainloop()

