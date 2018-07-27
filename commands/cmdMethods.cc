//
// example taken from tomtom's c++ dependencies analyser
//

#include <iostream>
#include <map>
#include <string>

class SUT {
public:
    SUT()
        : m_value(0) {
        ;
    }
    void RunCommands(std::string n);
    void RegisterCommands();
private:
    using Command = void (SUT::*)();
    int m_value;
    std::map<std::string, Command> m_registry;

    void Foo() {
        std::cout << "Foo" << m_value++ << std::endl;
    }

    void Bar() {
        std::cout << "Bar" << ++m_value << std::endl;
    }
};

void SUT::RunCommands(std::string n) {
    auto cmd = m_registry[n];
    if (cmd) {
        (this->*cmd)();
    }
}

void SUT::RegisterCommands() {
    m_registry["Foo"] = &SUT::Foo;
    m_registry["Bar"] = &SUT::Bar;
}

int main(int argc, char **argv) {
    SUT sut;
    sut.RegisterCommands();
    sut.RunCommands("dude");
    sut.RunCommands("Foo");
    sut.RunCommands("Bar");
    return 0;
}