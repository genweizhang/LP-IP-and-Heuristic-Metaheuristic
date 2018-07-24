#include <iostream>
using namespace std;


class Point 
	{ 
	friend Point add(Point, Point);
	protected:
         double _x;
 	     double _y;
	public:
	  Point(); // default constructor
	  Point(double x, double y); // non-default constructor
	  void display(); // a public function
     	  virtual ~Point(); //destructor
 	  Point& operator+ (Point& a);
		}; 
class colorpoint: public Point
	{
	public:
	colorpoint(); // default constructor
 	virtual ~colorpoint(); //destructor
	};
colorpoint::colorpoint(){
			double a;
			a=1;
			cout<<_x<<endl;
			cout<<"sub-class called, a="<<a<<endl;
			}
colorpoint::~colorpoint(){
                          cout<<"sub-class, destroy"<<endl;
		     	  }
Point::Point(){
		_x=1;
		_y=1;
		cout<<"class called"<<endl;
		}
Point::Point(double x, double y){
			_x=x+y;
			_y=x-y;
			}
void Point::display(){
			cout<<"x="<<_x<<","<<"y="<<_y<<endl;
			}
Point::~Point(){
		cout<<"Point was destroyed!!"<<endl;
		}
Point& Point::operator+ (Point& a)
		{
		Point* c;
 		c=new Point();
		(*c)._x=_x+a._x;
 		(*c)._y=_y+a._y;
		return *c;
		}
Point add(Point A, Point B)
                  {
                  Point c;
                  //c=new Point();
                  c._x=A._x+B._x;
                  c._y=A._y+B._y;
                  return c;
                  }
int main(){
	Point t1; //statically created
	Point t2(5.1,3);//statically created
    Point t3(20,10);
	Point* t4=NULL; //dynamically created, A POINTER!!!
        t4=new Point(100,200);
        Point t5;
	cout<<"after"<<'\n';
      	t5=add(t2,t3); 
	cout<<"before"<<'\n';
	t1.display();
	t2.display();
	t3.display();
	t4->display();
	t5.display();
	cout<<""<<'\n';
	delete t4;
	cout<<""<<'\n';
	colorpoint t6;
	return 0;
	}









