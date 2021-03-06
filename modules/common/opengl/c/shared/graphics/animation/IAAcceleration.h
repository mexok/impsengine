#ifndef IAAcceleration_h
#define IAAcceleration_h

#include "IARect.h"
#include "IAPoint.h"
#include "IAColor.h"
#include <stdint.h>

//progress must be between 0 and 1

float IAAcceleration_calculateProgress(uint64_t startTime, uint64_t currentTime, uint64_t duration);

float IAAcceleration_calculateCurrentValue(float startValue, float endValue, float progress, float(*accelerationFunction)(float, float, float));
IAPoint IAAcceleration_calculateCurrentPoint(IAPoint startPoint, IAPoint endPoint, float progress, float(*accelerationFunction)(float, float, float));
IASize IAAcceleration_calculateCurrentSize(IASize startSize, IASize endSize, float progress, float(*accelerationFunction)(float, float, float));
IARect IAAcceleration_calculateCurrentRect(IARect startRect, IARect endRect, float progress, float(*accelerationFunction)(float, float, float));
IAColor IAAcceleration_calculateCurrentColor(IAColor startColor, IAColor endColor, float progress, float(*accelerationFunction)(float, float, float));

float IAAcceleration_linearMovementFunction(float startValue, float endValue, float progress);
float IAAcceleration_uniformlyAccelerationFunction(float startValue, float endValue, float progress);
float IAAcceleration_uniformlyDecelerationFunction(float startValue, float endValue, float progress);
float IAAcceleration_normalAccelerationFunction(float startValue, float endValue, float progress);


float IAAcceleration_getWay(float speed, float acceleration);
float IAAcceleration_getDuration(float speed, float acceleration);

#endif
