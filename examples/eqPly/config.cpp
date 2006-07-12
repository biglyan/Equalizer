
/* Copyright (c) 2006, Stefan Eilemann <eile@equalizergraphics.com> 
   All rights reserved. */

#include "config.h"

Config::Config()
        : _running( false ),
          _frameData(NULL),
          _spinX(0),
          _spinY(0)
{}

bool Config::init( const uint32_t initID )
{
    _running = eq::Config::init( initID );
    return _running;
}

uint32_t Config::beginFrame()
{
    // update database
    _frameData->_data.rotation[0] += .01 * _spinY;
    _frameData->_data.rotation[1] += .01 * _spinX;
    const uint32_t version = _frameData->commit();

    return eq::Config::beginFrame( version );
}

bool Config::handleEvent( eq::ConfigEvent* event )
{
    switch( event->type )
    {
        case eq::ConfigEvent::TYPE_KEY_PRESS:
            switch( event->keyPress.key )
            {
                case 'q':
                case eq::KC_ESCAPE:
                    _running = false;
                    return true;

                case 'r':
                case ' ':
                    _spinX = 0;
                    _spinY = 0;
                    _frameData->reset();
                    return true;
            }
            break;

        case eq::ConfigEvent::TYPE_POINTER_BUTTON_RELEASE:
            if( event->pointerButtonRelease.buttons == eq::PTR_BUTTON_NONE &&
                event->pointerButtonRelease.button  == eq::PTR_BUTTON1 )
            {
                _spinX = event->pointerButtonRelease.dx;
                _spinY = event->pointerButtonRelease.dy;
            }
            return true;

        case eq::ConfigEvent::TYPE_POINTER_MOTION:
            if( event->pointerMotion.buttons == eq::PTR_BUTTON_NONE )
                return true;

            if( event->pointerMotion.buttons == eq::PTR_BUTTON1 )
            {
                _spinX = 0;
                _spinY = 0;
                _frameData->_data.rotation[0] += .1 * event->pointerMotion.dy;
                _frameData->_data.rotation[1] += .1 * event->pointerMotion.dx;
            }
            else if( event->pointerMotion.buttons == eq::PTR_BUTTON2 ||
                     event->pointerMotion.buttons == ( eq::PTR_BUTTON1 | 
                                                       eq::PTR_BUTTON3 ))
            {
                _frameData->_data.translation[2] +=
                    .005 * event->pointerMotion.dy;
            }
            else if( event->pointerMotion.buttons == eq::PTR_BUTTON3 )
            {
                _frameData->_data.translation[0] += 
                    .0005 * event->pointerMotion.dx;
                _frameData->_data.translation[1] -= 
                    .0005 * event->pointerMotion.dy;
            }
            return true;

        default:
            break;
    }
    return eq::Config::handleEvent( event );
}
