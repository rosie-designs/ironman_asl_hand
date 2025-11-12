# November 8, 2025
# Main program that runs the asl detection software

import cv2
import mediapipe as mp
import joblib #importing the saved model
import numpy as np
import serial
import time
import warnings
#import sound
import pygame
import threading
warnings.filterwarnings("ignore")


# Initialize MediaPipe and drawing utilities
mp_hands = mp.solutions.hands
mp_draw = mp.solutions.drawing_utils
cap = cv2.VideoCapture(0)

# Initialize the ASL Model
rf_classifier = joblib.load("asl_model.pkl")


# Text Colours
glow_color = (255, 200, 0)
text_color = (255, 255, 255)

# Communication with the Arduino
#arduino = serial.Serial("COM3", 9600)
time.sleep(2)
canSend = True
prevLetter = ''
newLetter = ''
counter = 0
MAX_COUNT = 50

# Play Start-Up Sound
def play_sound():
    pygame.mixer.init()
    pygame.mixer.music.load("C:\\Users\\rosie\\OneDrive\\Desktop\\BoxbotASL\\jarvis_sound.mp3")
    pygame.mixer.music.play()

#---------------- Start Program------------------------------#
with mp_hands.Hands(
    static_image_mode=False,
    max_num_hands=1,
    min_detection_confidence=0.7,
    min_tracking_confidence=0.7) as hands:

    while True:
        success, img = cap.read()

        if not success:
            break
        
        img = cv2.flip(img, 1) # flip camera

        # convert to RGB for MediaPipe processing
        img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

        # process the frame and detect hands
        results = hands.process(img_rgb)

        # glow code
        glow_result = img.copy()

        # ----------- MODE 1: USER ASL INPUT-------------#
        # if a hand is on screen, proceed
        if results.multi_hand_landmarks:
            for hand_landmarks in results.multi_hand_landmarks:
                mp_draw.draw_landmarks(img, hand_landmarks, mp_hands.HAND_CONNECTIONS)

                # get coordinates relative to the wrist
                wrist = hand_landmarks.landmark[0]
                coords = []
                for lm in hand_landmarks.landmark:
                    coords.extend([lm.x - wrist.x, lm.y-wrist.y, lm.z-wrist.z])
                coords = np.array(coords).reshape(1, -1)

                # use model to predict signed letter
                predicted_letter = rf_classifier.predict(coords)[0]

                # to account for the back and forth between letter
                if (predicted_letter == prevLetter):
                    counter += 1
                else:
                    prevLetter = predicted_letter
                    counter = 0

                # write text on screen
                text = f"Letter: {predicted_letter}"
                text_layer = np.zeros_like(img)
                cv2.putText(text_layer, text, (10, 70), cv2.FONT_HERSHEY_DUPLEX, 2, glow_color, 6, cv2.LINE_AA)
                # glow effect
                glow = cv2.GaussianBlur(text_layer, (25, 25), sigmaX=15)
                glow_result = cv2.addWeighted(img, 1.0, glow, 1.3, 0)
                cv2.putText(glow_result, text, (10, 70), cv2.FONT_HERSHEY_DUPLEX, 2, text_color, 3, cv2.LINE_AA)

                # read serial input from Arduino
                # if arduino.in_waiting > 0:  # only read if data is available
                #     line= arduino.readline().decode().strip()
                #     # only send predicted letter if robot is ready
                #     if line == "Received":
                #         canSend = False
                #     elif line == "Finished":
                #         canSend = True
                #     elif line == "PLAY1":
                #         threading.Thread(target=play_sound).start()
                #     print(line + '\n')

                # to ensure accuracy, prevents sending to many letters 
                # if canSend and counter >= MAX_COUNT:
                #     # send letter to robot/Arduino
                #     arduino.write((predicted_letter + '\n').encode())
                #     print("SENT:", predicted_letter + '\n')
                #     counter = 0
                #     canSend = False

        # ----------- MODE 2: USER MANUAL INPUT-------------#
        else:
            input_letter = chr(cv2.waitKey(1) & 0xFF) # get input
            
            # check if robot is ready
            # if arduino.in_waiting > 0:  # only read if data is available
            #     line = arduino.readline().decode().strip()
            #     if line == "Received":
            #         canSend = False
            #     elif line == "Finished":
            #         canSend = True
            #     elif line == "PLAY1": # play start-up sound
            #             threading.Thread(target=play_sound).start()
            #     print(line + '\n')
            
            # only send upper case letters
            # if input_letter <= 'z' and input_letter >= 'a':
            #     input_letter = input_letter.upper()
            # if input_letter <= 'Z' and input_letter >= 'A' and canSend:
            #     arduino.write((input_letter + '\n').encode())
            #     print("SENT:", input_letter + '\n')
            #     canSend = False
            
        # display the video
        cv2.imshow("ASL Hand Tracker", glow_result)        

        # press 'ESC KEY' to quit or 'X' button
        if cv2.waitKey(1) & 0xFF == 27 or cv2.getWindowProperty("ASL Hand Tracker", cv2.WND_PROP_VISIBLE) < 1:
            break 

# release resources
cap.release()
cv2.destroyAllWindows()
# arduino.close()
