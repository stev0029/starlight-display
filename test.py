import tkinter


def wheel(pos):
    # Input a value 0 to 255 to get a color value.
    # The colours are a transition r - g - b - back to r.
    if pos < 0 or pos > 255:
        return (0, 0, 0)
    if pos < 85:
        return (255 - pos * 3, pos * 3, 0)
    if pos < 170:
        pos -= 85
        return (0, 255 - pos * 3, pos * 3)
    pos -= 170
    return (pos * 3, 0, 255 - pos * 3)


def toHexString(r, g, b):
    return '#%02x%02x%02x' % (r, g, b)


def setBackground(x):
    a = toHexString(*wheel(int(x)))
    print(a)
    top['background'] = a

top = tkinter.Tk()
top['background'] = '#FF00FF'

var = tkinter.IntVar()
w = tkinter.Scale(top, command=setBackground, to=255)
w.pack()

top.mainloop()
