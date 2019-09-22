# ARDUpiTRAILcam
Arduino nano, controlling a Pi0w, and starting a script to capture images...

OUTPUT to Pi  
pi GPIO 26 ---- shutdown ---- Arduino OI 9  
pi GPIO 21 ---- Camera Trigger ---- Arduino OI 8  

OUTPUTS  
Arduino OI 7 - Motion Detect    
Arduino OI 10 - PWR (goes to shutdown of PowerSupply/Relay/Something)   

INPUT to Arduino Pro Mini  
Arduino OI 2 - MOTION Input from RCWL-0516 (Starts the timers)  
Arduino OI 3 - MOTION Detect Input from RCWL-0516 (kinda double up, but provides a realtime view of motion)  


 
                                         
Motion currently provided by RCWL-0516  

Just setup your python script or whatever to detect an input from the camera trigger on GPIO 21  

For shutdown edit /boot/config.txt and add the line;  
```dtoverlay=gpio-shutdown,gpio_pin=26```  

SHUTDOWN and camera trigger use a LOW output.. this is fully compatible with the Pi  


