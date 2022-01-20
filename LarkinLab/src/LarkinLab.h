#pragma once

// For use by applications

// Some library conflicts if this is included before stb_image on linux
#include "Utilities/Log.h"

#include "LabCore/Application.h"
#include "LabCore/Layers/Layer.h"
#include "LabCore/Input.h"

// Input Codes
#include "Utilities/KeyCodes.h"
#include "Utilities/MouseButtonCodes.h"

#include "LabCore/Layers/ImGuiLayer.h"

// -- Rendering Stuff -- //
#include "Platform/OpenGL/OpenGLTexture.h"

// -- Entry Point -- //
//#include "LabCore/EntryPoint.h"
//---------------------
