#include "IALibrary.h"
#include "IAProgram.h"
#include "IAOpenGLResourceManager.h"
#include "IAOpenGLAssert.h"


#define CLASSNAME "IAProgram"


void IAProgram_createOpenGLResources(IAProgram * this);
void IAProgram_stopUsingCurrentProgram();
void IAProgram_destroyOpenGLResources(IAProgram * this);


static IAProgram * currentProgram = NULL;


void IAProgram_onNewOpenGLContext(){
    currentProgram = NULL;
}

void IAProgram_init(IAProgram * this, const char * vertexShaderCode, const char * fragmentShaderCode, void (*glBindAttributeLocations)(GLuint programId)){
    glAssert();
    this->base = IAObject_make(this);
	this->programId = 0;
	this->vertexShader = IAShader_new(GL_VERTEX_SHADER, vertexShaderCode);
	this->fragmentShader = IAShader_new(GL_FRAGMENT_SHADER, fragmentShaderCode);
	IA_STRUCT_ARRAY_LIST_MALLOC_MAKE(this->attributes, IAProgramAttribute, 8);
    this->glBindAttributeLocations = glBindAttributeLocations;

    IAOpenGLResourceDelegateAttributes arguments;
    IAOpenGLResourceDelegateAttributes_make(&arguments, this);
    IAOpenGLResourceDelegateAttributes_setCreateResourcesFunction(&arguments, (void(*)(void * correspondingObject)) IAProgram_createOpenGLResources);
    IAOpenGLResourceDelegateAttributes_setDestroyResourcesFunction(&arguments, (void(*)(void * correspondingObject)) IAProgram_destroyOpenGLResources);
    IAOpenGLResourceDelegate_make(&this->delegate, &arguments);
    glAssert();
	IAOpenGLResourceManager_registerOpenGLResourceDelegate(&this->delegate);
    glAssert();
    IANotificationEvent_init(&this->linkingComplete);
    IA_incrementInitCount();
}

void IAProgram_createOpenGLResources(IAProgram * this){
    IAShader_createOpenGLResources(this->vertexShader);
    IAShader_createOpenGLResources(this->fragmentShader);

	this->programId = glCreateProgram();
    this->glBindAttributeLocations(this->programId);
    
	glAttachShader(this->programId, IAShader_getShaderId(this->vertexShader));
	glAttachShader(this->programId, IAShader_getShaderId(this->fragmentShader));
	glLinkProgram(this->programId);
    glAssert();
    GLboolean result;
    glGetBooleanv(GL_SHADER_COMPILER, &result);
    glAssert();
	glUseProgram(this->programId);
    glAssert();
    IANotificationEvent_notify(&this->linkingComplete);
    glAssert();
}

void IAProgram_registerDynamicAttribute(IAProgram * this, GLint attributeLocation){
    IA_STRUCT_ARRAY_LIST_REALLOC_MAKE_IF_NEEDED(this->attributes, IAProgramAttribute);
    IAProgramAttribute attribute = (IAProgramAttribute){
        .attributeLocation = attributeLocation
    };
    IAStructArrayList_IAProgramAttribute_add(this->attributes, attribute);
}

GLint IAProgram_getAttributeLocation(IAProgram * this, const GLchar * name){
    GLint location = glGetAttribLocation(this->programId, name);
    return location;
}

GLint IAProgram_getUniformLocation(IAProgram * this, const GLchar * name){
    return glGetUniformLocation(this->programId, name);
}

bool IAProgram_isEqual(IAProgram * this, IAProgram * program2){
    if(this == NULL || program2 == NULL){
        if(this == program2){
            return true;
        }else{
            return false;
        }
    }else{
        if (this->programId == program2->programId) {
            return true;
        }else{
            return false;
        }
    }
}

void IAProgram_use(IAProgram * this){
    if (this != currentProgram) {
        IAProgram_stopUsingCurrentProgram();
        glUseProgram(this->programId);
        for (int i = 0; i < IAStructArrayList_IAProgramAttribute_getCurrentSize(this->attributes); i++) {
            IAProgramAttribute attribute = IAStructArrayList_IAProgramAttribute_get(this->attributes, i);
            glEnableVertexAttribArray(attribute.attributeLocation);
        }
        currentProgram = this;
    }
}

void IAProgram_stopUsingCurrentProgram(){
    if (currentProgram != NULL) {
        for (int i = 0; i < IAStructArrayList_IAProgramAttribute_getCurrentSize(currentProgram->attributes); i++) {
            IAProgramAttribute attribute = IAStructArrayList_IAProgramAttribute_get(currentProgram->attributes, i);
            glDisableVertexAttribArray(attribute.attributeLocation);
        }
        currentProgram = NULL;
    }
}

void IAProgram_destroyOpenGLResources(IAProgram * this){
	if (IAProgram_isEqual(this, currentProgram)) {
	    IAProgram_stopUsingCurrentProgram();
	}
	glDeleteProgram(this->programId);
	IAShader_destroyOpenGLResources(this->vertexShader);
	IAShader_destroyOpenGLResources(this->fragmentShader);
}

void IAProgram_deinit(IAProgram * this){
	IAOpenGLResourceManager_unregisterOpenGLResourceDelegate(&this->delegate);
	IAShader_release(this->vertexShader);
	IAShader_release(this->fragmentShader);
    IA_STRUCT_ARRAY_LIST_FREE(this->attributes);
    IANotificationEvent_deinit(&this->linkingComplete);
    IA_decrementInitCount();
}

