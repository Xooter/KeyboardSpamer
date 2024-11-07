# NO ANDA EN FIREFOX, ES UNA GARCHA PYTHON

import pyautogui
import time
import random

time.sleep(2)

ls = ["BESOS", "VEZOS", "BBEESOS", "BESO"]

for _ in range(20):
    slp = random.randint(1, 3)
    i = random.randint(0, len(ls) - 1)

    time.sleep(slp)
    pyautogui.write(ls[i], interval=0.1)
    pyautogui.press("enter")
