//variables de animacion
int rotaz = -45, rotazsigno = 1, rotazDsigno = -1, desplazaysigno = 1;
float rotazD = 0, desplazay = 0;

//Instancia de escalera
void escalera(){
  glPushMatrix();
    //Primer soporte vertical
    glPushMatrix();
      glTranslatef(-0.5,0,-0.5);
      glScalef(1,12,1); //E1
      cubo.draw(); //Cubo
    glPopMatrix();

    //Segundo soporte vertical
    glTranslatef(0,0,6); //T4
    glPushMatrix();
      glTranslatef(-0.5,0,-0.5); //Centra el cubo en el eje
      glScalef(1,12,1); //E2
      cubo.draw(); //Genera el cubo con coordenadas de base 0,0,0 | 0,0,1 | 1,0,1 | 1,0,0
    glPopMatrix();

    //Primer escalon
    glTranslatef(0,1.5,-0.5); //T5
    glRotatef(-90,1,0,0); //R2
    glPushMatrix();
      glTranslatef(-0.5,0,-0.5); //Centra el cubo en el eje
      glScalef(1,5,1); //E2
      cubo.draw(); //Genera el cubo con coordenadas de base 0,0,0 | 0,0,1 | 1,0,1 | 1,0,0
    glPopMatrix();   

    for(int i = 0; i < 3; i++){ //3 escalones mas
      glTranslatef(0,0,3); //T6
      glPushMatrix();
        glTranslatef(-0.5,0,-0.5); //Centra el cubo en el eje
        glScalef(1,5,1); //E2
        cubo.draw(); //Genera el cubo con coordenadas de base 0,0,0 | 0,0,1 | 1,0,1 | 1,0,0
      glPopMatrix();   
    }

  glPopMatrix();

Dibuja(){
  //Inicializar luz, escena, etc...
	
  materialOrtoedro(white); //Material de la escalera
  glRotatef(rotaz,0,0,1); //Rzalfa
  glTranslatef(0,12,0); //T1
  //A
  glPushMatrix();
  glRotatef(-90,0,0,1); //R1
  glRotatef(rotaz2,0,0,1); //Rzbeta
  escalera();
  glPopMatrix();
  //D
  glPushMatrix();
  glRotatef(-180,0,0,1); //2*R1
  escalera();
  glPopMatrix();

  //B y C
  glTranslatef(-1,-12,0); //T2
  glTranslatef(0,desplazay,0); //Talfa
  escalera();
  glTranslatef(-1,0,0); //T3
  glTranslatef(0,desplazay,0); //Talfa
  escalera();      
}

//Rangos de animacion
void idle(int v){
  rotaz += 1*rotazsigno;
  if(rotaz >= 0){
    rotazsigno = -1;
  }
  else if(rotaz <= -45){
    rotazsigno = 1;
  }

  rotazD += (80.0f/45.0f)*rotazDsigno;
  if(rotazD > -1){
    rotazDsigno = -1;
  }
  else if(rotazD <= -80){
    rotazDsigno = 1;
  }

  desplazay += (10.0f/45.0f)*desplazaysigno;
  if(desplazay >= 10)
    desplazaysigno = -1;
  else if(desplazay < 0.1)
    desplazaysigno = 1;
}
