#include <enginethingy.hpp>
#include <iostream>

class AppQuit : public EngineThingy::Event {
public:
	ET_EVENT_CLASS(EngineThingy::EventType::ApplicationQuit,
				   EngineThingy::EventCategory::Application)
	AppQuit() = default;
};

int main() {
	using namespace EngineThingy;
	static_assert(is_event_v<AppQuit>);
	int x			   = 0;
	EventDispatcher el = EventDispatcher::Create<AppQuit>(
		[&x](const AppQuit &) { ++x; }, LAYERS_ALL);
	AppQuit q;
	el(q);
	assert(x == 1);

	KeyPressedEvent kp(KeyCode::Key0);
	assert(kp.HasCategory(EventCategory::Keyboard));
}