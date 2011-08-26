# Copyright (c) 2010 Daniel Pfeifer <daniel@pfeifer-mail.de>
#               2010 Stefan Eilemann <eile@eyescale.ch>

set(EQ_FABRIC_PUBLIC_HEADERS
    api.h
    base.h
    canvas.h
    canvasPackets.h
    channel.h
    client.h
    colorMask.h
    commands.h
    config.h
    configPackets.h
    configVisitor.h
    drawableConfig.h
    elementVisitor.h
	equalizerTypes.h
    error.h
    eye.h
    focusMode.h
    frustum.h
    global.h
    gpuInfo.h
    iAttribute.h
    init.h
    layout.h
    layoutPackets.h
    leafVisitor.h
    log.h
    node.h
    nodeType.h
    object.h
    observer.h
    packetType.h
    packets.h
    paths.h
    pipe.h
    pipePackets.h
    pixel.h
    pixelViewport.h
    projection.h
    queuePackets.h
    range.h
    renderContext.h
    segment.h
    server.h
    serverPackets.h
    subPixel.h
    swapBarrier.h
    task.h
    types.h
    view.h
    viewport.h
    visitorResult.h
    vmmlib.h
    wall.h
    window.h
    windowPackets.h
    zoom.h
  )

set(EQ_FABRIC_HEADERS
  nameFinder.h
  canvas.ipp
  channel.ipp
  config.ipp
  layout.ipp
  node.ipp
  observer.ipp
  pipe.ipp
  segment.ipp
  server.ipp
  view.ipp
  window.ipp
)

set(EQ_FABRIC_SOURCES
  client.cpp
  colorMask.cpp
  error.cpp
  eye.cpp
  frustum.cpp
  global.cpp
  iAttribute.cpp
  init.cpp
  object.cpp
  pixel.cpp
  projection.cpp
  range.cpp
  renderContext.cpp
  subPixel.cpp
  swapBarrier.cpp
  viewport.cpp
  wall.cpp
  zoom.cpp
)

