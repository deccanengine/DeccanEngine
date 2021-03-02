#pragma once
#include "../Config.h"
#include "PrimitiveGeometry.h"
#include "RenderTypes.h"
#include "Camera.h"

void DE_GenericPipelineCreate();
void DE_GenericPipelineDestroy();
void DE_GenericPipelineBegin(DeccanCamera *camera);
void DE_GenericPipelineDrawGeometry(DeccanGeometry geometry); 
void DE_GenericPipelineEnd();
