/***************************************************************************
                          encodervorbis.h  -  description
                             -------------------
    copyright            : (C) 2007 by Xiph.org
                           (C) 2007 by Wesley Stessens
    email                : wesley at ubuntu dot com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef ENCODERVORBIS_H
#define ENCODERVORBIS_H

#include <QObject>
#include "defs.h"

#include <vorbis/vorbisenc.h> // this also includes vorbis/codec.h

class EncoderVorbis : public QObject {
    Q_OBJECT
public:
    EncoderVorbis();
    ~EncoderVorbis();
    int init();
    int encodeBuffer(const CSAMPLE *samples, const int size);
signals:
    void pageReady(unsigned char *, unsigned char *, int, int);
private:
    int getSerial();
    ogg_stream_state oggs;    /* take physical pages, weld into logical stream
                                 of packets */
    ogg_page oggpage;         /* Ogg bitstream page: contains Vorbis packets */
    ogg_packet oggpacket;     /* raw packet of data */
    vorbis_block vblock;      /* local working space for packet-to-PCM */
    vorbis_dsp_state vdsp;    /* central working space for packet-to-PCM */
    vorbis_info vinfo;        /* stores all static vorbis bitstream settings */
    vorbis_comment vcomment;  /* stores all user comments */
};

#endif
