#include <graphics.h>  // директива препроцессора для работы с графикой
#include <conio.h>       //директива препроцессора для ввода одиночного символа
enum Boolean{false, true};  //логический тип
class Location
 {protected: 
  int X;int Y;  //защищенные поля класса
  public:   // открытый блок
  // Location (); //Такие конструкторы без параметров создаются компилятором. Его 
                         //объявлять не надо. 
  Location (int nx, int ny) { X=nx;Y=ny;} // Если функцию определили сразу в классе, то 
                                                                   // это встроенная функция. Она вызывается не 
                                                                   //через стек, а подстановкой в программу.
  int GetX() {return X;}
  int GetY() { return Y;}
 };

// класс Точка
class Point: public Location
 {protected:
  Boolean vis;
  public:
  Point (int nx,int ny); //конструктор
  //виртуальные функции
  virtual void Show();  //функция, реализующая отображение объекта на экране
  virtual void Hide();   //функция, позволяющая скрыть объект
          void Drag(int by);// движение объекта по экрану в зависимости от шага by
  Boolean Isvis() { return vis;}
  void MoveTo (int nx ,int ny); // перенос точки из одного места на экране в другое
 };
  //класс Окружность
class Circle : public Point
 {protected:
  int R;
  public:
  Circle (int nx,int ny, int nr); //конструктор
  void Show();       // Так как класс Circle является наследником класса Point, функции
  void Hide();         // Show() и Hide() также являются виртуальными
  void Expand(int by); // увеличение окружности
  void Contract(int by);// уменьшение окружности
 };
Boolean GetDelta (int &dx,int &dy); //функция определяет какую кнопку нажал
                                                            //пользователь
Point::Point(int nx,int ny):Location(nx,ny)
	 {  vis=false;   }
void Point:: Show()
	 { vis= true;putpixel(X,Y,getcolor());}// getcolor() возвращает цвет, который сейчас
                                                                         // установлен
void Point :: Hide()
	 {vis=false;putpixel(X,Y,getbkcolor());}//getbkcolor()возвращает цвет фона
void Point :: MoveTo(int nx,int ny)     
	 {Hide();X=nx;Y=ny;Show(); }// точка гасится на старом месте и воспроизводится
                                                               // на новом
Boolean GetDelta(int& dx,int& dy)
 {  char Keych;
	 Boolean Quit;
	 dx=0;dy=0;
	 do
	  {Keych=getch();
	  if (Keych == 13)
		return (false);
	  if (Keych == 0)
		{Quit=true;
		 Keych=getch();
		 switch (Keych){
	  case 72:dy=-1;break;        
	  case 80: dy=1; break;    
   	  case 75:dx=-1; break ;      	
              case 77: dx=1; break ;
	  default : Quit=false;};  };
		 } while (!Quit);
		 return (true); }

// движение объекта по экрану в зависимости от шага by
// Можно нажимать две кнопки одновременно, точка
// будет перемещаться  сразу по x и по y под углом 45 градусов
void Point::Drag(int by)
	 { int dlx,dly;
		int fx,fy;
		Show();
		fx= GetX();fy= GetY();
		while (GetDelta(dlx,dly))
		{  fx+=dlx*by;
	 fy+=dly*by;
	 MoveTo(fx,fy);};		}//перемещение точки, пока стрелка нажата
Circle::Circle(int nx,int ny,int nr):Point(nx,ny)
	{ R=nr;}
void Circle:: Show()
 {	vis=true;circle(X,Y,R);  }
void Circle :: Hide()
 {	unsigned tcol; // tcol - текущее значение цвета
	tcol=getcolor();
	setcolor(getbkcolor());// установка цвета фона
	vis=false;
	circle(X,Y,R); //стандартная функция рисования окружности
	setcolor(tcol);  }//гашение окружности, восстановление исходных значений цвета
void Circle :: Expand(int by) // увеличение окружности
 {Hide();
  R+=by;
  if (R<0)
   R=0;
  Show();  }
void Circle :: Contract(int by) // уменьшение окружности
 {Expand(-by);}

// класс Кольцо
class Ring: public Circle
 {protected:
  Int R1;
  public:
  Ring(int nx,int ny, int nr, int nr1); //конструктор
  void Show();
  void Hide();
  void Expand(int by);
  void Contract(int by);
 };
Ring::Ring(int nx,int ny, int nr, int nr1):Circle(nx,ny,nr)
 {R1=nr1;}
void Ring::Show()
  {vis=true;circle(X,Y,R);circle(X,Y,R1);}
void Ring::Hide()
 {	unsigned tcol;
	tcol=getcolor();
	setcolor(getbkcolor());
	vis=false;
	circle(X,Y,R);
	circle(X,Y,R1);
	setcolor(tcol);
 }
void Ring:: Expand(int by)
 {Hide();
  R+=by;
  R1+=by;
  if (R<0)
    R=0;
  if (R1<0)
    R1=0;
  Show();
 }
void Ring:: Contract(int by)
 {Expand(-by);}

//класс Ауди
class Audi : public Ring
 {protected:
  public:
  Audi(int nx,int ny, int nr, int nr1);
  void Show();
  void Hide();
  void Expand(int by);
  void Contract(int by);
 };
Audi::Audi(int nx,int ny, int nr, int nr1):Ring(nx,ny,nr,nr1)
 {}
void Audi::Show()
 {vis=true;
  circle(X,Y,R);circle(X,Y,R1);   //рисование взаимосвязанных колец
  circle(X+120,Y,R);circle(X+120,Y,R1);
  circle(X+240,Y,R);circle(X+240,Y,R1);
  circle(X+360,Y,R);circle(X+360,Y,R1);
  }
void Audi::Hide()
 {	unsigned tcol;
	tcol=getcolor();
	setcolor(getbkcolor());
	vis=false;
	circle(X,Y,R);circle(X,Y,R1);
	circle(X+120,Y,R);circle(X+120,Y,R1);
	circle(X+240,Y,R);circle(X+240,Y,R1);
	circle(X+360,Y,R);circle(X+360,Y,R1);
	setcolor(tcol);
 }
void Audi:: Expand(int by)
 {Hide();
  R+=by;
  R1+=by;
  if (R<0)
    R=0;
  if (R1<0)
    R1=0;
  Show();
 }
void Audi:: Contract(int by)
 {Expand(-by);}

//основная часть программы
  void main()
//инициализация графического режима
 { int graphdriver=DETECT,graphmode;
 initgraph(&graphdriver,&graphmode,"c:\\borlandc\\bgi");
// создание объекта класса Точка и действия с ним
 Point P(100,50);
 P.Show(); getch();
 P.MoveTo(300,100); getch();
 P.Hide();
// создание объекта класса Окружность и действия с ним
 Circle C(200,200,100);
 C.Show(); getch();
 C.MoveTo(300,200); getch();
 C.Contract(50);getch();
 C.Expand(50);getch();
 C.Drag(5);
 C.Hide();

// создание объекта класса Кольцо и действия с ним 
Ring R(300,300,100,80);
 R.Show();getch();
 R.MoveTo(200,200); getch();
 R.Contract(50);getch();
 R.Expand(50);getch();
 R.Drag(10);
 R.Hide();
// создание объекта класса Ауди и действия с ним
 Audi A(100,300,80,70);
 A.Show();getch();
 A.MoveTo(150,200); getch();
 A.Contract(50);getch();
 A.Expand(50);getch();
 A.Drag(10);
 A.Hide();
//закрытие графического режима
 closegraph();
    }

