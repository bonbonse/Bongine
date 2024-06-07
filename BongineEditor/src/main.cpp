#include <iostream>

#include <BongineCore/App.hpp>



class MyApp : public Bongine::App
{
	int frame = 0;

	virtual void update() override {
		/*Users functions here*/

		//std::cout << "Update frame: " << frame++ << std::endl;
	}
};

int main() {
	auto myApp = std::make_unique<MyApp>();

	int returnCode = myApp->start(1024, 768, "First");

	return returnCode;
}