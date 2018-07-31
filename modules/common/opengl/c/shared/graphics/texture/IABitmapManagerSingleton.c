//
//  IABitmapManagerSingleton.c
//  OpenGL
//
//  Created by Konstantin Merker on 02/10/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IABitmapManagerSingleton.h"

#define CLASSNAME "IABitmapManagerSingleton"



static IABitmapManager * defaultBitmapManager;
static IANotificationDelegate notificationDelegate;

static void IABitmapManagerSingleton_onMemoryWarningFunction(IABitmapManager * bitmapManager){
    IABitmapManager_destroyBitmapRefs(bitmapManager);
}

IABitmapManager * IABitmapManagerSingleton_getDefaultBitmapManager(){
    if (defaultBitmapManager == NULL) {
        defaultBitmapManager = IABitmapManager_new();
        notificationDelegate = (IANotificationDelegate){
            .correspondingObject = defaultBitmapManager,
            .notify = (void (*)(void *)) IABitmapManagerSingleton_onMemoryWarningFunction
        };
        IALibrary_registerOnMemoryWarningNotification(&notificationDelegate);
    }
    return defaultBitmapManager;
}

