/*  S 3,4
    Abdallah Emad 20200323
    Mona Abdelaziz 20200561
*/
#include <iostream>
#define SETCOLORFUN_H_INCLUDED
#include <windows.h>
using namespace std;
class ColoredBox
{
private:
    char character;
    int length;
    int wide;
    int color;
    char **array;
public:
    static int maxArea;
    ColoredBox();        //default Constructor
    ColoredBox(int len,int wid,int col,char boxChar);
    void setColor(int col);
    void setLenght(int len);
    void setWide(int wid);
    void setCharacter(char chr);
    void changeColor(int ForgC);
    void insertArray();
    int getColor();
    int getLenght();
    int getWide();
    char getCharacter();
    void display();
    void displayTransposed();
    void displayWider();
    void displayChess(int col2);
    int getArea();
    int getMaxArea();
    ~ColoredBox();
};
int ColoredBox:: maxArea=0; //static int to evaluate maxarea
// Constructors
ColoredBox::ColoredBox():length(0),wide(0),character('#'),color(15)
{
 insertArray();
}

ColoredBox::ColoredBox(int len,int wid,int col=15,char boxChar='#')
{
 length=len;
 wide=wid;
 color=col;
 character=boxChar;
 insertArray();
}

//2D dimension array
void ColoredBox::insertArray()
{
        array =new char*[length];
   for (int i = 0; i < length; i++)
    {
        array[i] = new char [wide];
    }
    for (int i = 0; i < length; i++)
     {
          for (int j = 0; j < wide; j++)
          {
              array[i][j]=character;
          }
     }
}
//function to change color
void ColoredBox::changeColor(int ForgC)
 {
     WORD wColor;

      HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
      CONSOLE_SCREEN_BUFFER_INFO csbi;

                           //We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
                     //Mask out all but the background attribute, and add in the forgournd color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}
//function set & get the value
void ColoredBox::setLenght(int len)
{
    length=len;
}
void ColoredBox::setWide(int wid)
{
    wide=wid;
}
void ColoredBox::setCharacter(char chr)
{
    character=chr;
}
void ColoredBox::setColor(int col)
{
    color=col;
}
int ColoredBox::getColor()
{
    return color;
}
int ColoredBox::getLenght()
{
    return length;
}
int ColoredBox::getWide()
{
    return wide;
}
char ColoredBox:: getCharacter()
{
    return character;
}
//function to display the array
void ColoredBox::display()
{
    for(int i=0;i<length;i++)
        {
            for(int j=0;j<wide;j++)
                {
                    changeColor(color);
                    cout<<array[i][j];
                }
            cout<<endl;
        }
         changeColor(15);
}
//function to Transposed and display the array
void ColoredBox::displayTransposed()
{
    int x=0;
    for(int i=0;i<length;i++)
        {
            for(int j=0;j<wide;j++)
                {
                    x++;
                    changeColor(color);
                    cout<<array[i][j];
                    if(x%length==0)cout<<endl;
                }
        }
         changeColor(15);
}
//function to display wide array
void ColoredBox::displayWider()
{
    for(int i=0;i<length;i++)
        {
            for(int j=0;j<wide;j++)
                {
                    changeColor(color);
                    cout<<array[i][j]<<" ";
                }
            cout<<endl;
        }
         changeColor(15);
}
//function to display chess array
void ColoredBox::displayChess(int col2)
{
    int col1=color;
    for(int i=0;i<length;i++)
        {

            for(int j=0;j<wide;j++)
                {
                    if(j%2==0)//check if it even
                        {
                            changeColor(col1);
                            cout<<array[i][j];
                        }
                        else
                        {
                            changeColor(col2);
                            cout<<array[i][j];
                        }
                }cout<<endl;
                swap(col1,col2);
        }
         changeColor(15);//return the main color
}

int ColoredBox::getArea()
{
    int area=length*wide;
    if (area>maxArea) maxArea=area;
    return area;
}

int ColoredBox::getMaxArea()
{
    getArea();
    return maxArea;
}
//destructor
ColoredBox::~ColoredBox()
{
    getArea();
    for (int i = 0; i < length; ++i)
        {
          for (int j = 0; j < wide; ++j)
           {
                array[i][j] = NULL;
           }
        }
    delete []array;
}
int main()
{
    int len,wid,col,col2;
    char boxChar;
    cout<<"Enter length and width of the box separated by a space: ";
    cin>>len>>wid;
    ColoredBox* cb1;
    cb1 = new ColoredBox(len,wid);
    cb1->display();
    cout<<"Set the box to another color: ";
    cin>>col;
    cb1->setColor(col);
    cout<<"Displaying Transposed: "<<endl;
    cb1->displayTransposed();
    cout<<"Displaying Wider: "<<endl;
    cb1->displayWider();
    cout<<"Displaying Chess, enter the other color: "<<endl;
    cin>>col2;
    cb1->displayChess(col2);
    cout<<endl<<"Area="<<cb1->getArea();
    cout<<endl<<"Max Area="<<cb1->getMaxArea()<<endl;
    delete cb1;

    cout<<"Enter length,width,color,character of the box separated by spaces: ";
    cin>>len>>wid>>col>>boxChar;
    ColoredBox* cb2;
    cb2 = new ColoredBox(len,wid,col,boxChar);
    cb2->display();
    cout<<"Displaying Transposed: "<<endl;
    cb2->displayTransposed();
    cout<<"Displaying Wider: "<<endl;
    cb2->displayWider();
    cout<<"Displaying Chess, enter the other color: "<<endl;
    cin>>col2;
    cb2->displayChess(col2);
    cout<<"Displaying original again:"<<endl;
    cb2->display();
    cout<<endl<<"Area="<<cb1->getArea();
    cout<<endl<<"Max Area="<<cb1->getMaxArea();
    delete cb2;
    return 0;
}
