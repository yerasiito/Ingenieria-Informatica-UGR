//Variables de animacion
int colsigno = 1, rsopsigno = 1, ysopsigno = 1; //Para cambiar la direccion de movimiento
float xcolumna = 0, rsoporte = 20, ysoporte = 0; 

void columnasysoportes(){
  glPushMatrix();
    glTranslatef(xcolumna,0,0); //Movimiento columna Talfa
    ortoedro(0.5,0,1,0.5,10,1,1,2); //B (Columna frontal) Equivale a un cubo unidad escalado 1x10x2

    glPushMatrix();
      materialOrtoedro(light_yellow);
      glTranslatef(0,ysoporte,0); //Movimiento soportes en y (Tbeta)
      glTranslatef(1,5,0.75); //T3
      glRotatef(-90,0,0,1); //R1
      glPushMatrix();
        glRotatef(-20,1,0,0); //R2
        glRotatef(rsoporte,1,0,0); //Rotacion soporte
        cilindro(0.25,0,0.25,0.25,5,0.25,0.5,0.5); //C(soporte izquierdo) Equivale a un cilindro unidad escalado 0.5x5x0.5
      glPopMatrix();
      glPushMatrix();
        glRotatef(20,1,0,0); //R3
        glRotatef(-rsoporte,1,0,0); //Rotacion soporte
        cilindro(0.25,0,0.25,0.25,5,0.25,0.5,0.5); //C(soporte derecho) Equivale a un cilindro unidad escalado 0.5x5x0.5
      glPopMatrix();
      materialOrtoedro(light_blue);
    glPopMatrix();

    glRotatef(90,0,1,0); //R4
    ortoedro(0.5,0,1,0.5,10,1,1,2); //B(columna lateral 1) Equivale a un cubo unidad escalado 1x10x2
    glTranslatef(-3,0,0); //T4
    ortoedro(0.5,0,1,0.5,10,1,1,2); //B(columna lateral 2) Equivale a un cubo unidad escalado 1x10x2
  glPopMatrix();
}

Dibuja(){
    Inicializar luz, escena, etc.....

    materialOrtoedro(light_blue); //Establece el material de la columna
    glPushMatrix();
      glRotatef(-90,0,0,1); //R1
      glTranslatef(-1,-6.5,0); //T1
      ortoedro(0.5,0,1,0.5,13,1,1,2); //A(Base) Equivale a un cubo unidad escalado 1x13x2
    glPopMatrix();

    glTranslatef(-7.5,0,0); //T2
    columnasysoportes(); //Funcion que dibuja 3 columnas en forma de U y sus soportes

    glTranslatef(15,0,2); //T5
    glRotatef(180,0,1,0); //R5
    columnasysoportes(); //Funcion que dibuja 3 columnas en forma de U y sus soportes
}

//Rangos de animacion
void idle(int v){
  //elevador
  xcolumna += 0.01*colsigno;
  if(xcolumna > 1.5)
    colsigno = -1;
  else if(xcolumna < 0)
    colsigno = 1;

  ysoporte += 0.1*ysopsigno;
  if(ysoporte > 5)
    ysopsigno = -1;
  else if(ysoporte < -3.5)
    ysopsigno = 1;

  rsoporte += 0.5*rsopsigno;
  if(rsoporte > 15)
    rsopsigno = -1;
  else if(rsoporte < 0)
    rsopsigno = 1;
}


