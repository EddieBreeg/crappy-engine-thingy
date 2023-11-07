#include <enginethingy.hpp>

class Sandbox : public EngineThingy::Application {
private:
	Sandbox(libstra::array_view<const char *> args) :
		EngineThingy::Application(args) {}
	void OnStart() override {
		auto &eventSystem = EngineThingy::EventSystem::Instance();
		eventSystem.AddListener<EngineThingy::WindowCloseEvent>(
			[this](const EngineThingy::WindowCloseEvent &) {
				ET_LOG_INFO("Received window close event");
				this->Stop();
				return true;
			});
		eventSystem.AddListener<EngineThingy::WindowFocusEvent>(
			[](const EngineThingy::WindowFocusEvent &evt) {
				if (evt.focused) ET_LOG_TRACE("Window gained focus");
				else ET_LOG_TRACE("Window lost focus");
				return true;
			});
		eventSystem.AddListener<EngineThingy::KeyPressedEvent>(
			[](const EngineThingy::KeyPressedEvent &evt) {
				ET_LOG_TRACE(
					fmt::format("Layer 0 key pressed {}", (int)evt.GetCode()));
				return true;
			},
			1);
		eventSystem.AddListener<EngineThingy::KeyPressedEvent>(
			[](const EngineThingy::KeyPressedEvent &evt) {
				ET_LOG_TRACE(
					fmt::format("Layer 1 key pressed {}", (int)evt.GetCode()));
				return false;
			},
			2);
	}

public:
	[[nodiscard]]
	static std::unique_ptr<Sandbox>
	Init(libstra::array_view<const char *> args) {
		return std::unique_ptr<Sandbox>(new Sandbox(args));
	}
	~Sandbox() { ET_LOG_INFO("Destroyed app"); }
};

int main(int argc, char const *argv[]) {
	auto app = Sandbox::Init({ argv, argv + argc });
	app->Run();

	return 0;
}
