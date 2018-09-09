
#include <cassert>

void RunTinyTests();

// source
// P155
//
// how accessibly should virtual functions be?
// public: rarely if ever
// protected: sometimes
// private: by default
//
// P156
// Prefer to make interfaces nonvirtual 
// circle.area() -> calling virtual circle.computeAreaCore() 
// See P156 Microsoft design guideline
// recall Template Method
//
void test_template_method() {
    struct Param {};

    class Widget {
    public:
        // P157
        // stable nonvirtual interface

        // uses runProcess...()
        int process(Param& param) {
            return runProcessPhaseOne(param) +\
                runProcessPhaseTwo(param);
        }

        // uses isDone...()
        bool isDone() {
            return isDonePhaseOne() &&\
                isDonePhaseTwo();
        }

    private:
        // P157
        // customization is an implementation detail that might or might
        // not directly correspond to the interface.
        // each of these functions might optionally be pure virtual,
        // and if so might or might not have an implementation in
        // Widget class;
        virtual int runProcessPhaseOne(Param&) = 0;
        virtual int runProcessPhaseTwo(Param&) = 0;
        virtual bool isDonePhaseOne() = 0;
        virtual bool isDonePhaseTwo() = 0;
    };

    class CustomWidget : virtual public Widget {
    private:
        int runProcessPhaseOne(Param& param) override {
            m_phaseOneDone = true;
            return 1;
        }

        int runProcessPhaseTwo(Param& param) override {
            m_phaseTwoDone = true;
            return 2;
        }

        bool isDonePhaseOne() override {
            return m_phaseOneDone;
        }

        bool isDonePhaseTwo() override {
            return m_phaseTwoDone;
        }

        // custom widget's state
        bool m_phaseOneDone = false;
        bool m_phaseTwoDone = false;
    };

    CustomWidget widget;
    Param param;
    assert(3 == widget.process(param));
    assert(widget.isDone());
}

// P157
// these public virtual functions, like all public virtual functions, 
// simultaneously specify both the interface and the customizable
// behavior. The problem is in that "simultaneously" part, because 
// every public virtual function is forced to serve two audiences with 
// distinct needs and different purposes
//
// Nonvirtual interface pattern
// recall NVI document wt atlas
//
// Prefer to use the NVI to make the interface stable and nonvirtual 
// while delegating customizable work to nonpublic virtual functions 
// that are responsible for implementing the customizable behavior. 
// after all, virtual functions are designed to let derived classes
// customize behavior; it is better to not let publicly derived classes 
// also customize the inherited interface, which is supposed to be 
// consistent,
//
// P159
// make the virtual function private;
// only if derived classes need to invoke the base implementation of 
// a virtual function, make the virtual function protected
//

int main() {
    RunTinyTests();
    return  0;
}


