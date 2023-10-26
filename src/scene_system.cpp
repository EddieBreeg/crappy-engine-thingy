#include <et/scene_system.hpp>

namespace EngineThingy {
	Scene::Scene() {}
	Scene::~Scene() {}
	void Scene::Update(Timing &delta) {}

	SceneSystem &SceneSystem::Init() {
		ET_ASSERT(!_instance);
		static SceneSystem sys;
		return *(_instance = &sys);
	}
	void SceneSystem::Update(Timing delta) {}
	SceneSystem::SceneSystem() {}
	SceneSystem::~SceneSystem() {}

} // namespace EngineThingy
