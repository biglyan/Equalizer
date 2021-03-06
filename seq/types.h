
/* Copyright (c) 2011-2017, Stefan Eilemann <eile@eyescale.ch>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 2.1 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef EQSEQUEL_TYPES_H
#define EQSEQUEL_TYPES_H

#include <seq/api.h>

#include <eq/types.h>

#include <eq/util/shader.h>

#include <eq/fabric/event.h>

/**
 * @namespace seq
 * @brief Sequel - A simple interface to the Equalizer parallel rendering
 *        framework.
 *
 * This namespace provides a simple programming interface to the Equalizer
 * parallel rendering framework. Sequel allows rapid development of clustered
 * multi-GPU applications while not sacrificing the flexibility and power of the
 * underlying Equalizer framework.
 */
namespace seq
{
using namespace eq::util::shader;

using eq::fabric::RenderContext;
using eq::AxisEvent;
using eq::ButtonEvent;
using eq::Event;
using eq::EventICommand;
using eq::Frustumf;
using eq::KeyEvent;
using eq::Matrix4f;
using eq::PixelViewport;
using eq::PointerEvent;
using eq::SizeEvent;
using eq::Statistic;
using eq::Vector2f;
using eq::Vector2i;
using eq::Vector3f;
using eq::Vector4f;
using eq::View;
using eq::uint128_t;
using eq::util::ObjectManager;
using namespace eq::fabric::eventTypes;

class Application;
class ObjectFactory;
class Renderer;
class ViewData;

typedef lunchbox::RefPtr< Application > ApplicationPtr;

enum EventType
{
    EVENT_REDRAW = eq::EVENT_USER,
    EVENT_USER
};

/** @cond IGNORE */
namespace detail
{

class Application;
class Channel;
class Config;
class Node;
class ObjectMap;
class Pipe;
class Renderer;
class View;
class Window;

}
/** @endcond */
}

#endif // EQSEQUEL_TYPES_H
