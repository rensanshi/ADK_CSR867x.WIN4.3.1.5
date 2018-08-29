/****************************************************************************
Copyright (c) 2010 - 2017 Qualcomm Technologies International, Ltd.

FILE NAME
    display.c

DESCRIPTION
     The main display manager file

*/
#include "display.h"

#include <stdlib.h>
#include <print.h>
#include <string.h>

typedef struct display_Tag
{
    Task plugin; 
    uint16 max_length;
    
}DISPLAY_t ;

    /*the global display library data structure*/
static DISPLAY_t DISPLAY = {0, 0} ;

/****************************************************************************
NAME    
    DisplayInit

DESCRIPTION
    This function initialises the display

RETURNS
    void
*/
bool DisplayInit(Task display_plugin,
                 Task app_task)
{   

    /*send a message to the plugin*/
    MAKE_DISPLAY_MESSAGE( DISPLAY_PLUGIN_INIT_MSG ) ;
    message->app_task = app_task;
    message->max_length = &DISPLAY.max_length;
    
    PRINT(("DISP: DisplayInit\n"));
        
    DISPLAY.plugin = display_plugin ;

    MessageSend( display_plugin, DISPLAY_PLUGIN_INIT_MSG , message  ) ;
            
    return TRUE ;
}

/*!
    @brief  update the state of the display
    @param  state The on/off state of display
    
*/
void DisplaySetState( bool state )
{
    if ( DISPLAY.plugin )   
    {
        MAKE_DISPLAY_MESSAGE( DISPLAY_PLUGIN_SET_STATE_MSG ) ; 

        message->state     = state ;
        
        MessageSend ( DISPLAY.plugin, DISPLAY_PLUGIN_SET_STATE_MSG, message ) ;
      
    }
}

/*!
    @brief  set the location of the status information
    @param  line The line on the display where the status information should be shown,
        specify 0 if no status information should be displayed
    @param  start If true the information is put at the start of the specified line,
        if false then it is put at the end

*/
void DisplaySetStatusLocation( uint8 line, bool start )
{
    if ( DISPLAY.plugin )
    {
        MAKE_DISPLAY_MESSAGE( DISPLAY_PLUGIN_SET_STATUS_LOCATION_MSG ) ;
        message->line = line ;
        message->start = start ;

        MessageSend ( DISPLAY.plugin, DISPLAY_PLUGIN_SET_STATUS_LOCATION_MSG, message ) ;
    }
}

/*!
    @brief  update the text line on the display

*/
void DisplaySetText( const char* text,
                     uint8 txtlen,
                     uint8 line,
                     bool  scroll,
                     uint16 scroll_update,
                     uint16 scroll_pause,
                     bool  flash,
                     uint16 display_time )
{
    if (txtlen > DISPLAY.max_length)
        txtlen = DISPLAY.max_length;


    if ( DISPLAY.plugin )   
    {
        MAKE_DISPLAY_MESSAGE_WITH_LEN( DISPLAY_PLUGIN_SET_TEXT_MSG, txtlen ) ;

        message->text_length = txtlen;
        message->line = line;
        message->scroll = scroll;
        message->scroll_pause = scroll_pause;
        message->scroll_update = scroll_update;
        message->flash_enable = flash;      
        message->display_time = display_time;
        memmove(message->text,text,txtlen) ;

        MessageSend ( DISPLAY.plugin, DISPLAY_PLUGIN_SET_TEXT_MSG, message ) ;      
    }
}

/****************************************************************************
NAME    
    DisplaySetVolume

DESCRIPTION
    update the volume level on the display

RETURNS
    void
*/
void DisplaySetVolume( uint16 volume  )
{
    if ( DISPLAY.plugin )   
    {
        MAKE_DISPLAY_MESSAGE( DISPLAY_PLUGIN_SET_VOLUME_MSG ) ; 

        message->volume     = volume ;
        
        MessageSend ( DISPLAY.plugin, DISPLAY_PLUGIN_SET_VOLUME_MSG, message ) ;
      
    }
}

/*!
    @brief  update an icon status on the display
    @param  icon The icon id
    @param  state state
    
*/
void DisplaySetIcon( uint8 icon, bool state )
{
    if ( DISPLAY.plugin )   
    {
        MAKE_DISPLAY_MESSAGE( DISPLAY_PLUGIN_SET_ICON_MSG ) ; 

        message->icon     = icon ;
        message->state    = state;      
        
        MessageSend ( DISPLAY.plugin, DISPLAY_PLUGIN_SET_ICON_MSG, message ) ;      
    }
}

/*!
    @brief  update the battery level on the display
    @param  battery_level The battery level
    
*/
void DisplaySetBatteryLevel( uint8 battery_level )
{
    if ( DISPLAY.plugin )   
    {
        MAKE_DISPLAY_MESSAGE( DISPLAY_PLUGIN_SET_BATTERY_MSG ) ; 

        message->battery_level     = battery_level ;
        
        MessageSend ( DISPLAY.plugin, DISPLAY_PLUGIN_SET_BATTERY_MSG, message ) ;      
    }
}


