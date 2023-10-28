#include <enginethingy.hpp>

class Sandbox : public EngineThingy::Application {
private:
	Sandbox(libstra::array_view<const char *> args) :
		EngineThingy::Application(args) {}
	void OnStart() override {
		auto &eventSystem = EngineThingy::EventSystem::Instance();
		eventSystem.AddListener<EngineThingy::ApplicationQuitEvent>(
			[this](const EngineThingy::ApplicationQuitEvent &) {
				ET_LOG_INFO("Received application quit event");
				this->Stop();
			});
		eventSystem.AddListener<EngineThingy::WindowCloseEvent>(
			[this](const EngineThingy::WindowCloseEvent &) {
				ET_LOG_INFO("Received window close event");
				this->Stop();
			});
		eventSystem.AddListener<EngineThingy::WindowFocusEvent>(
			[](const EngineThingy::WindowFocusEvent &evt) {
				if (evt.focused) ET_LOG_TRACE("Window gained focus");
				else ET_LOG_TRACE("Window lost focus");
			});
		eventSystem.AddListener<EngineThingy::KeyPressedEvent>(
			[](const EngineThingy::KeyPressedEvent &evt) {
				ET_LOG_TRACE((int)evt.GetCode());
			},
			3);
	}

public:
	[[nodiscard]]
	static Sandbox &Init(libstra::array_view<const char *> args) {
		auto *app = new Sandbox(args); // cleaned up by the engine
		return *app;
	}
	void Terminate() { delete this; }
	~Sandbox() { ET_LOG_INFO("Destroyed app"); }
};

int main(int argc, char const *argv[]) {
	auto &app = Sandbox::Init({ argv, argv + argc });
	app.Run();

	app.Terminate();
	return 0;
}
