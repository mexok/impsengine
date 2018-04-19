//
//  IALocalisation.c
//  ImpsEngineAndroid
//
//  Created by Konstantin Merker on Nov 1, 2015.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#include "IALocalisation.h"

#include "IALibrary.h"
#include "IAString.h"
#include "IAJni.h"
#include "JNIEnv+HelperMethods.h"

#define CLASSNAME "IALocalisation"

static IAString * localeId = NULL;

const char * IALocalisation_getLocaleId(){
	if (localeId == NULL){
		JNIEnv * env = IAJni_getJNIEnv();
		jclass jLocalisationClass = IAJni_loadClass(env, "com/impsapps/impsengine/common/inputoutput/IALocalisation");
		jmethodID getLocaleId = (*env)->GetStaticMethodID(env, jLocalisationClass, "getLocaleId", "()Ljava/lang/String;");
		jstring jLocaleId = (*env)->CallStaticObjectMethod(env, jLocalisationClass, getLocaleId);
		const char * utf8Chars = JNIEnv_createUTFChars(env, jLocaleId);
		IA_disableAllocationTracking();
		localeId = IAString_new(utf8Chars);
		IA_enableAllocationTracking();
		JNIEnv_destroyUTFChars(env, jLocaleId, utf8Chars);
		(*env)->DeleteLocalRef(env, jLocaleId);
		(*env)->DeleteLocalRef(env, jLocalisationClass);
	}
	return IAString_toCharArray(localeId);
}

