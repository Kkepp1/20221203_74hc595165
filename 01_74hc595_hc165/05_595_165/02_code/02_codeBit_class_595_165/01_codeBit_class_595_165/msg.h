#ifndef msg_h
#define msg_h
/*
 class for using read and write 165 and 595
 - ctrl to save state control bit drawer
 - look to save state read form drawer
 
*/
#include "stdio.h"
#include "Arduino.h"
class msg
{
private:
  uint8_t ctrl;
  uint8_t look;
public:
  void setOnCtrl(uint8_t);
  void setOffCtrl(uint8_t);
  void setLook(uint8_t);
  uint8_t getCtrl();
  uint8_t getLook();
};
#endif
