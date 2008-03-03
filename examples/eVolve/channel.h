
/* Copyright (c) 2006-2007, Stefan Eilemann <eile@equalizergraphics.com> 
   All rights reserved. */

#ifndef EVOLVE_CHANNEL_H
#define EVOLVE_CHANNEL_H

#include "eVolve.h"

#include <eq/eq.h>


namespace eVolve
{
    class FrameData;
    class InitData;
    struct Frame;

    class Channel : public eq::Channel
    {
    public:
        Channel( eq::Window* parent );
        bool _perspective;  // perspective/ortogonal projection

    protected:
        virtual ~Channel() {}

        virtual bool configInit( const uint32_t initID );

        virtual void frameStart( const uint32_t frameID, 
                                 const uint32_t frameNumber );

        virtual void frameDraw( const uint32_t frameID );
        virtual void frameAssemble( const uint32_t frameID );
        virtual void frameReadback( const uint32_t frameID );

        void applyFrustum() const;

        void clearViewport( const eq::PixelViewport &pvp );

        void frameClear( const uint32_t frameID );

    private:

        void _startAssemble();
        void _finishAssemble();

        void _orderFrames( std::vector< Frame >& frames );

        void _drawLogo();

        void _calcMVandITMV( vmml::Matrix4d& modelviewM, 
                             vmml::Matrix3d& modelviewITM ) const;

        const FrameData& _getFrameData() const;

        struct curFrData
        {
            eq::Range   lastRange;
        }
            _curFrData;

        vmml::Vector4f _bgColor; // background color

        enum BGColorMode
        {
            BG_SOLID_BLACK    = 0,
            BG_SOLID_COLORED  = 1,
            BG_TAINT_CHANNELS = 2
        } _bgColorMode;

        double _initTranslationZ; //!< initial Z-translation (for ortog. proj)

        eq::Image _image; //!< buffer for readback in case of DB compositing

        bool _haveDrawn;
    };

}

#endif // EVOLVE_CHANNEL_H

