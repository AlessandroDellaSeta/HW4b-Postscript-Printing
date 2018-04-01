/*author: Alessandro Della Seta, Shangxing Jiang        Date: March 30, 2018
Postscript 
*/
#include <iostream>
#include <fstream>
using namespace std;

class Postscript {
private:
    ofstream file;
public:
    Postscript(const string &name) {
        file.open(name);    //equals ofstream file(name)
    }
    ~Postscript(){file.close();}

    void line(int x0, int y0, int x1, int y1) {
        file << x0 << ' ' << y0 << " moveto " << x1 << ' ' << y1 << " lineto  stroke\n";

    }

    void setColor(float r, float g, float b) {
        file  << r << ' ' << g << ' ' << b << " setrgbcolor" <<  "\n";
        file << '\n';
    }

    void drawRect(int x, int y, int w, int h) {
        file << x << ' ' << y << " moveto\n" << x + w << ' ' << y << " lineto\n" << x + w
             << ' ' << y + h << " lineto\n" << x << ' ' << y + h << " lineto\n"
             << "closepath gsave stroke\n";
        file << '\n';
    }

    void fillRect(int x, int y, int w, int h) {
        file << x << ' ' << y << " moveto\n" << x + w << ' ' << y << " lineto\n" << x + w
             << ' ' << y + h << " lineto\n" << x << ' ' << y + h << " lineto\n"
             << "closepath gsave fill\n";
        file << '\n';
    }

    void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
        file << x1 << ' ' << y1 << " moveto\n" << x2 << ' ' << y2 << " lineto\n"
             << x3 << ' ' << y3 << " lineto\n" << "closepath gsave stroke\n";
        file << '\n';
    }

    void fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
        file << x1 << ' ' << y1 << " moveto\n" << x2 << ' ' << y2 << " lineto\n"
             << x3 << ' ' << y3 << " lineto\n" << "closepath gsave fill\n";
        file << '\n';
    }

    void drawCircle(int x, int y, int r) {
        file << x << ' ' << y << ' ' << r << " 0 360 arc stroke 2 setlinewidth\n";
        file << '\n';
    }

    void setFillColor(double r, double g, double b){
        file << "grestore gsave " << r << " " << g << " " << b << " setrgbcolor fill\n";
    }

    void setStrokeColor(double r, double g, double b){
        file << "grestore gsave " << r << " " << g << " " << b << " setrgbcolor 2 setlinewidth stroke\n";
    }

    void text(int x, int y, const string &t) {
        file << " /Times-Roman findfont 15 scalefont setfont newpath " << x << " " << y << " moveto " << "(" << t << ")"
             << " show" << '\n';
    }

    void  grid(int x0, int x1, int m, int y0, int y1, int n) {
        file << "0.1 setlinewidth\n";
        setColor(0,0,0);
        int x = x0, dx = (x1-x0)/(m-1);
        for (int i = 0; i <= m; i++, x += m) {
            line(x, y0, x, y1);
            text(x+1,y0+1,to_string(x));
        }
        int y = y0, dy = (y1-y0)/(n-1);
        for (int i = 0; i <= n; i++, y += n) {
            line(x0, y, x1, y);
            text(x0+1,y+1,to_string(y));
        }
    }
};


int main() {
    Postscript p("test.ps");
    p.line(150,100, 450,100);  // 0 0 moveto 300 400 lineto stroke
    int r = 255, g = 0, b = 0;
    p.setColor( r, g, b);
    p.drawRect(200, 150, 200, 150);   // x y moveto x+w y lineto x+w y+h lineto ... closepath stroke
    p.fillRect(201,150 , 201, 151);   // x y moveto x+w y lineto x+w y+h lineto ... closepath fill
    p.setFillColor(0,  0, 255); // 1.0 0.5 0 setrgbcolor
    // optional, figure out how you want to manage color
    p.setStrokeColor( 0,  255,  0);
    p.drawTriangle(200,301, 400,301,300,450);
    p.fillTriangle(225,325, 375,325, 300,425);
    p.drawCircle(300,300,150); // x y 0 360 r arc stroke
    p.text(300,125, "testing testing 123"); // look it up  setfont  (ABC) show
    p.grid(0, 610, 50, 0 , 800, 50);
}


