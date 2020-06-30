from OpenGL.GLUT import *
from OpenGL.GL import *

from src.base_settings import BaseSettings


# Изобразить каркасный тетраэдр и каркасную сферу. Размеры примитивов задать самостоятельно.
# Выполнить поворот тетраэдра на α=-180° вокруг оси Х, сферы - на α=-90° вокруг оси Z относительно начала координат.

class TetrahedronAndSphere(BaseSettings):
    def __init__(self):
        super().__init__()

    def draw(self):
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

        # Рисуем и вращаем сферу
        glPushMatrix()
        glRotatef(self.xrot, 0.0, 1.0, 1.0)  # glRotatef(Angle,Xtrue,Ytrue,Ztrue)
        glutWireSphere(1, 16, 16)
        glPopMatrix()

        # Рисуем и вращаем тетраэдр
        glPushMatrix()
        glRotatef(self.xrot * 2, 1.0, 1.0, 0.0)
        glutWireTetrahedron()
        glPopMatrix()

        glutSwapBuffers()


ts = TetrahedronAndSphere()
ts.run()
