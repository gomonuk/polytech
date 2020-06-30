from OpenGL.GLUT import *
from OpenGL.GL import *

from src.base_settings import BaseSettings


# Изобразить тор и куб. Одна вершина куба совпадает с центром тора.
# Промасштабировать тор с коэффициентом 0.3.

# glPushMatrix сдвигает текущий стек матрицы на единицу, дублируя текущую матрицу.
# То есть после вызова glPushMatrix матрица на вершине стека идентична матрице под ней

# glPopMatrix выталкивает текущий стек матрицы, заменяя текущую матрицу на ту,
# которая находится под ней в стеке.


class TorusAndCube(BaseSettings):
    def __init__(self):
        super().__init__()
        self.angle = 2

    def draw(self):
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

        glPushMatrix()
        glRotatef(45, 0.0, 1.0, 0.0)
        glRotatef(45, 0.0, 0.0, 1.0)
        glRotatef(45, 1.0, 0.0, 0.0)
        glutWireCube(1)  # glutWireCube(GLdouble width);
        glPopMatrix()

        glPushMatrix()
        glRotatef(90, 1.0, 0.0, 0.0)
        glTranslatef(-0.2, .0, -1)
        glutWireTorus(0.5 * self.xrot * 0.1,
                      2.0 * self.xrot * 0.1,
                      40,
                      60)  # glutWireTorus(dInnerRadius, dOuterRadius, nSides, nRings);
        glPopMatrix()

        glutSwapBuffers()


tc = TorusAndCube()
tc.run()
