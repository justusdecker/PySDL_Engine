import ctypes
import os
dll_path = os.path.join(os.getcwd(), 'bin', 'wsdl.dll') 
print(dll_path,os.getcwd(),os.path.isfile(dll_path))
WSDL3 = ctypes.CDLL(dll_path)

WSDL3.WSDL_InitializeWindow.restype = ctypes.c_char
WSDL3.WSDL_InitializeWindow.argtypes = [ctypes.c_char_p, ctypes.c_uint, ctypes.c_uint]

if not WSDL3.WSDL_InitializeWindow("TestWindow".encode('utf-8'),800,600):
    raise SyntaxError

WSDL_is_running = ctypes.c_bool.in_dll(WSDL3, "WSDL_is_running")

while WSDL_is_running.value:
    WSDL3.WSDL_Update()
    WSDL3.WSDL_CheckEvents()