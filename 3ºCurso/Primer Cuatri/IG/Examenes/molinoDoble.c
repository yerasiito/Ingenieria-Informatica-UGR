      //Metodo 1
      glTranslatef(-0.5,0,-0.5); //T1
      ortoedro(0.5,0,0.5,0.5,10,0.5,1,0); //A
      
      glTranslatef(0.5,0,0.5); //Trotacion
      glRotatef(ejey,0,1,0); //Ry alfa
      glTranslatef(-0.5,0,-0.5); //Trotacion
     
      glTranslatef(-4.5,11,0); //T2
      glRotatef(-90,0,0,1); //R1
      ortoedro(0.5,0,0.5,0.5,10,0.5,1,0); //B

      glTranslatef(1,0,0.5);
      glRotatef(ejex,0,1,0); //Rx alfa
      glTranslatef(-1,0,-0.5);
      
      glTranslatef(1,-1,5.5); //T3
      glRotatef(-90,1,0,0); //R2
      ortoedro(0.5,0,0.5,0.5,10,0.5,1,0); //D
      glTranslatef(0,0,10); //T4      
      ortoedro(0.5,0,0.5,0.5,10,0.5,1,0); //C
      
      //Metodo 2 con PushMatrix
      glPushMatrix();
      glRotatef(ejey,0,1,0); //R alfa
      glTranslatef(0,11,0); //T3
      glPushMatrix();
        glTranslatef(-6,0,0); //T2
        glRotatef(90,0,0,1); //Rb
        ortoedro(0.5,0,0.5,0.5,10,0.5,1,0); //B
      glPopMatrix();
      glPushMatrix();
        glTranslatef(-6,0,-6); //T4
        glRotatef(90,0,1,1); //Rc
        ortoedro(0.5,0,0.5,0.5,10,0.5,1,0); //C
        
        glTranslatef(-5,0,-6); //T5
        glRotatef(90,0,1,1); //RD
        ortoedro(0.5,0,0.5,0.5,10,0.5,1,0); //D
      glPopMatrix();
    glPopMatrix();

    glTranslatef(-0.5, 0, -0.5); //T1
    ortoedro(0.5,0,0.5,0.5,10,0.5,1,0); //D   
