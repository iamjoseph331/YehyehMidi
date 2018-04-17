#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Feb  4 23:16:37 2018

@author: home
"""
import tkinter as tk
import os
import sys
def show_values():
    dname = os.path.dirname(sys.argv[0])
    os.chdir(dname)
    file = open('../../configs/config1','a')
    file.write('PATH_9_CHORD_MAJ:\t%s\t%s\t%s\t%s\t%s\n'%(e1.get(),f1.get(),p1.get(),s1.get(),v1.get()))
    file.write('PATH_9_CHORD_MIN:\t%s\t%s\t%s\t%s\t%s\n'%(e2.get(),f2.get(),p2.get(),s2.get(),v2.get()))
    file.write('PATH_9_CHORD_DOMINANT:\t%s\t%s\t%s\t%s\t%s\n'%(e3.get(),f3.get(),p3.get(),s3.get(),v3.get()))
    file.write('PATH_7_CHORD_MAJ:\t%s\t%s\t%s\t%s\t%s\n'%(e4.get(),f4.get(),p4.get(),s4.get(),v4.get()))
    file.write('PATH_7_CHORD_MIN:\t%s\t%s\t%s\t%s\t%s\n'%(e5.get(),f5.get(),p5.get(),s5.get(),v5.get()))
    file.write('PATH_7_CHORD_DOMINANT:\t%s\t%s\t%s\t%s\t%s\n'%(e6.get(),f6.get(),p6.get(),s6.get(),v6.get()))
    file.write('PATH_7_CHORD_MINMAJ:\t%s\t%s\t%s\t%s\t%s\n'%(e7.get(),f7.get(),p7.get(),s7.get(),v7.get()))
    file.write('PATH_7_CHORD_HALFDIM:\t%s\t%s\t%s\t%s\t%s\n'%(e8.get(),f8.get(),p8.get(),s8.get(),v8.get()))
    file.write('PATH_7_CHORD_DIM:\t%s\t%s\t%s\t%s\t%s\n'%(e9.get(),f9.get(),p9.get(),s9.get(),v9.get()))
    file.write('PATH_7_CHORD_AUGMAJ:\t%s\t%s\t%s\t%s\t%s\n'%(e10.get(),f10.get(),p10.get(),s10.get(),v10.get()))
    file.write('PATH_7_CHORD_AUGDOM:\t%s\t%s\t%s\t%s\t%s\n'%(e11.get(),f11.get(),p11.get(),s11.get(),v11.get()))
    file.write('PATH_3_CHORD_MAJ:\t%s\t%s\t%s\t%s\t%s\n'%(e12.get(),f12.get(),p12.get(),s12.get(),v12.get()))
    file.write('PATH_3_CHORD_MIN:\t%s\t%s\t%s\t%s\t%s\n'%(e13.get(),f13.get(),p13.get(),s13.get(),v13.get()))
    file.write('PATH_3_CHORD_DIM:\t%s\t%s\t%s\t%s\t%s\n'%(e14.get(),f14.get(),p14.get(),s14.get(),v14.get()))
    file.write('PATH_3_CHORD_AUG:\t%s\t%s\t%s\t%s\t%s\n'%(e15.get(),f15.get(),p15.get(),s15.get(),v15.get()))
    file.write('PATH_CHORD_OTHER:\t%s\t%s\t%s\t%s\t%s\n'%(e16.get(),f16.get(),p16.get(),s16.get(),v16.get()))
    master.destroy()

master = tk.Tk()
master.resizable(width=False, height=False)
master.geometry('{}x{}'.format(500, 900))

l1 = tk.Label(master,text = 'PATH_9_CHORD_MAJ')
l1.grid(row=1,column=0)
c1 = tk.Label(master,text = 'frames')
c1.grid(row=1,column=1)
c2 = tk.Label(master,text = 'policy')
c2.grid(row=1,column=2)
c3 = tk.Label(master,text = 'size')
c3.grid(row=1,column=3)
c4 = tk.Label(master,text = 'vol_s')
c4.grid(row=1,column=4)

e1 = tk.Entry(master,width=20)
e1.insert(0,'NONE')
e1.grid(row=2,column=0)
f1 = tk.Entry(master,width=5)
f1.insert(0,'1')
f1.grid(row=2,column=1)
p1 = tk.Entry(master,width=5)
p1.insert(0,'1')
p1.grid(row=2,column=2)
s1 = tk.Entry(master,width=5)
s1.insert(0,'4')
s1.grid(row=2,column=3)
v1 = tk.Entry(master,width=5)
v1.insert(0,'1')
v1.grid(row=2,column=4)

l2 = tk.Label(master,text = 'PATH_9_CHORD_MIN')
l2.grid(row=3,column=0)
e2 = tk.Entry(master,width=20)
e2.insert(0,'NONE')
e2.grid(row=4,column=0)
f2 = tk.Entry(master,width=5)
f2.insert(0,'1')
f2.grid(row=4,column=1)
p2 = tk.Entry(master,width=5)
p2.insert(0,'1')
p2.grid(row=4,column=2)
s2 = tk.Entry(master,width=5)
s2.insert(0,'4')
s2.grid(row=4,column=3)
v2 = tk.Entry(master,width=5)
v2.insert(0,'1')
v2.grid(row=4,column=4)

l3 = tk.Label(master,text = 'PATH_9_CHORD_DOMINANT')
l3.grid(row=5,column=0)
e3 = tk.Entry(master,width=20)
e3.insert(0,'NONE')
e3.grid(row=6,column=0)
f3 = tk.Entry(master,width=5)
f3.insert(0,'1')
f3.grid(row=6,column=1)
p3 = tk.Entry(master,width=5)
p3.insert(0,'1')
p3.grid(row=6,column=2)
s3 = tk.Entry(master,width=5)
s3.insert(0,'4')
s3.grid(row=6,column=3)
v3 = tk.Entry(master,width=5)
v3.insert(0,'1')
v3.grid(row=6,column=4)

l4 = tk.Label(master,text = 'PATH_7_CHORD_MAJ')
l4.grid(row=7,column=0)
e4 = tk.Entry(master,width=20)
e4.insert(0,'NONE')
e4.grid(row=8,column=0)
f4 = tk.Entry(master,width=5)
f4.insert(0,'1')
f4.grid(row=8,column=1)
p4 = tk.Entry(master,width=5)
p4.insert(0,'1')
p4.grid(row=8,column=2)
s4 = tk.Entry(master,width=5)
s4.insert(0,'4')
s4.grid(row=8,column=3)
v4 = tk.Entry(master,width=5)
v4.insert(0,'1')
v4.grid(row=8,column=4)

l5 = tk.Label(master,text = 'PATH_7_CHORD_MIN')
l5.grid(row=9,column=0)
e5 = tk.Entry(master,width=20)
e5.insert(0,'NONE')
e5.grid(row=10,column=0)
f5 = tk.Entry(master,width=5)
f5.insert(0,'1')
f5.grid(row=10,column=1)
p5 = tk.Entry(master,width=5)
p5.insert(0,'1')
p5.grid(row=10,column=2)
s5 = tk.Entry(master,width=5)
s5.insert(0,'4')
s5.grid(row=10,column=3)
v5 = tk.Entry(master,width=5)
v5.insert(0,'1')
v5.grid(row=10,column=4)

l6 = tk.Label(master,text = 'PATH_7_CHORD_DOMINANT')
l6.grid(row=11,column=0)
e6 = tk.Entry(master,width=20)
e6.insert(0,'NONE')
e6.grid(row=12,column=0)
f6 = tk.Entry(master,width=5)
f6.insert(0,'1')
f6.grid(row=12,column=1)
p6 = tk.Entry(master,width=5)
p6.insert(0,'1')
p6.grid(row=12,column=2)
s6 = tk.Entry(master,width=5)
s6.insert(0,'4')
s6.grid(row=12,column=3)
v6 = tk.Entry(master,width=5)
v6.insert(0,'1')
v6.grid(row=12,column=4)

l7 = tk.Label(master,text = 'PATH_7_CHORD_MINMAJ')
l7.grid(row=13,column=0)
e7 = tk.Entry(master,width=20)
e7.insert(0,'NONE')
e7.grid(row=14,column=0)
f7 = tk.Entry(master,width=5)
f7.insert(0,'1')
f7.grid(row=14,column=1)
p7 = tk.Entry(master,width=5)
p7.insert(0,'1')
p7.grid(row=14,column=2)
s7 = tk.Entry(master,width=5)
s7.insert(0,'4')
s7.grid(row=14,column=3)
v7 = tk.Entry(master,width=5)
v7.insert(0,'1')
v7.grid(row=14,column=4)

l8 = tk.Label(master,text = 'PATH_7_CHORD_HALFDIM')
l8.grid(row=15,column=0)
e8 = tk.Entry(master,width=20)
e8.insert(0,'NONE')
e8.grid(row=16,column=0)
f8 = tk.Entry(master,width=5)
f8.insert(0,'1')
f8.grid(row=16,column=1)
p8 = tk.Entry(master,width=5)
p8.insert(0,'1')
p8.grid(row=16,column=2)
s8 = tk.Entry(master,width=5)
s8.insert(0,'4')
s8.grid(row=16,column=3)
v8 = tk.Entry(master,width=5)
v8.insert(0,'1')
v8.grid(row=16,column=4)

l9 = tk.Label(master,text = 'PATH_7_CHORD_DIM')
l9.grid(row=17,column=0)
e9 = tk.Entry(master,width=20)
e9.insert(0,'NONE')
e9.grid(row=18,column=0)
f9 = tk.Entry(master,width=5)
f9.insert(0,'1')
f9.grid(row=18,column=1)
p9 = tk.Entry(master,width=5)
p9.insert(0,'1')
p9.grid(row=18,column=2)
s9 = tk.Entry(master,width=5)
s9.insert(0,'4')
s9.grid(row=18,column=3)
v9 = tk.Entry(master,width=5)
v9.insert(0,'1')
v9.grid(row=18,column=4)

l10 = tk.Label(master,text = 'PATH_7_CHORD_AUGMAJ')
l10.grid(row=19,column=0)
e10 = tk.Entry(master,width=20)
e10.insert(0,'NONE')
e10.grid(row=20,column=0)
f10 = tk.Entry(master,width=5)
f10.insert(0,'1')
f10.grid(row=20,column=1)
p10 = tk.Entry(master,width=5)
p10.insert(0,'1')
p10.grid(row=20,column=2)
s10 = tk.Entry(master,width=5)
s10.insert(0,'4')
s10.grid(row=20,column=3)
v10 = tk.Entry(master,width=5)
v10.insert(0,'1')
v10.grid(row=20,column=4)

l11 = tk.Label(master,text = 'PATH_7_CHORD_AUGDOM')
l11.grid(row=21,column=0)
e11 = tk.Entry(master,width=20)
e11.insert(0,'NONE')
e11.grid(row=22,column=0)
f11 = tk.Entry(master,width=5)
f11.insert(0,'1')
f11.grid(row=22,column=1)
p11 = tk.Entry(master,width=5)
p11.insert(0,'1')
p11.grid(row=22,column=2)
s11 = tk.Entry(master,width=5)
s11.insert(0,'4')
s11.grid(row=22,column=3)
v11 = tk.Entry(master,width=5)
v11.insert(0,'1')
v11.grid(row=22,column=4)

l12 = tk.Label(master,text = 'PATH_3_CHORD_MAJ')
l12.grid(row=23,column=0)
e12 = tk.Entry(master,width=20)
e12.insert(0,'NONE')
e12.grid(row=24,column=0)
f12 = tk.Entry(master,width=5)
f12.insert(0,'1')
f12.grid(row=24,column=1)
p12 = tk.Entry(master,width=5)
p12.insert(0,'1')
p12.grid(row=24,column=2)
s12 = tk.Entry(master,width=5)
s12.insert(0,'4')
s12.grid(row=24,column=3)
v12 = tk.Entry(master,width=5)
v12.insert(0,'1')
v12.grid(row=24,column=4)

l13 = tk.Label(master,text = 'PATH_3_CHORD_MIN')
l13.grid(row=25,column=0)
e13 = tk.Entry(master,width=20)
e13.insert(0,'NONE')
e13.grid(row=26,column=0)
f13 = tk.Entry(master,width=5)
f13.insert(0,'1')
f13.grid(row=26,column=1)
p13 = tk.Entry(master,width=5)
p13.insert(0,'1')
p13.grid(row=26,column=2)
s13 = tk.Entry(master,width=5)
s13.insert(0,'4')
s13.grid(row=26,column=3)
v13 = tk.Entry(master,width=5)
v13.insert(0,'1')
v13.grid(row=26,column=4)

l14 = tk.Label(master,text = 'PATH_3_CHORD_DIM')
l14.grid(row=27,column=0)
e14 = tk.Entry(master,width=20)
e14.insert(0,'NONE')
e14.grid(row=28,column=0)
f14 = tk.Entry(master,width=5)
f14.insert(0,'1')
f14.grid(row=28,column=1)
p14 = tk.Entry(master,width=5)
p14.insert(0,'1')
p14.grid(row=28,column=2)
s14 = tk.Entry(master,width=5)
s14.insert(0,'4')
s14.grid(row=28,column=3)
v14 = tk.Entry(master,width=5)
v14.insert(0,'1')
v14.grid(row=28,column=4)

l15 = tk.Label(master,text = 'PATH_3_CHORD_AUG')
l15.grid(row=29,column=0)
e15 = tk.Entry(master,width=20)
e15.insert(0,'NONE')
e15.grid(row=30,column=0)
f15 = tk.Entry(master,width=5)
f15.insert(0,'1')
f15.grid(row=30,column=1)
p15 = tk.Entry(master,width=5)
p15.insert(0,'1')
p15.grid(row=30,column=2)
s15 = tk.Entry(master,width=5)
s15.insert(0,'4')
s15.grid(row=30,column=3)
v15 = tk.Entry(master,width=5)
v15.insert(0,'1')
v15.grid(row=30,column=4)

l16 = tk.Label(master,text = 'PATH_CHORD_OTHER')
l16.grid(row=31,column=0)
e16 = tk.Entry(master,width=20)
e16.insert(0,'NONE')
e16.grid(row=32,column=0)
f16 = tk.Entry(master,width=5)
f16.insert(0,'1')
f16.grid(row=32,column=1)
p16 = tk.Entry(master,width=5)
p16.insert(0,'1')
p16.grid(row=32,column=2)
s16 = tk.Entry(master,width=5)
s16.insert(0,'4')
s16.grid(row=32,column=3)
v16 = tk.Entry(master,width=5)
v16.insert(0,'1')
v16.grid(row=32,column=4)

tk.Button(master, text='Next', width=6, command=show_values).grid(row=33,column=4)
tk.mainloop()