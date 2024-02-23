import pyautogui as pyg
import webbrowser as wb
import mechanicalsoup as ms
from datetime import datetime
import time
import clipboard

#VALIDATION: Date indicates SIGN UP DATE (24 hours/1 day before the class)
# Monday   : Done
# Tuesday  : Done
# Wednesday: Done
# Thursday : Done
# Friday   : 
#
# Sunday   : Semi-done

#Drag cursor to top left of screen to abort
pyg.FAILSAFE = True
def open_site(url):
    wb.get(using='chrome').open(url, new=2)

#2 second delay
def delay(): 
    time.sleep(2)

def copy(x, y):
    pyg.click(x, y)
    pyg.hotkey('command', 'a')
    pyg.hotkey('command', 'c')

def clipMatch(str):
    return str in clipboard.paste()

def login(u, pw): 
    pyg.click(x=500, y=300)  # Username
    pyg.press('backspace', presses=20)
    pyg.write(u)
    pyg.click(x=500, y=400)  # Password
    pyg.press('backspace', presses=20)
    pyg.write(pw)
    pyg.click(x=500, y=450)  # Submit Login
    delay()

signinurl = "https://ucfrwc.org/Program/GetProgramDetails?courseId=3e5e88e3-af95-4a1e-b73d-2f686277f021&semesterId=797ad251-03c6-4af9-a0d8-252c8e01b788"
user = "la947280"
password = "tRacy1974!"
date = datetime.today().weekday()  # 0 is Monday, goes to 6.

open_site(signinurl)
delay()
# Check if logged in
copy(1340, 170)  # Click login button + copy page contents to validate sign in status
if (not clipMatch("LAUREN ROBINSON")):
    pyg.click(x=720, y=255)  # UCF NID
    delay()
    copy(600, 60)  # Check URL in case of prior authentication
    if(not clipMatch("GetProgramDetails?courseId")):
        login(user, password)

# Check sign up date
if (date == 2 or date == 4):
    pyg.click(225, 950)  # 2nd class in list
if (date == 6 or date == 0):
    pyg.click(1000, 800)  # 3rd class in list
if (date == 3):
    pyg.scroll(-2)
    pyg.click(225, 899)  # 4th class in list (Thursday)
if (date == 1):
    pyg.scroll(-1)
    pyg.click(600, 899)   # 5th position (Wednesday)

if(clipMatch("relatedRegistrationId")): #Correct registration link clicked, continue with signup
    delay()
    pyg.click(1200, 600)
    delay()
    pyg.click(1250, 820)
    delay()
    pyg.click(950, 300)
    delay()
    print("Full effort at your F45 session. I love you, my fit focused female <3 ")
else:
    print("Already signed up, or the system broke, I'll fix it.")
