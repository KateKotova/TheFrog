// Лабораторная работа No. 6.
// Классы.
// Выполнил: ст. гр. 443 Котова Е.
// Проверил: доцент Никичкин Б.В.
//-----------------------------------------------------------

#include <GRAPHICS.H>
#include <CONIO.H>
#include <MATH.H>
#include <STDIO.H>
#include <STDLIB.H>

#include "FROG.H"
//-----------------------------------------------------------

// Получение информации о текущем режиме рисования.
void GetFillStyleAndColor(
  struct fillsettingstype &CurrentFillInformation,
  unsigned &CurrentColor)
{
  // Получение информации о текущем режиме заливки.
  getfillsettings(&CurrentFillInformation);
  // Текущее значение цвета рисования.
  CurrentColor = getcolor();
} // GetFillInformationAndColor
//-----------------------------------------------------------

// Установка режима рисования.
void SetFillStyleAndColor(
  const struct fillsettingstype FillInformation,
  const unsigned Color)
{
  // Установка цвета рисования.
  setcolor(Color);
  // Установка режима заливки.
  setfillstyle(FillInformation.pattern,
               FillInformation.color);
} // SetFillStyleAndColor
//-----------------------------------------------------------

// Установка цвета контура и заливки в цвет экрана,
// а стиля заливки - в сплошной.
void SetBackgroundFillStyleAndColor()
{
  // Стиль заливки - сплошной.
  #define SOLID_FILL 1

  // Установка цвета фона.
  setcolor(getbkcolor());
  // Установка сплошного режима заливки цветом фона.
  setfillstyle(SOLID_FILL, getbkcolor());
} // SetBackgroundFillStyleAndColor
//-----------------------------------------------------------
//


// Определение кнопки, нажатой пользователем.
Boolean GetDelta (char &DeltaX,
                  char &DeltaY,
                  char &Increase,
                  char &YIncrease,
                  int  &DeltaAngle)
{
  // Обозначение кодов клавиш.
  #define VK_RETURN         13 // Enter.
  #define VK_UP             72 // Стрелка вверх.
  #define VK_DOWN           80 // Стрелка вниз.
  #define VK_LEFT           75 // Стрелка влево.
  #define VK_RIGHT          77 // Стрелка вправо.
  #define VK_EXPAND         69 // Латинская буква Е -
                               // увеличение объекта.
  #define VK_CONTRACT       67 // Латинская буква С -
                               // уменьшение объекта.
  #define VK_YEXPAND        82 // Латинская буква R -
                               // увеличение объекта.
  #define VK_YCONTRACT      86 // Латинская буква V -
                               // уменьшение объекта.
  #define VK_EXPAND_ANGLE   65 // Латинская буква A -
                               // увеличение угла объекта.
  #define VK_CONTRACT_ANGLE 90 // Латинская буква Z -
                               // уменьшение угла объекта.

  char KeyChar;   // Символ, введенный с клавиатуры.
  Boolean Quit;   // Признак выхода из цикла.
  DeltaX = 0;     // Смещение по оси ОХ.
  DeltaY = 0;     // Смещение по оси ОY.
  Increase  = 0;  // Увеличение (по оси ОХ).
  YIncrease = 0;  // Увеличение по оси ОУ.

  // Зацикливание до тех пор? пока не будет нажат <Enter>
  // или стрелка перемещения.
  do
  {
    KeyChar = getch();
    // Выход из функции по нажатие <Enter>;
    // функция возвращает false,
    // так как перемещение объекта прекращено.
    if (KeyChar == VK_RETURN)
      return (false);

    Quit = true;

    // Если код расширенный - состоит из двух символов.
    if (! KeyChar) // if (KeyChar == 0)
    {
      // Получение второго символа расширенного кода.
      KeyChar = getch();
      // Проверка, была ли нажата стрелка.
      switch (KeyChar)
      {
        case VK_UP   : DeltaY = -1; break;
        case VK_DOWN : DeltaY =  1; break;
        case VK_LEFT : DeltaX = -1; break;
        case VK_RIGHT: DeltaX =  1; break;
        // Стрелка не нажата - выходить из цикла рано.
        default      : Quit = false;
      } // switch (KeyChar)
    } // if (! KeyChar)

    // Если код состоит из одного символа.
    else
      // Проверка, была ли нажата клавиша увеличения/уменьшения.
      switch (KeyChar)
      {
        case VK_EXPAND         : Increase   =  1; break;
        case VK_CONTRACT       : Increase   = -1; break;
        case VK_YEXPAND        : YIncrease  =  1; break;
        case VK_YCONTRACT      : YIncrease  = -1; break;
        case VK_EXPAND_ANGLE   : DeltaAngle =  1; break;
        case VK_CONTRACT_ANGLE : DeltaAngle = -1; break;
        // <E> или <C> не нажато - выходить из цикла рано.
        default      : Quit = false;
      } // switch (KeyChar)
  } // do
  // Пока нет выхода из цикла.
  while (! Quit);
  // Символ стрелки определенно был нажат.
  return (true);
} // GetDelta
//-----------------------------------------------------------
//


// Преобразование угла к диапазону (-180; 180].
int SetAngleToRange (int Angle)
{
  short Sign;
  if (Angle >= 0)
    Sign =  1;
  else
    Sign = -1;

  while (Sign * Angle > Sign * 360)
    Angle -= Sign * 360;
  if (Sign * Angle > 180)
    Angle = -Sign * 180 + (Angle - Sign * 180);
/*
  if (Angle >= 0)
  { while (Angle > 360) Angle -= 360;
    if (Angle > 180)    Angle = -180 + (Angle - 180); }
  else
  { while (Angle < 360) Angle += 360;
    if (Angle < -180)   Angle = 180 + (Angle + 180);  }
*/
 return Angle;
} // SetAngleToRange
//-----------------------------------------------------------
//



// Изменение видимости.
void Point :: SetVisible (const Boolean NewVisible)
{ Visible = NewVisible; }
//-----------------------------------------------------------

// Конструктор: установка координат размещения и невидимости.
Point :: Point(const int InitX,
               const int InitY) : Location(InitX, InitY)
{ SetVisible(false); }
//-----------------------------------------------------------

// Прорисовка объекта.
void Point :: DrawVirtual()
  // Отрисовка точки текущим цветом контурных линий.
{ putpixel(X, Y, getcolor()); }
//-----------------------------------------------------------

// Отображение объекта на экране.
void Point :: ShowVirtual()
{
  // Точка видима.
  SetVisible(true);
  // Прорисовка объекта.
  DrawVirtual();
} // Point :: ShowVirtual
//-----------------------------------------------------------

// Сокрытие объекта с экрана.
void Point :: HideVirtual()
{
  // Точка невидима.
  SetVisible(false);

  // Информация о текущем режиме заливки.
  struct fillsettingstype CurrentFillInformation;
  unsigned CurrentColor;  // Текущее значение цвета рисования.

  // Получение информации о текущем режиме рисования.
  GetFillStyleAndColor(CurrentFillInformation, CurrentColor);
  // Установка цвета контура и заливки в цвет экрана,
  // а стиля заливки - в сплошной.
  SetBackgroundFillStyleAndColor();

  // Прорисовка объекта.
  DrawVirtual();

  // Установка режима рисования.
  SetFillStyleAndColor(CurrentFillInformation, CurrentColor);
} // Point :: HideVirtual
//-----------------------------------------------------------

// Перенос объекта с одного места на экране на другое.
void Point :: MoveToVirtual(const int NewX,
                            const int NewY,
                            const Boolean HideAndShow)
{
  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    // Сокрытие объекта с экрана.
    HideVirtual();

  // Установка координаты по оси ОХ.
  SetX(NewX);
  // Установка координаты по оси ОУ.
  SetY(NewY);

  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    // Сокрытие объекта с экрана.
    ShowVirtual();
} // Point :: MoveToVirtual
//-----------------------------------------------------------

// Перенос объекта на шаг от первоначального положения
// в указанном направлении.
void Point :: MoveOnStepVirtual(const char DeltaX,
                                const char DeltaY,
                                const int  Step,
                                const Boolean HideAndShow)
{
  int CurrentX,  // Текущее значение координаты X.
      CurrentY;  // Текущее значение координаты У.

  // Изменение текущих координат.
  CurrentX = GetX() + DeltaX * Step;
  CurrentY = GetY() + DeltaY * Step;
  // Перемещение точки.
  MoveToVirtual(CurrentX, CurrentY, HideAndShow);
} // Point :: MoveOnStepVirtual
//-----------------------------------------------------------

// Изменение положения или размеров объекта на экране.
void Point :: ChangeViewVirtual(const char DeltaX,
                                const char DeltaY,
                                const char Increase,
                                const char YIncrease,
                                const int  DeltaAngle,
                                const int  Step)
{
  // Если нет попытки увеличить точку.
  if (DeltaX || DeltaY)
    // Перенос объекта на шаг от первоначального положения
    // в указанном направлении.
    MoveOnStepVirtual(DeltaX, DeltaY, Step, true);
} // Point :: ChangeViewVirtual
//-----------------------------------------------------------

// Движение объекта по экрану при изменении его размеров
// в зависимости от шага Step для точки не предусмотренно увеличение).
// При нажатии двух кнопок, обозначающих стрелки, одновременно
// объект будет перемещаться сразу по обоим осям координат -
// ОХ и ОУ - под углом 45 градусов.
void Point :: Run(const int  Step)
{
  // Отображение точки на экране.
  ShowVirtual();

  char DeltaX,    // Смещение по оси ОХ.
       DeltaY,    // Смещение по оси ОY.
       Increase,
       YIncrease; // Увеличение, но
                  // точка не увеличивается.
  int DeltaAngle; // Угловое смещение.
  // Пока нажимаются кнопки перемещения
  // и пока не нажат <Enter>.
  while (GetDelta(DeltaX, DeltaY, Increase, YIncrease, DeltaAngle))
    // Изменение положения или размеров объекта на экране.
    ChangeViewVirtual(DeltaX, DeltaY, Increase, YIncrease, DeltaAngle, Step);

  // Сокрытие объекта с экрана.
  HideVirtual();
} // Point :: Run
//-----------------------------------------------------------
//


// Конструктор: установка координат размещения,
// радиуса и невидимости.
Circumference :: Circumference(const int InitX,
                               const int InitY,
                               const int InitRadius) :

  Point(InitX, InitY)
{ SetRadius(InitRadius); }
//-----------------------------------------------------------

// Прорисовка объекта.
void Circumference :: DrawVirtual()
  // Отрисовка окружности текущим цветом контурных линий.
{ circle(X, Y, Radius); }
//-----------------------------------------------------------

// Увеличение объекта на величину шага Step.
void Circumference :: ExpandVirtual(const int  Step,
                                    const Boolean HideAndShow)
{
  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    // Сокрытие объекта с экрана.
    HideVirtual();

  // Увеличение радиуса
  SetRadius(Radius + Step);
  // Если окружности уменьшена до такой степени,
  // что радиус становится отрицательным -
  // его обнуляют.
  if (Radius < 0)
    Radius = 0;

 // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    // Отображение объекта на экране.
    ShowVirtual();
} // Circumference :: ExpandVirtual
//-----------------------------------------------------------

// Уменьшение объекта на величину шага Step.
void Circumference :: Contract(const int  Step,
                               const Boolean HideAndShow)
{ ExpandVirtual(-Step, HideAndShow); }
//-----------------------------------------------------------

// Изменение положения или размеров объекта на экране.
void Circumference :: ChangeViewVirtual(const char DeltaX,
                                        const char DeltaY,
                                        const char Increase,
                                        const char YIncrease,
                                        const int  DeltaAngle,
                                        const int  Step)
{
  // Если нет попытоки увеличить окружность.
  if (DeltaX || DeltaY)
    // Перенос объекта на шаг от первоначального положения
    // в указанном направлении.
    MoveOnStepVirtual(DeltaX, DeltaY, Step);
  else
    if (Increase)
      ExpandVirtual(Increase * Step);
} // Circumference :: ChangeViewVirtual
//-----------------------------------------------------------
//


// Конструктор: установка координат размещения,
// радиуса и невидимости.
Circle :: Circle(const int InitX,
                 const int InitY,
                 const int InitRadius) :

  Circumference(InitX, InitY, InitRadius)
{ }
//-----------------------------------------------------------

// Прорисовка объекта.
void Circle :: DrawVirtual()
  // Отрисовка круга текущим цветом контурных линий.
{ fillellipse(X, Y, Radius, Radius); }
//-----------------------------------------------------------
//


// Конструктор: установка координат размещения,
// радиуcов и невидимости.
Ellipse :: Ellipse(const int InitX,
                   const int InitY,
                   const int InitRadius,
                   const int InitYRadius) :

  Circumference(InitX, InitY, InitRadius)
{ SetYRadius(InitYRadius); }
//-----------------------------------------------------------

// Прорисовка объекта.
void Ellipse :: DrawVirtual()
  // Отрисовка эллипс текущим цветом контурных линий.
{ ellipse(X, Y, 0, 360, Radius, YRadius); }
//-----------------------------------------------------------

// Увеличение объекта на величину шага Step по оси ОУ.
void Ellipse :: YExpandVirtual(const int  Step,
                               const Boolean HideAndShow)
{
  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    // Сокрытие объекта с экрана.
    HideVirtual();

  // Увеличение радиуса
  SetYRadius(YRadius + Step);
  // Если эллипс уменьшен до такой степени,
  // что радиус становится отрицательным -
  // его обнуляют.
  if (YRadius < 0)
    YRadius = 0;

  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    // Отображение объекта на экране.
    ShowVirtual();
} // Ellipse :: YExpandVirtual
//-----------------------------------------------------------

// Уменьшение объекта на величину шага Step по оси ОУ.
void Ellipse :: YContract(const int  Step,
                          const Boolean HideAndShow)
{ YExpandVirtual(-Step, HideAndShow); }
//-----------------------------------------------------------

// Окончательный вариант изменеия
// положения или размеров объекта на экране.
void Ellipse :: ChangeViewVirtual(const char DeltaX,
                                  const char DeltaY,
                                  const char Increase,
                                  const char YIncrease,
                                  const int  DeltaAngle,
                                  const int  Step)
{
  // Если нет попытоки увеличить окружность.
  if (DeltaX || DeltaY)
    // Перенос объекта на шаг от первоначального положения
    // в указанном направлении.
    MoveOnStepVirtual(DeltaX, DeltaY, Step);
  else
  {
    // Увеличение по оси ОХ.
    if (Increase)
      ExpandVirtual(Increase * Step);
    // Увеличение по оси ОУ.
    // if (YIncrease)
    else
      if (YIncrease)
        YExpandVirtual(YIncrease * Step);
  } // else
} // Ellipse :: ChangeViewVirtual
//-----------------------------------------------------------
//


// Конструктор: установка координат размещения,
// радиуcов и невидимости.
FillEllipse :: FillEllipse(const int InitX,
                           const int InitY,
                           const int InitRadius,
                           const int InitYRadius) :

  Ellipse(InitX, InitY, InitRadius, InitYRadius)
{ }
//-----------------------------------------------------------

// Прорисовка объекта.
void FillEllipse :: DrawVirtual()
  // Отрисовка эллипс текущим цветом контурных линий.
{ fillellipse(X, Y, Radius, YRadius); }
//-----------------------------------------------------------
//

#define WHITE 15

// Установка внутреннего радиуса.
void Ring :: SetInnerRadius(const int NewInnerRadius)
{
  // Если внутренний радиус меньше внешнего.
  if (NewInnerRadius <= Radius)
    InnerRadius = NewInnerRadius;
  // Если внутренний радиус больше внешнег,
  // то он приравнивается к внешнему.
  else
    InnerRadius = Radius;
} // Ring :: SetInnerRadius
//-----------------------------------------------------------

// Конструктор: установка координат размещения,
// цвета, радиусов и невидимости.
Ring :: Ring(const int InitX,
             const int InitY,
             const int InitRadius,
             const int InitInnerRadius,
             const unsigned InitInnerColor) :

  Circumference(InitX, InitY, InitRadius)
{
  SetInnerRadius(InitInnerRadius);
  InnerColor = InitInnerColor;
} // Ring :: Ring
//-----------------------------------------------------------

// Прорисовка внешней части объекта.
void Ring :: OuterDrawVirtual()
  //Вызов функции класса-предка.
{ this->Circumference :: DrawVirtual(); }
//-----------------------------------------------------------

// Прорисовка внутренней части объекта.
void Ring :: InnerDrawVirtual()
  // Прорисовка внутреннего радиуса.
{ circle(X, Y, InnerRadius); }
//-----------------------------------------------------------

// Прорисовка объекта, состоящего из двух частей.
void Ring :: DoubleDraw(const unsigned InnerFillColor,
                        const Boolean OuterDeleting)
{
  if (GetVisible())
  {
    // Прорисовка внешней окружности в текущем режиме рисования.
    // Прорисовка внешней части объекта.
    OuterDrawVirtual();

    // Информация о текущем режиме заливки.
    struct fillsettingstype CurrentFillInformation;
    unsigned CurrentColor;  // Текущее значение цвета рисования.

    // Получение информации о текущем режиме рисования.
    GetFillStyleAndColor(CurrentFillInformation, CurrentColor);

    // Информация о режиме заливки внутренней области объекта.
    struct fillsettingstype InnerFillInformation;
    // Палитра эквивалентна текущей.
    InnerFillInformation.pattern = CurrentFillInformation.pattern;
    // Цвет заливки для внутренней области объекта.
    InnerFillInformation.color = InnerFillColor;

    // Установка режима рисования внутренним цветом.
    SetFillStyleAndColor(InnerFillInformation, InnerColor);
    // Прорисовка внутренней части объекта.
    InnerDrawVirtual();

    // Установка первоначального режима рисования.
    SetFillStyleAndColor(CurrentFillInformation, CurrentColor);
  } // if (GetVisible())

  // Прорисовка окружностей цветом фона.
  else
  {
    // Прорисовка внешней части объекта.
    OuterDrawVirtual();
    // Если внутренняя часть объекта не пересрывется внешней,
    // то ее тоже надо стирать.
    if (! OuterDeleting)
      // Прорисовка внутренней части объекта.
      InnerDrawVirtual();
  } // else
} // Ring :: DoubleDraw
//-----------------------------------------------------------

// Прорисовка объекта.
void Ring :: DrawVirtual()
  // Прорисовка объекта, состоящего из двух частей.
{ DoubleDraw(0, false); }
//-----------------------------------------------------------

// Увеличение объекта на величину шага Step.
void Ring :: ExpandVirtual(const int  Step,
                           const Boolean HideAndShow)
{
  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    // Сокрытие объекта с экрана.
    HideVirtual();

  // Увеличение внешнего радиуса.
  SetRadius(Radius + Step);
  // Увеличение внутреннего радиуса.
  SetInnerRadius(InnerRadius + Step);

  // Если окружности уменьшены до такой степени,
  // что радиусы становится отрицательным -
  // их обнуляют.
  if (Radius < 0)
    Radius = 0;
  // Если внутренний радиус становится отрицательным.
  if (InnerRadius < 0)
  {
    // Обнуление внутреннего радиуса.
    InnerRadius = 0;
    // Внешний радиус не должен дальше уменьшаться.
    SetRadius(Radius - Step);
  } // if (InnerRadius < 0)

  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
  // Отображение объекта на экране.
  ShowVirtual();
} // Ring :: ExpandVirtual
//-----------------------------------------------------------
//


// Конструктор: установка координат размещения,
// цветов, радиусов и невидимости.
FillRing :: FillRing(const int InitX,
                     const int InitY,
                     const int InitRadius,
                     const int InitInnerRadius,
                     const unsigned InitInnerColor,
                     const unsigned InitInnerFillColor) :

  Ring(InitX, InitY, InitRadius, InitInnerRadius, InitInnerColor)
{ InnerFillColor = InitInnerFillColor; }
//-----------------------------------------------------------

// Прорисовка внешней части объекта.
void FillRing :: OuterDrawVirtual()
  //Вызов функции класса-предка.
{ fillellipse(X, Y, Radius, Radius); }
//-----------------------------------------------------------

// Прорисовка внутренней части объекта.
void FillRing :: InnerDrawVirtual()
  // Прорисовка внутреннего радиуса.
{ fillellipse(X, Y, InnerRadius, InnerRadius); }
//-----------------------------------------------------------

// Прорисовка объекта.
void FillRing :: DrawVirtual()
  // Прорисовка объекта, состоящего из двух частей.
{ DoubleDraw(InnerFillColor, true); }
//-----------------------------------------------------------
//


// Установка внутреннего радиуса.
void EllipticalRing :: SetInnerYRadius(const int NewInnerYRadius)
{
  // Если внутренний радиус меньше внешнего.
  if (NewInnerYRadius <= YRadius)
    InnerYRadius = NewInnerYRadius;
  // Если внутренний радиус больше внешнег,
  // то он приравнивается к внешнему.
  else
    InnerYRadius = YRadius;
} // Ring :: SetInnerYRadius
//-----------------------------------------------------------

// Конструктор: установка координат размещения,
// цвета, радиусов и невидимости.
EllipticalRing :: EllipticalRing(const int InitX,
                                 const int InitY,
                                 const int InitRadius,
                                 const int InitYRadius,
                                 const int InitInnerRadius,
                                 const int InitInnerYRadius,
                                 const unsigned InitInnerColor) :

  Ring(InitX, InitY, InitRadius, InitInnerRadius, InitInnerColor)
{
  SetYRadius(InitYRadius);
  SetInnerYRadius(InitInnerYRadius);
} // EllipticalRing :: EllipticalRing
//-----------------------------------------------------------

// Прорисовка внешней части объекта.
void EllipticalRing :: OuterDrawVirtual()
{ ellipse(X, Y, 0,360, Radius, YRadius); }
//-----------------------------------------------------------

// Прорисовка внутренней части объекта.
void EllipticalRing :: InnerDrawVirtual()
{ ellipse(X, Y, 0,360, InnerRadius, InnerYRadius); }
//-----------------------------------------------------------

// Прорисовка объекта.
void EllipticalRing :: DrawVirtual()
  // Прорисовка объекта, состоящего из двух частей.
{ DoubleDraw(0, false); }
//-----------------------------------------------------------

// Увеличение объекта на величину шага Step.
void EllipticalRing :: YExpandVirtual(const int  Step,
                                      const Boolean HideAndShow)
{
  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    // Сокрытие объекта с экрана.
    HideVirtual();

  // Увеличение внешнего радиуса.
  SetYRadius(YRadius + Step);
  // Увеличение внутреннего радиуса.
  SetInnerYRadius(InnerYRadius + Step);

  // Если окружности уменьшены до такой степени,
  // что радиусы становится отрицательным -
  // их обнуляют.
  if (YRadius < 0)
    YRadius = 0;
  // Если внутренний радиус становится отрицательным.
  if (InnerYRadius < 0)
  {
    // Обнуление внутреннего радиуса.
    InnerYRadius = 0;
    // Внешний радиус не должен дальше уменьшаться.
    SetYRadius(YRadius - Step);
  } // if (InnerYRadius < 0)

  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    // Отображение объекта на экране.
    ShowVirtual();
} // EllipticalRing :: YExpandVirtual
//-----------------------------------------------------------

// Окончательный вариант изменеия
// положения или размеров объекта на экране.
void EllipticalRing :: ChangeViewVirtual(const char DeltaX,
                                         const char DeltaY,
                                         const char Increase,
                                         const char YIncrease,
                                         const int  DeltaAngle,
                                         const int  Step)
{
  // Если нет попытоки увеличить окружность.
  if (DeltaX || DeltaY)
    // Перенос объекта на шаг от первоначального положения
    // в указанном направлении.
    MoveOnStepVirtual(DeltaX, DeltaY, Step);
  else
  {
    // Увеличение по оси ОХ.
    if (Increase)
      ExpandVirtual(Increase * Step);
    // Увеличение по оси ОУ.
    else
      if (YIncrease) 
        YExpandVirtual(YIncrease * Step);
  } // else
} // EllipticalRing :: ChangeViewVirtual
//-----------------------------------------------------------
//


// Конструктор: установка координат размещения,
// цветов, радиусов и невидимости.
FillEllipticalRing :: FillEllipticalRing(
  const int InitX,
  const int InitY,
  const int InitRadius,
  const int InitYRadius,
  const int InitInnerRadius,
  const int InitInnerYRadius,
  const unsigned InitInnerColor,
  const unsigned InitInnerFillColor) :

    EllipticalRing(InitX, InitY, InitRadius, InitYRadius,
                   InitInnerRadius, InitInnerYRadius, InitInnerColor)
{ InnerFillColor = InitInnerFillColor; }
//-----------------------------------------------------------

// Прорисовка внешней части объекта.
void FillEllipticalRing :: OuterDrawVirtual()
{ fillellipse(X, Y, Radius, YRadius); }
//-----------------------------------------------------------

// Прорисовка внутренней части объекта.
void FillEllipticalRing :: InnerDrawVirtual()
{ fillellipse(X, Y, InnerRadius, InnerYRadius); }
//-----------------------------------------------------------

// Прорисовка объекта.
void FillEllipticalRing :: DrawVirtual()
  // Прорисовка объекта, состоящего из двух частей.
{ DoubleDraw(InnerFillColor, true); }
//-----------------------------------------------------------
//

#define pi 3.1415926

// Установка координат точки
// в зависимости от исходной и угла.
void Leg :: SetXY(const int NewAngle,
                        int &ChangedX,
                        int &ChangedY)
{
  // Установка координаты точки по оси ОХ.
  ChangedX = (int) (X + Radius * cos(NewAngle * pi / 180));
  // Установка координаты точки по оси ОУ.
  ChangedY = (int) (Y - Radius * sin(NewAngle * pi / 180));
} // Leg :: SetXY
//-----------------------------------------------------------

// Установка координат точек
// в зависимости от исходной и угла.
void Leg :: SetXYsVirtual()
{
  // Установка координат точкек
  // в зависимости от исходной и углов.
  X = (int) (X1 - Radius * cos(StartAngle * pi / 180));
  Y = (int) (Y1 + Radius * sin(StartAngle * pi / 180));
  SetXY(Angle, X2, Y2);
} // Leg :: SetXYsVirtual
//----------------------------------------------------------

// Конструктор: установка координат размещения,
// радиуса и невидимости.
Leg :: Leg(const int InitX1,
           const int InitY1,
           const int InitRadius,
           const int InitAngle,
           const int InitStartAngle)
{
  StartAngle = SetAngleToRange(InitStartAngle);
  Angle = SetAngleToRange(InitAngle);
  SetRadius(InitRadius);
  X1 = InitX1;
  Y1 = InitY1;
  // Установка координат точек
  // в зависимости от исходной и угла.
  SetXYsVirtual();
} // Leg :: Leg
//-----------------------------------------------------------

// Прорисовка объекта.
void Leg :: DrawVirtual()
  // Отрисовка галочки текущим цветом контурных линий.
{
  moveto(X1, Y1);
  // Линия до позиции точки центра ноги.
  lineto(X, Y);
  // Линия до позиции конечной точки ноги.
  lineto(X2, Y2);
} // Leg :: DrawVirtual
//-----------------------------------------------------------

// Перенос объекта с одного места на экране на другое.
void Leg :: MoveToVirtual(const int NewX,
                          const int NewY,
                          const Boolean HideAndShow)

{
  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    // Сокрытие объекта с экрана.
    HideVirtual();

  X1 = NewX;
  Y1 = NewY;
  // Установка координат точек
  // в зависимости от исходной и угла.
  SetXYsVirtual();

  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    // Отображение объекта на экране.
    ShowVirtual();
} // Leg :: MoveToVirtual
//-----------------------------------------------------------

// Перенос объекта на шаг от первоначального положения
// в указанном направлении.
void Leg :: MoveOnStepVirtual(const char DeltaX,
                              const char DeltaY,
                              const int  Step,
                              const Boolean HideAndShow)
{
  int CurrentX,  // Текущее значение координаты X.
      CurrentY;  // Текущее значение координаты У.

  // Изменение текущих координат.
  CurrentX = GetX1() + DeltaX * Step;
  CurrentY = GetY1() + DeltaY * Step;
  // Перемещение точки.
  MoveToVirtual(CurrentX, CurrentY, HideAndShow);
} // Leg :: MoveOnStepVirtual
//-----------------------------------------------------------

// Увеличение объекта на величину шага Step.
void Leg :: ExpandVirtual(const int  Step,
                          const Boolean HideAndShow)
{
  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    // Сокрытие объекта с экрана.
    HideVirtual();

  // Увеличение радиуса
  SetRadius(Radius + Step);
  // Если окружности уменьшена до такой степени,
  // что радиус становится отрицательным -
  // его обнуляют.
  if (Radius < 0)
    Radius = 0;

  // в зависимости от исходной и угла.
  SetXYsVirtual();

  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    // Отображение объекта на экране.
    ShowVirtual();
} // Leg :: ExpandVirtual
//-----------------------------------------------------------

// Отклонение объекта на шаг Step.
void Leg :: DeclineVirtual(const int  Step,
                           const Boolean HideAndShow)
{
  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    // Сокрытие объекта с экрана.
    HideVirtual();

  // Преобразование угла к диапазону (-180; 180].
  Angle = SetAngleToRange(Angle + Step);
  // Локоть не должен гнуться в обратную сторону,
  // и кисть может дойти только до плеча.
  if ((Angle == StartAngle) ||
      (SetAngleToRange(Angle + 180) == StartAngle) ||
      (SetAngleToRange(Angle - 180) == StartAngle))
    // Возврат к прежнему значению.
    Angle = SetAngleToRange(Angle - Step);

  else
    // Установка координат точек
    // в зависимости от исходной и угла.
    SetXYsVirtual();

  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    // Отображение объекта на экране.
    ShowVirtual();
} // Leg :: DeclineVirtual
//-----------------------------------------------------------

// Окончательный вариант изменеия
// положения или размеров объекта на экране.
void Leg :: ChangeViewVirtual(const char DeltaX,
                              const char DeltaY,
                              const char Increase,
                              const char YIncrease,
                              const int  DeltaAngle,
                              const int  Step)
{
  // Если нет попытоки увеличить окружность.
  if (DeltaX || DeltaY)
    // Перенос объекта на шаг от первоначального положения
    // в указанном направлении.
    MoveOnStepVirtual(DeltaX, DeltaY, Step);
  else
  {
    // Увеличение по оси ОХ.
    if (Increase)
      ExpandVirtual(Increase * Step);
    // Отклонение объекта на шаг Step.
    else
      if (YIncrease) { }
        else
          if (DeltaAngle)
            DeclineVirtual(DeltaAngle * Step);
  } // else
} // Leg :: ChangeViewVirtual
//-----------------------------------------------------------
//


// Установка координат точек
// в зависимости от исходной и угла.
void Hand :: SetXYsVirtual()
{
  // Установка координат точкек
  // в зависимости от исходной и углов.
  SetXY(StartAngle,             X1, Y1);
  SetXY(StartAngle +     Angle, X2, Y2);
  SetXY(StartAngle + 2 * Angle, X3, Y3);
} // Hand :: SetXYsVirtual
//----------------------------------------------------------

// Конструктор: установка координат размещения,
// радиуса и невидимости.
Hand :: Hand(const int InitX,
             const int InitY,
             const int InitRadius,
             const int InitAngle,
             const int InitStartAngle)
{
  StartAngle = InitStartAngle;
  Angle = InitAngle;
  SetRadius(InitRadius);
  X = InitX;
  Y = InitY;
  // Установка координат точек
  // в зависимости от исходной и углов.
  SetXYsVirtual();
} // Hand :: Hand
//-----------------------------------------------------------

// Прорисовка объекта.
void Hand :: DrawVirtual()
{
  moveto(X1, Y1);
  // Первый палец ноги.
  lineto(X,  Y );
  // Второй палец ноги.
  lineto(X2, Y2);
  moveto(X,  Y );
  // Третий палец ноги.
  lineto(X3, Y3);
} // Hand :: DrawVirtual
//-----------------------------------------------------------

// Перенос объекта с одного места на экране на другое.
void Hand :: MoveToVirtual(const int NewX,
                           const int NewY,
                           const Boolean HideAndShow)

{
  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    // Сокрытие объекта с экрана.
    HideVirtual();

  SetX(NewX);
  SetY(NewY);
  // Установка координат точек
  // в зависимости от исходной и угла.
  SetXYsVirtual();

  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    // Отображение объекта на экране.
    ShowVirtual();
} // Hand :: MoveToVirtual
//-----------------------------------------------------------

// Перенос объекта на шаг от первоначального положения
// в указанном направлении.
void Hand :: MoveOnStepVirtual(const char DeltaX,
                               const char DeltaY,
                               const int  Step,
                               const Boolean HideAndShow)
{ this->Hand :: MoveOnStepVirtual(DeltaX, DeltaY, Step, HideAndShow); }
//-----------------------------------------------------------

// Отклонение объекта на шаг Step.
void Hand :: DeclineVirtual(const int  Step,
                            const Boolean HideAndShow)
{
  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    // Сокрытие объекта с экрана.
    HideVirtual();

  // Преобразование угла к диапазону (-180; 180].
  Angle += Step;
  // Локоть не должен гнуться в обратную сторону,
  // и кисть может дойти только до плеча.
  if ((abs(Angle) < abs(2 * Step)) ||
      (abs(2 * Angle) > 100))
    // Возврат к прежнему значению.
    Angle = SetAngleToRange(Angle - Step);
  else
  {
    SetAngleToRange(Angle);
    // Установка координат точек
    // в зависимости от исходной и угла.
    SetXYsVirtual();
  } // else

  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    // Отображение объекта на экране.
    ShowVirtual();
} // Hand :: DeclineVirtual
//-----------------------------------------------------------
//


// Установка радиуса подушечки пальцев.
void FingersHand :: SetFingerRadius(const int NewFingerRadius)
{
  if (NewFingerRadius <= Radius)
    FingerRadius = NewFingerRadius;
  else
    FingerRadius = 1;
} // FingersHand :: SetFingerRadius
//-----------------------------------------------------------

// Конструктор: установка координат размещения,
// радиуса и невидимости.
FingersHand :: FingersHand(const int InitX,
                           const int InitY,
                           const int InitRadius,
                           const int InitFingerRadius,
                           const int InitAngle,
                           const int InitStartAngle) :

  Hand(InitX, InitY, InitRadius, InitAngle, InitStartAngle)
  // Установка радиуса подушечки пальцев.
{ SetFingerRadius(InitFingerRadius); }
//-----------------------------------------------------------

// Прорисовка объекта.
void FingersHand :: DrawVirtual()
{
  // Вызов функции родительского класса.
  this->Hand :: DrawVirtual();
  // Подушечки пальцев.
  fillellipse(X1, Y1, FingerRadius, FingerRadius);
  fillellipse(X2, Y2, FingerRadius, FingerRadius);
  fillellipse(X3, Y3, FingerRadius, FingerRadius);
} // FingersHand :: DrawVirtual
//-----------------------------------------------------------
//


// Конструктор: установка координат размещения,
// радиуса и невидимости.
FrogPaw :: FrogPaw(const int InitX1,
                   const int InitY1,
                   const int InitRadius,
                   const int InitAngle,
                   const int InitStartAngle,
                   const int InitLegThickness,

                   const int InitHandRadius,
                   const int InitFingerRadius,
                   const int InitHandAngle,
                   const int InitHandStartAngle) :

  Leg(InitX1, InitY1, InitRadius, InitAngle, InitStartAngle)
{
  SetLegThickness(InitLegThickness);
  // Конструктор кисти.
  FrogHand = FingersHand(X2, Y2, InitHandRadius, InitFingerRadius,
                         InitHandAngle, InitHandStartAngle);
} // FrogPaw :: FrogPaw
//-----------------------------------------------------------

// Прорисовка объекта.
void FrogPaw :: DrawVirtual()
  // Отрисовка галочки текущим цветом контурных линий.
{
  // Информация о текущем стиле линий.
  struct linesettingstype CurrentLineInformation;
  getlinesettings(&CurrentLineInformation);

  // Новый стиль линии с измененной толщиной.
  struct linesettingstype LineInformation;
  LineInformation = CurrentLineInformation;
  LineInformation.thickness = LegThickness;

  // Установка новой толщины ноги.
  setlinestyle(LineInformation.linestyle,
               LineInformation.upattern,
               LineInformation.thickness);
  // Вызов функции предка.
  this->Leg :: DrawVirtual();

  // Установка прежней толщины ноги.
  setlinestyle(CurrentLineInformation.linestyle,
               CurrentLineInformation.upattern,
               CurrentLineInformation.thickness);
  // Отрисовка кисти.
  FrogHand.DrawVirtual();
} // FrogPaw :: DrawVirtual
//-----------------------------------------------------------

// Отображение объекта на экране.
void FrogPaw :: ShowVirtual()
{
  FrogHand.SetVisible(true);
  // Вызов функции предка.
  this->Leg :: ShowVirtual();
} // FrogPaw :: ShowVirtual
//-----------------------------------------------------------

// Сокрытие объекта с экрана.
void FrogPaw :: HideVirtual()
{
  FrogHand.SetVisible(false);
  // Вызов функции предка.
  this->Leg :: HideVirtual();
} // FrogPaw :: HideVirtual
//-----------------------------------------------------------

// Перенос объекта с одного места на экране на другое.
void FrogPaw :: MoveToVirtual(const int NewX,
                              const int NewY,
                              const Boolean HideAndShow)

{
  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    HideVirtual();

  // Вызов функции предка.
  this->Leg :: MoveToVirtual(NewX, NewY, false);
  // Перемещение кисти.
  FrogHand.MoveToVirtual(X2, Y2, false);

  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    ShowVirtual();
} // FrogPaw :: MoveToVirtual
//-----------------------------------------------------------

// Увеличение объекта на величину шага Step.
void FrogPaw :: ExpandVirtual(const int  Step,
                              const Boolean HideAndShow)
{
  this->Leg::ExpandVirtual(Step, HideAndShow);
  FrogHand.MoveToVirtual(X2, Y2, false);
  // Увеличение кисти.
  FrogHand.ExpandVirtual(Step, HideAndShow);
} // FrogPaw :: ExpandVirtual
//-----------------------------------------------------------

// Отклонение объекта на шаг Step.
void FrogPaw :: DeclineVirtual(const int  Step,
                               const Boolean HideAndShow)
{
  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    HideVirtual();

  // Вызов функции предка.
  this->Leg :: DeclineVirtual(Step, false);
  FrogHand.DeclineVirtual((int) float(Step / 2.5), false);
  // Перемещение кисти.
  FrogHand.MoveToVirtual(X2, Y2, false);

  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    ShowVirtual();
} // FrogPaw :: DeclineVirtual
//-----------------------------------------------------------
//

// Конструктор: установка координат размещения,
// радиуcов и невидимости.
FrogHad :: FrogHad(const int InitX,
                   const int InitY,
                         int InitRadius,
                         int InitYRadius,

                   const unsigned InitMouthColor,
                   const unsigned InitMouthFillColor,
                   const int      InitEyeRadius,
                   const unsigned InitEyeFillColor,
                   const unsigned InitEyeInnerColor,
                   const unsigned InitEyeInnerFillColor)
{
  // Если радиус головы по оси ОХ меньше шести радиусов глаза.
  if (InitRadius < 6 * InitEyeRadius)
    InitRadius = 6 * InitEyeRadius;
  // Если радиус головы по оси ОУ меньше радиуса глаза.
  if (InitYRadius < InitEyeRadius)
    InitYRadius = InitEyeRadius;

  // Конструктор родительского класса -
  // для формы и размещения головы.
  FillEllipse FrogFace(InitX, InitY, InitRadius, InitYRadius);
  this->Visible = FrogFace.GetVisible();
  this->X = FrogFace.GetX();
  this->Y = FrogFace.GetY();
  this->Radius = FrogFace.GetRadius();
  this->YRadius = FrogFace.GetYRadius();

  // Радиус глаза.
  EyeRadius = InitEyeRadius;

  // Контсрукторы глаз.
  // Расстояние между глазами - два диаметра глаза,
  // значит, межцентровое расстояние - шесть радиусов глаза.
  RightEye = FillRing(X + 3 * EyeRadius, Y - YRadius,
                      EyeRadius,         (int) floor(EyeRadius / 2),
                      InitEyeInnerColor, InitEyeInnerFillColor);
  LeftEye =  FillRing(X - 3 * EyeRadius, RightEye.GetY(),
                      EyeRadius,         RightEye.GetInnerRadius(),
                      InitEyeInnerColor, InitEyeInnerFillColor);
  // Цвет белка глаза.
  EyeFillColor = InitEyeFillColor;

  // Конструктор рта.
  // Кончики губ - на уровне центров зрачков.
  Mouth = FillEllipse(X, (int) floor(Y + YRadius / 2),
                      3 * EyeRadius, (int) floor(Radius / 8));

  // Цвета губ и полости рта.
  MouthColor = InitMouthColor;
  MouthFillColor = InitMouthFillColor;

  // Конструкторы ноздрей.
  // Ноздри находятся посередине головы
  // на расстоянии диаметра глаза.
  RightNostril = Circumference(X + EyeRadius, Y, (int) floor(EyeRadius / 4));
  LeftNostril  = Circumference(X - EyeRadius, Y, RightNostril.GetRadius());
} // FrogHad :: FrogHad
//-----------------------------------------------------------

// Прорисовка объекта.
void FrogHad :: DrawVirtual()
{
  this->FillEllipse :: DrawVirtual();

  //Параметры текущих заливки и цвета.
  struct fillsettingstype CurrentFillInformation;
  unsigned CurrentColor;
  // Параметры новой заливки.
  struct fillsettingstype FillInformation;

  // Если голову стирают, то ноздри и рот стирать не надо,
  // так как они находятся на залитом лице,
  // которое при стирании также стирает и их.
  if (GetVisible())
  {
    RightNostril.DrawVirtual();
    LeftNostril.DrawVirtual();

    // Получение информации о текущем режиме рисования.
    GetFillStyleAndColor(CurrentFillInformation, CurrentColor);

    // Режим для глаза.
    FillInformation = CurrentFillInformation;
    FillInformation.color = EyeFillColor;
    // Установка режима рисования.
    SetFillStyleAndColor(FillInformation, getcolor());
  } // if (GetVisible())

  // Прорисовка глаз.
  RightEye.DrawVirtual();
  LeftEye.DrawVirtual();

  if (GetVisible())
  {
    // Режим рисования рта.
    FillInformation.color = MouthFillColor;
    // Установка режима рисования.
    SetFillStyleAndColor(FillInformation, MouthColor);
    // Прорисовка рта.
    Mouth.DrawVirtual();
    // Установка прежнего режима рисования.
    SetFillStyleAndColor(CurrentFillInformation, CurrentColor);
  } // if (GetVisible())
} // FrogHad :: DrawVirtual()
//-----------------------------------------------------------

// Назначение одновременной видимости/невидимости
// всем объектм, входящим в состав данного класса.
void FrogHad :: SetSubObjectsVisibleVirtual(const Boolean SubObjectsVisible)
{
  this->SetVisible(SubObjectsVisible);
  // Правая ноздря.
  RightNostril.SetVisible(SubObjectsVisible);
  // Левая ноздря.
  LeftNostril.SetVisible(SubObjectsVisible);
  // Правый глаз.
  RightEye.SetVisible(SubObjectsVisible);
  // Левый глаз.
  LeftEye.SetVisible(SubObjectsVisible);
  // Рот.
  Mouth.SetVisible(SubObjectsVisible);
} // FrogHad :: SetSubObjectsVisibleVirtual
//-----------------------------------------------------------

// Отображение объекта на экране.
void FrogHad :: ShowVirtual()
{
  // Назначение одновременной видимости/невидимости
  // всем объектм, входящим в состав данного класса.
  SetSubObjectsVisibleVirtual(true);
  // Прорисовка объекта.
  DrawVirtual();
} // FrogHad :: ShowVirtual
//-----------------------------------------------------------

// Сокрытие объекта с экрана.
void FrogHad :: HideVirtual()
{
  // Назначение одновременной видимости/невидимости
  // всем объектм, входящим в состав данного класса.
  SetSubObjectsVisibleVirtual(false);

  // Информация о текущем режиме заливки.
  struct fillsettingstype CurrentFillInformation;
  unsigned CurrentColor;  // Текущее значение цвета рисования.

  // Получение информации о текущем режиме рисования.
  GetFillStyleAndColor(CurrentFillInformation, CurrentColor);
  // Установка цвета контура и заливки в цвет экрана,
  // а стиля заливки - в сплошной.
  SetBackgroundFillStyleAndColor();

  // Прорисовка объекта.
  DrawVirtual();

  // Установка режима рисования.
  SetFillStyleAndColor(CurrentFillInformation, CurrentColor);
} // FrogHad :: HideVirtual
//-----------------------------------------------------------

// Перенос объекта с одного места на экране на другое.
void FrogHad :: MoveToVirtual(const int NewX,
                              const int NewY,
                              const Boolean HideAndShow)

{
  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    HideVirtual();

  // Вызов функции предка.
  this->FillEllipse :: MoveToVirtual(NewX, NewY, false);

  // Правый глаз.
  RightEye.MoveToVirtual(X + 3 * EyeRadius, Y - YRadius, false);
  // Левый глаз.
  LeftEye.MoveToVirtual(X - 3 * EyeRadius, RightEye.GetY(), false);

  // Рот.
  Mouth.MoveToVirtual(X, (int) floor(Y + YRadius / 2), false);

  // Правая ноздря.
  RightNostril.MoveToVirtual(X + EyeRadius, Y, false);
  // Левая ноздря.
  LeftNostril.MoveToVirtual(X - EyeRadius, Y, false);

  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    ShowVirtual();
} // FrogHad :: MoveToVirtual
//-----------------------------------------------------------

// Увеличение объекта на величину шага Step.
void FrogHad :: ExpandVirtual(const int  Step,
                              const Boolean HideAndShow)
{
  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    // Сокрытие объекта с экрана.
    HideVirtual();

  // Увеличение радиуса
  SetRadius(Radius + Step);
  // Если окружности уменьшена до такой степени,
  // что радиус становится отрицательным -
  // его обнуляют.
  if (Radius < 0)
    Radius = 0;

  // Увеличение радиуса рта.
  Mouth.SetRadius(Mouth.GetRadius() + Step);
  // Если окружности уменьшена до такой степени,
  // что радиус становится отрицательным -
  // его обнуляют.
  if (Mouth.GetRadius() < 0)
  {
    Mouth.SetRadius(0);
    // Дальше лицо уменьшать нельзя.
    SetRadius(Radius - Step);
  } // if (Mouth.GetRadius() < 0)

  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    // Отображение объекта на экране.
    ShowVirtual();
} // FrogHad :: ExpandVirtual
//-----------------------------------------------------------

// Увеличение объекта на величину шага Step по оси ОУ.
void FrogHad :: YExpandVirtual(const int  Step,
                               const Boolean HideAndShow)
{
  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    // Сокрытие объекта с экрана.
    HideVirtual();

  // Увеличение радиуса
  SetYRadius(YRadius + Step);
  // Если эллипс уменьшен до такой степени,
  // что радиус становится отрицательным -
  // его обнуляют.
  if (YRadius < 0)
    YRadius = 0;

  // Увеличение радиуса рта.
  Mouth.SetYRadius((int) floor(Mouth.GetYRadius() + Step / 2));
  // Если окружности уменьшена до такой степени,
  // что радиус становится отрицательным -
  // его обнуляют.
  if (Mouth.GetYRadius() < 0)
  {
    Mouth.SetYRadius(0);
    // Увеличение внешнего радиуса.
    SetYRadius(YRadius - Step);
  } // if (Mouth.GetYRadius() < 0)

  // Рот.
  Mouth.MoveToVirtual(X, (int) floor(Y + YRadius / 2), false);
  // Правый глаз.
  RightEye.MoveToVirtual(X + 3 * EyeRadius, Y - YRadius, false);
  // Левый глаз.
  LeftEye.MoveToVirtual(X - 3 * EyeRadius, RightEye.GetY(), false);

  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    // Отображение объекта на экране.
    ShowVirtual();
} // FrogHad :: YExpandVirtual
//-----------------------------------------------------------
//


// Конструктор: установка координат размещения,
// радиуса и невидимости.
FrogPawsPair:: FrogPawsPair(const int InitX,
                            const int InitY,
                            const int InitRadius,

                            const int InitPawRadius,
                            const int InitPawAngle,
                            const int InitStartPawAngle,
                            const int InitLegThickness,

                            const int InitHandRadius,
                            const int InitFingerRadius,
                            const int InitHandAngle,
                            const int InitHandStartAngle) :

  Circumference(InitX, InitY, InitRadius)
{
  // Конструктор:
  RightPaw = FrogPaw(X + Radius,  Y, InitPawRadius,
                     InitPawAngle,   InitStartPawAngle,
                     InitLegThickness,
                     InitHandRadius, InitFingerRadius,
                     InitHandAngle,  InitHandStartAngle);
  // Конструктор:
  LeftPaw =  FrogPaw( X - Radius,      Y, InitPawRadius,
                      180 - InitPawAngle, 180 - InitStartPawAngle,
                      InitLegThickness,
                      InitHandRadius,     InitFingerRadius,
                     -InitHandAngle,      180 - InitHandStartAngle);
} // FrogPawsPair:: FrogPawsPair
//-----------------------------------------------------------

// Прорисовка объекта.
void FrogPawsPair :: DrawVirtual()
{
  RightPaw.DrawVirtual();
  LeftPaw.DrawVirtual();
} // FrogPawsPair :: DrawVirtual
//-----------------------------------------------------------

// Отображение объекта на экране.
void FrogPawsPair :: ShowVirtual()
{
  RightPaw.ShowVirtual();
  LeftPaw.ShowVirtual();
} // FrogPawsPair :: ShowVirtual
//-----------------------------------------------------------

// Сокрытие объекта с экрана.
void FrogPawsPair :: HideVirtual()
{
  RightPaw.HideVirtual();
  LeftPaw.HideVirtual();
} // FrogPawsPair :: HideVirtual
//-----------------------------------------------------------

// Перенос объекта с одного места на экране на другое.
void FrogPawsPair :: MoveToVirtual(const int NewX,
                                   const int NewY,
                                   const Boolean HideAndShow)

{
  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    HideVirtual();

  // Вызов функции предка.
  this->Circumference :: MoveToVirtual(NewX, NewY, false);

  RightPaw.MoveToVirtual(X + Radius, Y, false);
  LeftPaw.MoveToVirtual(X - Radius, Y, false);

  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    ShowVirtual();
} // FrogPawsPair :: MoveToVirtual
//-----------------------------------------------------------

// Увеличение объекта на величину шага Step.
void FrogPawsPair :: ExpandVirtual(const int  Step,
                                   const Boolean HideAndShow)
{
  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    // Сокрытие объекта с экрана.
    HideVirtual();

  RightPaw.ExpandVirtual(Step, false);
  LeftPaw.ExpandVirtual(Step, false);

  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    // Отображение объекта на экране.
    ShowVirtual();
} // FrogPawsPair :: ExpandVirtual
//-----------------------------------------------------------

// Отклонение объекта на шаг Step.
void FrogPawsPair :: DeclineVirtual(const int  Step,
                                    const Boolean HideAndShow)
{
  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    // Сокрытие объекта с экрана.
    HideVirtual();

  RightPaw.DeclineVirtual(Step, false);
  LeftPaw.DeclineVirtual(-Step, false);

  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    // Отображение объекта на экране.
    ShowVirtual();
} // FrogPawsPair :: DeclineVirtual
//-----------------------------------------------------------

// Изменение положения или размеров объекта на экране.
void FrogPawsPair :: ChangeViewVirtual(const char DeltaX,
                                       const char DeltaY,
                                       const char Increase,
                                       const char YIncrease,
                                       const int  DeltaAngle,
                                       const int  Step)
{
  // Если нет попытоки увеличить окружность.
  if (DeltaX || DeltaY)
    // Перенос объекта на шаг от первоначального положения
    // в указанном направлении.
    MoveOnStepVirtual(DeltaX, DeltaY, Step);
  else
  {
    // Увеличение по оси ОХ.
    if (Increase)
      ExpandVirtual(Increase * Step);
    // Отклонение объекта на шаг Step.
    else
      if (YIncrease) { }
        else
          if (DeltaAngle)
            DeclineVirtual(DeltaAngle * Step);
  } // else
} // FrogPawsPair :: ChangeViewVirtual
//-----------------------------------------------------------
//


// Конструктор: установка координат размещения,
// радиуcов и невидимости.
Frog :: Frog(const int InitX,
             const int InitY,
             const int InitRadius,
             const int InitYRadius,
             const int InitInnerRadius,
             const int InitInnerYRadius,
             const unsigned InitInnerColor,
             const unsigned InitInnerFillColor,



                   int InitHadRadius,
                   int InitHadYRadius,

             const unsigned InitMouthColor,
             const unsigned InitMouthFillColor,
             const int      InitEyeRadius,
             const unsigned InitEyeFillColor,
             const unsigned InitEyeInnerColor,
             const unsigned InitEyeInnerFillColor,



             const int InitLegThickness,

             const int InitUpperPawRadius,
             const int InitUpperPawAngle,
             const int InitStartUpperPawAngle,

             const int InitUpperHandRadius,
             const int InitUpperFingerRadius,
             const int InitUpperHandAngle,
             const int InitUpperHandStartAngle,


             const int InitLowerPawRadius,
             const int InitLowerPawAngle,
             const int InitStartLowerPawAngle,

             const int InitLowerHandRadius,
             const int InitLowerFingerRadius,
             const int InitLowerHandAngle,
             const int InitLowerHandStartAngle) :

  FillEllipticalRing(InitX, InitY, InitRadius, InitYRadius,
                     InitInnerRadius, InitInnerYRadius,
                     InitInnerColor,  InitInnerFillColor)
{
  // Конструктор:
  Had = FrogHad(X,                 Y - YRadius,
                InitHadRadius,     InitHadYRadius,
                InitMouthColor,    InitMouthFillColor,
                InitEyeRadius,     InitEyeFillColor,
                InitEyeInnerColor, InitEyeInnerFillColor);

  // Конструктор:
  UpperPawsPair = FrogPawsPair(
    X,                      Y - YRadius + Had.GetYRadius(),
    2 * Had.GetEyeRadius(), InitUpperPawRadius,
    InitUpperPawAngle,      InitStartUpperPawAngle,
    InitLegThickness,
    InitUpperHandRadius,    InitUpperFingerRadius,
    InitUpperHandAngle,     InitUpperHandStartAngle);

  // Конструктор:
  LowerPawsPair = FrogPawsPair(
    X,                      Y + YRadius - 3,
    0,                      InitLowerPawRadius,
    InitLowerPawAngle,      InitStartLowerPawAngle,
    InitLegThickness,
    InitLowerHandRadius,    InitLowerFingerRadius,
    InitLowerHandAngle,     InitLowerHandStartAngle);
} // Frog :: Frog
//-----------------------------------------------------------

// Прорисовка объекта.
void Frog :: DrawVirtual()
{
  UpperPawsPair.DrawVirtual();
  LowerPawsPair.DrawVirtual();
  // Вызов функции предка.
  this->FillEllipticalRing :: DrawVirtual();
  Had.DrawVirtual();
} // Frog :: DrawVirtual
//-----------------------------------------------------------

// Отображение объекта на экране.
void Frog :: ShowVirtual()
{
  LowerPawsPair.ShowVirtual();
  // Вызов функции предка.
  this->FillEllipticalRing :: ShowVirtual();
  Had.ShowVirtual();
  UpperPawsPair.ShowVirtual();
} // Frog :: ShowVirtual
//-----------------------------------------------------------

// Сокрытие объекта с экрана.
void Frog :: HideVirtual()
{
  LowerPawsPair.HideVirtual();
  // Вызов функции предка.
  this->FillEllipticalRing :: HideVirtual();
  Had.HideVirtual();
  UpperPawsPair.HideVirtual();
} // Frog :: HideVirtual
//-----------------------------------------------------------

// Перенос объекта с одного места на экране на другое.
void Frog :: MoveToVirtual(const int NewX,
                           const int NewY,
                           const Boolean HideAndShow)

{
  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    HideVirtual();

  // Вызов функции предка.
  this->FillEllipticalRing :: MoveToVirtual(NewX, NewY, false);

  UpperPawsPair.MoveToVirtual(X, Y - YRadius + Had.GetYRadius(),   false);
  LowerPawsPair.MoveToVirtual(X, Y + YRadius - 3,                  false);
  Had.MoveToVirtual(X, Y - YRadius, false);

  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    ShowVirtual();
} // Frog :: MoveToVirtual
//-----------------------------------------------------------

// Увеличение объекта на величину шага Step.
void Frog :: ExpandVirtual(const int  Step,
                           const Boolean HideAndShow)
{
  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    // Сокрытие объекта с экрана.
    HideVirtual();

  // Вызов функции предка.
  this->FillEllipticalRing :: ExpandVirtual(Step, false);

  UpperPawsPair.ExpandVirtual(Step, false);
  LowerPawsPair.ExpandVirtual(Step, false);
  Had.ExpandVirtual(Step, false);

  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    // Отображение объекта на экране.
    ShowVirtual();
} // Frog :: ExpandVirtual
//-----------------------------------------------------------

// Увеличение объекта на величину шага Step.
void Frog :: YExpandVirtual(const int  Step,
                            const Boolean HideAndShow)
{
  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    // Сокрытие объекта с экрана.
    HideVirtual();

  // Если радиус брюшка не станет отрицательным
  // с последующим обнулением,
  // тельце и олова растут, нижние ноги - на месте,
  // а центры тельца, головы и верхних лапок перемещаются.
  if ((GetInnerYRadius() + Step) >= 0)
  {
    this->FillEllipticalRing :: MoveToVirtual(X, Y - Step, false);
    Had.MoveToVirtual(X, Y - YRadius, false);
    UpperPawsPair.MoveToVirtual(X, Y - YRadius + Had.GetYRadius(), false);
  } // if (this->GetYRadius() > Step)

  // Вызов функции предка.
  this->FillEllipticalRing :: YExpandVirtual(Step, false);
  Had.YExpandVirtual(Step, false);

  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    // Отображение объекта на экране.
    ShowVirtual();
} // Frog :: YExpandVirtual
//-----------------------------------------------------------

// Отклонение объекта на шаг Step.
void Frog :: DeclineVirtual(const int  Step,
                            const Boolean HideAndShow)
{
  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
    // Сокрытие объекта с экрана.
    HideVirtual();

  UpperPawsPair.DeclineVirtual(Step, false);
  LowerPawsPair.DeclineVirtual(Step, false);

  // Если надо скрыть объект перед перемещением и проявить после.
  if (HideAndShow)
     // Отображение объекта на экране.
     ShowVirtual();
} // Frog :: DeclineVirtual
//-----------------------------------------------------------

// Изменение положения или размеров объекта на экране.
void Frog :: ChangeViewVirtual(const char DeltaX,
                               const char DeltaY,
                               const char Increase,
                               const char YIncrease,
                               const int  DeltaAngle,
                               const int  Step)
{
  // Если нет попытоки увеличить окружность.
  if (DeltaX || DeltaY)
    // Перенос объекта на шаг от первоначального положения
    // в указанном направлении.
    MoveOnStepVirtual(DeltaX, DeltaY, Step);
  else
  {
    // Увеличение по оси ОХ.
    if (Increase)
      ExpandVirtual(Increase * Step);
    else
      // Увеличение по оси ОY.
      if (YIncrease)
        YExpandVirtual(YIncrease * Step);
      else
        // Отклонение объекта на шаг Step.
        if (DeltaAngle)
          DeclineVirtual(DeltaAngle * Step);
  } // else
} // Frog :: ChangeViewVirtual
//-----------------------------------------------------------
//


void main()
{
  // заголовок программы.
  printf("\n                      F r o m   P o i n t   t o   F r o g\n\n");
  printf("\n");
  printf("            Демонстрация наслевования классов от точки до лягушки\n\n");
  printf("╔═══════════════════════════════╤═════════════════════════════════════════╗\n");
  printf("║   Русское названия класса     │  Название класса   │    Класс-предок    ║\n");
  printf("╠═══════════════════════════════╪════════════════════╪════════════════════╣\n");
  printf("║ Размещение                    │ Location           │ -                  ║\n");
  printf("║ Точка                         │ Point              │ Location           ║\n");
  printf("║ Окружность                    │ Circumference      │ Point              ║\n");
  printf("║ Круг                          │ Circle             │ Circumference      ║\n");
  printf("║ Эллипс                        │ Ellipse            │ Circumference      ║\n");
  printf("║ Залитый эллипс                │ FillEllipse        │ Ellipse            ║\n");
  printf("║ Крпуглое кольо                │ Ring               │ Circumference      ║\n");
  printf("║ Залитое круглок кольцо        │ FillRing           │ Ring               ║\n");
  printf("║ Эллиптическое кольцо          │ EllipticalRing     │ Ring               ║\n");
  printf("║ Залитое эллиптическое кольцо  │ FillEllipticalRing │ EllipticalRing     ║\n");
  printf("║ Нога                          │ Leg                │ Circumference      ║\n");
  printf("║ Трехпалая кисть               │ Hand               │ Leg                ║\n");
  printf("║ Трехпалая кисть с подушечками │ FingersHand        │ Hand               ║\n");
  printf("║ Лягушачья лапка               │ FrogPaw            │ Leg                ║\n");
  printf("║ Лягушачья голова              │ FrogHad            │ FillEllipse        ║\n");
  printf("║ Пара лягушачьих лап           │ FrogPawsPair       │ Circumference      ║\n");
  printf("╟───────────────────────────────┼────────────────────┼────────────────────╢\n");
  printf("║ ЛЯГУШКА                       │ Frog               │ FillEllipticalRing ║\n");
  printf("╚═══════════════════════════════╧════════════════════╧════════════════════╝\n\n");
  printf("Нажмите любую клавишу!");
  getch(); getch();

  printf("\n\n У п р а в л е н и е   о б ъ е к т р а м и\n");
  printf(" ─────────────────────────────────────────\n\n");
  printf(" <Стрелка вверх>  - перемещение вверх.\n");
  printf(" <Стрелка вниз>   - перемещение вниз.\n");
  printf(" <Стрелка влево>  - перемещение влево.\n");
  printf(" <Стрелка вправо> - перемещение враво.\n");
  printf(" <Е>              - увеличение объекта.\n");
  printf(" <С>              - уменьшение объекта.\n");
  printf(" <R>              - увеличение объекта.\n");
  printf(" <V>              - уменьшение объекта.\n");
  printf(" <A>              - увеличение угла объекта.\n");
  printf(" <Z>              - уменьшение угла объекта.\n");
  printf(" <Enter>          - конец демонстрации объекта.\n\n");
  printf("Нажмите любую клавишу!\n");
  getch(); getch();

  // Запрос автоматического определения графического рижима.
  int graphdriver = DETECT, graphmode, errorcode;
  // Инициализация графических переменных.
  initgraph(&graphdriver, &graphmode, "bgi");

  // Чтение результатов инициализации.
  errorcode = graphresult();
  // В случае ошибки.
  if (errorcode != grOk)
  {
     printf("Graphics error: %s\n", grapherrormsg(errorcode));
     printf("Press any key to halt:");
     getch();
     // Завершение с кодом ошибки.
     exit(1);
  } // if (errorcode != grOk)

  // Выравнивание текста по середине экрана.
  settextjustify(CENTER_TEXT, CENTER_TEXT);
  // Готический шрифт.
  settextstyle(GOTHIC_FONT, HORIZ_DIR, 7);
  setcolor(RED);

  // Кооридинаты центра экрана.
  int CenterX = (int) floor(getmaxx() / 2);
  int CenterY = (int) floor(getmaxy() / 2);

  // Строка текстового вывода.
  char *textstring = "The Frog";

  // Вывод заголовка.
  outtextxy(CenterX, CenterY, textstring);
  getch();
  setcolor(getbkcolor());
  outtextxy(CenterX, CenterY, textstring);

  // Стиль заливки.
  struct fillsettingstype CurrentFillInformation;
  CurrentFillInformation.pattern = SOLID_FILL;
  CurrentFillInformation.color = LIGHTGREEN;
  // Установка режима рисования.
  SetFillStyleAndColor(CurrentFillInformation, GREEN);

  // Cтиль линии.
  struct linesettingstype CurrentLineInformation;
  CurrentLineInformation.linestyle = SOLID_LINE;
  CurrentLineInformation.upattern = 1;
  CurrentLineInformation.thickness = 1;
  // Установка режима рисования.
  setlinestyle(CurrentLineInformation.linestyle,
               CurrentLineInformation.upattern,
               CurrentLineInformation.thickness);

  // Класс Точка.
  Point *PointArray[16];

  // Класс Точка.
  PointArray[0] = new Point(CenterX,    // const int InitX
                            CenterY);   // const int InitY
  // Класс Окружность.
  PointArray[1] = new Circumference(CenterX,   // const int InitX
                                    CenterY,   // const int InitY
                                     50);      // const int InitRadius
  // Класс Круг.
  PointArray[2] = new Circle(CenterX,   // const int InitX
                             CenterY,   // const int InitY
                             50);      // const int InitRadius
  // Класс Эллипс.
  PointArray[3] = new Ellipse(CenterX,   // const int InitX
                              CenterY,   // const int InitY
                              100,       // const int InitRadius
                               50);      // const int InitYRadius
  // Класс Залитый эллипс.
  PointArray[4] = new FillEllipse(CenterX,   // const int InitX
                                  CenterY,   // const int InitY
                                  100,       // const int InitRadius
                                   50);      // const int InitYRadius
  // Класс Круглое кольцо.
  PointArray[5] = new Ring(CenterX,      // const int InitX
                           CenterY,      // const int InitY
                           100,          // const int InitRadius
                            50,          // const int InitInnerRadius
                           LIGHTCYAN);   // const unsigned InitInnerColor
  // Класс Залитое круглое кольцо.
  PointArray[6] = new FillRing(CenterX,      // const int InitX
                               CenterY,      // const int InitY
                               100,          // const int InitRadius
                                50,          // const int InitInnerRadius
                               LIGHTCYAN,    // const unsigned InitInnerColor
                               LIGHTBLUE);   // const unsigned InitInnerFillColor
  // Класс Эллиптическое кольцо.
  PointArray[7] = new EllipticalRing(CenterX,      // const int InitX
                                     CenterY,      // const int InitY
                                     120,          // const int InitRadius
                                      60,          // const int InitYRadius
                                      75,          // const int InitInnerRadius
                                      40,          // const int InitInnerYRadius
                                     LIGHTCYAN);   // const unsigned InitInnerColor
  // Класс Залитое эллиптическое кольцо.
  PointArray[8] = new FillEllipticalRing(CenterX,      // const int InitX
                                         CenterY,      // const int InitY
                                         120,          // const int InitRadius
                                          60,          // const int InitYRadius
                                          75,          // const int InitInnerRadius
                                          40,          // const int InitInnerYRadius
                                         LIGHTCYAN,    // const unsigned InitInnerColor
                                         LIGHTBLUE);   // const unsigned InitInnerFillColor
  // Класс Нога.
  PointArray[9] = new Leg(CenterX,   // const int InitX1
                          CenterY,   // const int InitY1
                          100,       // const int InitRadius
                          240,       // const int InitAngle
                          200);      // const int InitStartAngle
  // Класс Кисть (трехпалая) ноги.
  PointArray[10] = new Hand(CenterX,   // const int InitX1
                            CenterY,   // const int InitY1
                            100,       // const int InitRadius
                            -30,       // const int InitAngle
                             40);      // const int InitStartAngle
  // Класс Кисть (трехпалая) ноги
  // с расплющенными подушечками на пальцах.
  PointArray[11] = new FingersHand(CenterX,   // const int InitX1
                                   CenterY,   // const int InitY1
                                   100,       // const int InitRadius
                                     3,       // const int InitFingerRadius
                                    30,       // const int InitAngle
                                    40);      // const int InitStartAngle
  // Класс Лягушачья лапа.
  PointArray[12] = new FrogPaw(CenterX,   // const int InitX
                               CenterY,   // const int InitY
                               100,       // const int InitRadius
                               240,       // const int InitAngle
                               200,       // const int InitStartAngle
                                 3,       // const int InitLegThickness

                                55,       // const int InitHandRadius
                                 3,       // const int InitFingerRadius
                                25,       // const int InitHandAngle
                               332);      // const int InitHandStartAngle
  // Класс Лягушачья голова.
  PointArray[13] = new FrogHad(CenterX,      // const int InitX
                               CenterY,      // const int InitY
                                80,          // const int InitRadius
                                40,          // const int InitYRadius

                               RED,          // const unsigned InitMouthColor
                               LIGHTRED,     // const unsigned InitMouthFillColor
                                14,          // const int      InitEyeRadius
                               LIGHTCYAN,    // const unsigned InitEyeFillColor
                               YELLOW,       // const unsigned InitEyeInnerColor
                               LIGHTBLUE);   // const unsigned InitEyeInnerFillColor
  // Класс Лягушачья пара лап.
  PointArray[14] = new FrogPawsPair(CenterX,   // const int InitX
                                    CenterY,   // const int InitY
                                     30,       // const int InitRadius

                                     75,       // const int InitPawRadius
                                     60,       // const int InitPawAngle
                                    145,       // const int InitStartPawAngle
                                      3,       // const int InitLegThickness

                                     33,       // const int InitHandRadius
                                      2,       // const int InitFingerRadius
                                     40,       // const int InitHandAngle
                                     15);      // const int InitHandStartAngle
  // Класс Лягушка.
  PointArray[15] = new Frog (CenterX,     // const int InitX
                             CenterY,     // const int InitY
                              50,         // const int InitRadius
                              90,         // const int InitYRadius
                              30,         // const int InitInnerRadius
                              60,         // const int InitInnerYRadius
                             BROWN,       // const unsigned InitInnerColor
                             YELLOW,      // const unsigned InitInnerFillColor

                              80,         //       int InitHadRadius
                              40,         //       int InitHadYRadius

                             RED,         // const unsigned InitMouthColor
                             LIGHTRED,    // const unsigned InitMouthFillColor
                              14,         // const int      InitEyeRadius
                             LIGHTCYAN,   // const unsigned InitEyeFillColor
                             YELLOW,      // const unsigned InitEyeInnerColor
                             LIGHTBLUE,   // const unsigned InitEyeInnerFillColor

                               3,         // const int InitLegThickness

                              75,         // const int InitUpperPawRadius
                              60,         // const int InitUpperPawAngle
                             145,         // const int InitStartUpperPawAngle

                              33,         // const int InitUpperHandRadius
                               2,         // const int InitUpperFingerRadius
                              40,         // const int InitUpperHandAngle
                              15,         // const int InitUpperHandStartAngle


                             100,         // const int InitLowerPawRadius
                             240,         // const int InitLowerPawAngle
                             200,         // const int InitStartLowerPawAngle

                              55,         // const int InitLowerHandRadius
                               3,         // const int InitLowerFingerRadius
                              20,         // const int InitLowerHandAngle
                             332);        // const int InitLowerHandStartAngle

  // Выравнивание текста по середине экрана.
  settextjustify(LEFT_TEXT, TOP_TEXT);
  // Готический шрифт.
  settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);

  int Step = 5;
  // Просмор всех объектов.
  for (int i = 0; i < 16; i++)
  {
    // Вывод имени класса.
    setcolor(RED);
    textstring = PointArray[i]->GetClassName();
    outtextxy(10, 10, textstring);

    setcolor(GREEN);
    // Демонстрация объекта класса.
    PointArray[i]->Run(Step);
 
    // Стирание надписи заголовка класса.
    setcolor(getbkcolor());
    outtextxy(10, 10, textstring);
    setcolor(GREEN);
  } // for
} // main
//-----------------------------------------------------------