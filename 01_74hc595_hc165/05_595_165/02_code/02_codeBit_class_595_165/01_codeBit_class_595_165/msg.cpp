#include "msg.h"
#include "stdio.h"
#include "Arduino.h"
void msg::setOnCtrl(uint8_t ctrl)
{
 this->ctrl|=ctrl;
}
void msg::setOffCtrl(uint8_t ctrl)
{
 this->ctrl&=~(ctrl);
}

void msg::setLook(uint8_t look)
{
  this->look=look;  
}

uint8_t msg::getCtrl()
{
  return this->ctrl;
}

uint8_t msg::getLook()
{
  return this->look; 
}
