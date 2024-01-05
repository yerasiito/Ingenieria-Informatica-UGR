//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

//Interfaz Instante

#include<iostream>
using namespace std;

class Instante{
private:
   int s = 0;
   int m = 0;
   int h = 0;
public:
   //opcion 1 introduciendo los segundos
   Instante(int seg){
      if(seg >=0){
         s=seg;
      }
      else
         s=-1;
   }
   //Opcion 2 introduciendo horas minutos segundos
   Instante(int hor, int min, int seg){
      if(seg >= 0 && min >= 0 && hor >= 0){
      s = seg;
      m = min;
      h = hor;
      }
      else{
         s = -1;
         m = -1;
         h = -1;
      }

   }

   void SetHorMinSeg(){
      while(s >= 60){
         m++;
         s-=60;
         while(m >= 60){
            h++;
            m-=60;
            while(h >= 24)
               h -= 24;
         }
      }
   }

   int S(){
      return s;
   }

   int M(){
      return m;
   }

   int H(){
      return h;
   }

   int SegTotales(){
      int s_total = 0;
      s_total = s + m*60 + h*3600;

      return s_total;
   }

   int Minutos(){
      int m_total = 0;
      m_total = m + h*60;

      return m_total;
   }

   void conversion_segundos(){
      while(s >= 60){
         m++;
         s-=60;
         while(m >= 60){
            h++;
            m-=60;
            while(h >= 24)
               h = 0;
         }

      }
   }
};

int main(){


   int s,m,h;
   cout << "Introduce los segundos: ";
   cin >> s;
   Instante tiempo0(s);
   tiempo0.conversion_segundos();
   cout << "Tiempo 0: " << tiempo0.H() << "h " << tiempo0.M() << "min " << tiempo0.S() << "seg" << endl;

   cout << "Introduzca la primera hora en formato(s m h): " << endl;
   cin >> h >> m >> s;
   Instante tiempo1(h,m,s);
   tiempo1.SetHorMinSeg();

   cout << "Introduzca la segunda hora en formato(s m h): " << endl;
   cin >> h >> m >> s;
   Instante tiempo2(h,m,s);
   tiempo2.SetHorMinSeg();

   cout << "\n\n";
   cout << "Tiempo 1: " << tiempo1.H() << "h " << tiempo1.M() << "min " << tiempo1.S() << "seg" << endl;
   cout << "Tiempo 2: " << tiempo2.H() << "h " << tiempo2.M() << "min " << tiempo2.S() << "seg" << endl;

   cout   << "Segundos(t1): " << tiempo1.SegTotales() << " segundos."
          << "\nMinutos(t1): " << tiempo1.Minutos() << " minutos" << endl;

   return 0;
}

