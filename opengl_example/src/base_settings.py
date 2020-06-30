from OpenGL.raw.GLU import gluPerspective, gluLookAt

from OpenGL.GLUT import *
from OpenGL.GL import *


class BaseSettings:
    def __init__(self):
        self.xrot = 0.0  # Величина вращения по оси x = 0
        self.yrot = 0.0  # Величина вращения по оси y = 0
        self.lightpos = [-20., 2., -2., 1.]
        self.light_color = [1.8, 1.0, 0.8, 1.0]
        self.perspective = (40., 1., 1., 40.)
        self.angle = 2

    def draw(self):
        raise NotImplemented

    def run(self):
        glutInit(sys.argv)
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH)
        glutInitWindowSize(666, 666)
        glutCreateWindow("OpenGL Python")

        glutDisplayFunc(self.draw)
        glutSpecialFunc(self.specialkeys)
        self.base_settings()
        glutMainLoop()

    def base_settings(self):
        glClearColor(1., 1., 1., 1.) # цвет фона
        glShadeModel(GL_SMOOTH)
        glEnable(GL_CULL_FACE)
        glEnable(GL_DEPTH_TEST)
        glEnable(GL_LIGHTING)
        glLightfv(GL_LIGHT0, GL_DIFFUSE, self.light_color)
        glLightfv(GL_LIGHT0, GL_POSITION, self.lightpos)  # Источник света

        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1)
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05)
        glEnable(GL_LIGHT0)

        glMatrixMode(GL_PROJECTION)
        gluPerspective(*self.perspective)

        glMatrixMode(GL_MODELVIEW)
        gluLookAt(0, 0, 10,
                  0, 0, 0,
                  0, 1, 0)

    def specialkeys(self, key, *args):
        # Обработчики для клавиш со стрелками
        if key == GLUT_KEY_UP:  # Клавиша вверх
            self.xrot -= self.angle  # Уменьшаем угол вращения по оси Х
        if key == GLUT_KEY_DOWN:  # Клавиша вниз
            self.xrot += self.angle  # Увеличиваем угол вращения по оси Х
        if key == GLUT_KEY_LEFT:  # Клавиша влево
            self.yrot -= self.angle  # Уменьшаем угол вращения по оси Y
        if key == GLUT_KEY_RIGHT:  # Клавиша вправо
            self.yrot += self.angle  # Увеличиваем угол вращения по оси Y

        glutPostRedisplay()  # Вызываем процедуру перерисовки
