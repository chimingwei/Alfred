from ctypes import cdll

# slibrecog =
recognizer = cdll.LoadLibrary('./librecog.so')
recognizer.init()

detectedUser = recognizer.predict()
print(detectedUser)