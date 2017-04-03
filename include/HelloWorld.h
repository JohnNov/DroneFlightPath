#ifndef HELLOWORLD_H
#define HELLOWORLD_H


class HelloWorld
{
    public:
        HelloWorld();
        void onButtonClick();
        void Run();
        virtual ~HelloWorld();
    protected:
    private:
    sfg::SFGUI m_sfgui;
    sfg::Label::Ptr m_label;
};

#endif // HELLOWORLD_H
