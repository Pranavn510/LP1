import tkinter as tk
import re

def submit():
    fname = entry_fname.get().strip()
    lname = entry_lname.get().strip()
    email = entry_email.get().strip()
    gender = entry_gender.get().strip()
    password = entry_password.get().strip()

    #validation
    if not fname: 
        print("Enter first name")
    elif not fname.isalpha():
        print("First name should contain only alphabets")
    elif not lname: 
        print("Enter first name")
    elif not lname.isalpha():
        print("First name should contain only alphabets")
    elif not re.match(r"[^@]+@[^@]+\.[^@]+",email):
        print("Enter valid email")
    elif not strong_pass(password):
        print("Password should be least 8 , should contain atleast one Uppercase alphabet , one lowercase alphabet , one symbol")
    elif not gender:
        print("Enter gender")
    elif  gender.lower() not in ["male" , "female" , "other"]:
        print("Invalid gender entered")
    else:
        print(f"INFORMATION!!! \nFirst_Name :{fname} ,Last_name = {lname}, email = {email} , gender = {gender} , password = {password} ")


def strong_pass(password):

    if not any(char.isupper() for char in password):
        return False
    if not any(char.islower() for char in password):
        return False
    if not any(char.isdigit() for char in password):
        return False
    
    symbols = "!~@#$%^&*()_+|}{}"
    if not any(char in symbols for char in password):
        return False
    else:
        return True
    

window = tk.Tk()
window.title("Registration Form!!")
window.config(bg = "#ff5500")
window.geometry("500x500")

frames = tk.Frame(window , bg= "black")
frames.pack(expand= True)

label_fname = tk.Label(frames , text = "FName:" , bg= "black" , fg = "white")
label_lname = tk.Label(frames , text = "LName:" , bg= "black" , fg = "white")
label_email = tk.Label(frames , text = "Email:" , bg= "black" , fg = "white")
label_password = tk.Label(frames , text = "Password:" , bg= "black" , fg = "white")
label_gender = tk.Label(frames , text = "Gender:" , bg= "black" , fg = "white")

entry_fname = tk.Entry(frames , bg = "black" , fg = "white")
entry_lname = tk.Entry(frames , bg = "black" , fg = "white")
entry_email = tk.Entry(frames , bg = "black" , fg = "white")
entry_password = tk.Entry(frames ,show = "*", bg = "black" , fg = "white")
entry_gender = tk.Entry(frames , bg = "black" , fg = "white")

submit_bttn = tk.Button(frames , text = "Submit" , command= submit , bg="#ff5500")

label_fname.pack(fill = tk.BOTH , padx = 10 , pady = 5)
entry_fname.pack(fill = tk.BOTH , padx = 10 , pady = 5)
label_lname.pack(fill = tk.BOTH , padx = 10 , pady = 5)
entry_lname.pack(fill = tk.BOTH , padx = 10 , pady = 5)
label_gender.pack(fill = tk.BOTH , padx = 10 , pady = 5)
entry_gender.pack(fill = tk.BOTH , padx = 10 , pady = 5)
label_email.pack(fill = tk.BOTH , padx = 10 , pady = 5)
entry_email.pack(fill = tk.BOTH , padx = 10 , pady = 5)
label_password.pack(fill = tk.BOTH , padx = 10 , pady = 5)
entry_password.pack(fill = tk.BOTH , padx = 10 , pady = 5)
submit_bttn.pack(fill = tk.BOTH , padx = 10 , pady= 10)

window.mainloop()