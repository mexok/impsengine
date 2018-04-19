//
//  IAGraphicRect.h
//  Hit Verto
//
//  Created by Konstantin Merker on 18/02/16.
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef Hit_Verto_IAGraphicRect_h
#define Hit_Verto_IAGraphicRect_h

#include "IADrawableRect.h"
#include "IAMatrix44.h"

typedef struct IAGraphicRect IAGraphicRect;

struct IAGraphicRect{
    //@extend
    IADrawableRect rect;
    IARect transformedRectToRender;
    void (*transformRectToRender)(const IAGraphicRect *, IARect *);
    void (*setupRendering)(const IAGraphicRect *, IARect);
};

void IAGraphicRect_commence();

void IAGraphicRect_make(IAGraphicRect *, void (*transformRectToRender)(const IAGraphicRect *, IARect *), void (*setupRendering)(const IAGraphicRect *, IARect));
void IAGraphicRect_makeCopy(IAGraphicRect *, const IAGraphicRect * graphicRectToCopy);

void IAGraphicRect_terminate();

#include "IAGraphicRect+Generated.h"

#endif
