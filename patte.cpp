#include <vector>
#include <stack>
#include <iostream>

using namespace std;

class Command {
public:
    virtual void positive() = 0;
    virtual void negative() = 0;
};

class Light {
public:
    void on() {
        cout << "Свет вкл" << endl;
    }
    void off() {
        cout << "Свет выкл" << endl;
    }
};

class Conditioner {
public:
    void on() {
        cout << "Кондиционер вкл" << endl;
    }
    void off() {
        cout << "Кондиционер выкл" << endl;
    }
    void speedUp()
    {
        cout << "Скорость кондиционера увеличина" << endl;
    }
    void speedDown()
    {
        cout << "Скорость кондиционера уменьшина" << endl;
    }
};

class LightCommand : public Command {
private:
    Light* light;

public:
    LightCommand(Light* _light) : light(_light) {}
    void positive() override {
        light->on();
    }
    void negative() override {
        light->off();
    }
};

class ConditionerCommand : public Command {
private:
    Conditioner* conditioner;

public:
    ConditionerCommand(Conditioner* _conditioner) : conditioner(_conditioner) {}
    void positive() override {
        conditioner->on();
    }
    void negative() override {
        conditioner->off();
    }
};

class ConditionerSpeed : public Command {
private:
    Conditioner* conditioner;

public:
    ConditionerSpeed(Conditioner* _conditioner) : conditioner(_conditioner) {}
    void positive() override {
        conditioner->speedUp();
    }
    void negative() override {
        conditioner->speedDown();
    }
};

class pult {
private:
    vector <Command*> commands;
    stack <Command*> history;
public:
    pult() {
        commands.resize(2);
    }
    void setCommand(int button, Command* command) {
        commands[button] = command;
    }

    void pressOn(int button) {
        commands[button]->positive();
        history.push(commands[button]);
    }

    void pressCancel() {
        if (!history.empty())

        {
            history.top()->negative();
            history.pop();
        }
    }
};

int main()
{
    setlocale(LC_ALL, "rus");

    Conditioner* conditioner = new Conditioner();
    Light* light = new Light();

    pult* pu = new pult();

    pu->setCommand(0, new ConditionerCommand(conditioner));
    pu->setCommand(1, new LightCommand(light));


    pu->pressOn(0);
    pu->pressOn(1);
    pu->pressCancel();
    pu->pressCancel();

    delete pu;
    delete conditioner;
    delete light;
}