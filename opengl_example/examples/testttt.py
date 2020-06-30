from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.GL import *
import sys

global xrot  # Величина вращения по оси x
global yrot  # Величина вращения по оси y
global lightpos  # Положение источника освещения


def init():
    global xrot  # Величина вращения по оси x
    global yrot  # Величина вращения по оси y
    global lightpos  # Положение источника освещения

    xrot = 0.0  # Величина вращения по оси x = 0
    yrot = 0.0  # Величина вращения по оси y = 0

    # где то здесь выставляется цвет  фона и линий
    glClearColor(0., 0., 1., 1.)
    glShadeModel(GL_SMOOTH)
    glEnable(GL_CULL_FACE)
    glEnable(GL_DEPTH_TEST)
    glEnable(GL_LIGHTING)
    lightpos = [-20., 2., -2., 1.]
    lightZeroColor = [1.8, 1.0, 0.8, 1.0]  # green tinged
    # glLightfv(GL_LIGHT0, GL_POSITION, lightpos)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightZeroColor)
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1)
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05)
    glEnable(GL_LIGHT0)

    glMatrixMode(GL_PROJECTION)
    gluPerspective(40., 1., 1., 40.)
    # glMaterialfv(GL_FRONT, GL_DIFFUSE, (0.2, 0.8, 0.0, 0.8))
    # glLightfv(GL_LIGHT0, GL_POSITION, lightpos)
    glMatrixMode(GL_MODELVIEW)
    gluLookAt(0, 0, 10,
              0, 0, 0,
              0, 1, 0)
    glPushMatrix()
    glutMainLoop()
    return


def draw():
    global xrot
    global yrot

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    # color = [1.0, 0., 0., 1.]
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos)  # Источник света вращаем вместе с елкой

    # Рисуем и вращаем сферу
    glPushMatrix()
    glRotatef(xrot, 0.0, 1.0, 1.0)  # glRotatef(Angle,Xtrue,Ytrue,Ztrue)
    glutWireSphere(1, 16, 16)
    glPopMatrix()

    glPushMatrix()
    glRotatef(xrot * 2, 1.0, 1.0, 0.0)  # Вращаем по оси X на величину xrot11
    glutWireTetrahedron()
    glPopMatrix()

    glutSwapBuffers()

    return


def specialkeys(key, x,y):
    global xrot
    global yrot

    angle = 2

    # Обработчики для клавиш со стрелками
    if key == GLUT_KEY_UP:  # Клавиша вверх
        xrot -= angle  # Уменьшаем угол вращения по оси Х
    if key == GLUT_KEY_DOWN:  # Клавиша вниз
        xrot += angle  # Увеличиваем угол вращения по оси Х
    if key == GLUT_KEY_LEFT:  # Клавиша влево
        yrot -= angle  # Уменьшаем угол вращения по оси Y
    if key == GLUT_KEY_RIGHT:  # Клавиша вправо
        yrot += angle  # Увеличиваем угол вращения по оси Y

    glutPostRedisplay()  # Вызываем процедуру перерисовки


glutInit(sys.argv)
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH)
glutInitWindowSize(666, 666)
glutCreateWindow('OpenGL Python')
glutDisplayFunc(draw)
glutSpecialFunc(specialkeys)
init()
glutMainLoop()
