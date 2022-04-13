#pragma once
#pragma region ∫ÙµÂ«√∑ß∆˚ ∫∞ ∂Û¿Ã∫Í∑Ø∏Æ √ﬂ∞° ∫Œ∫–
#ifdef _DEBUG
#ifdef _WIN64
#pragma comment(lib, "d2d_engine32d.lib")
#else
#pragma comment(lib, "d2d_engined.lib")
#endif
#else
#ifdef _WIN64
#pragma comment(lib, "d2d_engine32.lib")
#else
#pragma comment(lib, "d2d_engine.lib")
#endif
#endif // DEBUG
#pragma endregion
#include <Windows.h>
#include <wincodec.h>

#include <d2d1.h>
#include <dwrite.h>

#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib")

#include <map>
#include <vector>
#include <string>
using namespace std;

#include "Singleton.h"
#include "Observer.h"
#include "Subject.h"

#include "D2D_Macro.h"
#include "D2D_Engine.h"
#include "D2D_Struct.h"

#include "Transform.h"
#include "Object.h"
#include "Sprite.h"
#include "Animation.h"
#include "Renderer.h"
#include "Collision.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Camera.h"
#include "UI.h"
#include "TextUI.h"
#include "UIManager.h"
#include "Scene.h"
#include "SceneManager.h"