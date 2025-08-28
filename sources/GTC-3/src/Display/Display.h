// 2022/04/20 08:53:49 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Display/Colors.h"
#include "Utils/Text/String.h"


struct TypeMeasure
{
    enum E
    {
        Temperature,        // Температура
        Pressure,           // Давление
        Humidity,           // Влажность
        DewPoint,           // Точка росы
        Count
    };
};


namespace Display
{
    static const int WIDTH = 160;
    const int HEIGHT = 128;

    extern bool need_redraw;

    void SetMeasure(TypeMeasure::E, float measure);

    void Update();

    void BeginScene(Color::E);

    void EndScene();

    namespace Buffer
    {
        // Возвращает указатель на строку
        uint8 *GetLine(int x, int y);
    }
}


struct Rectangle
{
    Rectangle(int w, int h) : width(w), height(h) { }

    void Fill(int x, int y, Color::E = Color::Count);

    void Draw(int x, int y, Color::E = Color::Count);

    void DrawFilled(int x, int y, Color::E fill, Color::E draw);

private:

    int width;
    int height;
};


struct HLine
{
    HLine(int w) : width(w) {}

    void Draw(int x, int y, Color::E = Color::Count);

private:

    int width;
};


struct VLine
{
    VLine(int h) : height(h) {}

    void Draw(int x, int y, Color::E = Color::Count);

private:

    int height;
};


struct Point
{
    void Set(int x, int y, Color::E color = Color::Count);
};
