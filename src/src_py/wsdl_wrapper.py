import ctypes
import os
from typing import Iterable
from enum import Enum
WSDL3 = ctypes.CDLL('./bin/wsdl.dll')

class WSDLError(Exception): 
    """
    Something is going wrong in C
    """


class Application:
    """
    Represents the main application window and game loop.

    This class manages the initialization of the SDL window and provides a
    structured game loop for continuous updates and event handling. It acts as a
    high-level wrapper around the WSDL C functions.
    """
    def __init__(self,
                 window_title: str="WSDL",
                 dimensions: Iterable[int]=(800,600)):
        
        if len(dimensions) > 2:
            raise OverflowError
        elif len(dimensions) < 2:
            raise IndexError
        
        WSDL3.WSDL_InitializeWindow.restype = ctypes.c_char
        WSDL3.WSDL_InitializeWindow.argtypes = [ctypes.c_char_p, ctypes.c_uint, ctypes.c_uint]
        if not WSDL3.WSDL_InitializeWindow(window_title.encode('utf-8'),dimensions[0],dimensions[1]):
            raise WSDLError('Cannot Initialize SDL')
        self.__WSDL_is_running = ctypes.c_bool.in_dll(WSDL3, "WSDL_is_running")
    
    def mainloop(self) -> None:
        while self.is_running:
            WSDL3.WSDL_Update()
            WSDL3.WSDL_CheckEvents()
            WSDL3.WSDL_RenderDebug()
    
    @property
    def is_running(self) -> bool:
        return self.__WSDL_is_running.value

if __name__ == "__main__":
    APP = Application()
    APP.mainloop()