#pragma once

#include <functional>

class GameObject;
class Scene;
class Input;

typedef std::function< void( GameObject&, Scene&, const Input&, float ) > BehaviorFunction;
typedef size_t component_id;
