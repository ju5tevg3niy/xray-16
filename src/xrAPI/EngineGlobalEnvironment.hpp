#pragma once

class AISpaceBase;
class CDUInterface;
class CScriptEngine;
class IDebugRender;
class IRender;
class IRenderFactory;
class ISoundManager;
class IUIRender;
class UICore;

class EngineGlobalEnvironment {
 public:
  IRender* Render;
  IDebugRender* DRender;
  CDUInterface* DU;
  IUIRender* UIRender;
  IRenderFactory* RenderFactory;
  CScriptEngine* ScriptEngine;
  AISpaceBase* AISpace;
  ISoundManager* Sound;
  UICore* UI;

  bool isDedicatedServer;
};

extern EngineGlobalEnvironment GEnv;
