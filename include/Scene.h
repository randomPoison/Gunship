#pragma once

#include <vector>
#include <utility>

#include "entityx/entityx.h"

#include "Input.h"

namespace Ogre
{
	class Root;
	class RenderWindow;
	class SceneManager;
}

namespace Gunship
{
	class Engine;

	class Scene : public entityx::EntityX
	{
	public:
		explicit Scene( Engine* engine, Ogre::Root* root, Ogre::RenderWindow* renderWindow );

		/**
		 * \brief Update all the running systems.
		 */
		void Update( const Input& input, float delta );

	private:
		Engine* _engine;
		Ogre::Root* _root;
		Ogre::RenderWindow* _renderWindow;
		Ogre::SceneManager* _sceneManager;
	};
}
