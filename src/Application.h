#ifndef F1METER_APPLICATION_H
#define F1METER_APPLICATION_H

class Application {

    static Application* instance;

private:
    Application() = default;

public:
    void Start();

private:
    void Initialize();
    void Run();
    void CleanUp();

public:
    static Application& GetInstance();

private:
    static void DeleteInstance();

    friend int main();

};

#endif //F1METER_APPLICATION_H
