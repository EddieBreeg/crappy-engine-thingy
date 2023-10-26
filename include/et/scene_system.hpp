#pragma once

#include "core.hpp"
#include "singleton.hpp"

namespace EngineThingy {
	class ET_API Scene {
	private:
		/* data */
	public:
		Scene(/* args */);
		void Update(Timing &);
		~Scene();
	};

	class ET_API SceneSystem : public Singleton<SceneSystem *> {
	public:
		~SceneSystem();
		static SceneSystem &Init();
		void Update(Timing d);

	private:
		SceneSystem();
		std::unique_ptr<Scene> _currentScene;
	};

} // namespace EngineThingy
