# KuntalPatel
#11/14/2019


# This program stores passwords in a file 
# that is encrypted with a master password
#
# system packages: gcc libffi-devel python-devel openssl-devel
# python packages: pycryptodome 

# references:
#   1. https://stackoverflow.com/questions/19232011/convert-dictionary-to-bytes-and-back-again-python
#   2. https://www.pycryptodome.org/en/latest/src/examples.html
# 
# To run:
#	python pwMan_edited.py Google.com
# 
# To reset:
# 	rm passwords
#
# Example Output:
# $ python pwMan-template_edited.py google.com
# Do you have master password ? : enter y or n:
# y
# Enter Master Password:pass
# Your password is   pass Please save it
# No password database, creating....
# Loading database...
# No entry for google.com, creating new...
# Do you want sys generated pwd : enter y or n:
# n
# New entry - enter password for google.com: google
# stored


#working with file so need to import csv module
#json module methods will be used to convert byte stream into object and vice versa.
#cipher module will provide different modes by which encypt and decrypt file.
#Random module methods will suggest random password according to parameters.
#PBKDF2 algorithm takes 3 parameters 1)salt 2)master password and 3)lendth of the desired key

import csv, os, sys, json,string
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Protocol.KDF import PBKDF2
from random import *

passwordFile = "passwords"
##The salt value should be set here.
#salt value is hard coded here
salt = "1234"
##The header of the file.
head = " ____               __  __\n"+"|  _ \ __ _ ___ ___|  \/  | __ _ _ __  \n" +"| |_) / _` / __/ __| |\/| |/ _` | '_ \ \n" +"|  __/ (_| \__ \__ \ |  | | (_| | | | |\n" +"|_|   \__,_|___/___/_|  |_|\__,_|_| |_|\n"


#functions


#convert object into byte stream
def dictToBytes(dict):
	return json.dumps(dict).encode('utf-8')
#give object from byte stream
def bytesToDict(dict):
	return json.loads(dict)

	

#encryption mode is AES.
def encrypt(dict, k):
	##Define the encryption scheme here.
	
	cipher = AES.new(k, AES.MODE_EAX)
	
	##Encrypt the dictionary value here.
	ciphertext, tag = cipher.encrypt_and_digest(dict)

	## writing encrypted value into file
	with open(passwordFile, 'wb') as outfile:
		[outfile.write(x) for x in (cipher.nonce, tag, ciphertext)]
def decrypt(k):
	##reading  encrypted value from the  file
	with open(passwordFile, 'rb') as infile:
		nonce, tag, ciphertext = [ infile.read(x) for x in (16, 16, -1) ]
		##Define the encryption scheme here.
		cipher = AES.new(k, AES.MODE_EAX,nonce)
		
		##Decrypt the ciphertext here.
		data = cipher.decrypt_and_verify(ciphertext, tag)
		
		return data

#randomly generate password from ascii letters,punctuation marks and digits
def generate_random_pwd():
	characters = string.ascii_letters + string.punctuation  + string.digits
	password =  "".join(choice(characters) for x in range(randint(8, 16)))
	return password
	
def Main():

	print("\n\n")
	if os.path.isfile(passwordFile):
		mpw = input("Enter Master Password:\n")
	else:	
		masterpwd = input("Do you have master password ? : enter y or n:\n")
		if masterpwd == "y":
			mpw = input("Enter Master Password:") 
		else:
			mpw = generate_random_pwd()
		print("Your password is   "+ mpw +" Please save it")
	
	# derive key from password
	#generate key of length 16 key with the value of master password ans salt.
	k   = PBKDF2(mpw, salt, dkLen=16) 
	
	
	
	# check for password database file
	if not os.path.isfile(passwordFile):
		
		# create new passwords file
		print("No password database, creating....")
		newDict = dictToBytes({"TempSite":"TempPassword"})
		
		encrypt(newDict, k)

	# check usage
	if len(sys.argv)  != 2:
		print("usage: python pwMan-template_edited.py <website>")
		print("Please enter enough arguments")
		return
	else:

		# decrypt passwords file to dictionary
		try:
			print("Loading database...")
			pws1 =decrypt(k)

			pws = bytesToDict(pws1)
			
		except Exception as e:
			print("Wrong password")
			return

		# print value for  website or add new value
		entry = sys.argv[1]
		if entry in pws:
			print("entry   : " + str(entry))
			print("password: " + str(pws[entry]))
		else:
			print("No entry for " + str(entry) + ", creating new...")
			sys_gen_pwd = input("Do you want sys generated pwd : enter y or n:\n")
			if(sys_gen_pwd == "y"):
				newPass = generate_random_pwd()
				print("your "+ str(entry) + "password is   "+ newPass +"   please save it")
			else:
				newPass = input("New entry - enter password for "+entry+": ")
			pws[entry] = newPass
			encrypt( dictToBytes(pws), k)
			print("stored")


if __name__ == '__main__':
	print(str(head))
	Main()

