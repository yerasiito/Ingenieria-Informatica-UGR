#include "motorlib.hpp"

#include <glui/glui.h>
#include <dirent.h>

MonitorJuego monitor;

// variables que determninan la posicion y tamaño de la ventana X
const int IU_ancho_ventana = 1024;
const int IU_alto_ventana = 768;

// Variables que controlan las ventanas y vistas
GLuint ventanaPrincipal, vistaPrincipal, vistaMiniMapa, vistaIU;
GLUI *panelSelecMapa, *panelSelecMapaConfig;
GLUI_Listbox *listbox;
GLUI_RadioGroup *group, *group1;
GLUI_Button *botonElegirMapa, *botonConfigurar, *botonPaso, *botonEjecucion, *botonEjecutar, *botonSalir;
GLUI_EditText *editTextPasos, *editTextRetardo;
GLUI_Checkbox *drawMM, *drawMMVista, *evoResul;
GLUI_StaticText *lineaVacia, *info0, *info1, *info2, *info3, *info4, *info5, *info6, *info7, *info8, *info9, *resu0;
GLUI_Spinner *setup1, *setup2, *setup3, *setup4, *setup5, *setup6, *setup7, *setup8, *setup9, *setup10;
GLUI_Spinner *editPosColumna, *editPosFila;
GLUI_RadioButton *obj1, *obj2, *obj3;

int nPasos = 10, tRetardo = 1, MMmode = 0, MMmode2 = 1, MMmode3 = 0, PosColumna = 1, PosFila = 1, tMap = 100, colisiones = 0;
int objtiveSelected = 0;
int ultimomapaPos = 0, ultimonivel = 0;

void irAlJuego(int valor);

/*void keyboard(unsigned char key, int x, int y) {
  float a;
  switch(key) {
    case 'w': // UP
      a = monitor.getMapa()->getAngle();
      a = a + 0.01;
      cout << "Y1: " << a << endl;
      monitor.getMapa()->putAngle(a);
      break;

    case 's': // DCHA
      a = monitor.getMapa()->getParamX();
      a = a + 0.01;
      cout << "Y2: " << a << endl;
      monitor.getMapa()->PutParamX(a);
      break;

    case 'a': // IZQDA
      a = monitor.getMapa()->getParamZ();
      a = a + 0.01;
      cout << "Y3: " << a << endl;
      monitor.getMapa()->PutParamZ(a);
      break;

    case 'd': // IZQDA
      a = monitor.getMapa()->getParamZ();
      a = a - 0.01;
      cout << "Y3: " << a << endl;
      monitor.getMapa()->PutParamZ(a);
      break;

    default: // Paranoia
      cout << key << " " << "ERROR\n";
      break;
  }
}*/

//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion: nuevo ancho, nuevo alto
//***************************************************************************

void reshape(int ancho, int alto)
{
  if ((ancho > 1) and (alto > 1))
  {
    // parametros de la ventana principal

    float ratio = ((float)ancho * 0.7) / (float)alto;

    glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, ancho, alto);
    glLoadIdentity();
    gluOrtho2D(0, ancho, alto, 0);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    // Display vista principal
    glutSetWindow(vistaPrincipal);
    glutPositionWindow(0, 0);
    glutReshapeWindow(ancho * 0.7, alto);
    glutPostRedisplay();

    // Display vista mini-mapa

    glutSetWindow(vistaMiniMapa);
    glutPositionWindow(ancho * 0.7, 0);
    glutReshapeWindow((ancho * 0.3) + 1, alto * 0.3);
    glutPostRedisplay();

    // Display interfaz
    glutSetWindow(vistaIU);
    glutPositionWindow(ancho * 0.7, alto * 0.3);
    glutReshapeWindow((ancho * 0.3) + 1, (alto * 0.7) + 1);
    lineaVacia->set_w((ancho * 0.3) + 1);
    lineaVacia->set_h((alto * 0.7) + 1);
    glutPostRedisplay();
  }
}

void ResetViewport()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-10.0, 10.0, -10.0, 10.0, 0.0, 10.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void display_ventPrincipal(void)
{
  // Background Color
  glClearColor(0.8, 0.8, 0.8, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glutSwapBuffers();
}

void display_vistPrincipal()
{
  ResetViewport();

  glMatrixMode(GL_PROJECTION);

  if (monitor.getMapa() != 0)
  {
    float ratio = ((float)IU_ancho_ventana * 0.7) / (float)IU_alto_ventana;
    gluPerspective(45, ratio, 1, 1000);
    glClearColor(60.0 / 256.0, 154.0 / 256.0, 201.0 / 256.0, 1);
  }
  else
  {
    glClearColor(0.0, 0.0, 0.0, 1);
  }

  glMatrixMode(GL_MODELVIEW);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glDisable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);

  glPushMatrix();
  if (monitor.jugar())
  {
    if (monitor.getMapa() != 0 and MMmode2 != 0)
    {
      monitor.getMapa()->drawFirstPerson();
    }
  }
  glPopMatrix();
  glFlush();
  glutSwapBuffers();
}

void display_vistMiniMapa()
{
  ResetViewport();

  glMatrixMode(GL_MODELVIEW);
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  glDisable(GL_LIGHTING);
  glColor3f(1.0, 1.0, 1.0);
  glPushMatrix();
  if (monitor.jugar() /* or monitor.resultadosMostrados()*/)
  {
    if (MMmode == 0)
      monitor.getMapa()->drawMM2();
    else
      monitor.getMapa()->drawMM1();
  }
  glPopMatrix();
  glFlush();
  glutSwapBuffers();
}

void Descomponer(string str, vector<string> &strs)
{
  while (str.length() != 0)
  {
    strs.push_back(str.substr(0, str.find('\n')));
    str = str.substr(str.find('\n') + 1, str.length());
  }
}

void display_vistIU()
{
  ResetViewport();
  GLUI_Master.auto_set_viewport();
  std::vector<std::string> strs;
  string str;

  if (monitor.jugar() and monitor.numero_entidades() > 0)
  {
    str = monitor.get_entidad(0)->toString();

    Descomponer(str, strs);

    int i = 0;
    for (vector<string>::const_iterator it = strs.begin(); it != strs.end(); it++)
    {
      switch (i)
      {
      case 0:
        info0->set_text(it->c_str());
        break;
      case 1:
        info1->set_text(it->c_str());
        break;
      case 2:
        info2->set_text(it->c_str());
        break;
      case 3:
        info3->set_text(it->c_str());
        break;
      case 4:
        info4->set_text(it->c_str());
        break;
      case 5:
        info5->set_text(it->c_str());
        break;
      case 6:
        info6->set_text(it->c_str());
        break;
      case 7:
        info7->set_text(it->c_str());
        break;
      case 8:
        info8->set_text(it->c_str());
        break;
      case 9:
        info9->set_text(it->c_str());
        break;
      }
      i++;
    }
    if (MMmode3 == 1 or monitor.mostrarResultados())
    {
      str = to_string(monitor.CoincidenciaConElMapa());
      str += " \%";
      resu0->set_text(str.c_str());
    }
    else
    {
      resu0->set_text("no calculado");
    }
  }
  glutSwapBuffers();
}

void update(int valor)
{
  glutSetWindow(vistaPrincipal);
  glutPostRedisplay();

  glutSetWindow(vistaMiniMapa);
  glutPostRedisplay();

  glutSetWindow(vistaIU);
  glutPostRedisplay();
  // glutKeyboardFunc(keyboard);

  glutTimerFunc(1, irAlJuego, 0);
}

void irAlJuego(int valor)
{
  if (lanzar_motor_juego(colisiones, -1))
  {
    botonElegirMapa->enable();
    botonPaso->disable();
    botonEjecucion->disable();
    botonEjecutar->disable();
    botonSalir->disable();
    editTextPasos->disable();
    editTextRetardo->disable();
    botonSalir->enable();
    // colisiones = 0;
  }
  // glutKeyboardFunc(keyboard);
  glutTimerFunc(1, update, 0);
}

void botonCancelarNuevoMapaCB(int valor)
{
  panelSelecMapa->close();

  botonElegirMapa->enable();
  botonSalir->enable();
}

void botonAceptarNuevoMapaCB(int valor)
{

  botonElegirMapa->enable();
  drawMM->disable();
  botonPaso->enable();
  botonEjecucion->enable();
  botonEjecutar->enable();
  botonSalir->enable();
  editTextPasos->enable();
  editTextRetardo->enable();

  int posF, posC, orienta;

  ultimomapaPos = listbox->get_int_val();

  if (ultimomapaPos >= 0)
  {
    char path[255];
    strcpy(path, "./mapas/");
    const char *file = listbox->curr_text.c_str();
    string auxName = strcat(path, file);
    monitor.setMapa(auxName.c_str());
    if (auxName != monitor.get_currentMap())
    {
      monitor.set_n_aldeanos(monitor.getMapa()->getNCols() / 10);
      monitor.set_n_lobos(monitor.getMapa()->getNCols() / 10);
      monitor.set_currentMap(auxName);
      monitor.generate_a_valid_cell(posF, posC, orienta);
    }
    else
    {
      posC = monitor.get_entidad(0)->getCol();
      posF = monitor.get_entidad(0)->getFil();
      orienta = monitor.get_entidad(0)->getOrientacion();
      if (!monitor.is_a_valid_cell_like_goal(posF, posC))
      {
        monitor.generate_a_valid_cell(posF, posC, orienta);
      }
    }

    ultimonivel = group->get_int_val();

    monitor.startGame(ultimonivel);
    if (monitor.inicializarJuego())
    {
      monitor.inicializar(posF, posC, orienta);
      tMap = monitor.juegoInicializado();
      MMmode = 0;
      drawMM->set_int_val(0);
      drawMM->enable();
    }
  }
  else
  {
    cout << "No se puede leer el fichero..." << endl;
  }

  panelSelecMapa->close();
}

vector<string> getFilesList(string name, string extension)
{
  vector<string> v;

  DIR *dirp = opendir(name.c_str());
  struct dirent *dp = readdir(dirp);
  while (dp)
  {
    string fname(dp->d_name);
    if (fname.find(extension, 0) < fname.size())
    {
      v.push_back(fname);
    }
    dp = readdir(dirp);
  }
  closedir(dirp);

  return v;
}

void botonConfigurarSimOK(int valor)
{
  botonElegirMapa->enable();
  drawMM->enable();
  drawMMVista->enable();
  botonPaso->enable();
  botonEjecucion->enable();
  botonEjecutar->enable();
  botonSalir->enable();
  editTextPasos->enable();
  editTextRetardo->enable();

  monitor.set_semilla(setup1->get_int_val());
  srand(monitor.get_semilla());
  monitor.inicializar();
  monitor.get_entidad(0)->setPosicion(setup3->get_int_val(), setup2->get_int_val());
  monitor.get_entidad(0)->setOrientacion(static_cast<Orientacion>(setup6->get_int_val()));
  if (monitor.getLevel() >= 3)
    monitor.set_n_aldeanos(setup5->get_int_val());
  if (monitor.getLevel() >= 4)
    monitor.set_n_lobos(setup4->get_int_val());
}

void botonConfigurarSimCANCEL(int valor)
{
  botonConfigurarSimOK(1);
  MMmode = 0;
  panelSelecMapaConfig->close();
  monitor.init_casillas_especiales(monitor.get_entidad(0)->getFil(), monitor.get_entidad(0)->getCol());
}

void botonConfigurarNuevoMapaCB(int valor)
{
  /* LLamada para cargar el mapa */
  panelSelecMapa->close();

  botonElegirMapa->disable();
  drawMM->disable();
  drawMMVista->disable();
  botonPaso->disable();
  botonEjecucion->disable();
  botonEjecutar->disable();
  botonSalir->enable();
  editTextPasos->disable();
  editTextRetardo->disable();

  int item = listbox->get_int_val();
  int posC, posF, orienta, semilla, naldeanos, nlobos;

  if (item > 0)
  {
    char path[255];
    strcpy(path, "./mapas/");
    const char *file = listbox->curr_text.c_str();
    string auxName = strcat(path, file);
    monitor.setMapa(auxName.c_str());
    if (auxName != monitor.get_currentMap())
    {
      naldeanos = monitor.getMapa()->getNCols() / 10;
      monitor.set_n_aldeanos(naldeanos);
      nlobos = monitor.getMapa()->getNCols() / 10;
      monitor.set_n_lobos(nlobos);
      monitor.set_currentMap(auxName);
      monitor.generate_a_valid_cell(posF, posC, orienta);
    }
    else
    {
      posC = monitor.get_entidad(0)->getCol();
      posF = monitor.get_entidad(0)->getFil();
      orienta = monitor.get_entidad(0)->getOrientacion();
      if (!monitor.is_a_valid_cell_like_goal(posF, posC))
      {
        monitor.generate_a_valid_cell(posF, posC, orienta);
      }
      naldeanos = monitor.get_n_aldeanos();
      nlobos = monitor.get_n_lobos();
    }

    int nivel = group->get_int_val();

    /* Paso las variables de monitor a variables locales a este metodo */
    semilla = monitor.get_semilla();

    if (nivel < 3)
      naldeanos = 0;
    if (nivel < 4)
      nlobos = 0;

    monitor.startGame(nivel);
    if (monitor.inicializarJuego())
    {
      monitor.inicializar(posF, posC, orienta);
      tMap = monitor.juegoInicializado();
      MMmode = 0;
      drawMM->set_int_val(0);
      drawMM->enable();
    }
  }
  else
  {
    cout << "No se puede leer el fichero..." << endl;
  }

  MMmode = 1;
  panelSelecMapaConfig = GLUI_Master.create_glui("Configurar Mapa");

  int num_filas = monitor.getMapa()->getNFils();
  int num_col = monitor.getMapa()->getNCols();

  GLUI_Panel *obj_panel = panelSelecMapaConfig->add_panel("Setup");
  setup1 = panelSelecMapaConfig->add_spinner_to_panel(obj_panel, "                Semilla ", GLUI_SPINNER_INT, &semilla);

  GLUI_Panel *obj_subpanel0 = panelSelecMapaConfig->add_panel_to_panel(obj_panel, "Origen");

  setup3 = panelSelecMapaConfig->add_spinner_to_panel(obj_subpanel0, "            Fila ", GLUI_SPINNER_INT, &posF);
  setup3->set_int_limits(0, num_filas, GLUI_LIMIT_WRAP);
  setup2 = panelSelecMapaConfig->add_spinner_to_panel(obj_subpanel0, "     Columna ", GLUI_SPINNER_INT, &posC);
  setup2->set_int_limits(0, num_col, GLUI_LIMIT_WRAP);
  setup6 = panelSelecMapaConfig->add_spinner_to_panel(obj_subpanel0, " Orientacion ", GLUI_SPINNER_INT, &orienta);
  setup6->set_int_limits(0, 4, GLUI_LIMIT_WRAP);
  GLUI_Panel *obj_subpanel1 = panelSelecMapaConfig->add_panel_to_panel(obj_panel, "Parametros");
  setup5 = panelSelecMapaConfig->add_spinner_to_panel(obj_subpanel1, "    Numero Aldeanos ", GLUI_SPINNER_INT, &naldeanos);
  setup5->set_int_limits(0, num_filas, GLUI_LIMIT_WRAP);
  setup5->disable();
  setup4 = panelSelecMapaConfig->add_spinner_to_panel(obj_subpanel1, "    Numero Lobos  ", GLUI_SPINNER_INT, &nlobos);
  setup4->set_int_limits(0, num_col, GLUI_LIMIT_WRAP);
  setup4->disable();

  if (ultimonivel > 2)
  {
    setup5->enable();
  }
  if (ultimonivel > 3)
  {
    setup4->enable();
  }

  panelSelecMapaConfig->add_button("Ok", 1, botonConfigurarSimOK);
  panelSelecMapaConfig->add_button("Finish", 1, botonConfigurarSimCANCEL);
}

void botonElegirMapaCB(int valor)
{

  panelSelecMapa = GLUI_Master.create_glui("Nuevo Juego");

  botonElegirMapa->disable();
  botonPaso->disable();
  botonEjecucion->disable();
  botonEjecutar->disable();
  botonSalir->disable();

  // editPosColumna->disable();
  // editPosFila->disable();

  editTextPasos->disable();
  editTextRetardo->disable();
  // obj1->disable();
  // obj2->disable();
  // obj3->disable();

  listbox = panelSelecMapa->add_listbox("Mapas", &ultimomapaPos);

  int i = 1;
  vector<string> filesPaths = getFilesList("mapas/", ".map");
  vector<string>::const_iterator it = filesPaths.begin();
  while (it != filesPaths.end())
  {
    listbox->add_item(i++, (*it).c_str());
    it++;
  }

  listbox->set_int_val(ultimomapaPos);

  GLUI_Panel *obj_panel = panelSelecMapa->add_panel("Nivel");
  group = panelSelecMapa->add_radiogroup_to_panel(obj_panel, &ultimonivel);
  panelSelecMapa->add_radiobutton_to_group(group, "Nivel 0: Basico                          ");
  panelSelecMapa->add_radiobutton_to_group(group, "Nivel 1: Sin sensor de posicion          ");
  panelSelecMapa->add_radiobutton_to_group(group, "Nivel 2: Sin sensor de orientacion       ");
  panelSelecMapa->add_radiobutton_to_group(group, "Nivel 3: Con aldeanos                    ");
  panelSelecMapa->add_radiobutton_to_group(group, "Nivel 4: Con lobos                       ");

  panelSelecMapa->add_button("Ok", 1, botonAceptarNuevoMapaCB);
  panelSelecMapa->add_button("Ok y Configurar", 2, botonConfigurarNuevoMapaCB);
  panelSelecMapa->add_button("Salir", 3, botonCancelarNuevoMapaCB);
}

void botonPasoCB(int valor)
{
  monitor.setPasos(1);
}

void botonEjecucionCB(int valor)
{
  monitor.setPasos(3000);
}

void botonEjecutarCB(int valor)
{
  monitor.setPasos(nPasos);
}

void setRetardo(int valor)
{
  monitor.setRetardo(tRetardo);
}

void botonSalirCB(int valor)
{
  monitor.cerrarBelkan();
  exit(0);
}

void mouseClick(int button, int state, int x, int y)
{
  int tx, ty, tw, th;
  GLUI_Master.get_viewport_area(&tx, &ty, &tw, &th);
  int nx = round(x * tMap * 1.0 / tw);
  int ny = round(y * tMap * 1.0 / th);

  /*if ((button == GLUT_LEFT_BUTTON) and (state == GLUT_DOWN)) {
    if ((nx >= 0) and (nx <= tMap-1) and (ny >= 0) and (ny <= tMap-1)) {
    editPosFila->set_int_val(ny);
    editPosColumna->set_int_val(nx);
    setPosFila(ny);
    setPosColumna(nx);
  }
}*/
}

void lanzar_motor_grafico(int argc, char **argv)
{
  glutInit(&argc, argv);
  // Mode Setting
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  // window size (+gap size)
  glutInitWindowSize(IU_ancho_ventana, IU_alto_ventana);
  float ratio = ((float)IU_ancho_ventana * 0.7) / (float)IU_alto_ventana;
  // Initial position
  glutInitWindowPosition(300, 0);

  // Main Window
  ventanaPrincipal = glutCreateWindow("Practica 1: Agentes Reactivos. Curso 21/22");
  // Main Window callback function
  glutReshapeFunc(reshape);
  glutDisplayFunc(display_ventPrincipal);

  // World Window and Display
  vistaPrincipal = glutCreateSubWindow(ventanaPrincipal, 0, 0, IU_ancho_ventana * 0.7, IU_alto_ventana);
  glutDisplayFunc(display_vistMiniMapa);
  glutMouseFunc(mouseClick);
  // glutKeyboardFunc(keyboard);

  // screen Window and Display
  vistaMiniMapa = glutCreateSubWindow(ventanaPrincipal, IU_ancho_ventana * 0.7, 0, (IU_ancho_ventana * 0.3) + 1, IU_alto_ventana * 0.3);
  glutDisplayFunc(display_vistPrincipal);

  vistaIU = glutCreateSubWindow(ventanaPrincipal, IU_ancho_ventana * 0.7, IU_alto_ventana * 0.3, (IU_ancho_ventana * 0.3) + 1, (IU_alto_ventana * 0.7) + 1);
  glutDisplayFunc(display_vistIU);

  glutInitWindowPosition(IU_ancho_ventana * 0.7, 50);
  glutInitWindowSize(50, 50);

  GLUI *panelIU = GLUI_Master.create_glui_subwindow(vistaIU, GLUI_SUBWINDOW_TOP);
  panelIU->set_main_gfx_window(vistaIU);

  botonElegirMapa = panelIU->add_button("Nuevo Juego", 0, botonElegirMapaCB);
  botonElegirMapa->set_alignment(GLUI_ALIGN_CENTER);

  GLUI_Panel *obj_panel2 = panelIU->add_panel("Visualizacion");

  drawMMVista = panelIU->add_checkbox_to_panel(obj_panel2, "Vista en 1ª Persona", &MMmode2);
  drawMMVista->set_alignment(GLUI_ALIGN_CENTER);
  drawMMVista->enable();
  panelIU->add_column_to_panel(obj_panel2, true);

  drawMM = panelIU->add_checkbox_to_panel(obj_panel2, "Mostrar mapa", &MMmode);
  drawMM->set_alignment(GLUI_ALIGN_CENTER);
  drawMM->disable();

  // lineaVacia = panelIU->add_statictext("");

  GLUI_Panel *run_panel = panelIU->add_panel("Control");

  editTextPasos = panelIU->add_edittext_to_panel(run_panel, "Pasos", GLUI_EDITTEXT_INT, &nPasos);
  editTextPasos->set_int_val(nPasos);
  editTextPasos->set_int_limits(1, 10000000, GLUI_LIMIT_CLAMP);
  editTextPasos->set_alignment(GLUI_ALIGN_CENTER);

  editTextRetardo = panelIU->add_edittext_to_panel(run_panel, "Retardo", GLUI_EDITTEXT_INT, &tRetardo, -1, setRetardo);
  editTextRetardo->set_int_val(tRetardo);
  editTextRetardo->set_int_limits(0, 10000000, GLUI_LIMIT_CLAMP);
  editTextRetardo->set_alignment(GLUI_ALIGN_CENTER);
  setRetardo(tRetardo);

  panelIU->add_column_to_panel(run_panel, true);

  botonPaso = panelIU->add_button_to_panel(run_panel, "Paso", 0, botonPasoCB);
  botonPaso->set_alignment(GLUI_ALIGN_CENTER);
  botonEjecutar = panelIU->add_button_to_panel(run_panel, "Ciclo", 0, botonEjecutarCB);
  botonEjecutar->set_alignment(GLUI_ALIGN_CENTER);
  botonEjecucion = panelIU->add_button_to_panel(run_panel, "Ejecucion", 0, botonEjecucionCB);

  lineaVacia = panelIU->add_statictext("");

  botonSalir = panelIU->add_button("Salir", 0, botonSalirCB);
  botonSalir->set_alignment(GLUI_ALIGN_CENTER);

  lineaVacia = panelIU->add_statictext("");

  GLUI_Panel *panelInfo = panelIU->add_panel("Informacion");
  panelInfo->set_alignment(GLUI_ALIGN_CENTER);

  info0 = panelIU->add_statictext_to_panel(panelInfo, "              No hay informacion disponible           ");
  info1 = panelIU->add_statictext_to_panel(panelInfo, "");
  info2 = panelIU->add_statictext_to_panel(panelInfo, "");
  info3 = panelIU->add_statictext_to_panel(panelInfo, "");
  info4 = panelIU->add_statictext_to_panel(panelInfo, "");
  info5 = panelIU->add_statictext_to_panel(panelInfo, "");
  info6 = panelIU->add_statictext_to_panel(panelInfo, "");
  info6->set_font(GLUT_BITMAP_8_BY_13);
  info7 = panelIU->add_statictext_to_panel(panelInfo, "");
  info7->set_font(GLUT_BITMAP_8_BY_13);
  info8 = panelIU->add_statictext_to_panel(panelInfo, "");
  info8->set_font(GLUT_BITMAP_8_BY_13);
  info9 = panelIU->add_statictext_to_panel(panelInfo, "");
  info9->set_font(GLUT_BITMAP_8_BY_13);

  // panelIU->add_separator_to_panel(panelInfo);

  lineaVacia = panelIU->add_statictext("");

  GLUI_Panel *panelResu = panelIU->add_panel("Resultado");
  evoResul = panelIU->add_checkbox_to_panel(panelResu, "Actualizar", &MMmode3);
  evoResul->set_alignment(GLUI_ALIGN_CENTER);
  evoResul->enable();
  panelIU->add_column_to_panel(panelResu, true);
  panelResu->set_alignment(GLUI_ALIGN_CENTER);
  resu0 = panelIU->add_statictext_to_panel(panelResu, "    No hay informacion disponible         ");
  lineaVacia = panelIU->add_statictext("");

  glutTimerFunc(100, irAlJuego, 0);

  botonPaso->disable();
  botonEjecucion->disable();
  botonEjecutar->disable();
  // editPosColumna->disable();
  // editPosFila->disable();
  editTextPasos->disable();
  editTextRetardo->disable();

  glutMainLoop();
}

void lanzar_motor_grafico_verOnline(int argc, char **argv, EnLinea &argumentos)
{

  // Poner los valores del juego antes de lanzar el bucle
  const char *dirMapa = argumentos.ubicacion_mapa.c_str();
  monitor.setMapa(dirMapa);
  tMap = monitor.getMapa()->getNFils();
  monitor.startGame(argumentos.level);
  MMmode2 = 0;
  MMmode = 0;

  // Posicion inicial del agente
  monitor.inicializar(argumentos.fil_inicial, argumentos.col_inicial, argumentos.ori_inicial);

  monitor.get_entidad(0)->setOrientacion(static_cast<Orientacion>(argumentos.ori_inicial));
  // monitor.get_entidad(0)->setObjetivo(aux.first,aux.second);
  monitor.get_entidad(0)->setBateria(5000);
  monitor.get_entidad(0)->Cogio_Bikini(false);
  monitor.get_entidad(0)->Cogio_Zapatillas(false);
  monitor.setPasos(1);
  monitor.setRetardo(0);
  
  monitor.init_casillas_especiales(argumentos.fil_inicial, argumentos.col_inicial);

  glutInit(&argc, argv);
  // Mode Setting
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  // window size (+gap size)
  glutInitWindowSize(IU_ancho_ventana, IU_alto_ventana);
  float ratio = ((float)IU_ancho_ventana * 0.7) / (float)IU_alto_ventana;
  // Initial position
  glutInitWindowPosition(300, 0);

  // Main Window
  ventanaPrincipal = glutCreateWindow("Practica 1: Agentes Reactivos (21/22). Version BAJO PARAMETROS");
  // Main Window callback function
  glutReshapeFunc(reshape);
  glutDisplayFunc(display_ventPrincipal);

  // World Window and Display
  vistaPrincipal = glutCreateSubWindow(ventanaPrincipal, 0, 0, IU_ancho_ventana * 0.7, IU_alto_ventana);
  glutDisplayFunc(display_vistMiniMapa);
  glutMouseFunc(mouseClick);
  // glutKeyboardFunc(keyboard);

  // screen Window and Display
  vistaMiniMapa = glutCreateSubWindow(ventanaPrincipal, IU_ancho_ventana * 0.7, 0, (IU_ancho_ventana * 0.3) + 1, IU_alto_ventana * 0.3);
  glutDisplayFunc(display_vistPrincipal);

  vistaIU = glutCreateSubWindow(ventanaPrincipal, IU_ancho_ventana * 0.7, IU_alto_ventana * 0.3, (IU_ancho_ventana * 0.3) + 1, (IU_alto_ventana * 0.7) + 1);
  glutDisplayFunc(display_vistIU);

  glutInitWindowPosition(IU_ancho_ventana * 0.7, 50);
  glutInitWindowSize(50, 50);

  GLUI *panelIU = GLUI_Master.create_glui_subwindow(vistaIU, GLUI_SUBWINDOW_TOP);
  panelIU->set_main_gfx_window(vistaIU);

  botonElegirMapa = panelIU->add_button("Nuevo Juego", 0, botonElegirMapaCB);
  botonElegirMapa->set_alignment(GLUI_ALIGN_CENTER);

  GLUI_Panel *obj_panel2 = panelIU->add_panel("Visualizacion");

  drawMMVista = panelIU->add_checkbox_to_panel(obj_panel2, "Vista en 1ª Persona", &MMmode2);
  drawMMVista->set_alignment(GLUI_ALIGN_CENTER);
  drawMMVista->enable();
  panelIU->add_column_to_panel(obj_panel2, true);

  drawMM = panelIU->add_checkbox_to_panel(obj_panel2, "Mostrar mapa", &MMmode);
  drawMM->set_alignment(GLUI_ALIGN_CENTER);
  drawMM->enable();

  // lineaVacia = panelIU->add_statictext("");

  GLUI_Panel *run_panel = panelIU->add_panel("Control");

  editTextPasos = panelIU->add_edittext_to_panel(run_panel, "Pasos", GLUI_EDITTEXT_INT, &nPasos);
  editTextPasos->set_int_val(nPasos);
  editTextPasos->set_int_limits(1, 10000000, GLUI_LIMIT_CLAMP);
  editTextPasos->set_alignment(GLUI_ALIGN_CENTER);

  editTextRetardo = panelIU->add_edittext_to_panel(run_panel, "Retardo", GLUI_EDITTEXT_INT, &tRetardo, -1, setRetardo);
  editTextRetardo->set_int_val(tRetardo);
  editTextRetardo->set_int_limits(0, 10000000, GLUI_LIMIT_CLAMP);
  editTextRetardo->set_alignment(GLUI_ALIGN_CENTER);
  setRetardo(tRetardo);

  panelIU->add_column_to_panel(run_panel, true);

  botonPaso = panelIU->add_button_to_panel(run_panel, "Paso", 0, botonPasoCB);
  botonPaso->set_alignment(GLUI_ALIGN_CENTER);
  botonEjecutar = panelIU->add_button_to_panel(run_panel, "Ciclo", 0, botonEjecutarCB);
  botonEjecutar->set_alignment(GLUI_ALIGN_CENTER);
  botonEjecucion = panelIU->add_button_to_panel(run_panel, "Ejecucion", 0, botonEjecucionCB);

  lineaVacia = panelIU->add_statictext("");

  botonSalir = panelIU->add_button("Salir", 0, botonSalirCB);
  botonSalir->set_alignment(GLUI_ALIGN_CENTER);

  lineaVacia = panelIU->add_statictext("");

  GLUI_Panel *panelInfo = panelIU->add_panel("Informacion");
  panelInfo->set_alignment(GLUI_ALIGN_CENTER);

  info0 = panelIU->add_statictext_to_panel(panelInfo, "              No hay informacion disponible           ");
  info1 = panelIU->add_statictext_to_panel(panelInfo, "");
  info2 = panelIU->add_statictext_to_panel(panelInfo, "");
  info3 = panelIU->add_statictext_to_panel(panelInfo, "");
  info4 = panelIU->add_statictext_to_panel(panelInfo, "");
  info5 = panelIU->add_statictext_to_panel(panelInfo, "");
  info6 = panelIU->add_statictext_to_panel(panelInfo, "");
  info6->set_font(GLUT_BITMAP_8_BY_13);
  info7 = panelIU->add_statictext_to_panel(panelInfo, "");
  info7->set_font(GLUT_BITMAP_8_BY_13);
  info8 = panelIU->add_statictext_to_panel(panelInfo, "");
  info8->set_font(GLUT_BITMAP_8_BY_13);
  info9 = panelIU->add_statictext_to_panel(panelInfo, "");
  info9->set_font(GLUT_BITMAP_8_BY_13);

  // panelIU->add_separator_to_panel(panelInfo);

  lineaVacia = panelIU->add_statictext("");

  GLUI_Panel *panelResu = panelIU->add_panel("Resultado");
  evoResul = panelIU->add_checkbox_to_panel(panelResu, "Actualizar", &MMmode3);
  evoResul->set_alignment(GLUI_ALIGN_CENTER);
  evoResul->enable();
  panelIU->add_column_to_panel(panelResu, true);
  panelResu->set_alignment(GLUI_ALIGN_CENTER);
  resu0 = panelIU->add_statictext_to_panel(panelResu, "    No hay informacion disponible         ");
  lineaVacia = panelIU->add_statictext("");

  monitor.juegoInicializado();

  botonPaso->enable();
  botonEjecucion->enable();
  botonEjecutar->enable();
  // editPosColumna->disable();
  // editPosFila->disable();
  editTextPasos->enable();
  editTextRetardo->enable();

  // glutTimerFunc(100,update,0);
  glutTimerFunc(100, irAlJuego, 0);

  glutMainLoop();
}
