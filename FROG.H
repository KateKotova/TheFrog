// Лабораторная работа No. 6.
// Классы.
// Выполнил: ст. гр. 443 Котова Е.
// Проверил: доцент Никичкин Б.В.
//-----------------------------------------------------------

// Логический тип.
enum Boolean {false, true};
//-----------------------------------------------------------

// Получение информации о текущем режиме рисования.
void GetFillStyleAndColor(
  struct settingstype &CurrentFillInformation,
  unsigned &CurrentColor);

// Установка режима рисования.
void SetFillStyleAndColor(
  const struct fillsettingstype FillInformation,
  const unsigned Color);

// Установка цвета контура и заливки в цвет экрана,
// а стиля заливки - в сплошной.
void SetBackgroundFillStyleAndColor();
//----------------------------------------------------------

// Определение кнопки, нажатой пользователем.
Boolean GetDelta (char &DeltaX,
                  char &DeltaY,
                  char &Increase,
                  char &YIncrease,
                  int  &DeltaAngle);
//-----------------------------------------------------------

// Преобразование угла к диапазону (-180; 180].
int SetAngleToRange (int Angle);
//-----------------------------------------------------------

// Класс Размещение.
class Location
{
  // Защищенные поля класса.
  protected:
    int X;  // Координата по оси ОХ.
    int Y;  // Координата по оси ОУ.

  // Открытые поля класса.
  public:
    // Получение названия класса.
    virtual char *GetClassName() { return "Location"; };

    // Установка координаты по оси ОХ.
    void SetX(const int NewX)
    { X = NewX; }
    // Установка координаты по оси ОУ.
    void SetY(const int NewY)
    { Y = NewY; }

    // Получение координаты по оси ОХ.
    int  GetX() { return X; }
    // Получение координаты по оси ОУ.
    int  GetY() { return Y; }


    // Конструктор: установка координат размещения.
    Location(const int InitX = 0,
             const int InitY = 0)
    {
      SetX(InitX);
      SetY(InitY);
    }
}; // class Location
//-----------------------------------------------------------

// Класс Точка - наследник класса Размещение.
class Point : public Location
{
  // Защищенные поля класса.
  protected:
    Boolean Visible;  // Признак отображения точки на экране.

  // Открытые поля класса.
  public:
    // Получение названия класса.
    char *GetClassName() { return "Point"; };

    // Выявление видимости объекта на экране.
    Boolean GetVisible() { return Visible; }
    // Изменение видимости.
    void SetVisible (const Boolean NewVisible);

    // Конструктор: установка координат размещения и невидимости.
    Point(const int InitX = 0,
          const int InitY = 0);

    // Прорисовка объекта.
    virtual void DrawVirtual();

    // Отображение объекта на экране.
    virtual void ShowVirtual();
    // Сокрытие объекта с экрана.
    virtual void HideVirtual();

    // Перенос объекта с одного места на экране на другое.
    virtual void MoveToVirtual(const int NewX,
                               const int NewY,
                               const Boolean HideAndShow);
    // Перенос объекта на шаг от первоначального положения
    // в указанном направлении.
    virtual void MoveOnStepVirtual(const char DeltaX,
                                   const char DeltaY,
                                   const int Step = 1,
                                   const Boolean HideAndShow = true);

    // Изменение положения или размеров объекта на экране.
    virtual void ChangeViewVirtual (const char DeltaX,
                                    const char DeltaY,
                                    const char Increase,
                                    const char YIncrease,
                                    const int  DeltaAngle,
                                    const int  Step = 1);
    // Движение объекта по экрану при изменении его размеров
    // в зависимости от шага Step.
    void Run(const int Step = 1);
}; // class Point
//-----------------------------------------------------------

// Класс Окружность.
class Circumference : public Point
{
  // Защищенные поля класса.
  protected:
    int Radius; // Радиус окружности.

  // Открытые поля класса.
  public:
    // Получение названия класса.
    char *GetClassName() { return "Circumference"; };

    // Установка радиуса.
    void SetRadius(const int NewRadius)
    { Radius = NewRadius; }
    // Получение радиуса.
    int  GetRadius() { return Radius; }

    // Конструктор: установка координат размещения,
    // радиуса и невидимости.
    Circumference(const int InitX = 0,
                  const int InitY = 0,
                  const int InitRadius = 1);

    // Прорисовка объекта.
    void DrawVirtual();

    // Увеличение объекта на величину шага Step.
    virtual void ExpandVirtual (const int Step = 1,
                                const Boolean HideAndShow = true);
    // Уменьшение объекта на величину шага Step.
    void Contract(const int Step = 1,
                  const Boolean HideAndShow = true);

    // Изменение положения или размеров объекта на экране.
    void ChangeViewVirtual (const char DeltaX,
                            const char DeltaY,
                            const char Increase,
                            const char YIncrease,
                            const int  DeltaAngle,
                            const int  Step = 1);
}; // class Circumference
//-----------------------------------------------------------

// Класс Круг.
class Circle : public Circumference
{
  // Открытые поля класса.
  public:
    // Получение названия класса.
    char *GetClassName() { return "Circle"; };

    // Конструктор: установка координат размещения,
    // радиуса и невидимости.
    Circle(const int InitX = 0,
           const int InitY = 0,
           const int InitRadius = 1);

    // Прорисовка объекта.
    void DrawVirtual();
}; // class Circle
//-----------------------------------------------------------

// Класс Эллипс.
class Ellipse : public Circumference
{
  // Защищенные поля класса.
  protected:
    int YRadius; // Радиус эллипса по оси ОУ,
                 // Radius - радиус по оси ОХ.

  // Открытые поля класса.
  public:
    // Получение названия класса.
    char *GetClassName() { return "Ellipse"; };

    // Установка радиуса по оси ОУ.
    void SetYRadius(const int NewYRadius)
    { YRadius = NewYRadius; }
    // Получение радиуса по оси ОУ.
    int  GetYRadius() { return YRadius; }


    // Конструктор: установка координат размещения,
    // радиуcов и невидимости.
    Ellipse(const int InitX = 0,
            const int InitY = 0,
            const int InitRadius = 1,
            const int InitYRadius = 1);

    // Прорисовка объекта.
    void DrawVirtual();

    // Увеличение объекта на величину шага Step по оси ОУ.
    virtual void YExpandVirtual(const int Step = 1,
                                const Boolean HideAndShow = true);
    // Уменьшение объекта на величину шага Step по оси ОУ.
    void YContract(const int Step = 1,
                   const Boolean HideAndShow = true);

    // Изменение положения или размеров объекта на экране.
    void ChangeViewVirtual (const char DeltaX,
                            const char DeltaY,
                            const char Increase,
                            const char YIncrease,
                            const int  DeltaAngle,
                            const int  Step = 1);
}; // class Ellipse
//-----------------------------------------------------------

// Класс Залитый эллипс.
class FillEllipse : public Ellipse
{
  // Открытые поля класса.
  public:
    // Получение названия класса.
    char *GetClassName() { return "FillEllipse"; };

    // Конструктор: установка координат размещения,
    // радиуcов и невидимости.
    FillEllipse(const int InitX = 0,
                const int InitY = 0,
                const int InitRadius = 1,
                const int InitYRadius = 1);

    // Прорисовка объекта.
    void DrawVirtual();
}; // class FillEllipse
//-----------------------------------------------------------

#define WHITE 15

// Класс Круглое кольцо.
class Ring: public Circumference
{
  // Защищенные поля класса.
  protected:
    int InnerRadius;     // Внутренний радиус кольца.
    unsigned InnerColor; // Цвет внутреннего радиуса кольца.

  // Открытые поля класса.
  public:
    // Получение названия класса.
    char *GetClassName() { return "Ring"; };

    // Установка внутреннего радиуса.
    void SetInnerRadius(const int NewInnerRadius);
    // Получение внутреннего радиуса.
    int  GetInnerRadius() { return InnerRadius; }

    // Конструктор: установка координат размещения,
    // цвета, радиусов и невидимости.
    Ring(const int InitX = 0,
         const int InitY = 0,
         const int InitRadius = 1,
         const int InitInnerRadius = 1,
         const unsigned InitInnerColor = WHITE);

    // Прорисовка внешней части объекта.
    virtual void OuterDrawVirtual();
    // Прорисовка внутренней части объекта.
    virtual void InnerDrawVirtual();
    // Прорисовка объекта, состоящего из двух частей.
    void DoubleDraw(const unsigned InnerFillColor,
                    const Boolean OuterDeleting);
    // Прорисовка объекта.
    void DrawVirtual();

    // Увеличение объекта на величину шага Step.
    void ExpandVirtual (const int Step = 1,
                        const Boolean HideAndShow = true);
}; // class Ring
//-----------------------------------------------------------

// Класс Залитое круглое кольцо.
class FillRing: public Ring
{
  // Защищенные поля класса.
  protected:
    unsigned InnerFillColor; // Цвет заливки внутреннего радиуса кольца.

  // Открытые поля класса.
  public:
    // Получение названия класса.
    char *GetClassName() { return "FillRing"; };

    // Конструктор: установка координат размещения,
    // цветов, радиусов и невидимости.
    FillRing(const int InitX = 0,
             const int InitY = 0,
             const int InitRadius = 1,
             const int InitInnerRadius = 1,
             const unsigned InitInnerColor = WHITE,
             const unsigned InitInnerFillColor = WHITE);

    // Прорисовка внешней части объекта.
    void OuterDrawVirtual();
    // Прорисовка внутренней части объекта.
    void InnerDrawVirtual();
    // Прорисовка объекта.
    void DrawVirtual();
}; // class FillRing
//-----------------------------------------------------------

// Класс Эллиптическое кольцо.
class EllipticalRing: public Ring
{
  // Защищенные поля класса.
  protected:
    int YRadius;      // Внешний радиус эллипса по оси ОУ,
                      // Radius - внешний радиус по оси ОХ.
    int InnerYRadius; // Внутренний радиус кольца по оси ОУ,
                      // InnerRadius - внутренний радиус по оси ОХ.

  // Открытые поля класса.
  public:
    // Получение названия класса.
    char *GetClassName() { return "EllipticalRing"; };

    // Установка внешнего радиуса по оси ОУ.
    void SetYRadius(const int NewYRadius)
    { YRadius = NewYRadius; }
    // Получение внешнего радиуса по оси ОУ.
    int  GetYRadius() { return YRadius; }

    // Установка внутреннего радиуса по оси ОУ.
    void SetInnerYRadius(const int NewInnerYRadius);
    // Получение внутреннего радиуса по оси ОУ.
    int  GetInnerYRadius() { return InnerYRadius; }

    // Конструктор: установка координат размещения,
    // цвета, радиусов и невидимости.
    EllipticalRing(const int InitX = 0,
         const int InitY = 0,
         const int InitRadius = 1,
         const int InitYRadius = 1,
         const int InitInnerRadius = 1,
         const int InitInnerYRadius = 1,
         const unsigned InitInnerColor = WHITE);

    // Прорисовка внешней части объекта.
    void OuterDrawVirtual();
    // Прорисовка внутренней части объекта.
    void InnerDrawVirtual();
    // Прорисовка объекта.
    void DrawVirtual();

    // Увеличение объекта на величину шага Step по оси ОУ.
    virtual void YExpandVirtual(const int Step = 1,
                                const Boolean HideAndShow = true);

    // Изменение положения или размеров объекта на экране.
    void ChangeViewVirtual (const char DeltaX,
                            const char DeltaY,
                            const char Increase,
                            const char YIncrease,
                            const int  DeltaAngle,
                            const int  Step = 1);
}; // class EllipticalRing
//-----------------------------------------------------------

// Класс Залитое эллиптическое кольцо.
class FillEllipticalRing: public EllipticalRing
{
  // Защищенные поля класса.
  protected:
    unsigned InnerFillColor; // Цвет заливки внутреннего радиуса кольца.

  // Открытые поля класса.
  public:
    // Получение названия класса.
    char *GetClassName() { return "FillEllipticalRing"; };

    // Конструктор: установка координат размещения,
    // цветов, радиусов и невидимости.
    FillEllipticalRing(const int InitX = 0,
                       const int InitY = 0,
                       const int InitRadius = 1,
                       const int InitYRadius = 1,
                       const int InitInnerRadius = 1,
                       const int InitInnerYRadius = 1,
                       const unsigned InitInnerColor = WHITE,
                       const unsigned InitInnerFillColor = WHITE);

    // Прорисовка внешней части объекта.
    void OuterDrawVirtual();
    // Прорисовка внутренней части объекта.
    void InnerDrawVirtual();
    // Прорисовка объекта.
    void DrawVirtual();
}; // class FillEllipticalRing
//-----------------------------------------------------------

// Класс Нога.
class Leg : public Circumference
{
  // Защищенные поля класса.
  protected:
    int Angle;      // Угол разворота пальцев.
    int StartAngle; // Начальный угол разворота пальцев.
    int X1;         // Координата первой точки по оси ОХ.
    int Y1;         // Координата первой точки по оси ОУ.
    int X2;         // Координата второй точки по оси ОХ.
    int Y2;         // Координата второй точки по оси ОУ.

  // Открытые поля класса.
  public:
    // Получение названия класса.
    char *GetClassName() { return "Leg"; };

    // Установка координат точки
    // в зависимости от исходной и угла.
    void SetXY(const int NewAngle,
                     int &ChangedX,
                     int &ChangedY);

    // Установка координат точек
    // в зависимости от исходной и угла.
    virtual void SetXYsVirtual();

    // Получение координаты первой точки по оси ОХ.
    int  GetX1() { return X1; }
    // Получение координаты первой точки по оси ОУ.
    int  GetY1() { return Y1; }

    // Получение координаты второй точки по оси ОХ.
    int  GetX2() { return X2; }
    // Получение координаты второй точки по оси ОУ.
    int  GetY2() { return Y2; }


    // Конструктор: установка координат размещения,
    // радиуса и невидимости.
    Leg(const int InitX1 = 0,
        const int InitY1 = 0,
        const int InitRadius = 1,
        const int InitAngle = 0,
        const int InitStartAngle = 0);

    // Прорисовка объекта.
    void DrawVirtual();

    // Перенос объекта с одного места на экране на другое.
    void MoveToVirtual(const int NewX,
                       const int NewY,
                       const Boolean HideAndShow);
    // Перенос объекта на шаг от первоначального положения
    // в указанном направлении.
    void MoveOnStepVirtual(const char DeltaX,
                           const char DeltaY,
                           const int  Step = 1,
                           const Boolean HideAndShow = true);

    // Увеличение объекта на величину шага Step.
    void ExpandVirtual (const int Step = 1,
                        const Boolean HideAndShow = true);
    //Отклонение объекта на шаг Step.
    virtual void DeclineVirtual(const int  Step = 1,
                                const Boolean HideAndShow = true);

    // Изменение положения или размеров объекта на экране.
    void ChangeViewVirtual (const char DeltaX,
                            const char DeltaY,
                            const char Increase,
                            const char YIncrease,
                            const int  DeltaAngle,
                            const int  Step = 1);
}; // class Leg
//-----------------------------------------------------------

// Класс Кисть (трехпалая) ноги.
class Hand : public Leg
{
  // Защищенные поля класса.
  protected:
    int X3;  // Координата третьей точки по оси ОХ.
    int Y3;  // Координата третьей точки по оси ОУ.

  // Открытые поля класса.
  public:
    // Получение названия класса.
    char *GetClassName() { return "Hand"; };

    // Установка координат точек
    // в зависимости от исходной и угла.
    void SetXYsVirtual();

    // Получение координаты третьей точки по оси ОХ.
    int  GetX3() { return X3; }
    // Получение координаты третьей точки по оси ОУ.
    int  GetY3() { return Y3; }


    // Конструктор: установка координат размещения,
    // радиуса и невидимости.
    Hand(const int InitX = 0,
         const int InitY = 0,
         const int InitRadius = 1,
         const int InitAngle = 0,
         const int InitStartAngle = 0);

    // Прорисовка объекта.
    void DrawVirtual();

    // Перенос объекта с одного места на экране на другое.
    void MoveToVirtual(const int NewX,
                       const int NewY,
                       const Boolean HideAndShow);
    // Перенос объекта на шаг от первоначального положения
    // в указанном направлении.
    void MoveOnStepVirtual(const char DeltaX,
                           const char DeltaY,
                           const int  Step,
                           const Boolean HideAndShow);

    //Отклонение объекта на шаг Step.
    void DeclineVirtual(const int  Step = 1,
                        const Boolean HideAndShow = true);
}; // class Hand
//-----------------------------------------------------------

// Класс Кисть (трехпалая) ноги
// с расплющенными подушечками на пальцах.
class FingersHand : public Hand
{
  // Защищенные поля класса.
  protected:
    int FingerRadius;  // Радиус подушечки пальца.

  // Открытые поля класса.
  public:
    // Получение названия класса.
    char *GetClassName() { return "FingersHand"; };

    // Установка радиуса подушечки пальцев.
    void SetFingerRadius(const int NewFingerRadius);
    // Получение радиуса подушечки пальцев.
    int  GetFingerRadius() { return FingerRadius; };

    // Конструктор: установка координат размещения,
    // радиуса и невидимости.
    FingersHand(const int InitX = 0,
                const int InitY = 0,
                const int InitRadius = 1,
                const int InitFingerRadius = 1,
                const int InitAngle = 0,
                const int InitStartAngle = 0);

    // Прорисовка объекта.
    void DrawVirtual();
}; // class FingersHand
//-----------------------------------------------------------

// Класс Лягушачья лапа.
class FrogPaw : public Leg
{
  // Защищенные поля класса.
  protected:
    FingersHand FrogHand;  // Лягушачья кисть.
    int LegThickness;      // Толщина ноги.

  // Открытые поля класса.
  public:
    // Получение названия класса.
    char *GetClassName() { return "FrogPaw"; };

    // Установка новой толщины ноги.
    void SetLegThickness(const int NewLegThickness)
    { LegThickness = NewLegThickness; }
    // Получение новой ноги.
    int  GetLegThickness() { return(LegThickness); }

    // Конструктор: установка координат размещения,
    // радиуса и невидимости.
    FrogPaw(const int InitX1 = 0,
            const int InitY1 = 0,
            const int InitRadius = 1,
            const int InitAngle = 0,
            const int InitStartAngle = 0,
            const int InitLegThickness = 1,

            const int InitHandRadius = 1,
            const int InitFingerRadius = 1,
            const int InitHandAngle = 0,
            const int InitHandStartAngle = 0);

    // Прорисовка объекта.
    void DrawVirtual();
    // Отображение объекта на экране.
    void ShowVirtual();
    // Сокрытие объекта с экрана.
    void HideVirtual();

    // Перенос объекта с одного места на экране на другое.
    void MoveToVirtual(const int NewX,
                       const int NewY,
                       const Boolean HideAndShow);

    // Увеличение объекта на величину шага Step.
    void ExpandVirtual (const int Step = 1,
                        const Boolean HideAndShow = true);
    //Отклонение объекта на шаг Step.
    void DeclineVirtual(const int  Step = 1,
                        const Boolean HideAndShow = true);
}; // class FrogPaw
//-----------------------------------------------------------

// Класс Лягушачья голова.
class FrogHad : public FillEllipse
{
  // Защищенные поля класса.
  protected:
    FillRing      RightEye;      // Правый глаз.
    FillRing      LeftEye;       // Левый глаз.
    FillEllipse   Mouth;         // Рот.
    Circumference RightNostril;  // Правая ноздря.
    Circumference LeftNostril;   // Левая ноздря.

    unsigned MouthColor;         // Цвет губ.
    unsigned MouthFillColor;     // Цвет полости рта.
    int      EyeRadius;          // Радиус глаза.
    unsigned EyeFillColor;       // Цвет белков глаз.
    unsigned EyeInnerColor;      // Цвет радужной оболочки.
    unsigned EyeInnerFillColor;  // Цвет зрачка.

  // Открытые поля класса.
  public:
    // Получение названия класса.
    char *GetClassName() { return "FrogHad"; };

    // Установка нового радиуса глаза.
    void SetEyeRadius(const int NewEyeRadius)
    { EyeRadius = NewEyeRadius; }
    // Получение нового радиуса глаза.
    int  GetEyeRadius() { return(EyeRadius); }

    // Конструктор: установка координат размещения,
    // радиуcов и невидимости.
    FrogHad(const int InitX = 0,
            const int InitY = 0,
                  int InitRadius = 1,
                  int InitYRadius = 1,

            const unsigned InitMouthColor = WHITE,
            const unsigned InitMouthFillColor = WHITE,
            const int      InitEyeRadius = 1,
            const unsigned InitEyeFillColor = WHITE,
            const unsigned InitEyeInnerColor = WHITE,
            const unsigned InitEyeInnerFillColor = WHITE);

    // Прорисовка объекта.
    void DrawVirtual();

    // Назначение одновременной видимости/невидимости
    // всем объектм, входящим в состав данного класса.
    virtual void SetSubObjectsVisibleVirtual(const Boolean SubObjectsVisible);
    // Отображение объекта на экране.
    void ShowVirtual();
    // Сокрытие объекта с экрана.
    void HideVirtual();

    // Перенос объекта с одного места на экране на другое.
    void MoveToVirtual(const int NewX,
                       const int NewY,
                       const Boolean HideAndShow);

    // Увеличение объекта на величину шага Step.
    void ExpandVirtual (const int Step = 1,
                        const Boolean HideAndShow = true);
    // Увеличение объекта на величину шага Step по оси ОУ.
    void YExpandVirtual(const int Step = 1,
                        const Boolean HideAndShow = true);
}; // class FrogHad
//-----------------------------------------------------------

// Класс Лягушачья пара лап.
class FrogPawsPair : public Circumference
{
  // Защищенные поля класса.
  protected:
    FrogPaw RightPaw;
    FrogPaw LeftPaw;

  // Открытые поля класса.
  public:
    // Получение названия класса.
    char *GetClassName() { return "FrogPawsPair"; };

    // Конструктор: установка координат размещения,
    // радиуса и невидимости.
    FrogPawsPair(const int InitX = 0,
                 const int InitY = 0,
                 const int InitRadius = 1,

                 const int InitPawRadius = 1,
                 const int InitPawAngle = 0,
                 const int InitStartPawAngle = 0,
                 const int InitLegThickness = 1,

                 const int InitHandRadius = 1,
                 const int InitFingerRadius = 1,
                 const int InitHandAngle = 0,
                 const int InitHandStartAngle = 0);

    // Прорисовка объекта.
    void DrawVirtual();
    // Отображение объекта на экране.
    void ShowVirtual();
    // Сокрытие объекта с экрана.
    void HideVirtual();

    // Перенос объекта с одного места на экране на другое.
    void MoveToVirtual(const int NewX,
                       const int NewY,
                       const Boolean HideAndShow);

    // Увеличение объекта на величину шага Step.
    void ExpandVirtual (const int Step = 1,
                        const Boolean HideAndShow = true);
    //Отклонение объекта на шаг Step.
    virtual void DeclineVirtual(const int  Step = 1,
                                const Boolean HideAndShow = true);

    // Изменение положения или размеров объекта на экране.
    void ChangeViewVirtual (const char DeltaX,
                            const char DeltaY,
                            const char Increase,
                            const char YIncrease,
                            const int  DeltaAngle,
                            const int  Step = 1);
}; // class FrogPawsPair
//-----------------------------------------------------------

// Класс Лягушка.
class Frog : public FillEllipticalRing
{
  // Защищенные поля класса.
  protected:
    FrogHad Had;
    FrogPawsPair UpperPawsPair;
    FrogPawsPair LowerPawsPair;

  // Открытые поля класса.
  public:
    // Получение названия класса.
    char *GetClassName() { return "Frog"; };

    // Конструктор: установка координат размещения,
    // цветов, радиусов и невидимости.
    Frog(const int InitX = 0,
         const int InitY = 0,
         const int InitRadius = 1,
         const int InitYRadius = 1,
         const int InitInnerRadius = 1,
         const int InitInnerYRadius = 1,
         const unsigned InitInnerColor = WHITE,
         const unsigned InitInnerFillColor = WHITE,


                   
               int InitHadRadius = 1,
               int InitHadYRadius = 1,

         const unsigned InitMouthColor = WHITE,
         const unsigned InitMouthFillColor = WHITE,
         const int      InitEyeRadius = 1,
         const unsigned InitEyeFillColor = WHITE,
         const unsigned InitEyeInnerColor = WHITE,
         const unsigned InitEyeInnerFillColor = WHITE,



         const int InitLegThickness = 1,


         const int InitUpperPawRadius = 1,
         const int InitUpperPawAngle = 0,
         const int InitStartUpperPawAngle = 0,

         const int InitUpperHandRadius = 1,
         const int InitUpperFingerRadius = 1,
         const int InitUpperHandAngle = 0,
         const int InitUpperHandStartAngle = 0,
              

         const int InitLowerPawRadius = 1,
         const int InitLowerPawAngle = 0,
         const int InitStartLowerPawAngle = 0,

         const int InitLowerHandRadius = 1,
         const int InitLowerFingerRadius = 1,
         const int InitLowerHandAngle = 0,
         const int InitLowerHandStartAngle = 0);

    // Прорисовка объекта.
    void DrawVirtual();
    // Отображение объекта на экране.
    void ShowVirtual();
    // Сокрытие объекта с экрана.
    void HideVirtual();

    // Перенос объекта с одного места на экране на другое.
    void MoveToVirtual(const int NewX,
                       const int NewY,
                       const Boolean HideAndShow);


    // Увеличение объекта на величину шага Step.
    void ExpandVirtual (const int Step = 1,
                        const Boolean HideAndShow = true);
    // Увеличение объекта на величину шага Step по оси ОУ.
    void YExpandVirtual(const int Step = 1,
                        const Boolean HideAndShow = true);
    //Отклонение объекта на шаг Step.
    virtual void DeclineVirtual(const int  Step = 1,
                                const Boolean HideAndShow = true);

    // Изменение положения или размеров объекта на экране.
    void ChangeViewVirtual (const char DeltaX,
                            const char DeltaY,
                            const char Increase,
                            const char YIncrease,
                            const int  DeltaAngle,
                            const int  Step = 1);
}; // class Frog
//-----------------------------------------------------------

