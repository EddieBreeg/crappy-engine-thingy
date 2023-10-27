#include <enginethingy.hpp>

class Sandbox : public EngineThingy::Application {
private:
	/* data */
	Sandbox(libstra::array_view<const char *> args) :
		EngineThingy::Application(args) {}

public:
	static EngineThingy::Application &
	Init(libstra::array_view<const char *> args) {
		auto *app = new Sandbox(args); // cleaned up by the engine
		return *app;
	}
	~Sandbox() { ET_LOG_INFO("Destroyed app"); }
};

int main(int argc, char const *argv[]) {
	auto &app = Sandbox::Init({ argv, argv + argc });
	app.Run();
	return 0;
}
