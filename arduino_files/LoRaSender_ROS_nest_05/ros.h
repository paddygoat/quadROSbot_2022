#ifndef _ROS_H_
#define _ROS_H_

#include "ros/node_handle.h"
#include "ArduinoHardware.h"
#include <avr/pgmspace.h>
#if defined(ESP8266)
  #include "Esp8266Hardware.h"
#endif
#if defined(ESP32)
  #include "ESP32Hardware.h"
#endif

#define FLASH_CONVERTER_BUFFER 200
// #define FLASH_CONVERTER_BUFFER 150

// converter macro for string declared with PROGMEM keyword
#define FCAST( progmem_string_literal) (reinterpret_cast<const __FlashStringHelper *>( progmem_string_literal ))

namespace ros
{
  class FlashReadOutBuffer_ : public DefaultReadOutBuffer_
  {
  private:
    char* buffer_;
    int buffer_index_;
    
    const char* readFromFlash( const __FlashStringHelper * what )
    {
      PGM_P lp_p = (PGM_P) what ;
      
      int offset = buffer_index_;
      
      while ( buffer_index_ < FLASH_CONVERTER_BUFFER - 1 ) 
      {
  buffer_[ buffer_index_ ] = pgm_read_byte( lp_p++ );
    
  if ( buffer_[ buffer_index_ ] == 0)
  {
    buffer_index_++;
    
    break;
  }
  
  buffer_index_++;
      }
      
      if ( buffer_index_ >= FLASH_CONVERTER_BUFFER - 1 )
      {
  read_out_error_ = DefaultReadOutBuffer_::BufferOverflow;
      }
      
      return buffer_ + offset ;
    }
    
  protected:
    ReadoutError read_out_error_;
    
    // overrider of method from DefaultReadOutBuffer_
    virtual const char * readTopic( const char * topic, bool from_flash )
    {
      if ( from_flash )
      {
  return readFromFlash( reinterpret_cast<const __FlashStringHelper *>( topic ) );
      }
      else
      {
  return topic;
      }
    }
        
  public:
    FlashReadOutBuffer_() 
    {
      buffer_index_ = 0;
      
      buffer_ = new char[ FLASH_CONVERTER_BUFFER ];
      
      buffer_[0] = 0;  //zero termination at beginning
      buffer_[ FLASH_CONVERTER_BUFFER - 1 ] = 0; // assure zero termination
    }
    
    virtual ~FlashReadOutBuffer_() 
    {
      delete buffer_;
    }
    
    // for md5sum / msg type
    virtual const char *  readMsgInfo( const char * msg_info )
    {
      return readFromFlash( reinterpret_cast<const __FlashStringHelper*>( msg_info ) );
    }
    
    // for log msgs
    const char *  readLog( const __FlashStringHelper * msg )
    {
      return readFromFlash( msg );
    }
  };
  
#if defined(__AVR_ATmega8__) || defined(__AVR_ATmega168__)
  /* downsize our buffers */
  typedef NodeHandle_<ArduinoHardware, 6, 6, 150, 150, FlashReadOutBuffer_> NodeHandle;

#elif defined(__AVR_ATmega328P__)

  typedef NodeHandle_<ArduinoHardware, 25, 25, 280, 280, FlashReadOutBuffer_> NodeHandle;

#elif defined(ESP8266)

  typedef NodeHandle_<Esp8266Hardware> NodeHandle;
  
#elif defined(SPARK)
  typedef NodeHandle_<ArduinoHardware, 10, 10, 2048, 2048> NodeHandle;


#else

  // typedef NodeHandle_<ArduinoHardware, 25, 25, 512, 512, FlashReadOutBuffer_> NodeHandle;
  typedef NodeHandle_<ArduinoHardware, 25, 25, 1024, 1024, FlashReadOutBuffer_> NodeHandle;

#endif   
  
}

#endif
