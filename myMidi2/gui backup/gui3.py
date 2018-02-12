#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Feb  5 15:02:04 2018

@author: home
"""

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
    file.write('PATH_PALINDROME:\t%s\t%s\t%s\t%s\t%s\n'%(e1.get(),f1.get(),p1.get(),s1.get(),v1.get()))
    file.write('PATH_TRIO:\t%s\t%s\t%s\t%s\t%s\n'%(e2.get(),f2.get(),p2.get(),s2.get(),v2.get()))
    file.write('PATH_NOTE:\t%s\t%s\t%s\t%s\t%s\n'%(e3.get(),f3.get(),p3.get(),s3.get(),v3.get()))
    file.write('PATH_BACKGROUND:\t%s\n'%e4.get())
    master.destroy()

master = tk.Tk()
master.resizable(width=False, height=False)
master.geometry('{}x{}'.format(500, 250))

l1 = tk.Label(master,text = 'PATH_PALINDROME')
l1.grid(row=0,column=0)
c1 = tk.Label(master,text = 'frames')
c1.grid(row=0,column=1)
c2 = tk.Label(master,text = 'policy')
c2.grid(row=0,column=2)
c3 = tk.Label(master,text = 'size')
c3.grid(row=0,column=3)
c4 = tk.Label(master,text = 'vol_s')
c4.grid(row=0,column=4)

e1 = tk.Entry(master)
e1.insert(0,'NONE')
e1.grid(row=1,column=0)
f1 = tk.Entry(master,width=5)
f1.insert(0,'1')
f1.grid(row=1,column=1)
p1 = tk.Entry(master,width=5)
p1.insert(0,'1')
p1.grid(row=1,column=2)
s1 = tk.Entry(master,width=5)
s1.insert(0,'4')
s1.grid(row=1,column=3)
v1 = tk.Entry(master,width=5)
v1.insert(0,'1')
v1.grid(row=1,column=4)

l2 = tk.Label(master,text = 'PATH_TRIO')
l2.grid(row=2,column=0)
e2 = tk.Entry(master)
e2.insert(0,'NONE')
e2.grid(row=3,column=0)
f2 = tk.Entry(master,width=5)
f2.insert(0,'1')
f2.grid(row=3,column=1)
p2 = tk.Entry(master,width=5)
p2.insert(0,'1')
p2.grid(row=3,column=2)
s2 = tk.Entry(master,width=5)
s2.insert(0,'4')
s2.grid(row=3,column=3)
v2 = tk.Entry(master,width=5)
v2.insert(0,'1')
v2.grid(row=3,column=4)

l3 = tk.Label(master,text = 'PATH_NOTE')
l3.grid(row=4,column=0)
e3 = tk.Entry(master)
e3.insert(0,'NONE')
e3.grid(row=5,column=0)
f3 = tk.Entry(master,width=5)
f3.insert(0,'1')
f3.grid(row=5,column=1)
p3 = tk.Entry(master,width=5)
p3.insert(0,'1')
p3.grid(row=5,column=2)
s3 = tk.Entry(master,width=5)
s3.insert(0,'4')
s3.grid(row=5,column=3)
v3 = tk.Entry(master,width=5)
v3.insert(0,'1')
v3.grid(row=5,column=4)

l4 = tk.Label(master,text = 'PATH_BACKGROUND')
l4.grid(row=6,column=0)
e4 = tk.Entry(master)
e4.insert(0,'NONE')
e4.grid(row=7,column=0)

tk.Button(master, text='Start', width=6, command=show_values).grid(row=8,column=0)
tk.mainloop()
