
#define GL_SILENCE_DEPRECATION // Silenciar advertencias en macOS
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLuint bgTextureID;
// Posición inicial de la cámara
float camX = 0.0f, camY = 0.0f, camZ = 5.0f;
// Ángulo de rotación de la cámara (Yaw)
float angle = 0.0f;
// Vector de dirección de hacia dónde mira la cámara
float lx = 0.0f, lz = -1.0f;

void
loadBackgroundTexture ()
{
  // Example: Allocate and load your pixel array (width x height x 3 for RGB)
  int width = 512;
  int height = 512;
  int channels;
  unsigned char *imageData
      = stbi_load ("./test.jpg", &width, &height, &channels, 3);

  glGenTextures (1, &bgTextureID);
  glBindTexture (GL_TEXTURE_2D, bgTextureID);

  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                GL_UNSIGNED_BYTE, imageData);
}

void
drawBackground ()
{
  glDisable (GL_DEPTH_TEST); // Disable depth so background stays behind
  glMatrixMode (GL_PROJECTION);
  glPushMatrix ();
  glLoadIdentity ();
  gluOrtho2D (-1.0, 1.0, -1.0, 1.0); // Simple normalized 2D coordinates

  glMatrixMode (GL_MODELVIEW);
  glPushMatrix ();
  glLoadIdentity ();

  glEnable (GL_TEXTURE_2D);
  glBindTexture (GL_TEXTURE_2D, bgTextureID);

  glBegin (GL_QUADS);
  glTexCoord2f (0.0f, 0.0f);
  glVertex2f (-1.0f, -1.0f);
  glTexCoord2f (1.0f, 0.0f);
  glVertex2f (1.0f, -1.0f);
  glTexCoord2f (1.0f, 1.0f);
  glVertex2f (1.0f, 1.0f);
  glTexCoord2f (0.0f, 1.0f);
  glVertex2f (-1.0f, 1.0f);
  glEnd ();

  glDisable (GL_TEXTURE_2D);

  // Restore matrices
  glPopMatrix ();
  glMatrixMode (GL_PROJECTION);
  glPopMatrix ();
  glMatrixMode (GL_MODELVIEW);
  glEnable (GL_DEPTH_TEST);
}

void
init ()
{
  glEnable (GL_DEPTH_TEST); // Activar el búfer de profundidad
  glClearColor (0.1f, 0.1f, 0.1f, 1.0f);
  loadBackgroundTexture ();
}

void
display ()
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity ();

  drawBackground (); // Draw background first

  // Configuración de la cámara: posición (cam), punto objetivo (cam + l), y
  // vector arriba (0,1,0)
  gluLookAt (camX, camY, camZ, camX + lx, camY, camZ + lz, 0.0f, 1.0f, 0.0f);

  // Dibujar un cubo de referencia en el centro (0,0,0)
  //  glColor3f(0.0f, 0.7f, 0.9f);
  glutWireCube (1.5f);

  glutSwapBuffers ();
}

void
reshape (int w, int h)
{
  if (h == 0)
    h = 1;
  float ratio = w * 1.0 / h;
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  glViewport (0, 0, w, h);
  gluPerspective (45.0f, ratio, 0.1f, 100.0f);
  glMatrixMode (GL_MODELVIEW);
}

// Callback para detectar las teclas especiales (Flechas de dirección)
void
specialKeys (int key, int x, int y)
{
  float fraction = 0.2f; // Velocidad de movimiento

  switch (key)
    {
    case GLUT_KEY_LEFT: // Rotar a la izquierda
      angle -= 0.05f;
      lx = sin (angle);
      lz = -cos (angle);
      break;
    case GLUT_KEY_RIGHT: // Rotar a la derecha
      angle += 0.05f;
      lx = sin (angle);
      lz = -cos (angle);
      break;
    case GLUT_KEY_UP: // Avanzar
      camX += lx * fraction;
      camZ += lz * fraction;
      break;
    case GLUT_KEY_DOWN: // Retroceder
      camX -= lx * fraction;
      camZ -= lz * fraction;
      break;
    }
  glutPostRedisplay (); // Forzar el redibujado de la escena
}

void
gpu_main ()
{
  // glutInit (&argc, argv);
  // si hizo en el main
  glutInitDisplayMode (GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize (800, 600);
  glutCreateWindow ("GCC GLUT Camera Example");

  init ();

  glutDisplayFunc (display);
  glutReshapeFunc (reshape);
  glutSpecialFunc (specialKeys); // Registrar callback del teclado

  //  glutMainLoop ();
}
