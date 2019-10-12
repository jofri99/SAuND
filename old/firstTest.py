import numpy as np
import cv2
import os

cap=cv2.VideoCapture(0)
img = cv.imread('white.png',0)
i=0
while True:
    ret, frame = cap.read()
    gray=cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
    lowRes=cv2.resize(gray,(32,24))
    lowHighRes=cv2.resize(lowRes,(640,480))

    
    cv2.imshow('frame',lowHighRes)
    cv2.imshow('gray',gray)
    if(i>1):
        os.system('clear')
        for x in lowRes:
            for y in x:
                print(y,end='\t')
            print('')
        i=0
    i=i+1

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break




cap.release()
cv2.destroyAllWindows()